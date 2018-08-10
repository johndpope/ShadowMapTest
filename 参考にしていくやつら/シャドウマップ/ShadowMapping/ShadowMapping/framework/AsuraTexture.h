/**************************************************************************
　　AsuraTexture.h

　　Asura Texture Loader Library

　　Date : Dec. 01, 2007
　　Version : 1.0
　　Author : Pocol
***************************************************************************/

#ifndef _ASURA_TEXTURE_H_INCLUDED_
#define _ASURA_TEXTURE_H_INCLUDED_

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

#ifndef USE_GLEW
#define USE_GLEW 0
#endif

//
//　include
//
#include <iostream>
#if USE_GLEW
#include <GL/glew.h>
#endif
#include <GL/glut.h>
using namespace std;

//
// link
//
#if USE_GLEW
#pragma comment(lib, "glew32.lib")
#endif

//
//　enum
//
typedef enum ASURA_IMAGE_FILEFORMAT
{
	ASURA_UNKOWN = -1,
	ASURA_BMP =1,
	ASURA_TGA,
#if USE_GLEW
	ASURA_DDS,
#endif
};

class AsuraRect
{
public:
	unsigned long left;
	unsigned long right;
	unsigned long top;
	unsigned long bottom;

	AsuraRect(unsigned long l=0, unsigned long r=0, unsigned long t=0, unsigned long b=0)
		{ left = l; right = r; top = t; bottom = b; }
	AsuraRect &operator= (const AsuraRect &rect)
		{ left=rect.left; right=rect.right; top=rect.top; bottom=rect.bottom; return (*this); }
};

//-------------------------------------------------------------------------------------------------------
//　　AsuraTexture class
//-------------------------------------------------------------------------------------------------------
class AsuraTexture
{
protected:
	GLuint m_handle;
	GLenum m_target;
	char m_nameA[256];
	wchar_t m_nameW[256];
	
public:
	AsuraTexture(GLenum target=GL_TEXTURE_2D);
	~AsuraTexture();
	void Delete();
	void Parameter(GLenum pname, GLint param);
	void Enviorement(GLenum pname, GLint param);
	void Enable();
	void Disable();
	void SetHandle(GLuint handle) { m_handle=handle; }
	void SetTextureTarget(GLenum target) { m_target=target; }
	void SetNameA(char name[]) { strcpy(m_nameA, name); }
	void SetNameW(wchar_t name[]) { wcscpy(m_nameW, name); }
	GLuint GetHandle() { return m_handle; }
	GLenum GetTextureTarget() { return m_target; }
	char* GetNameA() { return m_nameA; }
	wchar_t* GetNameW() { return m_nameW; }
	AsuraTexture& operator = (const AsuraTexture &texture);
	bool operator == (const AsuraTexture &texture);
	bool operator != (const AsuraTexture &texture);
};

//
//　Function
//
void AsuraCreateTextureFromFileA(char* filename, AsuraTexture& texture);
void AsuraCreateTextureFromFileW(wchar_t* filename, AsuraTexture& texture);
void AsuraCreateTexture(int width, int height, GLuint format, AsuraTexture& texture);
bool AsuraCreateImageFileA(char *filename, int width, int height, ASURA_IMAGE_FILEFORMAT format, unsigned char *pixel); 
bool AsuraCreateImageFileW(wchar_t * filename, int width, int height, ASURA_IMAGE_FILEFORMAT format, unsigned char *pixel);
bool AsuraSaveSurfaceToFileA(char *filename, AsuraRect rect, ASURA_IMAGE_FILEFORMAT format);
bool AsuraSaveSurfaceToFileW(wchar_t *filename, AsuraRect rect, ASURA_IMAGE_FILEFORMAT format);
#ifdef UNICODE
#define AsuraCreateTextureFromFile AsuraCreateTextureFromFileW
#define AsuraCrateImageFile AsuraCreateImageFileW
#define AsuraSaveSurfaceToFile AsuraSaveSurfaceToFileW
#else
#define AsuraCreateTexutreFromFile AsuraCrateTextureFromFileA
#define AsuraCrateImageFile AsuraCrateImageFileA
#define AsuraSaveSurfaceToFile AsuraSaveSurfaceToFileA
#endif
#endif	//　_ASURA_TEXTURE_H_INCLUDED_