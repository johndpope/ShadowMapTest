//-----------------------------------------------------------------------------------------------------
// File : Main.cpp
//
// GLUT Empty Project
//
// Date : Jan. 03, 2008
// Version : 2.0
// Author : Pocol
// Memo :
//-----------------------------------------------------------------------------------------------------


//
// include
//
#include "framework/framework.h"
using namespace std;

//
// Global Variable
//
GLUTState Window = { 
	Vector2i(100, 100),
	Vector2i(800, 600),
	Vector2i(0, 0),
	Vector2i(0, 0),
	false,
	"★　シャドウマッピング　★",
	NULL, 
	NULL,
	NULL,
	NULL,
	0.0f,
	0.0, 0.0,
	0.0, 0.0,
	0,
};
ThirdPersonCamera g_Camera;
Color4f CornflowerBlue = ColorRGBA(100, 149, 237, 255);
Vector4f g_lightPosition(0.0f, 3.0f, -3.0f, 1.0f);
Color4f g_lightAmbient(0.0f, 0.0f, 0.0f, 1.0f);
Color4f g_lightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
Matrix4f View;
Matrix4f Projection;
Matrix4f LightView;
Matrix4f LightProjection;
GLuint meshListID = 0;
GLuint g_ShadowMap = 0;

#if USE_CG
CGcontext g_Context = NULL;
CGeffect g_Effect = NULL;
CGtechnique g_Technique = NULL;
CGparameter g_hWVP = NULL;
CGparameter g_hWLP = NULL;
CGparameter g_hWLPB = NULL;
CGparameter g_hLightPosition = NULL;
CGparameter g_hShadowMap = NULL;
#endif

//----------------------------------------------------------------------------------------------------
// Name : main()
// Desc : アプリケーションのエントリーポイント
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv )
{
	//　GLUTコールバック関数などの設定
	glutInit( &argc, argv );
	glutInitWindowPosition( Window.Position.x, Window.Position.y );
	glutInitWindowSize( Window.Size.x, Window.Size.y );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutCreateWindow( Window.Title );
	glutDisplayFunc( RenderFunc );
	glutReshapeFunc( ReshapeFunc );
	glutIdleFunc( IdleFunc );
	glutMouseFunc( MouseFunc );
	glutMotionFunc( MotionFunc );
	glutPassiveMotionFunc( PassiveMotionFunc );
	glutKeyboardFunc( KeyboardFunc );
	glutSpecialFunc( SpecialFunc );
	glutCreateMenu( MenuFunc );
	
	//　OpenGL初期化
	Initialize();	

	//　メインループ
	glutMainLoop();

	//　後片付け
	Shutdown();

	return 0;
}

//----------------------------------------------------------------------------------------------------
// Name : Initialize()
// Desc : 初期化処理
//----------------------------------------------------------------------------------------------------
void Initialize()
{
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *vender = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);

	sprintf(Window.Version, "OpenGL %s", version);
	sprintf(Window.Vender, "%s", vender);
	sprintf(Window.Renderer, "%s", renderer);

	//　深度テスト
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//　開始時間を保存
	Window.prevCount = glutGet(GLUT_ELAPSED_TIME);

	//　ポップアップメニューを追加
	glutAddMenuEntry("ToggleFullScreen (F1)", GLUT_KEY_F1);
	glutAddMenuEntry("Exit (ESC)", '\033');
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	//　補助軸用のライティング
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, g_lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, g_lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPosition);

	//　補助軸用のマテリアル設定
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	//　メッシュをロードし，ディスプレイリストを作成
	AsuraMesh mesh;
	AsuraLoadMeshFromX_A("Models/dosei.x", mesh);
	meshListID = AsuraCreateDisplayList(mesh);

#if USE_GLEW
	//　GLEWの初期化
	if ( glewInit() != GLEW_OK )
	{
		//　初期化失敗
		cout << "Error : GLEW Initialize false\n";
		Shutdown();
	}
#endif

#if USE_CG
	//　Cgの初期化
	InitializeCg();
#endif

}

