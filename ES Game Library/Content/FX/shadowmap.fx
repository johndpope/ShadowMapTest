// -------------------------------------------------------------
// シャドウマップの作成
// 
// Copyright (c) 2002 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// グローバル変数
// -------------------------------------------------------------
float4x4 mWVP;		// ローカルから射影空間への座標変換
float4x4 mWLP;		// ローカルから射影空間への座標変換
float4x4 mWLPB;		// テクスチャ座標系への射影
float4   vCol;		// メッシュの色
float4	 vLightDir;	// ライトの方向

// -------------------------------------------------------------
// テクスチャ
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
// 頂点シェーダからピクセルシェーダに渡すデータ
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
// 1パス目：頂点シェーダプログラム
// -------------------------------------------------------------
VS_OUTPUT VS_pass0(
      float4 Pos    : POSITION,          // モデルの頂点
      float3 Normal : NORMAL	         // モデルの法線
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ
    
    // 座標変換
	float4 pos = mul( Pos, mWLP );
	
    // 位置座標
    Out.Pos = pos;
    
    // カメラ座標系での深度をテクスチャに入れる
    Out.ShadowMapUV = pos.z / pos.w;

    return Out;
}
// -------------------------------------------------------------
// 1パス目：ピクセルシェーダプログラム
// -------------------------------------------------------------
PIXELSHADER PS = 
asm
{
    ps.1.1
    
    texcoord t0
    
    mov r0, t0	// テクスチャ座標を色として出力する
};
// -------------------------------------------------------------
// 頂点シェーダプログラム
// -------------------------------------------------------------
VS_OUTPUT VS_pass1(
      float4 Pos    : POSITION,          // モデルの頂点
      float3 Normal : NORMAL	         // モデルの法線
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ
	float4	uv;
	
	// 座標変換
    Out.Pos = mul(Pos, mWVP);
	// 色
	Out.Diffuse = vCol * max( dot(vLightDir, Normal), 0);// 拡散色
	Out.Ambient = vCol * 0.3f;                     // 環境色
	
	// テクスチャ座標
	uv = mul(Pos, mWLPB);
	Out.ShadowMapUV = uv;
	uv = mul(Pos, mWLP);
	Out.Depth       = uv.z / uv.w-0.003;
		
    return Out;
}
// -------------------------------------------------------------
// 2パス目：ピクセルシェーダプログラム
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
// テクニック
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // シェーダ
        VertexShader = compile vs_1_1 VS_pass0();
        PixelShader  = <PS>;
    }
    pass P1
    {
        // シェーダ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_2_0 PS20();
        
		Sampler[0] = (ShadowMapSamp);
    }
}
