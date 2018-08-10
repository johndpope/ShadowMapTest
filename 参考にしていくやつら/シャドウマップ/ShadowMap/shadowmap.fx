// -------------------------------------------------------------
// �V���h�E�}�b�v�̍쐬
// 
// Copyright (c) 2002 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float4x4 mWVP;		// ���[�J������ˉe��Ԃւ̍��W�ϊ�
float4x4 mWLP;		// ���[�J������ˉe��Ԃւ̍��W�ϊ�
float4x4 mWLPB;		// �e�N�X�`�����W�n�ւ̎ˉe
float4   vCol;		// ���b�V���̐F
float4	 vLightDir;	// ���C�g�̕���

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture ShadowMap;
sampler ShadowMapSamp = sampler_state
{
    Texture = <ShadowMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diffuse		: COLOR0;
	float4 Ambient		: COLOR1;
	float4 ShadowMapUV	: TEXCOORD0;
	float4 Depth		: TEXCOORD1;
};

// -------------------------------------------------------------
// 1�p�X�ځF���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass0(
      float4 Pos    : POSITION,          // ���f���̒��_
      float3 Normal : NORMAL	         // ���f���̖@��
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
    
    // ���W�ϊ�
	float4 pos = mul( Pos, mWLP );
	
    // �ʒu���W
    Out.Pos = pos;
    
    // �J�������W�n�ł̐[�x���e�N�X�`���ɓ����
    Out.ShadowMapUV = pos.z / pos.w;

    return Out;
}
// -------------------------------------------------------------
// 1�p�X�ځF�s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
PIXELSHADER PS = 
asm
{
    ps.1.1
    
    texcoord t0
    
    mov r0, t0	// �e�N�X�`�����W��F�Ƃ��ďo�͂���
};
// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass1(
      float4 Pos    : POSITION,          // ���f���̒��_
      float3 Normal : NORMAL	         // ���f���̖@��
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
	float4	uv;
	
	// ���W�ϊ�
    Out.Pos = mul(Pos, mWVP);
	// �F
	Out.Diffuse = vCol * max( dot(vLightDir, Normal), 0);// �g�U�F
	Out.Ambient = vCol * 0.3f;                     // ���F
	
	// �e�N�X�`�����W
	uv = mul(Pos, mWLPB);
	Out.ShadowMapUV = uv;
	uv = mul(Pos, mWLP);
	Out.Depth       = uv.z / uv.w-0.003;
		
    return Out;
}
// -------------------------------------------------------------
// 2�p�X�ځF�s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS20(VS_OUTPUT In) : COLOR
{   
    float4 Color = In.Ambient;
    float4 zero = {0,0,0,0};
    
	float  shadow_map = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
    
    Color += (shadow_map < In.Depth.z) ? zero : In.Diffuse;

    return Color;
}  
// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass0();
        PixelShader  = <PS>;
    }
    pass P1
    {
        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS20();
        
		Sampler[0] = (ShadowMapSamp);
    }
}
