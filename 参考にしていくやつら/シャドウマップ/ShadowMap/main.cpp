//-----------------------------------------------------------------------------
// File: main.cpp
//
// Desc: DirectX window application created by the DirectX AppWizard
//-----------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <basetsd.h>
#include <math.h>
#include <stdio.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <tchar.h>
#include "framework/DXUtil.h"
#include "framework/D3DEnumeration.h"
#include "framework/D3DSettings.h"
#include "framework/D3DApp.h"
#include "framework/D3DFont.h"
#include "framework/D3DFile.h"
#include "framework/D3DUtil.h"
#include "resource.h"
#include "main.h"

#define SHADOW_MAP_FORMAT D3DFMT_R32F
//#define SHADOW_MAP_FORMAT D3DFMT_A8R8G8B8
#define SHADOW_MAP_SIZE   2048

//-----------------------------------------------------------------------------
// デバッグ用に表示するテクスチャ用の構造体
//-----------------------------------------------------------------------------
typedef struct {
    FLOAT       p[4];
    FLOAT       tu, tv;
} TVERTEX;

//-----------------------------------------------------------------------------
// Global access to the app (needed for the global WndProc())
//-----------------------------------------------------------------------------
CMyD3DApplication* g_pApp  = NULL;
HINSTANCE          g_hInst = NULL;




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop. Idle time is used to render the scene.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    CMyD3DApplication d3dApp;

    g_pApp  = &d3dApp;
    g_hInst = hInst;

    InitCommonControls();
    if( FAILED( d3dApp.Create( hInst ) ) )
        return 0;

    return d3dApp.Run();
}




//-----------------------------------------------------------------------------
// Name: CMyD3DApplication()
// Desc: Application constructor.   Paired with ~CMyD3DApplication()
//       Member variables should be initialized to a known state here.  
//       The application window has not yet been created and no Direct3D device 
//       has been created, so any initialization that depends on a window or 
//       Direct3D should be deferred to a later stage. 
//-----------------------------------------------------------------------------
CMyD3DApplication::CMyD3DApplication()
{
	m_pMeshCar	 = new CD3DMesh();
	m_pMeshChess = new CD3DMesh();

	m_pShadowMap	 = NULL;
	m_pShadowMapSurf = NULL;
	m_pShadowMapZ	 = NULL;

	m_pFx = NULL;
	m_hmWVP						= NULL;
	m_hmWLP						= NULL;
	m_hmWLPB					= NULL;
	m_hvCol						= NULL;
	m_hvDir						= NULL;

	m_fWorldRotX                = -0.41271535f;
    m_fWorldRotY                = 0.0f;
	m_fViewZoom				    = 5.0f;
	m_LighPos					= D3DXVECTOR3( -5.0f, 5.0f,-2.0f );

	m_dwCreationWidth           = 500;
    m_dwCreationHeight          = 375;
    m_strWindowTitle            = TEXT( "main" );
    m_d3dEnumeration.AppUsesDepthBuffer   = TRUE;
	m_bStartFullscreen			= false;
	m_bShowCursorWhenFullscreen	= false;

	// Create a D3D font using d3dfont.cpp
    m_pFont                     = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_bLoadingApp               = TRUE;

    ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
}




//-----------------------------------------------------------------------------
// Name: ~CMyD3DApplication()
// Desc: Application destructor.  Paired with CMyD3DApplication()
//-----------------------------------------------------------------------------
CMyD3DApplication::~CMyD3DApplication()
{
}




//-----------------------------------------------------------------------------
// Name: OneTimeSceneInit()
// Desc: Paired with FinalCleanup().
//       The window has been created and the IDirect3D9 interface has been
//       created, but the device has not been created yet.  Here you can
//       perform application-related initialization and cleanup that does
//       not depend on a device.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::OneTimeSceneInit()
{
    // TODO: perform one time initialization

    // Drawing loading status message until app finishes loading
    SendMessage( m_hWnd, WM_PAINT, 0, 0 );

    m_bLoadingApp = FALSE;

    return S_OK;
}









