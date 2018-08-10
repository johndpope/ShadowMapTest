// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));

	this->shadowMapEffect_ = GraphicsDevice.CreateEffectFromFile(_T("FX/shadowmap.fx"));

	Viewport view = GraphicsDevice.GetViewport();
	this->camera_->SetLookAt(Vector3_Zero - (Vector3_Left + Vector3_Up) * 50.0f,Vector3_Zero,Vector3_Up);
	this->camera_->SetPerspectiveFieldOfView(50.0f,view.Width,view.Height,1.0f,1000.0f);

	this->shadowRenderTarget_ = GraphicsDevice.CreateRenderTarget(view.Width,view.Height,PixelFormat_Single,DepthFormat_Unknown);

	SimpleShape shape;
	shape.Type = Shape_Teapot;
	this->teaPot_ = GraphicsDevice.CreateModelFromSimpleShape(shape);
	this->teaPot_->SetPosition(Vector3_Zero);

	Light light;
	light.Type = Light_Directional;
	light.Ambient = Color(1.0f,1.0f,1.0f);
	light.Diffuse = Color(1.0f,1.0f,1.0f);
	light.Position = (Vector3_Up + Vector3_Backward ) * 50.0f;
	light.Direction = Vector3_Down + Vector3_Forward;

	CAMERA lightCamera;
	lightCamera->SetLookAt(light.Position,light.Direction,Vector3_Up);
	lightCamera->SetPerspectiveFieldOfView(50.0f,view.Width,view.Height,1.0f,1000.0f);



	Vector4 direction = Vector4_Zero;
	direction.x = light.Direction.x;
	direction.y = light.Direction.y;
	direction.z = light.Direction.z;

	Matrix wMatrix;
	wMatrix = this->teaPot_->GetWorldMatrix();
	Matrix vpMatrix;
	vpMatrix = this->camera_->GetViewProjectionMatrix();
	Matrix vpLightMatrix;
	vpLightMatrix = lightCamera->GetViewProjectionMatrix();

	float fOffsetX = 0.5f + (0.5f / (float)view.Width);
	float fOffsetY = 0.5f + (0.5f / (float)view.Height);
	Matrix scaleBiasMatrix(	0.5f,     0.0f,     0.0f,   0.0f,
							0.0f,    -0.5f,     0.0f,   0.0f,
							0.0f,     0.0f,     0.0f,	0.0f,
							fOffsetX, fOffsetY, 0.0f,   1.0f );


	//Light‚©‚çŒ©‚½ŽË‰es—ñ‚¾‚©‚çLight‚àViewProjection‚Å‚¦‚¦‚ñ‚â‚Å
	this->shadowMapEffect_->SetParameter("mWVP",wMatrix * vpMatrix);
	this->shadowMapEffect_->SetParameter("mWLP",wMatrix * vpLightMatrix);
	this->shadowMapEffect_->SetParameter("mWLPB",wMatrix * vpLightMatrix * scaleBiasMatrix);
	this->shadowMapEffect_->SetParameter("vLightDir",direction);
	this->shadowMapEffect_->SetParameter("ShadowMap",this->shadowRenderTarget_->GetTexture());

	this->shadowMapEffect_->RetisterMaterialByName("vCol",NULL,NULL,NULL,NULL,NULL);

	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here

}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here


	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();


	SpriteBatch.Begin();


	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
