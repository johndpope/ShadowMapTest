//-----------------------------------------------------------------------------------------
// File : ForwardPS.hlsl
// Desc : Forward Shading.
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------------------


// �~�����ł�.
#define PI          3.1415926535f

///////////////////////////////////////////////////////////////////////////////////////////
// VSOutput structure
///////////////////////////////////////////////////////////////////////////////////////////
struct VSOutput
{
    float4  Position : SV_POSITION;
    float4  WorldPos : WORLD_POSITION;
    float3  Normal   : NORMAL;
    float2  TexCoord : TEXCOORD0;
    float3  LightDir : LIGHT_DIRECTION;
    float3  ViewDir  : VIEW_DIRECTION;
    float4  SdwCoord : SHADOW_COORD;
};


///////////////////////////////////////////////////////////////////////////////////////////
// PSOutput structure
///////////////////////////////////////////////////////////////////////////////////////////
struct PSOutput
{
    float4 Color : SV_TARGET0;
};


/////////////////////////////////////////////////////////////////////////////////////////
// Material Buffer
/////////////////////////////////////////////////////////////////////////////////////////
cbuffer Material : register( b0 )
{
    float3 Diffuse  : packoffset( c0 );     //!< �g�U���ːF�ł�.
    float  Alpha    : packoffset( c0.w );   //!< ���ߓx�ł�.
    float3 Specular : packoffset( c1 );     //!< ���ʔ��ːF�ł�.
    float  Power    : packoffset( c1.w );   //!< ���ʔ��ˋ��x�ł�.
    float3 Emissive : packoffset( c2 );     //!< ���ȏƖ��F�ł�.
    float  Bump     : packoffset( c2.w );   //!< �o���v�}�b�s���O�t���O.
};


//---------------------------------------------------------------------------------------
// Textures
//---------------------------------------------------------------------------------------
Texture2D       DiffuseMap    : register( t0 );     //!< �f�B�t���[�Y�}�b�v�ł�.
Texture2D       SpecularMap   : register( t1 );     //!< �X�y�L�����[�}�b�v�ł�.
Texture2D       BumpMap       : register( t2 );     //!< �o���v�}�b�v�ł�.
Texture2D       ShadowMap     : register( t3 );     //!< �V���h�E�}�b�v�ł�.


//---------------------------------------------------------------------------------------
// Samplers
//---------------------------------------------------------------------------------------
SamplerState            DiffuseSmp    : register( s0 );     //!< �f�B�t���[�Y�}�b�v�p�T���v���[�X�e�[�g�ł�.
SamplerState            SpecularSmp   : register( s1 );     //!< �X�y�L�����[�}�b�v�p�T���v���[�X�e�[�g�ł�.
SamplerState            BumpSmp       : register( s2 );     //!< �o���v�}�b�v�p�T���v���[�X�e�[�g�ł�.
SamplerComparisonState  ShadowSmp     : register( s3 );     //!< �V���h�E�}�b�v�p�T���v���[��r�X�e�[�g�ł�.


//-----------------------------------------------------------------------------------------------
//! @biref      ���K�������o�[�g���C�e�B���O���v�Z���܂�.
//!
//! @param [in]     diffuse     �g�U���ːF.
//! @param [in]     lightDir    ���C�g�x�N�g��.
//! @param [in]     normal      �@���x�N�g��.
//! @return     �����o�[�g���C�e�B���O�������ʂ�ԋp���܂�.
//-----------------------------------------------------------------------------------------------
float3 NormalizedLambert( float3 diffuse, float3 lightDir, float3 normal )
{
   return diffuse * max( dot( normal, lightDir ), 0.0f ) * ( 1.0f / PI );
}

//------------------------------------------------------------------------------------------------
//! @brief      ���K���t�H�����C�e�B���O���s���܂�.
//!
//! @param [in]     specular    ���ʔ��ːF.
//! @param [in]     power       ���ʔ��ˋ��x.
//! @param [in]     viewDir     �����x�N�g��.
//! @param [in]     normal      �@���x�N�g��.
//! @parma [in]     lightDir    ���C�g�x�N�g��.
//! @return     �t�H�����C�e�B���O�̌��ʂ�ԋp���܂�.
//------------------------------------------------------------------------------------------------
float3 NormalizedPhong( float3 specular, float power, float3 viewDir, float3 normal, float3 lightDir )
{
    float3 R = -viewDir + ( 2.0f * dot( normal, viewDir ) * normal );

    return specular * pow( max ( dot( lightDir, R ), 0.0f ), power ) * ( ( power + 1.0f )/ ( 2.0 * PI ) );
}


//------------------------------------------------------------------------------------------------
//! @brief      �s�N�Z���V�F�[�_�̃G���g���[�|�C���g�ł�.
//------------------------------------------------------------------------------------------------
PSOutput PSFunc( VSOutput input )
{
    PSOutput output = (PSOutput)0;

    // �f�B�t���[�Y�}�b�v���t�F�b�`.
    float4 mapKd = DiffuseMap.Sample( DiffuseSmp, input.TexCoord );

    // �A���t�@�e�X�g.
    clip( ( mapKd.a < 0.125f ) ? -1.0f : 1.0f );

    // �X�y�L�����[�}�b�v���t�F�b�`.
    float4 mapKs = SpecularMap.Sample( SpecularSmp, input.TexCoord );

    // �V���h�E�}�b�v�̐[�x�l�Ɣ�r����.
    float3 shadowCoord = input.SdwCoord.xyz / input.SdwCoord.w;

    // �ő�[�x�X�΂����߂�.
    float  maxDepthSlope = max( abs( ddx( shadowCoord.z ) ), abs( ddy( shadowCoord.z ) ) );

    float  shadowThreshold = 1.0f;      // �V���h�E�ɂ��邩�ǂ�����臒l�ł�.
    float  bias            = 0.01f;     // �Œ�o�C�A�X�ł�.
    float  slopeScaledBias = 0.01f;     // �[�x�X��.
    float  depthBiasClamp  = 0.1f;      // �o�C�A�X�N�����v�l.

    float  shadowBias = bias + slopeScaledBias * maxDepthSlope;
    shadowBias = min( shadowBias, depthBiasClamp );

    float3 shadowColor     = float3( 0.25f, 0.25f, 0.25f );
    shadowThreshold = ShadowMap.SampleCmpLevelZero( ShadowSmp, shadowCoord.xy, shadowCoord.z - shadowBias );
    shadowColor     = lerp( shadowColor, float3( 1.0f, 1.0f, 1.0f ), shadowThreshold );

    // �X�y�L�����[�}�b�v���t�F�b�`.
    float4 spe = SpecularMap.Sample( SpecularSmp, input.TexCoord );
    {
        float3 N = normalize( input.Normal );
        float3 V = normalize( input.ViewDir );
        float3 L = normalize( input.LightDir );

        float3 diffuse   = NormalizedLambert( Diffuse * mapKd.rgb, L, N );
        float3 specular  = NormalizedPhong( Specular * mapKs.rgb, Power, V, N, L );
        output.Color.rgb = ( diffuse + specular ) * shadowColor;
        output.Color.a   = Alpha;
    }

    return output;
}