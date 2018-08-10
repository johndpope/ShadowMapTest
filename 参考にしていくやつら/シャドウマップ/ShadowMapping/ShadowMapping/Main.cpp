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
	"���@�V���h�E�}�b�s���O�@��",
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
// Desc : �A�v���P�[�V�����̃G���g���[�|�C���g
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv )
{
	//�@GLUT�R�[���o�b�N�֐��Ȃǂ̐ݒ�
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
	
	//�@OpenGL������
	Initialize();	

	//�@���C�����[�v
	glutMainLoop();

	//�@��Еt��
	Shutdown();

	return 0;
}

//----------------------------------------------------------------------------------------------------
// Name : Initialize()
// Desc : ����������
//----------------------------------------------------------------------------------------------------
void Initialize()
{
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *vender = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);

	sprintf(Window.Version, "OpenGL %s", version);
	sprintf(Window.Vender, "%s", vender);
	sprintf(Window.Renderer, "%s", renderer);

	//�@�[�x�e�X�g
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//�@�J�n���Ԃ�ۑ�
	Window.prevCount = glutGet(GLUT_ELAPSED_TIME);

	//�@�|�b�v�A�b�v���j���[��ǉ�
	glutAddMenuEntry("ToggleFullScreen (F1)", GLUT_KEY_F1);
	glutAddMenuEntry("Exit (ESC)", '\033');
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	//�@�⏕���p�̃��C�e�B���O
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, g_lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, g_lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, g_lightPosition);

	//�@�⏕���p�̃}�e���A���ݒ�
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	//�@���b�V�������[�h���C�f�B�X�v���C���X�g���쐬
	AsuraMesh mesh;
	AsuraLoadMeshFromX_A("Models/dosei.x", mesh);
	meshListID = AsuraCreateDisplayList(mesh);

#if USE_GLEW
	//�@GLEW�̏�����
	if ( glewInit() != GLEW_OK )
	{
		//�@���������s
		cout << "Error : GLEW Initialize false\n";
		Shutdown();
	}
#endif

#if USE_CG
	//�@Cg�̏�����
	InitializeCg();
#endif

}

