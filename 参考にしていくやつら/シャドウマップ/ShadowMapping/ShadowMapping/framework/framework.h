//---------------------------------------------------------------------------------------------------
// File : framework.h
//
// Date : May. 24, 2008
// Version : 1.0
// Author : Pocol
//---------------------------------------------------------------------------------------------------

#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#ifndef USE_GLEW
#define USE_GLEW 1
#endif
#ifndef USE_CG
#define USE_CG 1
#endif

// Disable Warning C4996
#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


//
// include
//
#include <iostream>
#if USE_GLEW
#include <GL/glew.h>
#endif
#include "framework/AsuraMath.h"
#include "framework/AsuraTexture.h"
#include "framework/AsuraMesh.h"
#include "framework/AsuraCamera.h"
#include <GL/glut.h>
#if USE_CG
#include <Cg/cgGL.h>
#endif
using namespace std;
using namespace AsuraMath;

//
// link
//
#if USE_GLEW
#pragma comment(lib, "glew32.lib")
#endif

#if USE_CG
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")
#endif

//
// define
//
#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (x) { delete x; x = NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) { if (x) { delete [] x; x = NULL; } }
#endif

//
// GLUTState struct
//
struct GLUTState
{
	Vector2i Position;
	Vector2i Size;
	Vector2i PrevPosition;
	Vector2i PrevSize;
	bool FullScreen;
	char *Title;
	char Version[50];
	char Vender[50];
	char Renderer[50];
	char FpsString[15];
	float FPS;	
	double currTime;
	double prevTime;
	double currCount;
	double prevCount;
	int frame;
};


//
// Functions
//
void Initialize();
void Render2D();
void Render3D();
void Update();
void Shutdown();
void RenderFunc();
void ReshapeFunc(int x, int y);
void IdleFunc();
void MouseFunc(int button, int state, int x, int y);
void MotionFunc(int x, int y);
void PassiveMotionFunc(int x, int y);
void KeyboardFunc(unsigned char key, int x, int y);
void SpecialFunc(int key, int x, int y);
void MenuFunc(int item);

void glutRenderText(void *bitmapFont, char *text);
void glutToggleFullScreen();
float glutGetFPS();

#if USE_GLEW
void CopyWindowToTexture(GLenum target, GLuint *handle, bool bufferClear=false);
#endif

#if USE_CG
void InitializeCg();
void ShutdownCg();
void CheckCgError();
#endif


#endif
