/*************************************************************************
　　Mouse.cpp
　　
　　Mouse Function Library

　　Version : 1.0
　　Date : Nov. 02, 2007
　　Author : Pocol
*************************************************************************/

//
//　includes
//
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "AsuraCamera.h"
using namespace std;



//
//　global
//
static Color4f Red(1.0f, 0.0f, 0.0f, 1.0f);
static Color4f Blue(0.0, 0.0f, 1.0f, 1.0f);
static Color4f Green(0.0f, 1.0f, 0.0f, 1.0f);
static Color4f Cyan(0.0f, 1.0f, 1.0f, 1.0f);
static Color4f Black(0.0f, 0.0f, 0.0f, 0.0f);


///////////////////////////////////////////////////////////////////////////
//　　MouseButton class
///////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------------
// Name : MouseButton()
// Desc : コンストラクタ
//------------------------------------------------------------------------------------------------------
MouseButton::MouseButton()
{
	Reset();
}


//------------------------------------------------------------------------------------------------------
// Name : ~MouseButton()
// Desc : デストラクタ
//------------------------------------------------------------------------------------------------------
MouseButton::~MouseButton()
{
}


//------------------------------------------------------------------------------------------------------
// Name : Reset()
// Desc : リセットする
//------------------------------------------------------------------------------------------------------
void MouseButton::Reset()
{
	Before.Zero();
	Current.Zero();
	After.Zero();
	State = _None;
}


///////////////////////////////////////////////////////////////////////////
//　　ThirdPersionCamera
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------------
// Name : ThirdPersonCamera()
// Desc : コンストラクタ
//-------------------------------------------------------------------------------------------------------
ThirdPersonCamera::ThirdPersonCamera(float distance)
{
	Distance = distance;
	Reset();
	TranslateSpeed = 0.005f;
	ZoomSpeed = 0.03f;
}

//-------------------------------------------------------------------------------------------------------
// Name : ~ThirdPersonCamera()
// Desc : デストラクタ
//-------------------------------------------------------------------------------------------------------
ThirdPersonCamera::~ThirdPersonCamera()
{
}

//-------------------------------------------------------------------------------------------------------
// Name : MotionFunc()
// Desc：マウスの移動処理
//-------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::MotionFunc( int x, int y ) 
{
	Vector2f Pos((float)x, (float)y);

	//　左ボタンの処理
	if ( Left.State == _Push )
	{
		//　移動量を計算
		Left.Current = Pos - Left.Before + Left.After;

		if ( Left.Current.y >= 360.0f ) Left.Current.y -= 360.0f;
		else if ( Left.Current.y < 0.0f ) Left.Current.y += 360.0f;
		
		Angle.x = ToRadian(Angle.x + Left.Current.x);
		Angle.y = ToRadian(Angle.y + Left.Current.y);
	}

	//　右ボタンの処理
	if ( Right.State == _Push )
	{
		Right.Current = Pos - Right.Before + Right.After;
	}

	//　中ボタンの処理
	if ( Middle.State == _Push )
	{
		//　移動量を計算
		Middle.Current = Pos - Middle.Before + Middle.After;
		Translate.x = Middle.Current.x * TranslateSpeed;
		Translate.y = Middle.Current.y * TranslateSpeed;
	}
}


//-------------------------------------------------------------------------------------------------------
// Name : MouseFunc()
// Desc：マウスのボタン処理
//-------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::MouseFunc( int button, int state, int x, int y ) 
{
	Vector2f Pos((float)x, (float)y);
	switch( button )
	{
	//　左ボタン
	case GLUT_LEFT_BUTTON :
		if( state == GLUT_DOWN )
		{
			Left.Before = Pos;
			Left.State = _Push;
		}
		else if( state == GLUT_UP )
		{	
			Left.After = Left.Current;
			Left.State = _Release;
		}
		break;

	//　右ボタン
	case GLUT_RIGHT_BUTTON :
		if( state == GLUT_DOWN ) 
		{ 		
			Right.Before = Pos;
			Right.State = _Push;
		}
		else if( state == GLUT_UP )
		{			
			Right.After = Right.Current;
			Right.State = _Release;
		}
		break;

	//　中ボタン
	case GLUT_MIDDLE_BUTTON :
		if ( state == GLUT_DOWN )
		{
			Middle.Before = Pos;
			Middle.State = _Push;
		}
		else if ( state == GLUT_UP )
		{
			Middle.After = Middle.Current;
			Middle.State = _Release;
		}
		break;
	}

}