//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the display device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
                                          D3DFORMAT Format )
{
    UNREFERENCED_PARAMETER( Format );
    UNREFERENCED_PARAMETER( dwBehavior );
    UNREFERENCED_PARAMETER( pCaps );
    
    BOOL bCapsAcceptable;

    // TODO: Perform checks to see if these display caps are acceptable.
    bCapsAcceptable = TRUE;

	// ピクセルシェーダバージョンチェック
    if( pCaps->PixelShaderVersion < D3DPS_VERSION(2,0) )
		bCapsAcceptable = FALSE;

    // 頂点シェーダバージョンが上位かソフトウェア頂点処理
    if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
        if( (dwBehavior & D3DCREATE_SOFTWARE_VERTEXPROCESSING ) == 0 )
			bCapsAcceptable = FALSE;

	if( bCapsAcceptable )         
        return S_OK;
    else
        return E_FAIL;
}


//-----------------------------------------------------------------------------
// Name: LoadPixelShader()
// Desc: Creates and loads pixel shader from file
//-----------------------------------------------------------------------------
HRESULT LoadPixelShader(LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* fileName, LPDIRECT3DPIXELSHADER9* pShader)
{
	LPD3DXBUFFER pShaderBuf = NULL;
    LPD3DXBUFFER pErrorBuf = NULL;
	HRESULT hr;

    hr = D3DXAssembleShaderFromFile(fileName, NULL, NULL, 0, &pShaderBuf, &pErrorBuf);
	if (SUCCEEDED(hr))
	{
	   if (pShaderBuf) 
		   hr = pd3dDevice->CreatePixelShader((DWORD*)pShaderBuf->GetBufferPointer(), pShader);
	   else
		   hr = E_FAIL;
	}
	SAFE_RELEASE(pShaderBuf);
	SAFE_RELEASE(pErrorBuf);

	return hr;
}

