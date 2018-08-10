/***************************************************************************
		Mouse.h

		Mouse Function Library

		Version : 1.0
		Date : Nov. 02, 2007
		Author : Pocol
****************************************************************************/

#ifndef _MOUSE_H_INCLUDED_
#define _MOUSE_H_INCLUDED_

//
//　include
//
#include <iostream>
#include "AsuraMath.h"
using namespace std;
using namespace AsuraMath;


//
//　global
//
typedef enum MOUSE_BUTTON_STATE	{ _Push, _Release, _None };

//////////////////////////////////////////////////////////////////////////
//　　MouseButton class
//////////////////////////////////////////////////////////////////////////
class MouseButton
{
public:
	Vector2f Before;
	Vector2f Current;
	Vector2f After;
	MOUSE_BUTTON_STATE State;

	MouseButton();
	~MouseButton();
	void Reset();
};

//////////////////////////////////////////////////////////////////////////
//　　ThirdPersonCamara class
//////////////////////////////////////////////////////////////////////////
class ThirdPersonCamera
{
public:
	MouseButton Right;
	MouseButton Left;
	MouseButton Middle;

	float ZoomSpeed;
	float TranslateSpeed;

	float Distance;
	Vector3f Angle;
	Vector3f Position;
	Vector3f Target;
	Vector3f UpVector;
	Vector3f Translate;

	ThirdPersonCamera(float distance=5.0f);
	~ThirdPersonCamera();
	void Reset();
	void MouseFunc(int button, int state, int x, int y);
	void MotionFunc(int x, int y);
	void SetView();
	void Calculate();
	void RenderSubAxis(int w, int h);
};



#endif		//　_MOUSE_WIN_H_INCLUDED_
