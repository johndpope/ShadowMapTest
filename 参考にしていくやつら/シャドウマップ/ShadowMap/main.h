//-----------------------------------------------------------------------------
// File: main.h
//
// Desc: Header file main sample app
//-----------------------------------------------------------------------------
#pragma once




//-----------------------------------------------------------------------------
// Defines, and constants
//-----------------------------------------------------------------------------
// TODO: change "DirectX AppWizard Apps" to your name or the company name
#define DXAPP_KEY        TEXT("Software\\DirectX AppWizard Apps\\main")

// Struct to store the current input state
struct UserInput
{
    // TODO: change as needed
    BOOL bRotateUp;
    BOOL bRotateDown;
    BOOL bRotateLeft;
    BOOL bRotateRight;
    BOOL bZoomIn;
    BOOL bZoomOut;
};




//-----------------------------------------------------------------------------
// Name: class CMyD3DApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CMyD3DApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CMyD3DApplication : public CD3DApplication
{
	CD3DMesh				*m_pMeshCar;
	CD3DMesh				*m_pMeshChess;
			
	// シェーダ
	LPD3DXEFFECT     m_pFx;		// シェーダが書かれたエフェクト
	D3DXHANDLE       m_hmWVP;	// ワールド×ビュー×射影行列
	D3DXHANDLE       m_hmWLP;	// ライト方向からの変換行列
	D3DXHANDLE       m_hmWLPB;	// ライト方向からの変換行列
	D3DXHANDLE       m_hvCol;	// メッシュの色
	D3DXHANDLE       m_hvDir;	// ライトの方向


	// シャドウマップ
	LPDIRECT3DTEXTURE9		m_pShadowMap;
	LPDIRECT3DSURFACE9		m_pShadowMapSurf;
	LPDIRECT3DSURFACE9		m_pShadowMapZ;

	// 通常の座標変換行列
	D3DXMATRIX				m_mWorld;
	D3DXMATRIX				m_mView;
	D3DXMATRIX				m_mProj;
	D3DXMATRIX				m_mLightVP;

	D3DXVECTOR3				m_LighPos;		// 光源の方向

	BOOL                    m_bLoadingApp;  // TRUE, if the app is loading
    CD3DFont*               m_pFont;        // Font for drawing text
    UserInput               m_UserInput;    // Struct for storing user input 

    FLOAT                   m_fWorldRotX;   // World rotation state X-axis
    FLOAT                   m_fWorldRotY;   // World rotation state Y-axis
    FLOAT                   m_fViewZoom;    // 視点の距離


	VOID DrawModel( int pass );	// 各パスで呼ばれるモデルの描画
protected:
    virtual HRESULT OneTimeSceneInit();
    virtual HRESULT InitDeviceObjects();
    virtual HRESULT RestoreDeviceObjects();
    virtual HRESULT InvalidateDeviceObjects();
    virtual HRESULT DeleteDeviceObjects();
    virtual HRESULT Render();
    virtual HRESULT FrameMove();
    virtual HRESULT FinalCleanup();
    virtual HRESULT ConfirmDevice( D3DCAPS9*, DWORD, D3DFORMAT );

    HRESULT RenderText();

    void    UpdateInput( UserInput* pUserInput );
public:
    LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
    CMyD3DApplication();
    virtual ~CMyD3DApplication();
};