//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Paired with DeleteDeviceObjects()
//       The device has been created.  Resources that are not lost on
//       Reset() can be created here -- resources in D3DPOOL_MANAGED,
//       D3DPOOL_SCRATCH, or D3DPOOL_SYSTEMMEM.  Image surfaces created via
//       CreateImageSurface are never lost and can be created here.  Vertex
//       shaders and pixel shaders can also be created here as they are not
//       lost on Reset().
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InitDeviceObjects()
{
    HRESULT hr;

	// 車の読み込み
	if( FAILED( hr = m_pMeshCar->Create( m_pd3dDevice, _T("car.x") )))
        return DXTRACE_ERR( "LoadCar", hr );
	m_pMeshCar->UseMeshMaterials(FALSE);// レンダリング時にテクスチャの設定をしない
	// 地面の読み込み
	if( FAILED( hr = m_pMeshChess->Create( m_pd3dDevice, _T("chess.x") )))
        return DXTRACE_ERR( "LoadChess", hr );
	m_pMeshChess->UseMeshMaterials(FALSE);// レンダリング時にテクスチャの設定をしない

	// Init the font
    m_pFont->InitDeviceObjects( m_pd3dDevice );

	// シェーダの読み込み
    if( FAILED( D3DXCreateEffectFromFile( m_pd3dDevice, "shadowmap.fx", NULL, NULL, 
                                        0, NULL, &m_pFx, NULL ) ) ) return E_FAIL;
	m_hmWVP = m_pFx->GetParameterByName( NULL, "mWVP" );
	m_hmWLP = m_pFx->GetParameterByName( NULL, "mWLP" );
	m_hmWLPB= m_pFx->GetParameterByName( NULL, "mWLPB" );
	m_hvCol = m_pFx->GetParameterByName( NULL, "vCol" );
	m_hvDir = m_pFx->GetParameterByName( NULL, "vLightDir" );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Paired with InvalidateDeviceObjects()
//       The device exists, but may have just been Reset().  Resources in
//       D3DPOOL_DEFAULT and any other device state that persists during
//       rendering should be set here.  Render states, matrices, textures,
//       etc., that don't change during rendering can be set once here to
//       avoid redundant state setting during Render() or FrameMove().
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RestoreDeviceObjects()
{
    // TODO: setup render states

    // Setup a material
    D3DMATERIAL9 mtrl;
    D3DUtil_InitMaterial( mtrl, 1.0f, 0.0f, 0.0f );
    m_pd3dDevice->SetMaterial( &mtrl );

    // Set up the textures
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

    // Set miscellaneous render states
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE,   FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_SPECULARENABLE, FALSE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,        TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT,        0x000F0F0F );

    // Set the world matrix
    D3DXMATRIX matIdentity;
    D3DXMatrixIdentity( &m_mWorld );

	// Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXMATRIX matView;
    D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_mView, &vFromPt, &vLookatPt, &vUpVec );

    // Set the projection matrix
    D3DXMATRIX matProj;
    FLOAT fAspect = ((FLOAT)m_d3dsdBackBuffer.Width) / m_d3dsdBackBuffer.Height;
    D3DXMatrixPerspectiveFovLH( &m_mProj, D3DX_PI/4, fAspect, 1.0f, 100.0f );

    // Restore the font
    m_pFont->RestoreDeviceObjects();

	m_pMeshCar  ->RestoreDeviceObjects( m_pd3dDevice );
	m_pMeshChess->RestoreDeviceObjects( m_pd3dDevice );

	// シャドウマップの生成
	if (FAILED(m_pd3dDevice->CreateTexture(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 1, 
		D3DUSAGE_RENDERTARGET, SHADOW_MAP_FORMAT, D3DPOOL_DEFAULT, &m_pShadowMap, NULL)))
		return E_FAIL;
	if (FAILED(m_pShadowMap->GetSurfaceLevel(0, &m_pShadowMapSurf)))
		return E_FAIL;
	if (FAILED(m_pd3dDevice->CreateDepthStencilSurface(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 
		D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pShadowMapZ, NULL)))
		return E_FAIL;

	if( m_pFx != NULL ) m_pFx->OnResetDevice();

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FrameMove()
{
    // TODO: update world

    // Update user input state
    UpdateInput( &m_UserInput );

    // Update the world state according to user input
    D3DXMATRIX matWorld;
    D3DXMATRIX matRotY;
    D3DXMATRIX matRotX;

    if( m_UserInput.bRotateLeft && !m_UserInput.bRotateRight )
        m_fWorldRotY += m_fElapsedTime;
    else if( m_UserInput.bRotateRight && !m_UserInput.bRotateLeft )
        m_fWorldRotY -= m_fElapsedTime;

    if( m_UserInput.bRotateUp && !m_UserInput.bRotateDown )
        m_fWorldRotX += m_fElapsedTime;
    else if( m_UserInput.bRotateDown && !m_UserInput.bRotateUp )
        m_fWorldRotX -= m_fElapsedTime;

    D3DXMatrixRotationX( &matRotX, m_fWorldRotX );
    D3DXMatrixRotationY( &matRotY, m_fWorldRotY );

    D3DXMatrixMultiply( &m_mWorld, &matRotX, &matRotY );
	
	// --------------------------------------------------------------------------
	// ビュー行列の設定
	// --------------------------------------------------------------------------
    if( m_UserInput.bZoomIn && !m_UserInput.bZoomOut )
        m_fViewZoom += m_fElapsedTime;
    else if( m_UserInput.bZoomOut && !m_UserInput.bZoomIn )
        m_fViewZoom -= m_fElapsedTime;

    D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, -m_fViewZoom );
    D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &m_mView, &vFromPt, &vLookatPt, &vUpVec );

	return S_OK;
}
//-----------------------------------------------------------------------------
// Name: UpdateInput()
// Desc: Update the user input.  Called once per frame 
//-----------------------------------------------------------------------------
void CMyD3DApplication::UpdateInput( UserInput* pUserInput )
{
    pUserInput->bRotateUp    = ( m_bActive && (GetAsyncKeyState( VK_UP )    & 0x8000) == 0x8000 );
    pUserInput->bRotateDown  = ( m_bActive && (GetAsyncKeyState( VK_DOWN )  & 0x8000) == 0x8000 );
    pUserInput->bRotateLeft  = ( m_bActive && (GetAsyncKeyState( VK_LEFT )  & 0x8000) == 0x8000 );
    pUserInput->bRotateRight = ( m_bActive && (GetAsyncKeyState( VK_RIGHT ) & 0x8000) == 0x8000 );
    
	pUserInput->bZoomIn      = ( m_bActive && (GetAsyncKeyState( 'Z'     )  & 0x8000) == 0x8000 );
    pUserInput->bZoomOut     = ( m_bActive && (GetAsyncKeyState( 'X'      ) & 0x8000) == 0x8000 );
}

