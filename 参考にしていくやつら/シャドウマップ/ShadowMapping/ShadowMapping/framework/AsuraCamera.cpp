/*************************************************************************
�@�@Mouse.cpp
�@�@
�@�@Mouse Function Library

�@�@Version : 1.0
�@�@Date : Nov. 02, 2007
�@�@Author : Pocol
*************************************************************************/

//
//�@includes
//
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "AsuraCamera.h"
using namespace std;



//
//�@global
//
static Color4f Red(1.0f, 0.0f, 0.0f, 1.0f);
static Color4f Blue(0.0, 0.0f, 1.0f, 1.0f);
static Color4f Green(0.0f, 1.0f, 0.0f, 1.0f);
static Color4f Cyan(0.0f, 1.0f, 1.0f, 1.0f);
static Color4f Black(0.0f, 0.0f, 0.0f, 0.0f);


///////////////////////////////////////////////////////////////////////////
//�@�@MouseButton class
///////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------------
// Name : MouseButton()
// Desc : �R���X�g���N�^
//------------------------------------------------------------------------------------------------------
MouseButton::MouseButton()
{
	Reset();
}


//------------------------------------------------------------------------------------------------------
// Name : ~MouseButton()
// Desc : �f�X�g���N�^
//------------------------------------------------------------------------------------------------------
MouseButton::~MouseButton()
{
}


//------------------------------------------------------------------------------------------------------
// Name : Reset()
// Desc : ���Z�b�g����
//------------------------------------------------------------------------------------------------------
void MouseButton::Reset()
{
	Before.Zero();
	Current.Zero();
	After.Zero();
	State = _None;
}


///////////////////////////////////////////////////////////////////////////
//�@�@ThirdPersionCamera
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------------
// Name : ThirdPersonCamera()
// Desc : �R���X�g���N�^
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
// Desc : �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------
ThirdPersonCamera::~ThirdPersonCamera()
{
}

//-------------------------------------------------------------------------------------------------------
// Name : MotionFunc()
// Desc�F�}�E�X�̈ړ�����
//-------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::MotionFunc( int x, int y ) 
{
	Vector2f Pos((float)x, (float)y);

	//�@���{�^���̏���
	if ( Left.State == _Push )
	{
		//�@�ړ��ʂ��v�Z
		Left.Current = Pos - Left.Before + Left.After;

		if ( Left.Current.y >= 360.0f ) Left.Current.y -= 360.0f;
		else if ( Left.Current.y < 0.0f ) Left.Current.y += 360.0f;
		
		Angle.x = ToRadian(Angle.x + Left.Current.x);
		Angle.y = ToRadian(Angle.y + Left.Current.y);
	}

	//�@�E�{�^���̏���
	if ( Right.State == _Push )
	{
		Right.Current = Pos - Right.Before + Right.After;
	}

	//�@���{�^���̏���
	if ( Middle.State == _Push )
	{
		//�@�ړ��ʂ��v�Z
		Middle.Current = Pos - Middle.Before + Middle.After;
		Translate.x = Middle.Current.x * TranslateSpeed;
		Translate.y = Middle.Current.y * TranslateSpeed;
	}
}


//-------------------------------------------------------------------------------------------------------
// Name : MouseFunc()
// Desc�F�}�E�X�̃{�^������
//-------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::MouseFunc( int button, int state, int x, int y ) 
{
	Vector2f Pos((float)x, (float)y);
	switch( button )
	{
	//�@���{�^��
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

	//�@�E�{�^��
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

	//�@���{�^��
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
// Desc�F�p�����[�^�����Z�b�g����
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
// Desc : �~�Ղ�`�悷��
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
// Desc : ���_�̐ݒ�
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::SetView()
{
	//�@���_�̌v�Z
	Calculate();

	//�@���s�ړ�
	glTranslatef( Translate.x, Translate.y, Translate.z );

	//�@���_�ʒu�̐ݒ�
	gluLookAt(
		Position.x, Position.y, Position.z,
		Target.x, Target.y, Target.z,
		UpVector.x, UpVector.y, UpVector.z );
}

//------------------------------------------------------------------------------------------------------
// Name : Calculate()
// Desc : ���_�̐ݒ�
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::Calculate()
{
	float zoom = Distance;
	zoom += (Right.Current.y*ZoomSpeed);

	//�@���_�ʒu������
	Position.x = sinf(Angle.x) * cosf(Angle.y) * zoom;
	Position.y = sinf(Angle.y) * zoom;
	Position.z = cosf(Angle.x) * cosf(Angle.y) * zoom;

	//�@�A�b�v�x�N�g���̐ݒ�
	if( Angle.y > ToRadian(90.0f)  &&  Angle.y < ToRadian(270.0f) ) UpVector.y = -1.0f;
	else UpVector.y = 1.0f;
}

//------------------------------------------------------------------------------------------------------
// Name : RenderSubAxis()
// Desc : �⏕���̕`��
//------------------------------------------------------------------------------------------------------
void ThirdPersonCamera::RenderSubAxis(int w, int h)
{
	const float zoom = 10.0f;
	Vector3f eye;
	GLint viewport[4];
	bool isLighting = false;

	//�@�r���[�|�[�g��ۑ�
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	//�@�E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport( w-100, h-100, 100, 100);

	//�@�����ϊ��s��̐ݒ�
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0, 1, 0.1, 1000.0);

	//�@���f���r���[�ϊ��̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	eye.x = sinf(Angle.x)*cosf(Angle.y)*zoom;
	eye.y = sinf(Angle.y)*zoom;
	eye.z = cosf(Angle.x)*cosf(Angle.y)*zoom;

	//�@���_�ʒu�̐ݒ�
	gluLookAt( 
		eye.x, eye.y, eye.z,
		0.0, 0.0, 0.0,
		UpVector.x,UpVector.y, UpVector.z );

	//�@���C�e�B���O����������ꍇ
	if ( glIsEnabled(GL_LIGHTING) )
	{
		//�@���C�e�B���O������
		glDisable(GL_LIGHTING);

		//�@���C�e�B���O������������
		isLighting = true;
	}

	//�@���̕���
	glColor4fv(Black ); 
	glRasterPos3d(2.25, 0.0, 0.0);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'x');
	glRasterPos3d(0.0, 2.25, 0.0);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'y');
	glRasterPos3d(0.0, 0.0, 2.25);		
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)'z');
	
	//�@���C�e�B���O�������������ꍇ
	if ( isLighting )
	{
		//�@���C�e�B���O��L����
		glEnable(GL_LIGHTING);
	}
	

	//�@x����
	glPushMatrix();
	glColor4fv(Red);
	glTranslated(1.75, 0.0, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();	

	//�@y����
	glPushMatrix();	
	glColor4fv(Green);
	glTranslated(0.0, 1.75, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//�@z����
	glPushMatrix();
	glColor4fv(Blue);
	glTranslated(0.0, 0.0, 1.75);
	glRotated(180.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//�@�L���[�u
	glPushMatrix();
	glColor4fv(Cyan);
	glutSolidCube(1.0);
	glPopMatrix();

	//�@x����
	glPushMatrix();
	glTranslated(-1.75, 0.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//�@y����
	glPushMatrix();
	glTranslated(0.0, -1.75, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();

	//�@z����
	glPushMatrix();
	glTranslated(0.0, 0.0, -1.75);
	glutSolidCone(0.35, 1.0, 10, 10);
	drawDisk();
	glPopMatrix();	

	//�@�s���߂�
	glPopMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	//�@�r���[�|�[�g�����ɖ߂�
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

}