//------------------------------------------------------------------------------------------------------
// Name : Reset()
// Desc：パラメータをリセットする
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::Reset()
{
	Left.Reset();
	Right.Reset();
	Middle.Reset();

	Angle.x = ToRadian(45.0f);
	Angle.y= ToRadian(45.0f);
	Angle.z = 0.0f;
	Position.Zero();
	Target.Zero();
	UpVector.Up();
	Translate.Zero();

	TranslateSpeed = 0.005f;
	ZoomSpeed = 0.03f;
}
		

//------------------------------------------------------------------------------------------------------
// Name : drawDisk()
// Desc : 円盤を描画する
//------------------------------------------------------------------------------------------------------
void drawDisk()
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	glPushMatrix();
		glRotated( 180, 1.0, 0.0, 0.0 );
		gluDisk( qobj, 0.0, 0.35, 10, 10 );
	glPopMatrix();
}


//------------------------------------------------------------------------------------------------------
// Name : SetView()
// Desc : 視点の設定
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::SetView()
{
	//　視点の計算
	Calculate();

	//　平行移動
	glTranslatef( Translate.x, Translate.y, Translate.z );

	//　視点位置の設定
	gluLookAt(
		Position.x, Position.y, Position.z,
		Target.x, Target.y, Target.z,
		UpVector.x, UpVector.y, UpVector.z );
}

//------------------------------------------------------------------------------------------------------
// Name : Calculate()
// Desc : 視点の設定
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::Calculate()
{
	float zoom = Distance;
	zoom += (Right.Current.y*ZoomSpeed);

	//　視点位置を決定
	Position.x = sinf(Angle.x) * cosf(Angle.y) * zoom;
	Position.y = sinf(Angle.y) * zoom;
	Position.z = cosf(Angle.x) * cosf(Angle.y) * zoom;

	//　アップベクトルの設定
	if( Angle.y > ToRadian(90.0f)  &&  Angle.y < ToRadian(270.0f) ) UpVector.y = -1.0f;
	else UpVector.y = 1.0f;
}

//------------------------------------------------------------------------------------------------------
// Name : RenderSubAxis()
// Desc : 補助軸の描画
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::RenderSubAxis(int w, int h)
{
	const float zoom = 10.0f;
	Vector3f eye;
	GLint viewport[4];
	bool isLighting = false;

	//　ビューポートを保存
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	//　ウィンドウ全体をビューポートにする
	glViewport( w-100, h-100, 100, 100);

	//　透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0, 1, 0.1, 1000.0);

	//　モデルビュー変換の設定
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	eye.x = sinf(Angle.x)*cosf(Angle.y)*zoom;
	eye.y = sinf(Angle.y)*zoom;
	eye.z = cosf(Angle.x)*cosf(Angle.y)*zoom;

	//　視点位置の設定
	gluLookAt( 
		eye.x, eye.y, eye.z,
		0.0, 0.0, 0.0,
		UpVector.x,UpVector.y, UpVector.z );

	//　ライティング処理がある場合
	if ( glIsEnabled(GL_LIGHTING) )
	{
		//　ライティング無効化
		glDisable(GL_LIGHTING);

		//　ライティング処理があった
		isLighting = true;
	}

	//　軸の文字
	glColor4fv(Black ); 
	glRasterPos3d(2.25, 0.0, 0.0);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'x');
	glRasterPos3d(0.0, 2.25, 0.0);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'y');
	glRasterPos3d(0.0, 0.0, 2.25);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'z');
	
	//　ライティング処理があった場合
	if ( isLighting )
	{
		//　ライティングを有効化
		glEnable(GL_LIGHTING);
	}
	

	//　x軸正
	glPushMatrix();
	glColor4fv(Red);
	glTranslated(1.75, 0.0, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();	

	//　y軸正
	glPushMatrix();	
	glColor4fv(Green);
	glTranslated(0.0, 1.75, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//　z軸正
	glPushMatrix();
	glColor4fv(Blue);
	glTranslated(0.0, 0.0, 1.75);
	glRotated(180.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//　キューブ
	glPushMatrix();
	glColor4fv(Cyan);
	glutSolidCube(1.0);
	glPopMatrix();

	//　x軸負
	glPushMatrix();
	glTranslated(-1.75, 0.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//　y軸負
	glPushMatrix();
	glTranslated(0.0, -1.75, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//　z軸負
	glPushMatrix();
	glTranslated(0.0, 0.0, -1.75);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();	

	//　行列を戻す
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	//　ビューポートを元に戻す
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

}