//-----------------------------------------------------------------------------
// 各モデルの描画
//-----------------------------------------------------------------------------
VOID CMyD3DApplication::DrawModel( int pass )
{
    D3DXMATRIX m, mL, mS, mT, mR;
	D3DXVECTOR3 vDir;
	D3DXVECTOR4 v;
	D3DMATERIAL9 *pMtrl;
	DWORD i;
	
	//-------------------------------------------------------------------------
	// 行列の生成
	//-------------------------------------------------------------------------
	D3DXMATRIX mVP = m_mWorld * m_mView * m_mProj;
	
	// 射影空間から、テクスチャーの空間に変換する
	float fOffsetX = 0.5f + (0.5f / (float)SHADOW_MAP_SIZE);
	float fOffsetY = 0.5f + (0.5f / (float)SHADOW_MAP_SIZE);
	D3DXMATRIX mScaleBias(	0.5f,     0.0f,     0.0f,   0.0f,
							0.0f,    -0.5f,     0.0f,   0.0f,
							0.0f,     0.0f,     0.0f,	0.0f,
							fOffsetX, fOffsetY, 0.0f,   1.0f );

	//-------------------------------------------------------------------------
	// 車
	//-------------------------------------------------------------------------
	// ワールド行列の生成
    D3DXMatrixScaling( &mS, 0.05f, 0.05f, 0.05f );
	D3DXMatrixTranslation( &mT, 1.0f, 0.0f ,0.0f );
// m_fTime=1.3f;
	D3DXMatrixRotationY( &mR, m_fTime );
	mL = mS * mT * mR;
	switch(pass){
	case 0:// シャドウマップの作成
		m = mL * m_mLightVP;
        if( m_hmWLP != NULL ) m_pFx->SetMatrix( m_hmWLP, &m );
		m_pMeshCar  ->Render( m_pd3dDevice );// 描画
		break;
	default:// シーンの描画
		m = mL * mVP;
        if( m_hmWVP != NULL ) m_pFx->SetMatrix( m_hmWVP, &m );
		m = mL * m_mLightVP;
        if( m_hmWLP != NULL ) m_pFx->SetMatrix( m_hmWLP, &m );
		m = m * mScaleBias;
        if( m_hmWLPB != NULL ) m_pFx->SetMatrix( m_hmWLPB, &m );
		D3DXMatrixInverse( &m, NULL, &mL);
		D3DXVec3Transform( &v, &m_LighPos, &m );
		D3DXVec4Normalize( &v, &v );v.w = 0;
		if( m_hvDir != NULL ) m_pFx->SetVector( m_hvDir, &v );

		pMtrl = m_pMeshCar->m_pMaterials;
        for( i=0; i<m_pMeshCar->m_dwNumMaterials; i++ ) {
			v.x = pMtrl->Diffuse.r;
			v.y = pMtrl->Diffuse.g;
			v.z = pMtrl->Diffuse.b;
			v.w = pMtrl->Diffuse.a;
			if( m_hvCol != NULL ) m_pFx->SetVector( m_hvCol, &v );
            m_pMeshCar->m_pLocalMesh->DrawSubset( i );	// 描画
			pMtrl++;
        }
		break;
	}

	//-------------------------------------------------------------------------
	// 地形
	//-------------------------------------------------------------------------
	// ワールド行列の生成
	D3DXMatrixIdentity( &mL );
	switch(pass){
	case 0:// シャドウマップの作成
		m = mL * m_mLightVP;
        if( m_hmWLP != NULL ) m_pFx->SetMatrix( m_hmWLP, &m );
		m_pMeshChess->Render( m_pd3dDevice );// 描画
		break;
	default:// シーンの描画
		m = mL * mVP;
        if( m_hmWVP != NULL ) m_pFx->SetMatrix( m_hmWVP, &m );
		m = mL * m_mLightVP;
        if( m_hmWLP != NULL ) m_pFx->SetMatrix( m_hmWLP, &m );
		m = m * mScaleBias;
        if( m_hmWLPB != NULL ) m_pFx->SetMatrix( m_hmWLPB, &m );
		D3DXMatrixInverse( &m, NULL, &mL);
		D3DXVec3Transform( &v, &m_LighPos, &m );
		D3DXVec4Normalize( &v, &v );v.w = 0;
		if( m_hvDir != NULL ) m_pFx->SetVector( m_hvDir, &v );

		pMtrl = m_pMeshChess->m_pMaterials;
        for( i=0; i<m_pMeshChess->m_dwNumMaterials; i++ ) {
			v.x = pMtrl->Diffuse.r;
			v.y = pMtrl->Diffuse.g;
			v.z = pMtrl->Diffuse.b;
			v.w = pMtrl->Diffuse.a;
			if( m_hvCol != NULL ) m_pFx->SetVector( m_hvCol, &v );
            m_pMeshChess->m_pLocalMesh->DrawSubset( i );	// 描画
			pMtrl++;
        }
		break;
	}

}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::Render()
{
    D3DXMATRIX mLP, mView, mProj;
	LPDIRECT3DSURFACE9 pOldBackBuffer, pOldZBuffer;
	D3DVIEWPORT9 oldViewport;

	//-------------------------------------------------------------------------
	// 行列の作成
	//-------------------------------------------------------------------------
    // ライト方向から見た射影空間への行列
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &mView, &m_LighPos, &vLookatPt, &vUpVec );
    D3DXMatrixPerspectiveFovLH( &mProj
							, 0.21f*D3DX_PI		// 視野角
							, 1.0f				// アスペクト比
							, 5.0f, 12.0f );	// near far
	m_mLightVP = mView * mProj;

	//-------------------------------------------------------------------------
	// 描画
	//-------------------------------------------------------------------------
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )
    {
		if( m_pFx != NULL ) 
		{
			//-------------------------------------------------------------------------
			// シェーダの設定
			//-------------------------------------------------------------------------
			D3DXHANDLE hTechnique = m_pFx->GetTechniqueByName( "TShader" );
			m_pFx->SetTechnique( hTechnique );
			m_pFx->Begin( NULL, 0 );

			//-------------------------------------------------------------------------
			// レンダリングターゲットの保存
			//--------------------------------------------------------------------------
			m_pd3dDevice->GetRenderTarget(0, &pOldBackBuffer);
			m_pd3dDevice->GetDepthStencilSurface(&pOldZBuffer);
			m_pd3dDevice->GetViewport(&oldViewport);

			//-------------------------------------------------------------------------
			// レンダリングターゲットの変更
			//--------------------------------------------------------------------------
			m_pd3dDevice->SetRenderTarget(0, m_pShadowMapSurf);
			m_pd3dDevice->SetDepthStencilSurface(m_pShadowMapZ);
			// ビューポートの変更    x y       width         height       minz maxz
			D3DVIEWPORT9 viewport = {0,0, SHADOW_MAP_SIZE,SHADOW_MAP_SIZE,0.0f,1.0f};
			m_pd3dDevice->SetViewport(&viewport);

			// シャドウマップのクリア
			m_pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
								0xFFFFFFFF, 1.0f, 0L);

			//-----------------------------------------------------------------------------
			// 1パス目:シャドウマップの作成
			//-----------------------------------------------------------------------------
			m_pFx->Pass( 0 );
			DrawModel( 0 );

			//-------------------------------------------------------------------------
			// レンダリングターゲットを元に戻す
			//--------------------------------------------------------------------------
			m_pd3dDevice->SetRenderTarget(0, pOldBackBuffer);
			m_pd3dDevice->SetDepthStencilSurface(pOldZBuffer);
			m_pd3dDevice->SetViewport(&oldViewport);
			pOldBackBuffer->Release();
			pOldZBuffer->Release();

			//-----------------------------------------------------------------------------
			// 2パス目:シーンの描画
			//-----------------------------------------------------------------------------
			// バッファのクリア
			m_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
								0x00404080, 1.0f, 0L );

			//-------------------------------------------------------------------------
			// 描画
			//--------------------------------------------------------------------------
			m_pFx->SetTexture("ShadowMap", m_pShadowMap);// テクスチャの設定
			m_pFx->Pass( 1 );
			DrawModel( 1 );

			m_pFx->End();
		}

        // ヘルプの表示
        RenderText();

