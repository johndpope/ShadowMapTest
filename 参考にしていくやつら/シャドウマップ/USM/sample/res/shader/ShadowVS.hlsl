//-----------------------------------------------------------------------------------------
// File : ShadowVS.hlsl
// Desc : Generate Shadow Map
// Copyright(c) Project Asura. All right reserved.
//-----------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////
// VSInput structure
///////////////////////////////////////////////////////////////////////////////////////////
struct VSInput
{
    float3  Position    : POSITION;         //!< �ʒu���W�ł�(���[�J�����W�n).
    float3  Normal      : NORMAL;           //!< �@���x�N�g���ł�(���[�J�����W�n).
    float3  Tangent     : TANGENT;          //!< �ڃx�N�g���ł�(���[�J�����W�n).
    float2  TexCoord    : TEXCOORD;         //!< �e�N�X�`�����W�ł�.
};


///////////////////////////////////////////////////////////////////////////////////////////
// VSOutput structure
///////////////////////////////////////////////////////////////////////////////////////////
struct VSOutput
{
    float4  Position : SV_POSITION;
};


///////////////////////////////////////////////////////////////////////////////////////////
// CBMatrix buffer
///////////////////////////////////////////////////////////////////////////////////////////
cbuffer CBMatrix : register( b0 )
{
    float4x4    World : packoffset( c0 );
    float4x4    View  : packoffset( c4 );
    float4x4    Proj  : packoffset( c8 );
};


//-----------------------------------------------------------------------------------------
//! @brief      ���_�V�F�[�_�̃��C���G���g���[�|�C���g�ł�.
//-----------------------------------------------------------------------------------------
VSOutput VSFunc( VSInput input )
{
    VSOutput output = (VSOutput)0;

    float4 localPos = float4( input.Position, 1.0f );
    float4 worldPos = mul( World, localPos );
    float4 viewPos  = mul( View, worldPos );
    float4 projPos  = mul( Proj, viewPos );

    output.Position = projPos;

    return output;
}