//---------------------------------------------------------------------------------------------------
// Name : IdleFunc()
// Desc : アイドリング時の処理
//---------------------------------------------------------------------------------------------------
void IdleFunc()
{
	//　更新処理
	Update();

	//　再描画
	glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------
// Name : ReshapeFunc()
// Desc : サイズ変更
//---------------------------------------------------------------------------------------------------
void ReshapeFunc(int x, int y)
{
	//　ウィンドウサイズを保存
	Window.Size.x = x;
	Window.Size.y = y;

	//　サイズチェック
	if ( Window.Size.x < 1 ) Window.Size.x = 1;
	if ( Window.Size.y < 1 ) Window.Size.y = 1;

	//　アスペクト比
	float aspectRatio = (float)Window.Size.x/(float)Window.Size.y;

	//　ビューポートの設定
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	//　射影行列
	Projection = CreatePerspectiveFieldOfView((float)PiOver4, aspectRatio, 0.01f, 1000.0f);
	LightProjection = CreatePerspectiveFieldOfView( (float)PiOver4, aspectRatio, 4.0f, 12.0f );
}

//---------------------------------------------------------------------------------------------------
// Name : Update()
// Desc : 更新処理
//---------------------------------------------------------------------------------------------------
void Update()
{
	sprintf( Window.FpsString, "%.3f FPS", glutGetFPS() );
}


//---------------------------------------------------------------------------------------------------
// Name : RenderFunc()
// Desc : ウィンドウへの描画
//---------------------------------------------------------------------------------------------------
void RenderFunc()
{
	//　視点の計算
	g_Camera.Calculate();

	//　ビュー行列
	View = CreateLookAt(g_Camera.Position, g_Camera.Target, g_Camera.UpVector);
	LightView = CreateLookAt( g_lightPosition.xyz(), Vector3f().Zero(), Vector3f().Up() );

	//　シーンを描画(3次元)
	Render3D();

	//　シーンを描画(2次元)
	Render2D();

	//　補助軸を描画
	g_Camera.RenderSubAxis(Window.Size.x, Window.Size.y);

	//　ダブルバッファリング
	glutSwapBuffers();

#if defined(DEBUG) || defined(_DEBUG)
	//　エラーチェック
	glutReportErrors();
#endif
}

//---------------------------------------------------------------------------------------------------
// Name : Render2D()
// Desc : 2次元シーンの描画
//---------------------------------------------------------------------------------------------------
void Render2D()
{
	bool isLighting = false;

	//　3D　→　2D
	glMatrixMode( GL_PROJECTION) ;
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0, Window.Size.x, Window.Size.y, 0 );
	glMatrixMode( GL_MODELVIEW) ;
	glPushMatrix();
	glLoadIdentity();

	//　ライティングが有効である場合
	if ( glIsEnabled(GL_LIGHTING) )
	{
		//　ライティングを無効化
		glDisable(GL_LIGHTING);

		//　ライティング処理があった
		isLighting = true;
	}

	//　文字の描画
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(15, 15);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Version);
	glRasterPos2i(15, 30);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Vender);
	glRasterPos2i(15, 45);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Renderer);
	glRasterPos2i(15, 60);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.FpsString);

	//　深度テクスチャの表示
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_ShadowMap);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, Window.Size.y-150.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, Window.Size.y, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(200.0f, Window.Size.y, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(200.0f, Window.Size.y-150.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//　ライティング処理があった場合
	if ( isLighting )
	{
		//　ライティングを有効化
		glEnable(GL_LIGHTING);
	}

	//　2D　→　3D
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//-------------------------------------------------------------------------------------------------
// Name : RenderGround()
// Desc : 地面の描画
//-------------------------------------------------------------------------------------------------
void RenderGround(float width, float height, float length)
{
	float w = width/5.0f;
	float l = length/5.0f;
	float color[][4] = {
		{ 0.7f, 0.7f, 0.7f, 1.0f },
		{ 0.0f, 0.5f, 0.0f, 1.0f },
  };

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int j = -5; j < 5; j++)
	{
	    for (int i = -5; i < 5; i++)
		{
			glColor4fv( color[(i + j) & 1] );
			glVertex3f( w * (i + 0), height, l * (j + 0) );
			glVertex3f( w * (i + 0), height, l * (j + 1) );
			glVertex3f( w * (i + 1), height, l * (j + 1) );
			glVertex3f( w * (i + 1), height, l * (j + 0) );
	    }
	}
	glEnd();
}

//--------------------------------------------------------------------------------------------------
// Name : Render3D()
// Desc : 3次元シーンの描画
//--------------------------------------------------------------------------------------------------
void Render3D()
{
	Matrix4f m, mW, mVP, mLP;
	Vector3f v;

	//　射影空間からテクスチャ空間に変換
	float fOffsetX = 0.5f + ( 0.5f / (float)Window.Size.x );
	float fOffsetY = 0.5f + ( 0.5f / (float)Window.Size.y );
	Matrix4f mScaleBias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		fOffsetX, fOffsetY, 0.0f, 1.0f
		);

	//　
	mVP = View * Projection;
	mLP = LightView * LightProjection;

	//　バッファをクリア
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	

	//　最初のパスをセット
	CGpass pass = cgGetFirstPass(g_Technique);

	//　シャドウマップの作成
	cgSetPassState(pass);
	{
		//　メッシュを描画
		mW.Identity();	
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );
		glCallList(meshListID);

		//　地面を描画
		mW.Identity();
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );
		RenderGround(5.0, -1.0f, 5.0f);
	}
	cgResetPassState(pass);

	//　ウィンドウの描画内容をキャプチャ
	CopyWindowToTexture( GL_TEXTURE_2D, &g_ShadowMap );

	//　シャドウマップを送る
	cgGLSetTextureParameter( g_hShadowMap, g_ShadowMap );

	//　バッファをクリア
	glClearColor( CornflowerBlue.r, CornflowerBlue.g, CornflowerBlue.b, CornflowerBlue.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//　次のパスをセット
	pass = cgGetNextPass(pass);

	//　影をつけて描画
	cgSetPassState(pass);
	{
		//　メッシュを描画
		mW.Identity();
		m = mW * mVP;
		cgSetMatrixParameterfr( g_hWVP, m );		//　ワールドビュー射影行列
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );		//　ライトのワールドビュー射影行列
		m = m * mScaleBias;
		cgSetMatrixParameterfr( g_hWLPB, m );	//　テクスチャ空間への射影行列
		v = g_lightPosition.xyz();
		cgSetParameter3fv( g_hLightPosition, v );	//　ライトの位置
		glCallList(meshListID);

		//　地面を描画
		mW.Identity();
		m = mW * mVP;
		cgSetMatrixParameterfr( g_hWVP, m );		//　ワールドビュー射影行列
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );		//　ライトのワールドビュー射影行列
		m = m * mScaleBias;
		cgSetMatrixParameterfr( g_hWLPB, m );	//　テクスチャ空間への射影行列
		v = g_lightPosition.xyz();
		cgSetParameter3fv( g_hLightPosition, v );	//　ライトの位置
		RenderGround(5.0f, -1.0f, 5.0f);
	}
	cgResetPassState(pass);
}