//---------------------------------------------------------------------------------------------------
// Name : IdleFunc()
// Desc : �A�C�h�����O���̏���
//---------------------------------------------------------------------------------------------------
void IdleFunc()
{
	//�@�X�V����
	Update();

	//�@�ĕ`��
	glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------
// Name : ReshapeFunc()
// Desc : �T�C�Y�ύX
//---------------------------------------------------------------------------------------------------
void ReshapeFunc(int x, int y)
{
	//�@�E�B���h�E�T�C�Y��ۑ�
	Window.Size.x = x;
	Window.Size.y = y;

	//�@�T�C�Y�`�F�b�N
	if ( Window.Size.x < 1 ) Window.Size.x = 1;
	if ( Window.Size.y < 1 ) Window.Size.y = 1;

	//�@�A�X�y�N�g��
	float aspectRatio = (float)Window.Size.x/(float)Window.Size.y;

	//�@�r���[�|�[�g�̐ݒ�
	glViewport(0, 0, Window.Size.x, Window.Size.y);

	//�@�ˉe�s��
	Projection = CreatePerspectiveFieldOfView((float)PiOver4, aspectRatio, 0.01f, 1000.0f);
	LightProjection = CreatePerspectiveFieldOfView( (float)PiOver4, aspectRatio, 4.0f, 12.0f );
}

//---------------------------------------------------------------------------------------------------
// Name : Update()
// Desc : �X�V����
//---------------------------------------------------------------------------------------------------
void Update()
{
	sprintf( Window.FpsString, "%.3f FPS", glutGetFPS() );
}


//---------------------------------------------------------------------------------------------------
// Name : RenderFunc()
// Desc : �E�B���h�E�ւ̕`��
//---------------------------------------------------------------------------------------------------
void RenderFunc()
{
	//�@���_�̌v�Z
	g_Camera.Calculate();

	//�@�r���[�s��
	View = CreateLookAt(g_Camera.Position, g_Camera.Target, g_Camera.UpVector);
	LightView = CreateLookAt( g_lightPosition.xyz(), Vector3f().Zero(), Vector3f().Up() );

	//�@�V�[����`��(3����)
	Render3D();

	//�@�V�[����`��(2����)
	Render2D();

	//�@�⏕����`��
	g_Camera.RenderSubAxis(Window.Size.x, Window.Size.y);

	//�@�_�u���o�b�t�@�����O
	glutSwapBuffers();

#if defined(DEBUG) || defined(_DEBUG)
	//�@�G���[�`�F�b�N
	glutReportErrors();
#endif
}

//---------------------------------------------------------------------------------------------------
// Name : Render2D()
// Desc : 2�����V�[���̕`��
//---------------------------------------------------------------------------------------------------
void Render2D()
{
	bool isLighting = false;

	//�@3D�@���@2D
	glMatrixMode( GL_PROJECTION) ;
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0, Window.Size.x, Window.Size.y, 0 );
	glMatrixMode( GL_MODELVIEW) ;
	glPushMatrix();
	glLoadIdentity();

	//�@���C�e�B���O���L���ł���ꍇ
	if ( glIsEnabled(GL_LIGHTING) )
	{
		//�@���C�e�B���O�𖳌���
		glDisable(GL_LIGHTING);

		//�@���C�e�B���O������������
		isLighting = true;
	}

	//�@�����̕`��
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(15, 15);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Version);
	glRasterPos2i(15, 30);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Vender);
	glRasterPos2i(15, 45);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.Renderer);
	glRasterPos2i(15, 60);
	glutRenderText(GLUT_BITMAP_HELVETICA_12, Window.FpsString);

	//�@�[�x�e�N�X�`���̕\��
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

	//�@���C�e�B���O�������������ꍇ
	if ( isLighting )
	{
		//�@���C�e�B���O��L����
		glEnable(GL_LIGHTING);
	}

	//�@2D�@���@3D
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//-------------------------------------------------------------------------------------------------
// Name : RenderGround()
// Desc : �n�ʂ̕`��
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
// Desc : 3�����V�[���̕`��
//--------------------------------------------------------------------------------------------------
void Render3D()
{
	Matrix4f m, mW, mVP, mLP;
	Vector3f v;

	//�@�ˉe��Ԃ���e�N�X�`����Ԃɕϊ�
	float fOffsetX = 0.5f + ( 0.5f / (float)Window.Size.x );
	float fOffsetY = 0.5f + ( 0.5f / (float)Window.Size.y );
	Matrix4f mScaleBias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		fOffsetX, fOffsetY, 0.0f, 1.0f
		);

	//�@
	mVP = View * Projection;
	mLP = LightView * LightProjection;

	//�@�o�b�t�@���N���A
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	

	//�@�ŏ��̃p�X���Z�b�g
	CGpass pass = cgGetFirstPass(g_Technique);

	//�@�V���h�E�}�b�v�̍쐬
	cgSetPassState(pass);
	{
		//�@���b�V����`��
		mW.Identity();	
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );
		glCallList(meshListID);

		//�@�n�ʂ�`��
		mW.Identity();
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );
		RenderGround(5.0, -1.0f, 5.0f);
	}
	cgResetPassState(pass);

	//�@�E�B���h�E�̕`����e���L���v�`��
	CopyWindowToTexture( GL_TEXTURE_2D, &g_ShadowMap );

	//�@�V���h�E�}�b�v�𑗂�
	cgGLSetTextureParameter( g_hShadowMap, g_ShadowMap );

	//�@�o�b�t�@���N���A
	glClearColor( CornflowerBlue.r, CornflowerBlue.g, CornflowerBlue.b, CornflowerBlue.a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//�@���̃p�X���Z�b�g
	pass = cgGetNextPass(pass);

	//�@�e�����ĕ`��
	cgSetPassState(pass);
	{
		//�@���b�V����`��
		mW.Identity();
		m = mW * mVP;
		cgSetMatrixParameterfr( g_hWVP, m );		//�@���[���h�r���[�ˉe�s��
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );		//�@���C�g�̃��[���h�r���[�ˉe�s��
		m = m * mScaleBias;
		cgSetMatrixParameterfr( g_hWLPB, m );	//�@�e�N�X�`����Ԃւ̎ˉe�s��
		v = g_lightPosition.xyz();
		cgSetParameter3fv( g_hLightPosition, v );	//�@���C�g�̈ʒu
		glCallList(meshListID);

		//�@�n�ʂ�`��
		mW.Identity();
		m = mW * mVP;
		cgSetMatrixParameterfr( g_hWVP, m );		//�@���[���h�r���[�ˉe�s��
		m = mW * mLP;
		cgSetMatrixParameterfr( g_hWLP, m );		//�@���C�g�̃��[���h�r���[�ˉe�s��
		m = m * mScaleBias;
		cgSetMatrixParameterfr( g_hWLPB, m );	//�@�e�N�X�`����Ԃւ̎ˉe�s��
		v = g_lightPosition.xyz();
		cgSetParameter3fv( g_hLightPosition, v );	//�@���C�g�̈ʒu
		RenderGround(5.0f, -1.0f, 5.0f);
	}
	cgResetPassState(pass);
}