#if 1 // デバッグ用にテクスチャを表示する
		{
		m_pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,	D3DTOP_SELECTARG1);
		m_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,	D3DTA_TEXTURE);
		m_pd3dDevice->SetTextureStageState(1,D3DTSS_COLOROP,    D3DTOP_DISABLE);
		float scale = 128.0f;
		TVERTEX Vertex[4] = {
			// x  y  z rhw tu tv
			{    0,    0,0, 1, 0, 0,},
			{scale,    0,0, 1, 1, 0,},
			{scale,scale,0, 1, 1, 1,},
			{    0,scale,0, 1, 0, 1,},
		};
		m_pd3dDevice->SetTexture( 0, m_pShadowMap );
		m_pd3dDevice->SetVertexShader(NULL);
		m_pd3dDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 );
		m_pd3dDevice->SetPixelShader(0);
		m_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, Vertex, sizeof( TVERTEX ) );
		}
#endif		

		// 描画の終了
        m_pd3dDevice->EndScene();
    }

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: RenderText()
// Desc: Renders stats and help text to the scene.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::RenderText()
{
    D3DCOLOR fontColor        = D3DCOLOR_ARGB(255,255,255,0);
    TCHAR szMsg[MAX_PATH] = TEXT("");

    // Output display stats
    FLOAT fNextLine = 40.0f; 

    // Output statistics & help
    fNextLine = (FLOAT) m_d3dsdBackBuffer.Height; 
    lstrcpy( szMsg, TEXT("Use arrow keys to rotate camera") );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    lstrcpy( szMsg, TEXT("Press 'F2' to configure display") );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );

    lstrcpy( szMsg, m_strDeviceStats );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
    lstrcpy( szMsg, m_strFrameStats );
    fNextLine -= 20.0f; m_pFont->DrawText( 2, fNextLine, fontColor, szMsg );
	
	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Overrrides the main WndProc, so the sample can do custom message