//---------------------------------------------------------------------------------------------------
// Name : MouseFunc()
// Desc : マウス処理
//---------------------------------------------------------------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{
	g_Camera.MouseFunc(button, state, x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : MotionFunc()
// Desc : マウスドラッグ時
//-------------------------------------------------------------------------------------------------
void MotionFunc(int x, int y)
{
	g_Camera.MotionFunc(x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : PassiveMotionFunc()
// Desc : マウス移動時
//--------------------------------------------------------------------------------------------------
void PassiveMotionFunc(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
// Name : KeyboardFunc()
// Desc : キーボード処理
//--------------------------------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch ( key )
	{
	case '\033':
		Shutdown();
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
// Name : SpecialFunc()
// Desc : 特殊キー処理
//--------------------------------------------------------------------------------------------------
void SpecialFunc(int key, int x, int y)
{
	switch ( key )
	{
	case GLUT_KEY_F1:
		glutToggleFullScreen();
		break;

	case GLUT_KEY_F2:
		break;

	case GLUT_KEY_F3:
		break;

	case GLUT_KEY_F4:
		break;

	case GLUT_KEY_F5:
		break;

	case GLUT_KEY_F6:
		break;

	case GLUT_KEY_F7:
		break;

	case GLUT_KEY_F8:
		break;

	case GLUT_KEY_F9:
		break;

	case GLUT_KEY_F10:
		break;

	case GLUT_KEY_F11:
		break;

	case GLUT_KEY_F12:
		break;

	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;

	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_HOME:
		break;

	case GLUT_KEY_END:
		break;

	case GLUT_KEY_INSERT:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
// Name : MenuFunc()
// Desc : ポップアップメニューの処理
//--------------------------------------------------------------------------------------------------
void MenuFunc(int item)
{
	if ( (1 <= item && item <= 12 ) 
		|| (100<=item && item <= 108) ) 
		SpecialFunc(item, 0, 0);
	else
		KeyboardFunc((unsigned char)item, 0, 0);
}

//--------------------------------------------------------------------------------------------------
// Name : Shutdown()
// Desc : 後片付け
//--------------------------------------------------------------------------------------------------
void Shutdown()
{
#if USE_CG
	ShutdownCg();
#endif

	exit(0);
}

//--------------------------------------------------------------------------------------------------
// Name : glutRenderText()
// Desc : ASCII文字列の描画
//--------------------------------------------------------------------------------------------------
void glutRenderText(void* bitmapfont, char*text)
{
	for ( int i=0; i<(int)strlen(text); i++ )
		glutBitmapCharacter(bitmapfont, (int)text[i]);
}

//--------------------------------------------------------------------------------------------------
// Name : glutToggleFullScreen()
// Desc : フルスクリーンとウィンドウモードの切り替え
//--------------------------------------------------------------------------------------------------
void glutToggleFullScreen()
{
	Window.FullScreen = (Window.FullScreen ? false : true);
	if ( Window.FullScreen )
	{
		Window.PrevPosition.x = glutGet(GLUT_WINDOW_X);
		Window.PrevPosition.y = glutGet(GLUT_WINDOW_Y);
		Window.PrevSize.x = glutGet(GLUT_WINDOW_WIDTH);
		Window.PrevSize.y = glutGet(GLUT_WINDOW_HEIGHT);
		glutFullScreen();
	}
	else
	{
		glutPositionWindow(Window.PrevPosition.x, Window.PrevPosition.y);
		glutReshapeWindow(Window.PrevSize.x, Window.PrevSize.y);
		glutShowWindow();
	}
}

//---------------------------------------------------------------------------------------------------
// Name : glutGetFPS()
// Desc : FPSを取得する
//--------------------------------------------------------------------------------------------------
float glutGetFPS()
{
	Window.currCount = glutGet(GLUT_ELAPSED_TIME);
	Window.currTime = (Window.currCount - Window.prevCount)/1000.0;
	Window.frame++;

	//　最後の更新からの経過時間を算出
	double dtime = (Window.currTime - Window.prevTime);

	//　1秒以上たったら更新
	if ( dtime >= 1.0 )
	{
		Window.FPS = (float)(Window.frame/dtime);
		Window.frame = 0;
		Window.prevTime = Window.currTime;
	}

	return Window.FPS;
}


#if USE_CG 
//---------------------------------------------------------------------------------------------------
// Name : CheckCgError()
// Desc : Cgエラーをチェックする
//---------------------------------------------------------------------------------------------------
void CheckCgError()
{
	CGerror lastError = cgGetError();
	if ( lastError )
	{
		cout << "Error : Cgエラーが発生しました\n";
		cout << cgGetErrorString(lastError) << endl;
		cout << cgGetLastListing(g_Context) << endl;
		Shutdown();
	}
}

//---------------------------------------------------------------------------------------------------
// Name : InitializeCg()
// Desc : Cgの初期化
//---------------------------------------------------------------------------------------------------
void InitializeCg()
{
	//　エラーコールバック関数の設定
	cgSetErrorCallback(CheckCgError);

	//　コンテキストを作成
	g_Context = cgCreateContext();
	cgGLRegisterStates(g_Context);

	//　エフェクトを作成
	g_Effect = cgCreateEffectFromFile(g_Context, "Shader/ShadowMap.cgfx", NULL);

	//　テクニックを取得
	g_Technique = cgGetNamedTechnique(g_Effect, "Render");

	//　チェック
	while ( g_Technique && cgValidateTechnique(g_Technique) == CG_FALSE )
	{
		cout << "Error : Technique " << cgGetTechniqueName(g_Technique) << "did not valid. Skipping\n";
		g_Technique = cgGetNextTechnique(g_Technique);
	}
	if ( !g_Technique )
	{
		cout << "Error : No valid techniques\n";
		Shutdown();
	}

	//　パラメータを取得
	g_hWVP = cgGetNamedEffectParameter(g_Effect, "mWVP");
	g_hWLP = cgGetNamedEffectParameter(g_Effect, "mWLP");
	g_hWLPB = cgGetNamedEffectParameter(g_Effect, "mWLPB");
	g_hLightPosition = cgGetNamedEffectParameter(g_Effect, "vLightPosition");
	g_hShadowMap = cgGetNamedEffectParameter(g_Effect, "ShadowMapSmp");
}

//---------------------------------------------------------------------------------------------------
// Name : ShutdownCg()
// Desc : Cgの後片付け
//---------------------------------------------------------------------------------------------------
void ShutdownCg()
{
	if ( g_Effect )
	{
		cgDestroyEffect(g_Effect);
		g_Effect = NULL;
	}
	if ( g_Context )
	{
		cgDestroyContext(g_Context);
		g_Context = NULL;
	}
}
#endif

#if USE_GLEW
//---------------------------------------------------------------------------------------------------
// Name : CopyWindowToTexture()
// Desc : 描画内容をテクスチャにコピー
//---------------------------------------------------------------------------------------------------
void CopyWindowToTexture(GLenum target, GLuint *handle, bool bufferClear)
{
	if ( *handle )
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(target, *handle);
		glCopyTexSubImage2D(target, 0, 0, 0, 0, 0, Window.Size.x, Window.Size.y);
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, handle);
		glBindTexture(target, *handle);

		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glCopyTexImage2D(target, 0, GL_RGBA, 0, 0, Window.Size.x, Window.Size.y, 0);
		glDisable(GL_TEXTURE_2D);
	}

	if ( bufferClear )
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
#endif