//---------------------------------------------------------------------------------------------------
// Name : MouseFunc()
// Desc : �}�E�X����
//---------------------------------------------------------------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{
	g_Camera.MouseFunc(button, state, x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : MotionFunc()
// Desc : �}�E�X�h���b�O��
//-------------------------------------------------------------------------------------------------
void MotionFunc(int x, int y)
{
	g_Camera.MotionFunc(x, y);
}

//--------------------------------------------------------------------------------------------------
// Name : PassiveMotionFunc()
// Desc : �}�E�X�ړ���
//--------------------------------------------------------------------------------------------------
void PassiveMotionFunc(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
// Name : KeyboardFunc()
// Desc : �L�[�{�[�h����
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
// Desc : ����L�[����
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
// Desc : �|�b�v�A�b�v���j���[�̏���
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
// Desc : ��Еt��
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
// Desc : ASCII������̕`��
//--------------------------------------------------------------------------------------------------
void glutRenderText(void* bitmapfont, char*text)
{
	for ( int i=0; i<(int)strlen(text); i++ )
		glutBitmapCharacter(bitmapfont, (int)text[i]);
}

//--------------------------------------------------------------------------------------------------
// Name : glutToggleFullScreen()
// Desc : �t���X�N���[���ƃE�B���h�E���[�h�̐؂�ւ�
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
// Desc : FPS���擾����
//--------------------------------------------------------------------------------------------------
float glutGetFPS()
{
	Window.currCount = glutGet(GLUT_ELAPSED_TIME);
	Window.currTime = (Window.currCount - Window.prevCount)/1000.0;
	Window.frame++;

	//�@�Ō�̍X�V����̌o�ߎ��Ԃ��Z�o
	double dtime = (Window.currTime - Window.prevTime);

	//�@1�b�ȏソ������X�V
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
// Desc : Cg�G���[���`�F�b�N����
//---------------------------------------------------------------------------------------------------
void CheckCgError()
{
	CGerror lastError = cgGetError();
	if ( lastError )
	{
		cout << "Error : Cg�G���[���������܂���\n";
		cout << cgGetErrorString(lastError) << endl;
		cout << cgGetLastListing(g_Context) << endl;
		Shutdown();
	}
}

//---------------------------------------------------------------------------------------------------
// Name : InitializeCg()
// Desc : Cg�̏�����
//---------------------------------------------------------------------------------------------------
void InitializeCg()
{
	//�@�G���[�R�[���o�b�N�֐��̐ݒ�
	cgSetErrorCallback(CheckCgError);

	//�@�R���e�L�X�g���쐬
	g_Context = cgCreateContext();
	cgGLRegisterStates(g_Context);

	//�@�G�t�F�N�g���쐬
	g_Effect = cgCreateEffectFromFile(g_Context, "Shader/ShadowMap.cgfx", NULL);

	//�@�e�N�j�b�N���擾
	g_Technique = cgGetNamedTechnique(g_Effect, "Render");

	//�@�`�F�b�N
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

	//�@�p�����[�^���擾
	g_hWVP = cgGetNamedEffectParameter(g_Effect, "mWVP");
	g_hWLP = cgGetNamedEffectParameter(g_Effect, "mWLP");
	g_hWLPB = cgGetNamedEffectParameter(g_Effect, "mWLPB");
	g_hLightPosition = cgGetNamedEffectParameter(g_Effect, "vLightPosition");
	g_hShadowMap = cgGetNamedEffectParameter(g_Effect, "ShadowMapSmp");
}

//---------------------------------------------------------------------------------------------------
// Name : ShutdownCg()
// Desc : Cg�̌�Еt��
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
// Desc : �`����e���e�N�X�`���ɃR�s�[
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