//       handling (e.g. processing mouse, keyboard, or menu commands).
//-----------------------------------------------------------------------------
LRESULT CMyD3DApplication::MsgProc( HWND hWnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam )
{
    switch( msg )
    {
        case WM_PAINT:
        {
            if( m_bLoadingApp )
            {
                // Draw on the window tell the user that the app is loading
                // TODO: change as needed
                HDC hDC = GetDC( hWnd );
                TCHAR strMsg[MAX_PATH];
                wsprintf( strMsg, TEXT("Loading... Please wait") );
                RECT rct;
                GetClientRect( hWnd, &rct );
                DrawText( hDC, strMsg, -1, &rct, DT_CENTER|DT_VCENTER|DT_SINGLELINE );
                ReleaseDC( hWnd, hDC );
            }
            break;
        }

    }

    return CD3DApplication::MsgProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: InvalidateDeviceObjects()
// Desc: Invalidates device objects.  Paired with RestoreDeviceObjects()
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::InvalidateDeviceObjects()
{
	m_pMeshCar  ->InvalidateDeviceObjects();
	m_pMeshChess->InvalidateDeviceObjects();

    // TODO: Cleanup any objects created in RestoreDeviceObjects()
    m_pFont->InvalidateDeviceObjects();

	// シャドウマップ
	SAFE_RELEASE(m_pShadowMapSurf);
	SAFE_RELEASE(m_pShadowMap);
	SAFE_RELEASE(m_pShadowMapZ);

	// シェーダ
    if( m_pFx != NULL ) m_pFx->OnLostDevice();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Paired with InitDeviceObjects()
//       Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.  
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::DeleteDeviceObjects()
{
    // シェーダ
	SAFE_RELEASE( m_pFx );
	m_pMeshCar  ->Destroy();
	m_pMeshChess->Destroy();

    // TODO: Cleanup any objects created in InitDeviceObjects()
    m_pFont->DeleteDeviceObjects();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Paired with OneTimeSceneInit()
//       Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CMyD3DApplication::FinalCleanup()
{
    SAFE_DELETE( m_pMeshChess );
	SAFE_DELETE( m_pMeshCar );

    // TODO: Perform any final cleanup needed
    // Cleanup D3D font
    SAFE_DELETE( m_pFont );

    return S_OK;
}




