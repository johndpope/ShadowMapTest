//-----------------------------------------------------------------------------------------------------
// File : AsuraMath.h
//
// Asura Math Helper Library
//
// Date : Jan. 18, 2007
// Version : 2.0
// Author : Pocol
//------------------------------------------------------------------------------------------------------

#ifndef _ASURA_MATH_H_INCLUDED_
#define _ASURA_MATH_H_INCLUDED_ 

//
//　include
//
#include <iostream>
#include <cmath>

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201)

#ifndef AsuraInline
#ifdef _MSC_VER
  #if (_MSC_VER >= 1200)
  #define AsuraInline __forceinline
  #else
  #define AsuraInline __inline
  #endif
#else
  #ifdef __cplusplus
  #define AsuraInline inline
  #else
  #define AsuraInline
  #endif
#endif
#endif


#ifndef AsuraTemplate
#define AsuraTemplate template<typename T>
#endif

// defineで定義されたmaxとminは使わない
#define NOMINMAX
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace AsuraMath
{

//
//　const
//
#ifndef ASURA_MATH_PI
#define ASURA_MATH_PI
const double Pi = 3.1415926535897932384626433832795;
const double OneByPi = 0.31830988618379067153776752674503;
const double PiOver2 = 1.5707963267948966192313216916398;
const double PiOver3 = 1.0471975511965977461542144610932;
const double PiOver4 = 0.78539816339744830961566084581988;
const double PiOver6 = 0.52359877559829887307710723054658;
#endif


//
//　prototype
//
AsuraTemplate class Vector2;
AsuraTemplate class Vector3;
AsuraTemplate class Vector4;
AsuraTemplate class Matrix;
AsuraTemplate class Plane;
AsuraTemplate class Quaternion;
AsuraTemplate class Color;

//
//　typedef
//
#ifndef _DEFINE_UCHAR_
#define _DEFINE_UCHAR_
typedef unsigned char uchar;
#endif

#ifndef _DEFINE_UINT_
#define _DEFINE_UINT_
typedef unsigned int uint;
#endif

#ifndef _DEFINE_ULONG_
#define _DEFINE_ULONG_
typedef unsigned long ulong;
#endif

#ifndef _DEFINE_PSTR_
#define _DEFINE_PSTR_
typedef char* pstr;
#endif

#ifndef _DEFINE_PCSTR_
#define _DEFINE_PCSTR_
typedef const char* pcstr;
#endif

#ifndef _DEFINE_WCHAR_
#define _DEFINE_WCHAR_
typedef wchar_t wchar;
#endif

#ifndef _DEFINE_PWSTR_
#define _DEFINE_PWSTR_
typedef wchar_t* pwstr;
#endif

#ifndef _DEFINE_PCWSTR_
#define _DEFINE_PCWSTR_
typedef const wchar_t* pcwstr;
#endif

typedef Vector2<int>			Vector2i;
typedef Vector2<double>	Vector2d;
typedef Vector2<float>		Vector2f;
typedef Vector3<int>			Vector3i;
typedef Vector3<double>	Vector3d;
typedef Vector3<float>		Vector3f;
typedef Vector4<int>			Vector4i;
typedef Vector4<double>	Vector4d;
typedef Vector4<float>		Vector4f;
typedef Matrix<int>			Matrix4i;
typedef Matrix<double>	Matrix4d;
typedef Matrix<float>		Matrix4f;
typedef Plane<int>				Planei;
typedef Plane<double>		Planed;
typedef Plane<float>			Planef;
typedef Quaternion<int>		Quaternioni;
typedef Quaternion<double>	Quaterniond;
typedef Quaternion<float>	Quaternionf;
typedef Color<float>			Color4f;
typedef Color<double>		Color4d;


//////////////////////////////////////////////////////////////////////
//　　Function
//////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Name : max()
// Desc : 2つの値を比較して大きいほうの値を返す
//--------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T max(T a, T b) { return (T)(a > b ? a : b); }

//---------------------------------------------------------------------------------------------
// Name : min()
// Desc : 2つの値を比較して小さいほうの値を返す
//---------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T min(T a, T b) { return (T)(a < b ? a : b ); }

//---------------------------------------------------------------------------------------------
// Name : sign()
// Desc : 値が0なら0，プラスなら1.0，マイナスなら-1.0を返す
//---------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T sign(T x) { if(x==0.0) return (T)0.0; else if(x>0.0) return (T)1.0; return (T)-1.0; }

//----------------------------------------------------------------------------------------------
// Name : clamp()
// Desc : xの値をaからbの範囲に制限する
//----------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T clamp(T x, T a, T b) { return (T) Asura::max(a, Asura::min(b, x)); }

//-------------------------------------------------------------------------------------------------
// Name : ToDegree()
// Desc : ラジアンから度数に値を変換して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T ToDegree(T rad) { return (T)((double)(rad)*(180.0/Pi)); }

//-------------------------------------------------------------------------------------------------
// Name : ToRadian()
// Desc : 度数からラジアンに値を変換して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T ToRadian(T deg) { return (T)((double)(deg)*(Pi/180.0)); }

//-------------------------------------------------------------------------------------------------
// Name : sec()
// Desc : xのセカントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T sec(T x) { return (T)(1.0/cos( (double)x ) ); }

//-------------------------------------------------------------------------------------------------
// Name : csc()
// Desc : xのコセカントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T csc(T x) { return (T)(1.0/sin( (double)x) ); }

//-------------------------------------------------------------------------------------------------
// Name : cot()
// Desc : xのコタンジェントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T cot(T x) { return (T)(1.0/tan( (double)x) ); }

//-------------------------------------------------------------------------------------------------
// Name : asec()
// Desc : xのアークセカントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T asec(T x) { return (T)(2.0*atan(1.0) - atan(Asura::sign( (double)x )/sqrt( (double)x*(double)x-1.0) ) ); }

//-------------------------------------------------------------------------------------------------
// Name : acsc()
// Desc : xのアークコセカントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T acsc(T x) { return (T)(atan(Asura::sign( (double)x )/sqrt( (double)x*(double)x-1.0 ) ) ); }

//-------------------------------------------------------------------------------------------------
// Name : acot()
// Desc : xのアークコタンジェントの値を計算して返す
//-------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T acot(T x) { return (T)(2.0*atan(1.0) - atan( (double)x) ); }

//--------------------------------------------------------------------------------------------------
// Name : sech()
// Desc : xのハイパボリックセカントの値を計算して返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T sech(T x) { return (T)(2.0/(exp( (double)x )+exp( (double)-x) ) ); }

//--------------------------------------------------------------------------------------------------
// Name : csch()
// Desc : xのハイパボリックコカントの値を計算して返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T csch(T x) { return (T)(2.0/(exp( (double)x )-exp( (double)-x ) ) ); }

//--------------------------------------------------------------------------------------------------
// Name : coth()
// Desc : xのハイパボリックタンジェントの値を計算して返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T coth(T x) { return (T)( (exp( (double)x )+exp( (double)-x ))/(exp( (double)x )-exp( (double)-x ) ) ); }

//--------------------------------------------------------------------------------------------------
// Name : asinh()
// Desc : xのハイパボリックアークサインの値を計算して返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T asinh(T x) { return (T)(log( (double)x + sqrt( (double)x*(double)x + 1.0 ) ) ); }

//--------------------------------------------------------------------------------------------------
// Name : acosh()
// Desc : xのハイパボリックアークコサインの値を計算して返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T acosh(T x) { return (T)(log((double)x+sqrt((double)x*(double)x-1.0))); }

//---------------------------------------------------------------------------------------------------
// Name : atanh()
// Desc : xのハイパボリックアークタンジェントの値を計算して返す
//---------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T atanh(T x) { return (T)(log((1.0+(double)x)/(1.0-(double)x))/2.0); }

//---------------------------------------------------------------------------------------------------
// Name : asech()
// Desc : xのハイパボリックアークセカントの値を計算して返す
//---------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T asech(T x) { return (T)(log((sqrt(-(double)x*(double)x+1.0)+1.0)/(double)x)); }

//----------------------------------------------------------------------------------------------------
// Name : acsch()
// Desc : xのハイパボリックアークコセカントの値を計算して返す
//----------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T acsch(T x) { return (T)(log((Asura::sign((double)x)*sqrt((double)x*(double)x+1.0)+1.0)/(double)x)); }

//----------------------------------------------------------------------------------------------------
// Name : acoth()
// Desc : xのハイパボリックアークコタンジェントの値を計算して返す
//----------------------------------------------------------------------------------------------------
AsuraTemplate static AsuraInline T acoth(T x) { return (T)(log(((double)x+1.0)/(double)x-1.0)/2.0); }


/////////////////////////////////////////////////////////////////////
//　　Vector2 class
/////////////////////////////////////////////////////////////////////
AsuraTemplate
class Vector2
{
public:
	union{ struct{ T x, y; }; T v[2]; };
	Vector2<T> (T nx=0, T ny=0) : x(nx), y(ny) {}
	Vector2<T> (const Vector2<T> &vec) : x(vec.x), y(vec.y) {}
	Vector2<T> (const Vector2<T> &a, const Vector2<T> &b) : x(a.x - b.x), y(a.y - b.y) {}
	Vector2<T> (const T *v) : x(v[0]), y(v[1]) {}
	operator T * ();
	operator const T* () const;
	Vector2<T> &operator= (const Vector2<T> &vec);
	Vector2<T> &operator= (const T &s);
	bool operator == (const Vector2<T> &vec)const;
	bool operator != (const Vector2<T> &vec)const;
	bool operator > (const Vector2<T> &vec)const;
	bool operator < (const Vector2<T> &vec)const;
	bool operator >= (const Vector2<T> &vec)const;
	bool operator <= (const Vector2<T> &vec)const;
	Vector2<T> operator+ (const Vector2<T> &vec)const;
	Vector2<T> operator- (const Vector2<T> &vec) const;
	Vector2<T> operator+() const;
	Vector2<T> operator-() const;
	Vector2<T> &operator+= (const Vector2<T> &vec);
	Vector2<T> &operator-= (const Vector2<T> &vec);
	Vector2<T> &operator*= (const T s);
	Vector2<T> &operator/= (const T s);
	Vector2<T> operator* (const T s)const;
	Vector2<T> operator/ (const T s)const;
	Vector2<T> operator* (const Vector2<T> &vec)const;
	Vector2<T> UnitVector() const;
	T Dot(const Vector2<T> &vec) const;
	T Length() const;
	T LengthSquared() const;
	void Normalize();
	Vector2<T> One();
	Vector2<T> Zero();
	Vector2<T> UnitX();	// (1.0, 0.0)
	Vector2<T> UnitY();	// (0.0, 1.0);
	void ConsoleOut();
	friend Vector2<T> operator * ( T s, const Vector2<T> &vec){ return Vector2<T>(s*vec.x, s*vec.y); }
};

/////////////////////////////////////////////////////////////////////
//　　Vector3 class
/////////////////////////////////////////////////////////////////////
AsuraTemplate
class Vector3
{
public:
	union{ struct{ T x, y, z; }; T v[3]; };
	Vector3<T> (T nx=0.0, T ny=0.0, T nz=0.0) : x(nx), y(ny), z(nz) {}
	Vector3<T> (const Vector2<T> &vec, T nz) : x(vec.x), y(vec.y), z(nz) {}
	Vector3<T> (const Vector3<T> &vec) : x(vec.x), y(vec.y), z(vec.z) {}
	Vector3<T> (const Vector3<T> &a, const Vector3<T> &b) : x(a.x - b.x), y(a.y - b.y), z(a.z - b.z) {}
	Vector3<T> (const T *v) : x(v[0]), y(v[1]), z(v[2]) {}
	operator T * ();
	operator const T* () const;
	Vector3<T> &operator= (const Vector3<T> &vec);
	Vector3<T> &operator= (const T &s);
	bool operator== (const Vector3<T> &vec)const;
	bool operator!= (const Vector3<T> &vec)const;
	bool operator> (const Vector3<T> &vec)const;
	bool operator< (const Vector3<T> &vec)const;
	bool operator>= (const Vector3<T> &vec)const;
	bool operator<= (const Vector3<T> &vec)const;
	Vector3<T> operator+ (const Vector3<T> &vec)const;
	Vector3<T> operator+() const;
	Vector3<T> &operator+= (const Vector3<T> &vec);
	Vector3<T> operator- (const Vector3<T> &vec)const;
	Vector3<T> operator-() const;
	Vector3<T> &operator-= (const Vector3<T> &vec);
	Vector3<T> &operator*= (const T s);
	Vector3<T> &operator/= (const T s);
	Vector3<T> operator* (const T s)const;
	Vector3<T> operator/ (const T s)const;
	Vector3<T> operator* (const Vector3<T> &vec) const;
	Vector3<T> Cross(const Vector3<T> &vec) const; 
	Vector3<T> UnitVector() const; 
	T Dot(const Vector3<T> &vec) const;
	T Length() const;
	T LengthSquared() const;
	void Normalize();
	Vector2<T> xy();
	Vector3<T> One();
	Vector3<T> Zero();
	Vector3<T> UnitX();	// (1.0, 0.0, 0.0)
	Vector3<T> UnitY();	// (0.0, 1.0, 0.0)
	Vector3<T> UnitZ();	// (0.0, 0.0, 1.0)
	Vector3<T> Forward();
	Vector3<T> Backward();
	Vector3<T> Up();
	Vector3<T> Down();
	Vector3<T> Left();
	Vector3<T> Right();
	void ConsoleOut();
	Color<T> ToColor() { return Color<T>(x, y, z, 1.0); }
	friend Vector3<T> operator * ( T s, const Vector3<T> &vec) { return Vector3<T>(s*vec.x, s*vec.y, s*vec.z); }
};


/////////////////////////////////////////////////////////////////////
//　　Vector4 class
/////////////////////////////////////////////////////////////////////
AsuraTemplate
class Vector4
{
public:
	union{ struct{ T x, y, z, w; }; T v[4]; };
	Vector4<T> (T nx=0.0, T ny=0.0, T nz=0.0, T nw=0.0) : x(nx), y(ny), z(nz), w(nw) {}
	Vector4<T> (const Vector2<T> &vec, T nz, T nw) : x(vec.x), y(vec.y), z(nz), w(nw) {}
	Vector4<T> (const Vector3<T> &vec, T nw) : x(vec.x), y(vec.y), z(vec.z), w(nw) {}
	Vector4<T> (const Vector4<T> &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	Vector4<T> (const Vector4<T> &a, const Vector4<T> &b) : x(a.x - b.x), y(a.y - b.y), z(a.z - b.z), w(a.w - b.w) {}
	Vector4<T> (const T *v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}
	operator T * ();
	operator const T* () const;
	Vector4<T> &operator= (const Vector4<T> &vec);
	Vector4<T> &operator= (const T &s);
	bool operator== (const Vector4<T> &vec)const;
	bool operator!= (const Vector4<T> &vec)const;
	bool operator> (const Vector4<T> &vec)const;
	bool operator< (const Vector4<T> &vec)const;
	bool operator>= (const Vector4<T> &vec)const;
	bool operator <= (const Vector4<T> &vec)const;
	Vector4<T> operator+ (const Vector4<T> &vec)const;
	Vector4<T> operator+() const;
	Vector4<T> &operator+= (const Vector4<T> &vec);
	Vector4<T> operator- (const Vector4<T> &vec)const;
	Vector4<T> operator-() const;
	Vector4<T> &operator-= (const Vector4<T> &vec);
	Vector4<T> &operator*= (const T s);
	Vector4<T> &operator/= (const T s);
	Vector4<T> operator* (const T s)const;
	Vector4<T> operator/ (const T s)const;
	Vector4<T> operator* (const Vector4<T> &vec)const;
	Vector4<T> UnitVector() const;
	T Dot(const Vector4<T> &vec) const;
	T Length() const;
	T LengthSquared() const;
	void Normalize();
	Vector2<T> xy();
	Vector3<T> xyz();
	Vector4<T> One();
	Vector4<T> Zero();
	Vector4<T> UnitX();	// (1.0, 0.0, 0.0, 0.0)
	Vector4<T> UnitY();	// (0.0, 1.0, 0.0, 0.0)
	Vector4<T> UnitZ();	// (0.0, 0.0, 1.0, 0.0)
	Vector4<T> UnitW();	// (0.0, 0.0, 0.0, 1.0)
	void ConsoleOut();
	Color<T> ToColor() { return Color<T>(x, y, z, w); }
	friend Vector4<T> operator * ( T s, const Vector4<T> &vec) { return Vector4<T>(s*vec.x, s*vec.y, s*vec.z, s*vec.w); }
};

//////////////////////////////////////////////////////////////////////
//　　Vector function
/////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Name : Clamp()
// Desc : vの値をminiからmaxiの範囲に制限する
//-------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Clamp(Vector2<T> v, Vector2<T> min, Vector2<T> max);
AsuraTemplate Vector3<T> Clamp(Vector3<T> v, Vector3<T> min, Vector3<T> max);
AsuraTemplate Vector4<T> Clamp(Vector4<T> v, Vector4<T> min, Vector4<T> max);
AsuraTemplate void Clamp(Vector2<T> &v, Vector2<T> &min, Vector2<T> &max, Vector2<T> &result);
AsuraTemplate void Clamp(Vector3<T> &v, Vector3<T> &min, Vector3<T> &max, Vector3<T> &result);
AsuraTemplate void Clamp(Vector4<T> &v, Vector4<T> &min, Vector4<T> &max, Vector4<T> &result);

//-------------------------------------------------------------------------------------------------
// Name : Distance()
// Desc : v1とv2の間の距離を求める
//-------------------------------------------------------------------------------------------------
AsuraTemplate T Distance(Vector2<T> v1, Vector2<T> v2);
AsuraTemplate T Distance(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate T Distance(Vector4<T> v1, Vector4<T> v2);
AsuraTemplate void Distance(Vector2<T> &v1, Vector2<T> &v2, T &result);
AsuraTemplate void Distance(Vector3<T> &v1, Vector3<T> &v2, T &result);
AsuraTemplate void Distance(Vector4<T> &V1, Vector4<T> &v2, T &result);

//-------------------------------------------------------------------------------------------------
// Name : DistanceSquared()
// Desc : v1とv2の間の距離の2乗を求める
//-------------------------------------------------------------------------------------------------
AsuraTemplate T DistanceSquared(Vector2<T> v1, Vector2<T> v2);
AsuraTemplate T DistanceSquared(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate T DistanceSquared(Vector4<T> v1, Vector4<T> v2);
AsuraTemplate void DistanceSquared(Vector2<T> &v1, Vector2<T> &v2, T &result);
AsuraTemplate void DistanceSquared(Vector3<T> &v1, Vector3<T> &v2, T &reslut);
AsuraTemplate void DistanceSquared(Vector4<T> &v1, Vector4<T> &v2, T &result);

//--------------------------------------------------------------------------------------------------
// Name : Dot()
// Desc : v1とv2の内積を求める
//--------------------------------------------------------------------------------------------------
AsuraTemplate T Dot(Vector2<T> v1, Vector2<T> v2);
AsuraTemplate T Dot(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate T Dot(Vector4<T> v1, Vector4<T> v2);
AsuraTemplate void Dot(Vector2<T> &v1, Vector2<T> &v2, T &result);
AsuraTemplate void Dot(Vector3<T> &v1, Vector3<T> &v2, T &result);
AsuraTemplate void Dot(Vector4<T> &v1, Vector4<T> &v2, T &result);

//--------------------------------------------------------------------------------------------------
// Name : Cross()
// Desc : v1とv2の外積を求める
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector3<T> Cross(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate void Cross(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result);
	
//--------------------------------------------------------------------------------------------------
// Name : Normalize()
// Desc : vを正規化する
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Normalize(Vector2<T> v);
AsuraTemplate Vector3<T> Normalize(Vector3<T> v);
AsuraTemplate Vector4<T> Normalize(Vector4<T> v);
AsuraTemplate void Normalize(Vector2<T> &v, Vector2<T> &result);
AsuraTemplate void Normalize(Vector3<T> &v, Vector3<T> &result);
AsuraTemplate void Normalize(Vector4<T> &v, Vector4<T> &result);

//-------------------------------------------------------------------------------------------------
// Name : GetNormal()
// Desc : v1, v2, v3からなる三角形の法線ベクトルを求める
//-------------------------------------------------------------------------------------------------
AsuraTemplate Vector3<T> GetNormal(Vector3<T> v1, Vector3<T> v2, Vector3<T> v3);
AsuraTemplate void GetNormal(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, Vector3<T> &result);

//-------------------------------------------------------------------------------------------------
// Name : GetQuadNormal()
// Desc : v1, v2, v3, v4からなる四角形の法線ベクトルを求める
//-------------------------------------------------------------------------------------------------
AsuraTemplate Vector3<T> GetQuadNormal(Vector3<T> v1, Vector3<T> v2, Vector3<T> v3, Vector3<T> v4);
AsuraTemplate void GetQuadNormal(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, Vector3<T> &v4, Vector3<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Min()
// Desc : v1とv2の成分を比較し各成分の最小値をベクトルとして出力する
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Min(Vector2<T> v1, Vector2<T> v2);
AsuraTemplate Vector3<T> Min(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate Vector4<T> Min(Vector4<T> v1, Vector4<T> v2);
AsuraTemplate void Min(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &result);
AsuraTemplate void Min(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result);
AsuraTemplate void Min(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Max()
// Desc : v1とv2の成分を比較し各成分の最大値をベクトルとして出力する
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Max(Vector2<T> v1, Vector2<T> v2);
AsuraTemplate Vector3<T> Max(Vector3<T> v1, Vector3<T> v2);
AsuraTemplate Vector4<T> Max(Vector4<T> v1, Vector4<T> v2);
AsuraTemplate void Max(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &result);
AsuraTemplate void Max(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result);
AsuraTemplate void Max(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Reflect()
// Desc : 入射方向i，面法線nとし，計算によって求められた反射ベクトルを返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Reflect(Vector2<T> i, Vector2<T> n);
AsuraTemplate Vector3<T> Reflect(Vector3<T> i, Vector3<T> n);
AsuraTemplate void Reflect(Vector2<T> &i, Vector2<T> &n, Vector2<T> &result);
AsuraTemplate void Reflect(Vector3<T> &i, Vector3<T> &n, Vector3<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Refract()
// Desc : 入射方向i，面法線n，屈折係数etaとし，計算によって求められた屈折ベクトルを返す
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector3<T> Refract(Vector3<T> i, Vector3<T> n, Vector3<T> eta);
AsuraTemplate void Refract(Vector3<T> &i, Vector3<T> &n, Vector3<T> &eta, Vector3<T> &result);

//---------------------------------------------------------------------------------------------------
// Name : Barycentric()
// Desc : 指定したベクトルを使って，重心座標での点を返す
// Param : f, g　加重係数
//---------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Barycentric(Vector2<T> v1, Vector2<T> v2, Vector2<T> v3, T f, T g);
AsuraTemplate Vector3<T> Barycentric(Vector3<T> v1, Vector3<T> v2, Vector3<T> v3, T f, T g);
AsuraTemplate Vector4<T> Barycentric(Vector4<T> v1, Vector4<T> v2, Vector4<T> v3, T f, T g);
AsuraTemplate void Barycentric(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &v3, T f, T g, Vector2<T> &result);
AsuraTemplate void Barycentric(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, T f, T g, Vector3<T> &result);
AsuraTemplate void Barycentric(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &v3, T f, T g, Vector4<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Lerp()
// Desc : 線形補間を行う
// Param : t　加重係数　
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Lerp(Vector2<T> v1, Vector2<T> v2, T t);
AsuraTemplate Vector3<T> Lerp(Vector3<T> v1, Vector3<T> v2, T t);
AsuraTemplate Vector4<T> Lerp(Vector4<T> v1, Vector4<T> v2, T t);
AsuraTemplate void Lerp(Vector2<T> &v1, Vector2<T> &v2, T t, Vector2<T> &result);
AsuraTemplate void Lerp(Vector3<T> &v1, Vector3<T> &v2, T t, Vector3<T> &result);
AsuraTemplate void Lerp(Vector4<T> &v1, Vector4<T> &v2, T t, Vector4<T> &result);

//---------------------------------------------------------------------------------------------------
// Name : Hermite()
// Desc : 指定されたベクトルを使ってエルミートのスプライン補間を行う
// Param : v1, v2　位置ベクトル
//             t1, t2　接線ベクトル
//　　　s　加重係数
//---------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Hermite(
	Vector2<T> v1, Vector2<T> t1,
	Vector2<T> v2, Vector2<T> t2, T s);
AsuraTemplate Vector3<T> Hermite(
	Vector3<T> v1, Vector3<T> t1,
	Vector3<T> v2, Vector3<T> t2, T s);
AsuraTemplate Vector4<T> Hermite(
	Vector4<T> v1, Vector4<T> t1,
	Vector4<T> v2, Vector4<T> t2, T s);	
AsuraTemplate void Hermite(
   Vector2<T> &v1, Vector2<T> &t1,
   Vector2<T> &v2, Vector2<T> &t2, T s, Vector2<T> &result);
AsuraTemplate void Hermite(
   Vector3<T> &v1, Vector3<T> &t1,
   Vector3<T> &v2, Vector3<T> &t2, T s, Vector3<T> &result);
AsuraTemplate void Hermite(
	Vector4<T> &v1, Vector4<T> &t1,
	Vector4<T> &v2, Vector4<T> &t2, T s, Vector4<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : CatmullRom()
// Desc : 指定されたベクトルを使ってCatmull-Rom補間を行う
// Param : v1, v2, v3, v4　位置ベクトル
//             s　加重係数
//----------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> CatmullRom(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T s);
AsuraTemplate Vector3<T> CatmullRom(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T s);
AsuraTemplate Vector4<T> CatmullRom(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T s);
AsuraTemplate void CatmullRom(
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T s, Vector2<T> &result);
AsuraTemplate void CatmullRom(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T s, Vector3<T> &result);
AsuraTemplate void CatmullRom(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T s, Vector4<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : Bezier()
// Desc : 指定されたベクトルを使ってベジエ補間を行う
// Param : v0, v1, v2, v3　制御点の位置ベクトル
//             t　加重係数
//----------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Bezier(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T t);
AsuraTemplate Vector3<T> Bezier(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T t);
AsuraTemplate Vector4<T> Bezier(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T t);
AsuraTemplate void Bezier(	
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T t, Vector2<T> &result);
AsuraTemplate void Bezier(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T t, Vector3<T> &result);
AsuraTemplate void Bezier(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T t, Vector4<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : B_Spline()
// Desc : 指定されたベクトルを使ってBスプライン補間を行う
// Param : v0, v1, v2, v3　位置ベクトル
//             t　加重係数
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> B_Spline(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T t);
AsuraTemplate Vector3<T> B_Spline(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T t);
AsuraTemplate Vector4<T> B_Spline(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T t);
AsuraTemplate void B_Spline(
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T t, Vector2<T> &result);
AsuraTemplate void B_Spline(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T t, Vector3<T> &result);
AsuraTemplate void B_Spline(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T t, Vector4<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : SmoothStep()
// Desc :
//---------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> SmoothStep(Vector2<T> value1, Vector2<T> value2, T amount);
AsuraTemplate Vector3<T> SmoothStep(Vector3<T> value1, Vector3<T> value2, T amount);
AsuraTemplate Vector4<T> SmoothStep(Vector4<T> value1, Vector4<T> value2, T amount);
AsuraTemplate void SmoothStep(Vector2<T> &value1, Vector2<T> &value2, T amount, Vector2<T> &result);
AsuraTemplate void SmoothStep(Vector3<T> &value1, Vector3<T> &value2, T amount, Vector3<T> &result);
AsuraTemplate void SmoothStep(Vector4<T> &value1, Vector4<T> &value2, T amount, Vector4<T> &result);

//--------------------------------------------------------------------------------------------------
// Name : Transform()
// Desc :
//--------------------------------------------------------------------------------------------------
AsuraTemplate Vector2<T> Transform(Vector2<T> position, Matrix<T> matrix);
AsuraTemplate Vector3<T> Transform(Vector3<T> position, Matrix<T> matrix);
AsuraTemplate Vector4<T> Transform(Vector4<T> position, Matrix<T> matrix);
AsuraTemplate void Transform(Vector2<T> &position, Matrix<T> &matrix, Vector2<T> &result);
AsuraTemplate void Transform(Vector3<T> &position, Matrix<T> &matrix, Vector3<T> &result);
AsuraTemplate void Transform(Vector4<T> &position, Matrix<T> &matrix, Vector4<T> &result);
AsuraTemplate Vector2<T> TransformNormal(Vector2<T> normal, Matrix<T> matrix);
AsuraTemplate Vector3<T> TransformNormal(Vector3<T> normal, Matrix<T> matrix);
AsuraTemplate void TransformNormal(Vector2<T> &normal, Matrix<T> &matrix, Vector2<T> &result);
AsuraTemplate void TransformNormal(Vector3<T> &normal, Matrix<T> &matrix, Vector3<T> &result);

//////////////////////////////////////////////////////////////////////
//　　AsuraMatrix
//////////////////////////////////////////////////////////////////////
AsuraTemplate 
class Matrix
{
public:
	union 
	{
		struct 
		{
			T	_11, _12, _13, _14;
			T	_21, _22, _23, _24;
			T	_31, _32, _33, _34;
			T	_41, _42, _43, _44;
		};
		T m[4][4];
	};

	Matrix();
	Matrix(const T* m);
	Matrix(const Matrix<T> &mat);
	Matrix(T m11, T m12, T m13, T m14,
		T m21, T m22, T m23, T m24,
		T m31, T m32, T m33, T m34,
		T m41, T m42, T m43, T m44 );
	T& operator() (unsigned int row, unsigned int col);
	T operator() (unsigned int row, unsigned int col) const;
	operator T*();
	operator const T*() const;
	Matrix<T>& operator = (const Matrix<T> &mat);
	Matrix<T>& operator *= (const Matrix<T> &mat);
	Matrix<T>& operator += (const Matrix<T> &mat);
	Matrix<T>& operator -= (const Matrix<T> &mat);
	Matrix<T>& operator *= (T t);
	Matrix<T>& operator /= (T t);
	Matrix<T> operator + () const;
	Matrix<T> operator - () const;
	Matrix<T> operator * (const Matrix<T> &mat) const;
	Matrix<T> operator + (const Matrix<T> &mat) const;
	Matrix<T> operator - (const Matrix<T> &mat) const;
	Matrix<T> operator * (T t) const;
	Matrix<T> operator / (T t) const;
	Vector4<T> operator* (const Vector4<T> &vec) const;
	bool operator == (const Matrix<T> &mat) const;
	bool operator !=  (const Matrix<T> &mat) const;
	void Identity();
	void Zero();
	void One();
	T Determinant();

	Vector4<T> _11_12_13_14();
	Vector4<T> _21_22_23_24();
	Vector4<T> _31_32_33_34();
	Vector4<T> _41_42_43_44();

	Vector4<T> _11_21_31_41();
	Vector4<T> _12_22_32_42();
	Vector4<T> _13_23_33_43();
	Vector4<T> _14_24_34_44();
	
	void ConsoleOut();

	friend Matrix<T> operator *(T s, const Matrix<T> &mat)
	{
		return Matrix<T>(
			s*mat._11, s*mat._12, s*mat._13, s*mat._14,
			s*mat._21, s*mat._22, s*mat._23, s*mat._24,
			s*mat._31, s*mat._32, s*mat._33, s*mat._34,
			s*mat._41, s*mat._42, s*mat._43, s*mat._44);
	}
};

//////////////////////////////////////////////////////////////////////////
//　　Matrix Functions
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
// Name : Transpose()
// Desc : 行列を転置する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> Transpose(Matrix<T> value);
AsuraTemplate void Transpose(Matrix<T> &value, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : Multiply()
// Desc : 行列の積を計算する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> Multiply(Matrix<T> value1, Matrix<T> value2);
AsuraTemplate void Multiply(Matrix<T> &value1, Matrix<T> &value2, Matrix<T> &result);
AsuraTemplate Matrix<T> Multiply(Matrix<T> value, T scaleFactor);
AsuraTemplate void Multiply(Matrix<T> &value, T scaleFactor, Matrix<T> &result);

//------------------------------------------------------------------------------------------------------
// Name : MultiplyTranspose()
// Desc : 2つの行列の積の転置を計算する
//------------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> MultiplyTranspose(Matrix<T> value1, Matrix<T> value2);
AsuraTemplate void MultiplyTranspose(Matrix<T> &value1, Matrix<T> &value2, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : Invert()
// Desc : 逆行列を計算する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> Invert(Matrix<T> value);
AsuraTemplate void Invert(Matrix<T> &value, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateFromQuaternion()
// Desc : 四元数から行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateFromQuaternion(Quaternion<T> qua);
AsuraTemplate void CreateFromQuaternion(Quaternion<T> &qua, Matrix<T> &result);
	
//-----------------------------------------------------------------------------------------------------
// Name : CreateScale()
// Desc : 拡大行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateScale(T scale);
AsuraTemplate void CreateSacle(T scale, Matrix<T> &result);
AsuraTemplate Matrix<T> CreateScale(T xScale, T yScale, T zScale);
AsuraTemplate void CreateScale(T xScale, T yScale, T zScale, Matrix<T> &result);
AsuraTemplate Matrix<T> CreateScale(Vector3<T> scales);
AsuraTemplate void CreateScale(Vector3<T> &scales, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateTranslation()
// Desc : オフセットを指定して行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateTranslation(T xPosition, T yPosition, T zPosition);
AsuraTemplate void CreateTranslation(T xPosition, T yPosition, T zPosition, Matrix<T> &result);
AsuraTemplate Matrix<T> CreateTranslation(Vector3<T> position);
AsuraTemplate void CreateTranslation(Vector3<T> &position, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateRotationX()
// Desc : x軸を回転軸にして回転する行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateRotationX(T radians);
AsuraTemplate void CreateRotationX(T radians, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateRoataionY()
// Desc : y軸を回転軸にして回転する行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateRotationY(T radians);
AsuraTemplate void CreateRotationY(T radians, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateRotationZ()
// Desc : z軸を回転軸にして回転する行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateRotationZ(T radians);
AsuraTemplate void CreateRotationZ(T radians, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateFromAxisAngle()
// Desc : 任意軸を回転軸にして回転する行列を作成する
// Param : angle　回転角度(ラジアン単位)
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateFromAxisAngle(Vector3<T> axis, T radians);
AsuraTemplate void CreateFromAxisAngle(Vector3<T> &axis, T radians, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateLookAt()
// Desc : 右手座標系ビュー行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateLookAt(Vector3<T> cameraPosition, Vector3<T> cameraTarget, Vector3<T> caneraUpVector);
AsuraTemplate void CreateLookAt(Vector3<T> &cameraPosition, Vector3<T> &cameraTarget, Vector3<T> &cameraUpVector, Vector3<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : CreatePerspective()
// Desc : 右手座標系遠近射影行列を作成する
//----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreatePerspective(T width, T height, T nearPlaneDistance, T farPlaneDistance);
AsuraTemplate void CreatePerspective(T width, T height, T nearPlaneDistance, T farPlaneDistance, Matrix<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : CreatePerspectiveFiledOfView()
// Desc : 視野に基づいて右手座標系遠近射影行列を作成する
//----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreatePerspectiveFieldOfView(T fieldOfView, T aspectRatio, T nearPlaneDistance, T farPlaneDistance);
AsuraTemplate void CreatePerspectiveFieldOfView(T fieldOfView, T apectRatio, T nearPlaneDistance, T farPlaneDistance, Matrix<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : CreatePerspectiveOffcenter()
// Desc : カスタマイズした右手座標系遠近射影行列を作成する
//----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreatePerspectiveOffcenter(T left, T right, T bottom, T top, T nearPlaneDistance, T farPlaneDistance);
AsuraTemplate void CreatePerspectiveOffcenter(T left, T right, T bottom, T top, T nearPlaenDistance, T farPlaenDistance, Matrix<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : CreateOrthographic()
// Desc : 右手座標系正射影行列を作成する
//----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateOrthographic(T width, T height, T zNearPlane, T zFarPlane);
AsuraTemplate void CreateOrthographic(T width, T height, T zNearPlane, T zFarPlane, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateOrthograhicOffcenter()
// Desc : カスタマイズした右手座標系正射影行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateOrthographicOffcenter(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane);
AsuraTemplate void CreateOrthographicOffcenter(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateShadow()
// Desc : ジオメトリを平面に射影する行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateShadow(Vector3<T> lightDirection, Plane<T> plane);
AsuraTemplate void CreateShadow(Vector3<T> &lightDirection, Plane<T> &plane, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : CreateReflect()
// Desc : 平面に対して座標系を反転した行列を作成する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> CreateReflection(Plane<T> plane);
AsuraTemplate void CreateReflection(Plane<T> &plane, Matrix<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : Lerp()
// Desc : 2つの行列を線形補間する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> Lerp(Matrix<T> value1, Matrix<T> value2, T amount);
AsuraTemplate void Lerp(Matrix<T> &value1, Matrix<T> &value2, T amount, Matrix<T> &result);

////////////////////////////////////////////////////////////////////////////
//　　Plane
////////////////////////////////////////////////////////////////////////////
AsuraTemplate 
class Plane
{
public:
	T a, b, c, d;
	Plane<T>(T na=0.0, T nb=0.0, T nc=0.0, T nd=0.0) : a(na), b(nb), c(nc), d(nd) {}
	Plane<T>(Vector3<T> normal, T nd) : a(normal.x), b(normal.y), c(normal.z), d(nd) {}
	Plane<T>(Vector3<T> position1, Vector3<T> position2, Vector3<T> position3);
	Plane<T>(Vector4<T> value ) : a(value.x), b(value.y), c(value.z), d(value.w) {}
	Plane<T>(const T *pf);
	operator T* ();
	operator const T*() const;
	Plane<T>& operator = (const Plane<T> &p);
	Plane<T>& operator *= (T f);
	Plane<T>& operator /= (T f);
	Plane<T> operator + () const;
	Plane<T> operator - () const;
	Plane<T> operator * (T f)const;
	Plane<T> operator / (T f)const;
	friend Plane<T> operator * ( T , const Plane<T> &);
	bool operator == (const Plane<T> &) const;
	bool operator != (const Plane<T> & ) const;
	Vector3<T> abc();
	Vector4<T> ToVector4();
	void Normalize();
	Plane<T> Zero();
	Plane<T> One();
	void ConsoleOut();
};

////////////////////////////////////////////////////////////////////////////
//　　Plane Function
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------
// Name : Dot()
// Desc : 平面と4次元ベクトルの内積を計算する
//--------------------------------------------------------------------------------------------------------
AsuraTemplate T Dot(Plane<T> p, Vector4<T> v);
AsuraTemplate void Dot(Plane<T> &p, Vector4<T> &v, T &result);

//---------------------------------------------------------------------------------------------------------
// Name : DotCoordinate()
// Desc : 平面と3次元ベクトルの内積を計算する。w成分の値は1とみなす
//---------------------------------------------------------------------------------------------------------
AsuraTemplate T DotCoordinate(Plane<T> p, Vector3<T> v);
AsuraTemplate void DotCoordinate(Plane<T> &p, Vector3<T> &v, T &result);

//--------------------------------------------------------------------------------------------------------
// Name : DotNormal()
// Desc : 平面と3次元ベクトルの内積を計算する。w成分の値は0とみなす
//--------------------------------------------------------------------------------------------------------
AsuraTemplate T DotNormal(Plane<T> p, Vector3<T> v);
AsuraTemplate void DotNormal(Plane<T> &p, Vector3<T> &v, T &result);

//-------------------------------------------------------------------------------------------------------
// Name : Normalize()
// Desc : 平面の係数を正規化して，平面の法線の長さを正規化する
//-------------------------------------------------------------------------------------------------------
AsuraTemplate Plane<T> Normalize(Plane<T> p);
AsuraTemplate void Normalize(Plane<T> &p, Plane<T> &result);


////////////////////////////////////////////////////////////////////////////
//　　Quaternion
////////////////////////////////////////////////////////////////////////////
AsuraTemplate 
class Quaternion
{
public:
	union { struct { T x, y, z, w; }; T v[4]; };
	Quaternion<T>(T nx=0.0, T ny=0.0, T nz=0.0, T nw=0.0 ) : x(nx), y(ny), z(nz), w(nw) {}
	Quaternion<T>(Vector3<T> value, T nw) : x(value.x), y(value.y), z(value.z), w(nw) {}
	Quaternion<T>(const T* qua);
	operator T* ();
	operator const T*() const;
	Quaternion<T>& operator = (const Quaternion<T> &qua);
	Quaternion<T>& operator += (const Quaternion<T> &qua);
	Quaternion<T>& operator -= (const Quaternion<T> &qua);
	Quaternion<T>& operator *= (const Quaternion<T> &qua);
	Quaternion<T>& operator *= (T t);
	Quaternion<T>& operator /= (T t);
	Quaternion<T> operator + () const;
	Quaternion<T> operator - () const;
	Quaternion<T> operator + (const Quaternion<T> &qua) const;
	Quaternion<T> operator - (const Quaternion<T> &qua) const;
	Quaternion<T> operator * (const Quaternion<T> &qua) const;
	Quaternion<T> operator * (T t) const;
	Quaternion<T> operator / (T t) const;
	bool operator == (const Quaternion<T> &qua) const;
	bool operator != (const Quaternion<T> &qua) const;
	friend Quaternion<T> operator * (T , const Quaternion<T> &);
	T Length();
	T LengthSquared();
	Vector3<T> xyz();
	Vector4<T> ToVector4();
	void Conjugate();
	void Normalize();
	void Identity();
	Quaternion<T> Zero();
	Quaternion<T> One();
	void ConsoleOut();
};

////////////////////////////////////////////////////////////////////////////
//　　Quaternion Function
////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
// Name : Dot()
// Desc : 2つのクォータニオンの内積を返す
//-----------------------------------------------------------------------------------------------------
AsuraTemplate T Dot(Quaternion<T> q1, Quaternion<T> q2);
AsuraTemplate void Dot(Quaternion<T> &q1, Quaternion<T> &q2, Quaternion<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : Conjugate()
// Desc : クォータニオンの共役を返す
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> Conjugate(Quaternion<T> &qua);
AsuraTemplate void Conjugate(Quaternion<T> &qua, Quaternion<T> &result);

//----------------------------------------------------------------------------------------------------
// Name : Normalize()
// Desc : 長さを正規化した長さのクォータニオンを返す
//----------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> Normalize(Quaternion<T> qua);
AsuraTemplate void Normalize(Quaternion<T> &qua, Quaternion<T> &result);
	
//---------------------------------------------------------------------------------------------------
// Name : Inverse()
// Desc : クォータニオンを共役して再正規化する
//---------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> Inverse(Quaternion<T> qua);
AsuraTemplate void Inverse(Quaternion<T> &qua, Quaternion<T> &result);

//---------------------------------------------------------------------------------------------------
// Name : CreateFromYawPitchRoll
// Desc : ロール・ピッチ・ヨーを指定してクォータニオンを作成
//---------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> CreateFromYawPitchRoll(T yaw, T pitch, T roll);
AsuraTemplate void CreateFromYawPitchRoll(T yaw, T pitch, T roll, Quaternion<T> &result);

//------------------------------------------------------------------------------------------------------
// Name : Slerp()
// Desc : 球面線形補間を使ってクォータニオン間を補間する
//------------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> Slerp(Quaternion<T> q1, Quaternion<T> q2, T t);
AsuraTemplate void Slerp(Quaternion<T> &q1, Quaternion<T> &q2, T t, Quaternion<T> &result);

//-----------------------------------------------------------------------------------------------------
// Name : Squad()
// Desc : 球面2次補間を使ってクォータニオン間を補完する
//-----------------------------------------------------------------------------------------------------
AsuraTemplate Quaternion<T> Squad(
	Quaternion<T> q1, Quaternion<T> a,
	Quaternion<T> b, Quaternion<T> c, T t);
AsuraTemplate void Squad(
	 Quaternion<T> &q1, Quaternion<T> &a,
	 Quaternion<T> &b, Quaternion<T> &c, T t, Quaternion<T> &result);


//////////////////////////////////////////////////////////////////////////
// Color class
//////////////////////////////////////////////////////////////////////////
AsuraTemplate
class Color
{
public:
	float r, g, b, a;
	Color<T>() : r(0.0), g(0.0), b(0.0), a(0.0) {}
	Color<T>( ulong argb );
	Color<T>( const T * pf );
	Color<T>( T nr, T ng, T nb, T na ) : r(nr), g(ng), b(nb), a(na) {}
	Color<T>( Vector2<T> &vec, T nb, T na ) : r(vec.x), g(vec.y), b(nb), a(na) {}
	Color<T>( Vector3<T> &vec, T na ) : r(vec.x), g(vec.y), b(vec.z), a(na) {}
	Color<T>( Vector4<T> &vec ) : r(vec.x), g(vec.y), b(vec.z), a(vec.w) {}

	operator ulong () const;

	operator T * ();
	operator const T * () const;

	Color<T>& operator += ( const Color<T>& col );
	Color<T>& operator -= ( const Color<T>& col );
	Color<T>& operator *= ( T f );
	Color<T>& operator /= ( T f );
	Color<T>& operator = ( const Color<T>& col );

	Color<T> operator + () const;
	Color<T> operator - () const;

	Color<T> operator + ( const Color<T>& col ) const;
	Color<T> operator - ( const Color<T>& col ) const;
	Color<T> operator * ( T f ) const;
	Color<T> operator / ( T f ) const;

	friend Color<T> operator * ( T f, const Color<T>& col ) { return Color<T>(f*col.r, f*col.g, f*col.b, f*col.a); }

	bool operator == ( const Color<T>& col ) const;
	bool operator != ( const Color<T>& col ) const;

	void ConsoleOut();
	Color<T> One();
	Color<T> Zero();

	Vector4<T> ToVector4();
	Vector3<T> ToVector3();
};

AsuraTemplate void Negative(Color<T>&col, Color<T>& result);
AsuraTemplate Color<T> Negative(Color<T> col);
AsuraTemplate void Lerp(Color<T>& c1, Color<T>& c2, T f, Color<T>& result);
AsuraTemplate Color<T> Lerp(Color<T> c1, Color<T> c2, T f);
ulong ColorARGB(ulong a, ulong r, ulong g, ulong b); 
ulong ColorRGBA(ulong r, ulong g, ulong b, ulong a);
ulong ColorXRGB(ulong r, ulong g, ulong b);

}	// namespace AsuraMath

//
// Inline File
//
#include "AsuraMath.inl"


#endif	// _ASURA_MATH_H_INCLUDED_