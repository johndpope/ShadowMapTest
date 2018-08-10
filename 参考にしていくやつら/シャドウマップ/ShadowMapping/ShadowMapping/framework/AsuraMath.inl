/***********************************************************************
　　AsuraMath.inl

　　Asura Math Library

　　Date : Jan. 18, 2008
　　Version : 2.0
　　Author : Pocol
************************************************************************/

#ifndef _ASURA_MATH_INL_INCLUDED_
#define _ASURA_MATH_INL_INCLUDED_


namespace AsuraMath
{

///////////////////////////////////////////////////////////////////////
//　　Vector2 class
///////////////////////////////////////////////////////////////////////
AsuraTemplate AsuraInline 
Vector2<T>::operator T * ()
	{ return (T*)&x; }
	
AsuraTemplate AsuraInline 
Vector2<T>::operator const T* () const
	{ return (const T*)&x; }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator= (const Vector2<T> &vec)
	{ x=vec.x, y=vec.y; return *this; }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator= (const T &s)
	{ x=y=s; return *this; }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator == (const Vector2<T> &vec)const
	{ return ( x==vec.x && y==vec.y ); }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator != (const Vector2<T> &vec)const
	{ return !(*this==vec); }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator > (const Vector2<T> &vec)const
	{ return (x>vec.x && y>vec.y); }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator < (const Vector2<T> &vec)const
	{ return (x<vec.x && y<vec.y); }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator >= (const Vector2<T> &vec)const
	{ return (x>=vec.x && y>=vec.y); }
	
AsuraTemplate AsuraInline 
bool Vector2<T>::operator <= (const Vector2<T> &vec)const
	{ return (x<=vec.x && y<=vec.y); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator+ (const Vector2<T> &vec)const
	{ return Vector2<T>(x+vec.x, y+vec.y); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator- (const Vector2<T> &vec) const
	{ return Vector2<T>(x-vec.x, y-vec.y); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator+() const
	{ return Vector2<T>(*this); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator-() const
	{ return Vector2<T>(-x, -y); }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator+= (const Vector2<T> &vec)
	{ x+=vec.x; y+=vec.y; return *this; }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator-= (const Vector2<T> &vec)
	{ x-=vec.x, y-=vec.y; return *this; }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator*= (const T s)
	{ x*=s; y*=s; return *this; }
	
AsuraTemplate AsuraInline 
Vector2<T> &Vector2<T>::operator/= (const T s)
	{ const T recip =(T)1.0/s; x*= recip; y*= recip; return *this; }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator* (const T s)const
	{ return Vector2<T>(x*s, y*s); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator/ (const T s)const
	{ const T recip = (T)1.0/s; return Vector2<T>(recip*x, recip*y); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::operator* (const Vector2<T> &vec)const
	{ return Vector2<T>(x*vec.x, y*vec.y); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::UnitVector() const
	{
		T mag = Length();
		if ( mag > 0 )
			return (*this)/mag;
		else
			return Vector2<T>((T)0.0, (T)0.0);
	}

AsuraTemplate AsuraInline 
T Vector2<T>::Dot(const Vector2<T> &vec) const
	{ return (x*vec.x + y*vec.y); }
	
AsuraTemplate AsuraInline 
T Vector2<T>::Length() const
	{ return (T)sqrt((double)x*(double)x + (double)y*(double)y); }
	
AsuraTemplate AsuraInline 
T Vector2<T>::LengthSquared() const
	{ return (T)(x*x +y*y); }
	
AsuraTemplate AsuraInline 
void Vector2<T>::Normalize()
	{
		T mag = Length();
		if ( mag > 0 )
		{
			T magInv = (T)1.0/mag;
			x *= magInv;
			y *= magInv;
		}
		else
			x=y=(T)0.0;
	}
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::One()
	{ x=(T)1.0; y=(T)1.0; return (*this); }
	
AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::Zero()
	{ x=(T)0.0; y=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::UnitX()	
	{ x=(T)1.0; y=(T)0.0; return (*this); } 

AsuraTemplate AsuraInline 
Vector2<T> Vector2<T>::UnitY()
	{ x=(T)0.0; y=(T)1.0; return (*this); }
	
AsuraTemplate AsuraInline 
void Vector2<T>::ConsoleOut()
	{ std::cout << "(x, y) = (" << x << ", " << y << ")\n"; }
	

///////////////////////////////////////////////////////////////////////
//　　Vector3 class
///////////////////////////////////////////////////////////////////////

AsuraTemplate AsuraInline 
Vector3<T>::operator T * ()
	{ return (T*)&x; }
	
AsuraTemplate AsuraInline 
Vector3<T>::operator const T* () const
	{ return (const T*)&x; }
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator= (const Vector3<T> &vec)
	{ x=vec.x; y=vec.y; z=vec.z; return *this; }
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator= (const T &s)
	{ x=y=z=s; return *this; }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator== (const Vector3<T> &vec)const
	{ return ((x==vec.x)&&(y==vec.y)&&(z==vec.z)); }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator!= (const Vector3<T> &vec)const
	{ return!(*this==vec); }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator> (const Vector3<T> &vec)const
	{ return (x>vec.x && y>vec.y && z>vec.z); }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator< (const Vector3<T> &vec)const
	{ return (x<vec.x && y<vecc.y && z<vec.z); }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator>= (const Vector3<T> &vec)const
	{ return (x>=vec.x && y>=vec.y && z>=vec.z); }
	
AsuraTemplate AsuraInline 
bool Vector3<T>::operator<= (const Vector3<T> &vec)const
	{ return (x<=vec.x && y<=vec.y && z<=vec.z); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator+ (const Vector3<T> &vec)const
	{ return Vector3<T>(x+vec.x, y+vec.y, z+vec.z); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator+() const
	{ return Vector3<T>(*this); }
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator+= (const Vector3<T> &vec)
	{ x+=vec.x; y+=vec.y; z+=vec.z; return *this; }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator- (const Vector3<T> &vec)const
	{ return Vector3<T>(x-vec.x, y-vec.y, z-vec.z); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator-() const
	{ return Vector3<T>(-x, -y, -z); }
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator-= (const Vector3<T> &vec)
	{ x-=vec.x; y-=vec.y; z-=vec.z; return *this; }
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator*= (const T s)
	{ x*=s; y*=s; z*=s; return *this; }	
	
AsuraTemplate AsuraInline 
Vector3<T> &Vector3<T>::operator/= (const T s)
	{ const T recip = (T)1.0/s; x*= recip; y*=recip; z*=recip; return *this; }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator* (const T s)const
	{ return Vector3<T>(x*s, y*s, z*s); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator/ (const T s)const
	{ const T recip = (T)1.0/s; return Vector3<T>(recip*x, recip*y, recip*z); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::operator* (const Vector3<T> &vec) const
	{ return Vector3<T>(x*vec.x, y*vec.y, z*vec.z); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::Cross(const Vector3<T> &vec) const 
	{ return Vector3<T>(y*vec.z-z*vec.y, z*vec.x-x*vec.z, x*vec.y-y*vec.x); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::UnitVector() const 
	{ 
		T mag = Length();
		if ( mag > 0 )
			return (*this)/mag;
		else
			return Vector3<T>((T)0.0, (T)0.0, (T)0.0);
	}

AsuraTemplate AsuraInline 
T Vector3<T>::Dot(const Vector3<T> &vec) const
	{ return (x*vec.x+ y*vec.y + z*vec.z); }
	
AsuraTemplate AsuraInline 
T Vector3<T>::Length() const
	{ return (T)sqrt((double)x*(double)x + (double)y*(double)y + (double)z*(double)z ); }
	
AsuraTemplate AsuraInline 
T Vector3<T>::LengthSquared() const
	{ return (T)(x*x + y*y + z*z); }
		
AsuraTemplate AsuraInline 
void Vector3<T>::Normalize()
{
	T mag = Length();
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		x *= magInv;
		y *= magInv;
		z *= magInv;
	}
	else
		x=y=z=(T)0.0; 
}

AsuraTemplate AsuraInline
Vector2<T> Vector3<T>::xy()
{
	return Vector2<T>(x, y);
}
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::One()
	{ x=(T)1.0; y=(T)1.0; z=(T)1.0; return (*this); }
	
AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::Zero()
	{ x=(T)0.0; y=(T)0.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::UnitX()
	{ x=(T)1.0; y=(T)0.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::UnitY()
	{ x=(T)0.0; y=(T)1.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector3<T> Vector3<T>::UnitZ()
	{ x=(T)0.0; y=(T)0.0; z=(T)1.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Forward()
{ x=(T)0.0; y=(T)0.0; z=(T)-1.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Backward()
{ x=(T)0.0; y=(T)0.0; z=(T)1.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Up()
{ x=(T)0.0; y=(T)1.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Down()
{ x=(T)0.0; y=(T)-1.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Left()
{ x=(T)-1.0; y=(T)0.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline
Vector3<T> Vector3<T>::Right()
{ x=(T)1.0; y=(T)0.0; z=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
void Vector3<T>::ConsoleOut()
	{ std::cout << "(x, y, z) = (" << x << ", " << y << ", " << z << ")\n"; }

	
///////////////////////////////////////////////////////////////////////
//　　Vector4 class
///////////////////////////////////////////////////////////////////////

AsuraTemplate AsuraInline 
Vector4<T>::operator T * ()
	{ return (T*)&x; }
	
AsuraTemplate AsuraInline 
Vector4<T>::operator const T* () const
	{ return (const T*)&x; }
	
AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator= (const Vector4<T> &vec)
	{ x=vec.x; y=vec.y; z=vec.z; w=vec.w; return *this; }	

AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator= (const T &s)
	{ x=y=z=w=s; return *this; }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator== (const Vector4<T> &vec)const
	{ return ((x==vec.x)&&(y==vec.y)&&(z==vec.z)&&(w==vec.w)); }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator!= (const Vector4<T> &vec)const
	{ return !(*this==vec); }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator> (const Vector4<T> &vec)const
	{ return (x>vec.x && y>vec.y && z>vec.z && w>vec.w); }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator< (const Vector4<T> &vec)const
	{ return (x<vec.x && y<vec.y && vec.z && vec.w); }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator>= (const Vector4<T> &vec)const
	{ return (x>=vec.x && y>=vec.y && z>=vec.z && w>=vec.w); }
	
AsuraTemplate AsuraInline 
bool Vector4<T>::operator <= (const Vector4<T> &vec)const
	{ return (x<=vec.x && y<=vec.y && z<=vec.z && w<=vec.w); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator+ (const Vector4<T> &vec)const
	{ return Vector4<T>(x+vec.x, y+vec.y, z+vec.z, w+vec.w); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator+() const
	{ return Vector4<T>(*this); }
	
AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator+= (const Vector4<T> &vec)
	{ x+=vec.x; y+=vec.y; z+=vec.z; w+=vec.w; return *this; }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator- (const Vector4<T> &vec)const
	{ return Vector4<T>(x-vec.x, y-vec.y, z-vec.z, w-vec.w); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator-() const
	{ return Vector4<T>(-x, -y, -z, -w); }
	
AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator-= (const Vector4<T> &vec)
	{ x-=vec.x; y-=vec.y; z-=vec.z; w-=vec.w; return *this; }
	
AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator*= (const T s)
	{ x*=s; y*=s; z*=s; w*=s; return *this; }
	
AsuraTemplate AsuraInline 
Vector4<T> &Vector4<T>::operator/= (const T s)
	{ const T recip = (T)1.0/s; x*= recip; y*= recip; z*=recip; w*=recip; return *this; }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator* (const T s)const
	{ return Vector4<T>(x*s, y*s, z*s, w*s); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator/ (const T s)const
	{ const T recip = (T)1.0/s; return Vector4<T>(recip*x, recip*y, recip*z, recip*w); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::operator* (const Vector4<T> &vec)const
	{ return Vector4<T>(x*vec.x, y*vec.y, z*vec.z, w*vec.w); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::UnitVector() const
	{
		T mag = Length();
		if ( mag > 0 )
			return (*this)/mag;
		else
			return Vector4<T>((T)0.0, (T)0.0, (T)0.0);
	}

AsuraTemplate AsuraInline 
T Vector4<T>::Dot(const Vector4<T> &vec) const
	{ return (T)(x*vec.x+y*vec.y+z*vec.z+w*vec.w); }
	
AsuraTemplate AsuraInline 
T Vector4<T>::Length() const
	{ return (T)sqrt((double)x*(double)x+(double)y*(double)y+(double)z*(double)z+(double)w*(double)w); } 
	
AsuraTemplate AsuraInline 
T Vector4<T>::LengthSquared() const
	{ return (T)(x*x + y*y + z*z + w*w); }
	
AsuraTemplate AsuraInline 
void Vector4<T>::Normalize()
{ 
	T mag = Length();
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		x *= magInv;
		y *= magInv;
		z *= magInv;
		w *= magInv;
	}
	else 
		x=y=z=w=(T)0.0;
}
	
AsuraTemplate AsuraInline
Vector2<T> Vector4<T>::xy()
{
	return Vector2<T>(x, y);
}

AsuraTemplate AsuraInline
Vector3<T> Vector4<T>::xyz()
{
	return Vector3<T>(x, y, z);
}

AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::One()
	{ x=(T)1.0; y=(T)1.0; z=(T)1.0; w=(T)1.0; return (*this); }
	
AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::Zero()
	{ x=(T)0.0; y=(T)0.0; z=(T)0.0; w=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::UnitX()
	{ x=(T)1.0; y=(T)0.0; z=(T)0.0; w=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::UnitY()
	{ x=(T)0.0; y=(T)1.0; z=(T)0.0; w=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::UnitZ()
	{ x=(T)0.0; y=(T)0.0; z=(T)1.0; w=(T)0.0; return (*this); }

AsuraTemplate AsuraInline 
Vector4<T> Vector4<T>::UnitW()
	{ x=(T)0.0; y=(T)0.0; z=(T)0.0; w=(T)1.0; return (*this); }
	
AsuraTemplate AsuraInline 
void Vector4<T>::ConsoleOut()
	{ std::cout <<  "(x, y, z, w) = (" << x << ", " << y << ", " << z <<  ", " << w << ")\n"; }
	
///////////////////////////////////////////////////////////////////////
//　　Matrix class
///////////////////////////////////////////////////////////////////////

AsuraTemplate AsuraInline 
Matrix<T>::Matrix()
	{ Zero(); _11=_22=_33=_44=1.0; }
	
AsuraTemplate AsuraInline 
Matrix<T>::Matrix(const T* m)
	{ if ( !m) return; memcpy(&_11, m, sizeof(Matrix)); }
	
AsuraTemplate AsuraInline 
Matrix<T>::Matrix(const Matrix<T> &mat)
	{ memcpy(&_11, &mat, sizeof(Matrix)); }
	
AsuraTemplate AsuraInline 
Matrix<T>::Matrix(T m11, T m12, T m13, T m14,
	T m21, T m22, T m23, T m24,
	T m31, T m32, T m33, T m34,
	T m41, T m42, T m43, T m44 )
	{
		_11 = m11; _12 = m12; _13 = m13; _14 = m14;
		_21 = m21; _22 = m22; _23 = m23; _24 = m24;
		_31 = m31; _32 = m32; _33 = m33; _34 = m34;
		_41 = m41; _42 = m42; _43 = m43; _44 = m44;
	}
	
AsuraTemplate AsuraInline 
T& Matrix<T>::operator() (unsigned int row, unsigned int col)
	{ return m[row][col]; }
	
AsuraTemplate AsuraInline 
T Matrix<T>::operator() (unsigned int row, unsigned int col) const
	{ return m[row][col]; }
	
AsuraTemplate AsuraInline 
Matrix<T>::operator T*()
	{ return (T*)&_11; }
	
AsuraTemplate AsuraInline 
Matrix<T>::operator const T*() const
	{ return (const T*)&_11; }
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator = (const Matrix<T> &mat)
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 =mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator *= (const Matrix<T> &mat)
	{
		Multiply((*this), mat, (*this));
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator += (const Matrix<T> &mat)
	{
		_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
		_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
		_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
		_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;			
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator -= (const Matrix<T> &mat)
	{
		_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
		_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
		_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
		_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator *= (T t)
	{
		_11 *= t; _12 *= t; _13 *= t; _14 *= t;
		_21 *= t; _22 *= t; _23 *= t; _24 *= t;
		_31 *= t; _32 *= t; _33 *= t; _34 *= t;
		_41 *= t; _42 *= t; _43 *= t; _44 *= t;
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T>& Matrix<T>::operator /= (T t)
	{
		T tInv = (T)1.0/t;
		_11 *= tInv; _12 *= tInv; _13 *= tInv; _14 *= tInv;
		_21 *= tInv; _22 *= tInv; _23 *= tInv; _24 *= tInv;
		_31 *= tInv; _32 *= tInv; _33 *= tInv; _34 *= tInv;
		_41 *= tInv; _42 *= tInv; _43 *= tInv; _44 *= tInv;
		return (*this);
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator + () const
	{ return (*this); }	
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator - () const
	{ 
		return Matrix<T>(
			-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44 );
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator * (const Matrix<T> &mat) const
	{ 
		Matrix<T> temp(_11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44 );
		Matrix<T> result;
		result = Multiply(temp, mat); 
		return result; 
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator + (const Matrix<T> &mat) const
	{
		return Matrix<T>(
			_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
			_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
			_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
			_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44 );
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator - (const Matrix<T> &mat) const
	{
		return Matrix<T>(
			_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
			_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
			_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
			_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44 );
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator * (T t) const
	{
		return Matrix<T>(
			_11 * t, _12 * t, _13 * t, _14 * t,
			_21 * t, _22 * t, _23 * t, _24 * t,
			_31 * t, _32 * t, _33 * t, _34 * t,
			_41 * t, _42 * t, _43 * t, _44 * t );
	}
	
AsuraTemplate AsuraInline 
Matrix<T> Matrix<T>::operator / (T t) const
	{
		T tInv = (T)1.0/t;
		return Matrix<T>(
			_11 * tInv, _12 * tInv, _13 * tInv, _14 * tInv,
			_21 * tInv, _22 * tInv, _23 * tInv, _24 * tInv,
			_31 * tInv, _32 * tInv, _33 * tInv, _34 * tInv,
			_41 * tInv, _42 * tInv, _43 * tInv, _44 * tInv );
	}

AsuraTemplate AsuraInline 
Vector4<T> Matrix<T>::operator * (const Vector4<T> &vec) const
	{
		return Vector4<T>(
			(_11*vec.x + _12*vec.y + _13*vec.z + _14*vec.w),
			(_21*vec.x + _22*vec.y + _23*vec.z + _24*vec.w),
			(_31*vec.x + _32*vec.y + _33*vec.z + _34*vec.w),
			(_41*vec.x + _42*vec.y + _43*vec.z + _44*vec.w) );
	}

AsuraTemplate AsuraInline 	
Matrix<T> operator * (T t, const Matrix<T> &mat)
	{
		return Matrix<T>(
			t * mat._11, t * mat._12, t * mat._13, t * mat._14,
			t * mat._21, t * mat._22, t * mat._23, t * mat._24,
			t * mat._31, t * mat._32, t * mat._33, t * mat._34,
			t * mat._41, t * mat._42, t * mat._43, t * mat._44 );
	}
	
AsuraTemplate AsuraInline 
bool Matrix<T>::operator == (const Matrix<T> &mat) const
	{ return 0 == memcmp(this, &mat, sizeof(Matrix)); }
	
AsuraTemplate AsuraInline 
bool Matrix<T>::operator !=  (const Matrix<T> &mat) const
	{ return 0 != memcmp(this, &mat, sizeof(Matrix)); }
	
AsuraTemplate AsuraInline 
void Matrix<T>::Identity()
	{ Zero(); _11=_22=_33 =_44=1.0; }
	
AsuraTemplate AsuraInline 
void Matrix<T>::Zero()
	{ _11=_12=_13=_14=_21=_22=_23=_24=_31=_32=_33=_34=_41=_42=_43=_44=0.0; }

AsuraTemplate AsuraInline 
void Matrix<T>::One()
	{ _11=_12=_13=_14=_21=_22=_23=_24=_31=_32=_33=_34=_41=_42=_43=_44=1.0; }

AsuraTemplate AsuraInline
T Matrix<T>::Determinant()
{
		T det = _11*_22*_33*_44 + _11*_23*_34*_42 
			+ _11*_24*_32*_43	+ _12*_21*_34*_43 
			+ _12*_23*_31*_44	+ _12*_24*_33*_41
			+ _13*_21*_32*_44	+ _13*_22*_34*_41
			+ _13*_24*_31*_42 + _14*_21*_33*_42
			+ _14*_22*_31*_43 + _14*_23*_32*_41
			- _11*_22*_34*_43 - _11*_23*_32*_44
			- _11*_24*_33*_42 - _12*_21*_33*_44
			- _12*_23*_34*_41 - _12*_24*_31*_43
			- _13*_21*_34*_42 - _13*_22*_31*_44
			- _13*_24*_32*_41 - _14*_21*_32*_43
			- _14*_22*_33*_41 - _14*_23*_31*_42;
		return det;
}

AsuraTemplate AsuraInline 
void Matrix<T>::ConsoleOut()
	{
		std::cout << "[_11 _12 _13 _14] = [" << _11 << " " << _12 << " " << _13 << " " << _14 << "]\n";
		std::cout << "[_21 _22 _23 _24] = [" << _21 << " " << _22 << " " << _23 << " " << _24 << "]\n";
		std::cout << "[_31 _32 _33 _34] = [" << _31 << " " << _32 << " " << _33 << " " << _34 << "]\n";
		std::cout << "[_41 _42 _43 _44] = [" << _41 << " " << _42 << " " << _43 << " " << _44 << "]\n";
	}
	
AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_11_12_13_14()
{
	return Vector4<T>(_11, _12, _13, _14);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_21_22_23_24()
{
	return Vector4<T>(_21, _22, _23, _24);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_31_32_33_34()
{
	return Vector4<T>(_31, _32, _33, _34);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_41_42_43_44()
{
	return Vector4<T>(_41, _42, _43, _44);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_11_21_31_41()
{
	return Vector4<T>(_11, _21, _31, _41);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_12_22_32_42()
{
	return Vector4<T>(_12, _22, _32, _42);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_13_23_33_43()
{
	return Vector4<T>(_13, _23, _33, _43);
}

AsuraTemplate AsuraInline
Vector4<T> Matrix<T>::_14_24_34_44()
{
	return Vector4<T>(_14, _24, _34, _44);
}
	
	
///////////////////////////////////////////////////////////////////////
//　　Plane
///////////////////////////////////////////////////////////////////////
AsuraTemplate AsuraInline
Plane<T>::Plane(Vector3<T> posoition1, Vector3<T> position2, Vector3<T> position3)
{
	Vector3<T> normal = GetNormal(position1, position2, position3);
	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = -(a*position1.x + b*position1.y + c*position1.z);
}

AsuraTemplate AsuraInline 
Plane<T>::Plane(const T *pf)
		{ a=pf[0]; b=pf[1]; c=pf[2]; d=pf[3]; }
		
AsuraTemplate AsuraInline 
Plane<T>::operator T* ()
	{ return (T*)&a; }
	
AsuraTemplate AsuraInline 
Plane<T>::operator const T*() const
	{ return (const T*)&a; }
	
AsuraTemplate AsuraInline 
Plane<T>& Plane<T>::operator = (const Plane<T> &p)
	{ a=p.a; b=p.b; c=p.c; d=p.d; return (*this); }
	
AsuraTemplate AsuraInline 
Plane<T>& Plane<T>::operator *= (T f)
	{ a*=f; b*=f; c*=f; d*=f; return (*this); }

AsuraTemplate AsuraInline 
Plane<T>& Plane<T>::operator /= (T f)
	{ T fInv = (T)1.0/f; a*=fInv; b*=fInv; c*=fInv; d*=fInv; return (*this); }
	
AsuraTemplate AsuraInline 
Plane<T> Plane<T>::operator + () const
	{ return (*this); }
	
AsuraTemplate AsuraInline 
Plane<T> Plane<T>::operator - () const
	{ return Plane<T>(-a, -b, -c, -d); }
	
AsuraTemplate AsuraInline 
Plane<T> Plane<T>::operator * (T f)const
	{ return Plane<T>(a*f, b*f, c*f, d*f); }
	
AsuraTemplate AsuraInline 
Plane<T> Plane<T>::operator / (T f)const
	{ T fInv =(T)1.0/f; return Plane<T>(a*fInv, b*fInv, c*fInv, d*fInv); }
	
AsuraTemplate AsuraInline 
Plane<T> operator * (T f, const Plane<T> &p)
	{ return Plane<T>(f*p.a, f*p.b, f*p.c, f*p.d); }
	
AsuraTemplate AsuraInline 
bool Plane<T>::operator == (const Plane<T> &) const
	{ return (a==p.a && b==p.b && c==p.c && d==p.d); }
	
AsuraTemplate  AsuraInline 
bool Plane<T>::operator != (const Plane<T> & ) const
	{ return (a!=p.a || b!=p.b || c!=p.c || d!=p.d); }

AsuraTemplate AsuraInline
Vector3<T> Plane<T>::abc()
{
	return Vector3<T>(a, b, c);
}

AsuraTemplate AsuraInline
Vector4<T> Plane<T>::ToVector4()
{
	return Vector4<T>(a, b, c, d);
}

AsuraTemplate AsuraInline
void Plane<T>::Normalize()
{ 
	T mag = sqrt(a*a + b*b + c*c);
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		a *= magInv;
		b *= magInv;
		c *= magInv;
	}
	else
	{
		a = b = c = (T)0.0;
	}
}

AsuraTemplate AsuraInline
Plane<T> Plane<T>::Zero()
{ a=b=c=d=(T)0.0; return *this; }

AsuraTemplate AsuraInline
Plane<T> Plane<T>::One()
{ a=b=c=d=(T)1.0; return *this; }
	
AsuraTemplate AsuraInline 
void Plane<T>::ConsoleOut()
	{ std::cout << "(a, b, c, d) = (" << a << ", " << b << ", " << c << ", " << d << ")\n"; }
	
	
///////////////////////////////////////////////////////////////////////
//　　Quaternion
///////////////////////////////////////////////////////////////////////
AsuraTemplate AsuraInline 
Quaternion<T>::Quaternion(const T* qua)
	{ x=qua[0]; y=qua[1]; z=qua[2]; w=qua[3]; }
	
AsuraTemplate AsuraInline 
Quaternion<T>::operator T* ()
	{ return (T*)&x; }
	
AsuraTemplate AsuraInline 
Quaternion<T>::operator const T*() const
	{ return (const T*)&x; }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator = (const Quaternion<T> &qua)
	{ x=qua.x; y=qua.y; z=qua.z; w=qua.w; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator += (const Quaternion<T> &qua)
	{ x+=qua.x; y+=qua.y; z+=qua.z; w+=qua.w; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator -= (const Quaternion<T> &qua)
	{ x-=qua.x; y-=qua.y; z-=qua.z; w-=qua.w; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator *= (const Quaternion<T> &qua)
	{ *this = *this*q; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator *= (T t)
	{ x*=t; y*=t; z*=t; w*=t; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T>& Quaternion<T>::operator /= (T t)
	{ T s=(T)1.0/t; x*=s; y*=s; z*=s; w*=s; return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator + () const
	{ return (*this); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator - () const
	{ return Quaternion<T>(-x, -y, -z, -w); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator + (const Quaternion<T> &qua) const
	{ return Quaternion<T>(x+qua.x, y+qua.y, z+qua.z, w+qua.w); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator - (const Quaternion<T> &qua) const
	{ return Quaternion<T>(x-qua.x, y-qua.y, z-qua.z, w-qua.w); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator * (const Quaternion<T> &qua) const
	{
		return Quaternion<T>(
			-(x*qua.x) - (y*qua.y) - (z*qua.z),
			(w*qua.x) + (y*qua.y) - (z*qua.y),
			(w*qua.y) + (y*qua.z) - (x*qua.z),
			(w*qua.z) + (x*qua.y) - (y*qua.x) );
	}
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator * (T t) const
	{ return Quaternion<T>(x*t, y*t, z*t, w*t); }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::operator / (T t) const
	{ T s=(T)1.0/t; return Quaternion<T>(x*s, y*s, z*s, w*s); }
	
AsuraTemplate AsuraInline 
Quaternion<T> operator * (T t, const Quaternion<T> &qua)
	{ return Quaternion<T>(t*qua.x, t*qua.y, t*qua.z, t*qua.w); }
	
AsuraTemplate AsuraInline 
bool Quaternion<T>::operator == (const Quaternion<T> &qua) const
	{ return (x==qua.x && y==qua.y && z==qua.z && w==qua.w); }
	
AsuraTemplate AsuraInline 
bool Quaternion<T>::operator != (const Quaternion<T> &qua) const
	{ return (x!=qua.x || y!=qua.y || z!=qua.z || w!=qua.w); }
	
AsuraTemplate AsuraInline 
T Quaternion<T>::Length()
	{ return (T)sqrt((double)x*(double)x + (double)y*(double)y + (double)z*(double)z + (double)w*(double)w); }

AsuraTemplate AsuraInline 
T Quaternion<T>::LengthSquared()
	{ return (T)(x*x + y*y + z*z + w*w); }
	
AsuraTemplate AsuraInline 
void Quaternion<T>::Conjugate()
	{ x =-x, y =-y, z =-z; }
	
AsuraTemplate AsuraInline 
void Quaternion<T>::Normalize()
	{
		T mag = Length();
		if ( mag > 0 )
		{
			T magInv=(T)1.0/mag;
			x *= magInv;
			y *= magInv;
			z *= magInv;
			w *= magInv;
		}
		else
		{
			x=y=z=w=(T)0.0;
		}
	}

AsuraTemplate AsuraInline
void Quaternion<T>::Identity()
{
	x = (T)0.0;
	y = (T)0.0;
	z = (T)0.0;
	w = (T)1.0;
}
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::Zero()
	{ x=y=z=w=(T)0.0; return *this; }
	
AsuraTemplate AsuraInline 
Quaternion<T> Quaternion<T>::One()
	{ x=y=z=w=(T)1.0; return *this }
	
AsuraTemplate AsuraInline 
void Quaternion<T>::ConsoleOut()
	{ std::cout << "(x, y, z, w) = ("<< x << ", " << y << ", " << z << ", " << w << ")\n"; }
	
AsuraTemplate AsuraInline
Vector3<T> Quaternion<T>::xyz()
{
	return Vector3<T>(x, y, z);
}

AsuraTemplate AsuraInline
Vector4<T> Quaternion<T>::ToVector4()
{
	return Vector4<T>(x, y, z, w);
}

////////////////////////////////////////////////////////////////////////
// Color
////////////////////////////////////////////////////////////////////////
AsuraTemplate AsuraInline 
Color<T>::Color( ulong argb )
{
	const T f=(T)(1.0/255.0);
	r = f * (T)(unsigned char)(argb >> 16);
	g = f * (T)(unsigned char)(argb >> 8);
	b = f * (T)(unsigned char)(argb >> 0);
	a = f * (T)(unsigned char)(argb >> 24);
}

AsuraTemplate AsuraInline 
Color<T>::Color( const T* pf )
{
	r = pf[0];
	g = pf[1];
	b = pf[2];
	a = pf[3];
}

AsuraTemplate AsuraInline 
Color<T>::operator ulong() const
{
	ulong dwR = r >= 1.0 ? 0xff : r <= 0.0 ? 0x00 : (ulong) (r * 255.0 + 0.5);
    ulong dwG = g >= 1.0 ? 0xff : g <= 0.0 ? 0x00 : (ulong) (g * 255.0 + 0.5);
    ulong dwB = b >= 1.0 ? 0xff : b <= 0.0 ? 0x00 : (ulong) (b * 255.0 + 0.5);
    ulong dwA = a >= 1.0 ? 0xff : a <= 0.0 ? 0x00 : (ulong) (a * 255.0 + 0.5);

    return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

AsuraTemplate AsuraInline 
Color<T>::operator T * ()
{
	return (T*)&r;
}

AsuraTemplate AsuraInline 
Color<T>::operator const T *() const
{
	return (const T*)&r;
}

AsuraTemplate AsuraInline 
Color<T>& Color<T>::operator += ( const Color<T>& col )
{
	r += col.r;
	g += col.g;
	b += col.b;
	a += col.a;
	return *this;
}

AsuraTemplate AsuraInline 
Color<T>& Color<T>::operator -= ( const Color<T>& col )
{
	r -= col.r;
	g -= col.g;
	b -= col.b;
	a -= col.a;
	return *this;
}

AsuraTemplate AsuraInline 
Color<T>& Color<T>::operator *= ( T f )
{
	r *= f;
	g *= f;
	b *= f;
	a *= f;
	return *this;
}

AsuraTemplate AsuraInline 
Color<T>& Color<T>::operator /= ( T f )
{
	T fInv = (T)(1.0/f);
	r *= fInv;
	g *= fInv;
	b *= fInv;
	a *= fInv;
	return *this;
}

AsuraTemplate AsuraInline 
Color<T>& Color<T>::operator = ( const Color<T>& col )
{
	r = col.r;
	g = col.g;
	b = col.b;
	a = col.a;
	return *this;
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator + () const
{
	return *this;
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator - () const
{
	return Color<T>(-r, -g, -b, -a);
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator + ( const Color<T>& col ) const
{
	return Color<T>(r+col.r, g+col.g, b+col.b, a+col.a);
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator - ( const Color<T>& col ) const
{
	return Color<T>(r-col.r, g-col.g, b-col.b, a-col.a);
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator * ( T f ) const
{
	return Color<T>(r*f, g*f, b*f, a*f);
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::operator / ( T f ) const
{
	float fInv = 1.0f/f;
	return Color(r*fInv, g*fInv, b*fInv, a*fInv);
}

AsuraTemplate AsuraInline 
bool Color<T>::operator ==(const Color<T> &col) const
{
	return r==col.r && g==col.g && b==col.b && a==col.a;
}

AsuraTemplate AsuraInline 
bool Color<T>::operator != (const Color<T>& col ) const
{
	return r!= col.r || g!=col.g || b!=col.b || a!=col.a;
}

AsuraTemplate AsuraInline 
void Color<T>::ConsoleOut()
{
	std::cout << "(R, G, B, A) = (" << r << "," << g << "," << b << ", " << a << ")\n";
}

AsuraTemplate AsuraInline 
Color<T> Color<T>::One()
{
	r = (T)1.0;
	g = (T)1.0;
	b = (T)1.0;
	a = (T)1.0;
	return *this;
}
AsuraTemplate AsuraInline 
Color<T> Color<T>::Zero()
{
	r = (T)0.0;
	g = (T)0.0;
	b = (T)0.0;
	a = (T)0.0;
	return *this;
}

AsuraTemplate AsuraInline
Vector4<T> Color<T>::ToVector4()
{
	return Vector4<T>(r, g, b, a);
}

AsuraTemplate AsuraInline
Vector3<T> Color<T>::ToVector3()
{
	return Vector3<T>(r, g, b);
}


///////////////////////////////////////////////////////////////////////
//　　Vector Function
///////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//　　Clamp
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Clamp(Vector2<T> v, Vector2<T> min, Vector2<T> max)
	{ 
		Vector2<T> temp; 
		temp.x = clamp(v.x, min.x, max.x);
		temp.y = clamp(v.y, min.y, max.y);
		return temp;
	}
AsuraTemplate AsuraInline Vector3<T> Clamp(Vector3<T> v, Vector3<T> min, Vector3<T> max)
	{
		Vector3<T> temp;
		temp.x = clamp(v.x, min.x, max.x);
		temp.y = clamp(v.y, min.y, max.y);
		temp.z = clamp(v.z, min.z, max.z);
		return temp;
	}
AsuraTemplate AsuraInline Vector4<T> Clamp(Vector4<T> v, Vector4<T> min, Vector4<T> max)
	{
		Vector4<T> temp;
		temp.x = clamp(v.x, min.x, max.x);
		temp.y = clamp(v.y, min.y, max.y);
		temp.z = clamp(v.z, min.z, max.z);
		temp.w = clamp(v.w, min.w, max.w);
		return temp;
	}
AsuraTemplate AsuraInline void Clamp(Vector2<T> &v, Vector2<T> &min, Vector2<T> &max, Vector2<T> &result)
{
	Vector2<T> temp = Clamp(v, min, max);
	result = temp;
}
AsuraTemplate AsuraInline void Clamp(Vector3<T> &v, Vector3<T> &min, Vector3<T> &max, Vector3<T> &result)
{
	Vector3<T> temp = Clamp(v, min, max);
	result = temp;
}
AsuraTemplate AsuraInline void Clamp(Vector4<T> &v, Vector4<T> &min, Vector4<T> &max, Vector4<T> &result)
{
	Vector4<T> temp = Clamp(v, min, max);
	result = temp;
}

//-------------------------------------------------------------------------------------------------
//　　Distance
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T Distance(Vector2<T> v1, Vector2<T> v2)
{
	Vector2<T> vec = v2-v1;
	return (T)sqrt((double)vec.x*(double)vec.x + (double)vec.y*(double)vec.y);
}
AsuraTemplate AsuraInline T Distance(Vector3<T> v1, Vector3<T> v2)
{
	Vector3<T> vec =v2-v1; 
	return (T)sqrt((double)vec.x*(double)vec.x + (double)vec.y*(double)vec.y + (double)vec.z*(double)vec.z);
}
AsuraTemplate AsuraInline T Distance(Vector4<T> v1, Vector4<T> v2)
{
	Vector4<T> vec= v2-v1;
	return (T)sqrt((double)vec.x*(double)vec.x + (double)vec.y*(double)vec.y + (double)vec.z*(double)vec.z + (double)vec.w*(double)vec.w);
}
AsuraTemplate AsuraInline void Distance(Vector2<T> &v1, Vector2<T> &v2, T &result)
{
	T temp = Distance(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Distance(Vector3<T> &v1, Vector3<T> &v2, T &result)
{
	T temp = Distance(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Distance(Vector4<T> &v1, Vector4<T> &v2, T &result)
{
	T temp = Distance(v1, v2);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　DistanceSquared
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T DistanceSquared(Vector2<T> v1, Vector2<T> v2)
{
	Vector2<T> vec = v2 - v1;
	return (T)(vec.x*vec.x + vec.y*vec.y); 
}
AsuraTemplate AsuraInline T DistanceSquared(Vector3<T> v1, Vector3<T> v2)
{
	Vector3<T> vec = v2- v1;
	return (T)(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z); 
}
AsuraTemplate AsuraInline T DistanceSquared(Vector4<T> v1, Vector4<T> v2)
{
	Vector4<T> vec = v2-v1;
	return (T)(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w); 
}
AsuraTemplate AsuraInline void DistanceSquared(Vector2<T> &v1, Vector2<T> &v2, T &result)
{
	Vector2<T> vec = v2 -v1;
	return (T)(vec.x*vec.x + vec.y*vec.y);
}
AsuraTemplate AsuraInline void DistanceSquared(Vector3<T> &v1, Vector3<T> &v2, T &result)
{
	Vector3<T> vec = v2 -v1;
	return (T)(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}
AsuraTemplate AsuraInline void DistanceSquared(Vector4<T> &v1, Vector4<T> &v2, T &result)
{
	Vector4<T> vec = v2-v1;
	return (T)(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w);
}

//--------------------------------------------------------------------------------------------------
//　　Dot
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T Dot(Vector2<T> v1, Vector2<T> v2)
{
	return (T)(v1.x*v2.x + v1.y*v2.y); 
}
AsuraTemplate AsuraInline T Dot(Vector3<T> v1, Vector3<T> v2)
{
	return (T)(v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
AsuraTemplate AsuraInline T Dot(Vector4<T> v1, Vector4<T> v2)
{
	return (T)(v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w);
}
AsuraTemplate AsuraInline void Dot(Vector2<T> &v1, Vector2<T> &v2, T &result)
{
	Vector2<T> temp;
	temp = Dot(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Dot(Vector3<T> &v1, Vector3<T> &v2, T &result)
{
	Vector3<T> temp;
	temp = Dot(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Dot(Vector4<T> &v1, Vector4<T> &v2, T &result)
{
	Vector4<T> temp;
	temp = Dot(v1, v2);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Cross
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector3<T> Cross(Vector3<T> v1, Vector3<T> v2)
{
	Vector3<T> result;
	result.x = (v1.y*v2.z) - (v1.z*v2.y);
	result.y = (v1.z*v2.x) - (v1.x*v2.z);
	result.z = (v1.x*v2.y) - (v1.y*v2.x);
	return result;
}
AsuraTemplate AsuraInline void Cross(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result)
{
	Vector3<T> temp = Cross(v1, v2);
	result = temp;
}


//--------------------------------------------------------------------------------------------------
//　　Normalize
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Normalize(Vector2<T> v)
{
	Vector2<T> result;
	T mag = v.Length();
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		result.x = v.x*magInv;
		result.y = v.y*magInv;
	}
	else
	{
		result.x = result.y = (T)0.0;
	}
	return result;
}
AsuraTemplate AsuraInline Vector3<T> Normalize(Vector3<T> v)
{
	Vector3<T> result;
	T mag = v.Length();
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		result.x = v.x*magInv;
		result.y = v.y*magInv;
		result.z = v.z*magInv;
	}
	else
	{
		result.x = result.y = result.z= (T)0.0;
	}
	return result;
}
AsuraTemplate AsuraInline Vector4<T> Normalize(Vector4<T> v)
{
	Vector4<T> result;
	T mag = v.Length();
	if ( mag > 0 )
	{
		T magInv = (T)1.0/mag;
		result.x = v.x*magInv;
		result.y = v.y*magInv;
		result.z = v.z*magInv;
		result.w = v.w*magInv;
	}
	else
	{
		result.x = result.y = result.z = result.w = (T)0.0;
	}
	return result;
}
AsuraTemplate AsuraInline void Normalize(Vector2<T> &v, Vector2<T> &result)
{
	Vector4<T> temp = Normalize(v);
	result = temp;
}
AsuraTemplate AsuraInline void Normalize(Vector3<T> &v, Vector3<T> &result)
{
	Vector3<T> temp = Normalize(v);
	result = temp;
}
AsuraTemplate AsuraInline void Normalize(Vector4<T> &v, Vector4<T> &result)
{
	Vector4<T> temp = Normalize(v);
	result = temp;
}

//-------------------------------------------------------------------------------------------------
//　　GetNormal
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector3<T> GetNormal(
	Vector3<T> v1, Vector3<T> v2, Vector3<T> v3)
{
	Vector3<T> vec1(v1-v2);
	Vector3<T> vec2(v1-v3);
	Vector3<T> temp;
	temp = vec1.Cross(vec2);
	temp.Normalize();
	return temp;
}
AsuraTemplate AsuraInline void GetNormal(
	Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, Vector3<T> &result)
{
	Vector3<T> temp = GetNormal(v1, v2, v3);
	result = temp;
}

//-------------------------------------------------------------------------------------------------
//　　GetQuadNormal
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector3<T> GetQuadNormal(
	Vector3<T> v1, Vector3<T> v2, Vector3<T> v3, Vector3<T> v4)
{
	Vector3<T> n, n1a, n1b, n2a, n2b;
	n1a = GetNormal(v1, v2, v3);
	n1b = GetNormal(v1, v3, v4);
	n2a = GetNormal(v2, v3, v4);
	n2b = GetNormal(v2, v4, v1);
	if ( Dot(n1a, n1b) > Dot(n2a, n2b) )
	{
		Vector3<T> temp1 = (n1a + n1b);
		n = Normalize(temp1);
	}
	else
	{
		Vector3<T> temp2 = (n2a + n2b);
		n = Normalize(temp2);
	}
	return n;
}
AsuraTemplate AsuraInline void GetQuadNormal(
	Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, Vector3<T> &v4, Vector3<T> &result)
{
	Vector3<T> temp = GetQuadNormal(v1, v2, v3, v4);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Min
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Min(Vector2<T> v1, Vector2<T> v2)
{
	Vector2<T> temp;
	temp.x = v1.x < v2.x ? v1.x : v2.x;
	temp.y = v1.y < v2.y ? v1.y : v2.y;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> Min(Vector3<T> v1, Vector3<T> v2)
{
	Vector3<T> temp;
	temp.x = v1.x < v2.x ? v1.x : v2.x;
	temp.y = v1.y < v2.y ? v1.y : v2.y;
	temp.z = v1.z < v2.z ? v1.z : v2.z;
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> Min(Vector4<T> v1, Vector4<T> v2)
{
	Vector4<T> temp;
	temp.x = v1.x < v2.x ? v1.x : v2.x;
	temp.y = v1.y < v2.y ? v1.y : v2.y;
	temp.z = v1.z < v2.z ? v1.z : v2.z;
	temp.w = v1.w < v2.w ? v1.w : v2.w;
	return temp;
}
AsuraTemplate AsuraInline void Min(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &result)
{
	Vector2<T> temp = Min(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Min(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result)
{
	Vector3<T> temp = Min(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Min(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &result)
{
	Vector4<T> temp = Min(v1, v2);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Max
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Max(Vector2<T> v1, Vector2<T> v2)
{
	Vector2<T> temp;
	temp.x = v1.x > v2.x ? v1.x : v2.x;
	temp.y = v1.y > v2.y ? v1.y : v2.y;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> Max(Vector3<T> v1, Vector3<T> v2)
{
	Vector3<T> temp;
	temp.x = v1.x > v2.x ? v1.x : v2.x;
	temp.y = v1.y > v2.y ? v1.y : v2.y;
	temp.z = v1.z > v2.z ? v1.z : v2.z;
	return temp;	
}
AsuraTemplate AsuraInline Vector4<T> Max(Vector4<T> v1, Vector4<T> v2)
{
	Vector4<T> temp;
	temp.x = v1.x > v2.x ? v1.x: v2.x;
	temp.y = v1.y > v2.y ? v1.y : v2.y;
	temp.z = v1.z > v2.z ? v1.z : v2.z;
	temp.w = v1.w > v2.w ? v1.z : v2.w;
	return temp;
}
AsuraTemplate AsuraInline void Max(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &result)
{
	Vector2<T> temp = Max(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Max(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &result)
{
	Vector3<T> temp = Max(v1, v2);
	result = temp;
}
AsuraTemplate AsuraInline void Max(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &result)
{
	Vector4<T> temp = Max(v1, v2);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Reflect
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Reflect(Vector2<T> i, Vector2<T> n)
{
	Vector2<T> temp = i - 2.0 * n * Dot(n,i);
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> Reflect(Vector3<T> i, Vector3<T> n)
{
	Vector3<T> temp = i - 2.0 * n * Dot(n, i); 
	return temp; 
}
AsuraTemplate AsuraInline void Reflect(Vector2<T> &i, Vector2<T> &n, Vector2<T> &reslut)
{
	Vector2<T> temp = Reflect(i, n);
	result = temp;
}
AsuraTemplate AsuraInline void Reflect(Vector3<T> &i, Vector3<T> &n, Vector3<T> &result)
{
	Vector3<T> temp = Reflect(i, n);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Refract
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector3<T> Refract(Vector3<T> i, Vector3<T> n, Vector3<T> eta)
{ 
	 T cosi = Dot(-i, n);
	 T cost2 = 1.0 - eta * eta * (1.0 - cosi*cosi);
	 Vector3<T> t = eta*i + ((eta*cosi - sqrt(abs(cost2))) * n);
	return t * (T)(cost2 > 0);
}
AsuraTemplate AsuraInline void Refract(Vector3<T> &i, Vector3<T> &n, Vector3<T> &eta, Vector3<T> &result)
{
	Vector3<T> temp = Refract(i, n, eta);
	result = temp;
}


//-------------------------------------------------------------------------------------------------
//　　Barycentric
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Barycentric(Vector2<T> v1, Vector2<T> v2, Vector2<T> v3, T f, T g)
{
	Vector2<T> temp; 
	temp = v1 + f*(v2 - v1) + g*(v3 - v1);
	return temp; 
}
AsuraTemplate AsuraInline Vector3<T> Barycentric(Vector3<T> v1, Vector3<T> v2, Vector3<T>v3, T f, T g)
{
	Vector3<T> temp;
	temp = v1 + f*(v2 - v1) + g*(v3 - v1); 
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> Barycentric(Vector4<T> v1, Vector4<T> v2, Vector4<T> v3, T f, T g)
{
	Vector4<T> temp;
	temp = v1 + f*(v2 - v1) + g*(v3 - v1); 
	return temp; 
}
AsuraTemplate AsuraInline void Barycentric(Vector2<T> &v1, Vector2<T> &v2, Vector2<T> &v3, T f, T g, Vector2<T> &result)
{
	Vector2<T> temp = Barycentric(v1, v2, v3, f, g);
	result = temp;
}
AsuraTemplate AsuraInline void Barycentric(Vector3<T> &v1, Vector3<T> &v2, Vector3<T> &v3, T f, T g, Vector3<T> &result)
{
	Vector3<T> temp = Barycentric(v1, v2, v3, f, g);
}
AsuraTemplate AsuraInline void Barycentric(Vector4<T> &v1, Vector4<T> &v2, Vector4<T> &v3, T f, T g, Vector4<T> &result)
{
	Vector4<T> temp = Barycentric(v1, v2, v3, f, g);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Lerp
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Lerp(Vector2<T> v1, Vector2<T> v2, T amount)
{
	Vector2<T> temp = (1.0-amount)*v1 + amount*v2;
	return temp; 
}
AsuraTemplate AsuraInline Vector3<T> Lerp(Vector3<T> v1, Vector3<T> v2, T amount)
{
	Vector3<T> temp = (1.0-amount)*v1 + amount*v2; 
	return temp; 
}
AsuraTemplate AsuraInline Vector4<T> Lerp(Vector4<T> v1, Vector4<T> v2, T amount)
{
	Vector4<T> temp = (1.0-amount)*v1 + amount*v2;
	return temp; 
}
AsuraTemplate AsuraInline void Lerp(Vector2<T> &v1, Vector2<T> &v2, T amount, Vector2<T> &result)
{
	Vector2<T> temp = Lerp(v1, v2, amount);
	result = temp;
}
AsuraTemplate AsuraInline void Lerp(Vector3<T> &v1, Vector3<T> &v2, T amount, Vector3<T> &result)
{
	Vector3<T> temp = Lerp(v1, v2, amount);
	result = temp;
}
AsuraTemplate AsuraInline void Lerp(Vector4<T> &v1, Vector4<T> &v2, T amount, Vector4<T> &result)
{
	Vector4<T> temp = Lerp(v1, v2, amount);
	result = temp;
}

//---------------------------------------------------------------------------------------------------
//　　Hermite
//---------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Hermite(
	Vector2<T> v1, Vector2<T> t1,
	Vector2<T> v2, Vector2<T> t2, T s)
{
	T s2 = s*s, s3 = s*s*s;
	Vector2<T> temp = (2.0*s3 - 3.0*s2 + 1.0)*v1 + (-2.0*s3 + 3.0*s2)*v2+ (s3 - 2.0*s2 + s)*t1 + (s3 - s2)*t2;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> Hermite(
	Vector3<T> v1, Vector3<T> t1,
	Vector3<T> v2, Vector3<T> t2, T s)
{
	T s2 = s*s, s3 = s*s*s;
	Vector3<T> temp = (2.0*s3 - 3.0*s2 + 1.0)*v1 + (-2.0*s3 + 3.0*s2)*v2+ (s3 - 2.0*s2 + s)*t1 + (s3 - s2)*t2;	
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> Hermite(
	Vector4<T> v1, Vector4<T> t1,
	Vector4<T> v2, Vector4<T> t2, T s)
{
	T s2 = s*s, s3 = s*s*s;
	Vector4<T> temp = (2.0*s3 - 3.0*s2 + 1.0)*v1 + (-2.0*s3 + 3.0*s2)*v2+ (s3 - 2.0*s2 + s)*t1 + (s3 - s2)*t2;
	return temp;
}
AsuraTemplate AsuraInline void Hermite(
	Vector2<T> &v1, Vector2<T> &t1,
	Vector2<T> &v2, Vector2<T> &t2, T s, Vector2<T> &result)
{
	Vector2<T> temp = Hermite(v1, t1, v2, t2, s);
	result = temp;
}
AsuraTemplate AsuraInline void Hermite(
	Vector3<T> &v1, Vector3<T> &t1,
	Vector3<T> &v2, Vector3<T> &t2, T s, Vector3<T> &result)
{
	Vector3<T> temp = Hermite(v1, t1, v2, t2, s);
	result = temp;
}
AsuraTemplate AsuraInline void Hermite(
	Vector4<T> &v1, Vector4<T> &t1,
	Vector4<T> &v2, Vector4<T> &t2, T s, Vector4<T> &result)
{
	Vector4<T> temp = Hermite(v1, t1, v2, t2, s);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　CatmullRom
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> CatmullRom(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T s)
{
	T s2=s*s, s3=s*s*s;
	Vector2<T> temp = ( (-s3 + 2.0*s2 -s)*v0 + (3.0*s3 - 5.0*s2 + 2.0)*v1 + (-3.0*s3 + 4.0*s2 + s)v2 + (s3 - s2)*v3) *0.5;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> CatmullRom(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T s)
{
	T s2=s*s, s3=s*s*s;
	Vector3<T> temp = ( (-s3 + 2.0*s2 -s)*v0 + (3.0*s3 - 5.0*s2 + 2.0)*v1 + (-3.0*s3 + 4.0*s2 + s)v2 + (s3 - s2)*v3) *0.5;
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> CatmullRom(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T s)
{
	T s2=s*s, s3=s*s*s;
	AsuraVectorD<T> temp = ( (-s3 + 2.0*s2 -s)*v0 + (3.0*s3 - 5.0*s2 + 2.0)*v1 + (-3.0*s3 + 4.0*s2 + s)v2 + (s3 - s2)*v3) *0.5;
	return temp;
}
AsuraTemplate AsuraInline void CatmullRom(
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T s, Vector2<T> &result)
{
	Vector2<T> temp = CatmullRom(v0, v1, v2, v3, s);
	result = temp;
}
AsuraTemplate AsuraInline void CatmullRom(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T s, Vector3<T> &result)
{
	Vector3<T> temp = CatmullRom(v0, v1, v2, v3, s);
	result = temp;
}
AsuraTemplate AsuraInline void CatmullRom(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T s, Vector4<T> &result)
{
	Vector4<T> temp = CatmullRom(v0, v1, v2, v3);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　Bezier 
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> Bezier(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T t)
{
	T B0 = (1.0-t)*(1.0-t)*(1.0-t);
	T B1 = 3.0*t*(1.0-t)*(1.0-t);
	T B2 = 3.0*t*t*(1.0 -t);
	T B3 = t*t*t;
	Vector2<T> temp = v0*B0 +v1*B1 + v2*B2 + v3*B3;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> Bezier(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T t)
{
	T B0 = (1.0-t)*(1.0-t)*(1.0-t);
	T B1 = 3.0*t*(1.0-t)*(1.0-t);
	T B2 = 3.0*t*t*(1.0-t);
	T B3 = t*t*t;
	Vector3<T> temp = v0*B0 + v1*B1 + v2*B2 + v3*B3;
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> Bezier(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T t)
{
	T B0 = (1.0-t)*(1.0-t)*(1.0-t);
	T B1 = 3.0*t*(1.0-t)*(1.0-t);
	T B2 = 3.0*t*t*(1.0-t);
	T B3 = t*t*t;
	Vector4<T> temp = v0*B0 + v1*B1 + v2*B2 + v3*B3;
	return temp;
}
AsuraTemplate AsuraInline void Bezier(
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T t, Vector2<T> &result)
{
	Vector2<T> temp = Bezier(v0, v1, v2, v3, t);
	result = temp;
}
AsuraTemplate AsuraInline void Bezier(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T t, Vector3<T> &result)
{
	Vector3<T> temp = Bezier(v0, v1, v2, v3, t);
	result = temp;
}
AsuraTemplate AsuraInline void Bezier(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T t, Vector4<T> &result)
{
	Vector4<T> temp = Bezier(v0, v1, v2, v3, t);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　B_Spline
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Vector2<T> B_Spline(
	Vector2<T> v0, Vector2<T> v1,
	Vector2<T> v2, Vector2<T> v3, T t)
{
	T X0 = ((1.0/6.0)*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X1 = (0.5*t*t*t) - (t*t) + (2.0/3.0);
	T X2 = (-0.5*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X3 = (1.0/6.0)*t*t*t;
	Vector2<T> temp = X0*v0 + X1*v1 + X2*v2 + X3*v3;
	return temp;
}
AsuraTemplate AsuraInline Vector3<T> B_Spline(
	Vector3<T> v0, Vector3<T> v1,
	Vector3<T> v2, Vector3<T> v3, T t)
{
	T X0 = ((1.0/6.0)*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X1 = (0.5*t*t*t) - (t*t) + (2.0/3.0);
	T X2 = (-0.5*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X3 = (1.0/6.0)*t*t*t;
	Vector3<T> temp = X0*v0 + X1*v1 + X2*v2 + X3*v3;
	return temp;
}
AsuraTemplate AsuraInline Vector4<T> B_Spline(
	Vector4<T> v0, Vector4<T> v1,
	Vector4<T> v2, Vector4<T> v3, T t)
{
	T X0 = ((1.0/6.0)*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X1 = (0.5*t*t*t) - (t*t) + (2.0/3.0);
	T X2 = (-0.5*t*t*t) + (0.5*t*t) + (0.5*t) + (1.0/6.0);
	T X3 = (1.0/6.0)*t*t*t;
	Vector4<T> temp = X0*v0 + X1*v1 + X2*v2 + X3*v3;
	return temp;
}
AsuraTemplate AsuraInline void B_Spline(
	Vector2<T> &v0, Vector2<T> &v1,
	Vector2<T> &v2, Vector2<T> &v3, T t, Vector2<T> &result)
{
	Vector2<T> temp = B_Spline(v0, v1, v2, v3, t);
	result = temp;
}
AsuraTemplate AsuraInline void B_Spline(
	Vector3<T> &v0, Vector3<T> &v1,
	Vector3<T> &v2, Vector3<T> &v3, T t, Vector3<T> &result)
{
	Vector3<T> temp = B_Spline(v0, v1, v2, v3);
	result = temp;
}
AsuraTemplate AsuraInline void B_Spline(
	Vector4<T> &v0, Vector4<T> &v1,
	Vector4<T> &v2, Vector4<T> &v3, T t, Vector4<T> &result)
{
	Vector4<T> temp = B_Spline(v0, v1, v2, v3);
	result = temp;
}

//
//
//
AsuraTemplate AsuraInline Vector2<T> SmoothStep(Vector2<T> value1, Vector2<T> value2, T amout)
{
	T s1 = clamp(amount, 0.0, 1.0);
    return Lerp(value1, value2, (s1 * s1) * (3.0 - (2.0 * s1)));
}
AsuraTemplate AsuraInline Vector3<T> SmoothStep(Vector3<T> value1, Vector3<T> value2, T amout)
{
	 T s1 = clamp(amount, 0.0, 1.0);
     return Lerp(value1, value2, (s1 * s1) * (3.0 - (2.0 * s1)));
}
AsuraTemplate AsuraInline Vector4<T> SmoothStep(Vector4<T> value1, Vector4<T> value2, T amout)
{
	 T s1 = clamp(amount, 0.0, 1.0);
     return Lerp(value1, value2, (s1 * s1) * (3.0 - (2.0 * s1)));
}
AsuraTemplate AsuraInline void SmoothStep(Vector2<T> &value1, Vector2<T> &value2, T amout, Vector2<T> &result)
{
	Vector2<T> temp = SmoothStep(value1, value2, amount);
	result = temp;
}
AsuraTemplate AsuraInline void SmoothStep(Vector3<T> &value1, Vector3<T> &value2, T amout, Vector3<T> &result)
{
	Vector3<T> temp = SmoothStep(value1, value2, amount);
	result = temp;
}
AsuraTemplate AsuraInline void SmoothStep(Vector4<T> &value1, Vector4<T> &value2, T amout, Vector4<T> &result)
{
	Vector4<T> temp = SmoothStep(value1, value2, amount);
	result = temp;
}


//
//
//
AsuraTemplate AsuraInline Vector2<T> Transform(Vector2<T> position, Matrix<T> matrix)
{
	return Vector2<T>( 
		((position.x * matrix._11 ) + (position.y * matrix._21)) + matrix._41,
		((position.x * matrix._12) + (position.y * matrix._22)) + matrix._42);
}
AsuraTemplate AsuraInline Vector3<T> Transform(Vector3<T> position, Matrix<T> matrix)
{
	return Vector3<T>(
		( ((position.x * matrix._11) + (position.y * matrix._21)) + (position.z * matrix._31)) + matrix._41,
		( ((position.x * matrix._12) + (position.y * matrix._22)) + (position.z * matrix._32)) + matrix._42,
		( ((position.x * matrix._13) + (position.y * matrix._23)) + (position.z * matrix._33)) + matrix._43 );
}
AsuraTemplate AsuraInline Vector4<T> Transform(Vector4<T> position, Matrix<T> matrix)
{
	return Vector4<T>(
		( ( ((position.x * matrix._11) + (position.y * matrix._21)) + (position.z * matrix._31) ) + (position.w * matrix._41)),
		( ( ((position.x * matrix._12) + (position.y * matrix._22)) + (position.z * matrix._32) ) + (position.w * matrix._42)),
		( ( ((position.x * matrix._13) + (position.y * matrix._23)) + (position.z * matrix._33) ) + (position.w * matrix._43)),
		( ( ((position.x * matrix._14) + (position.y * matrix._24)) + (position.z * matrix._34) ) + (position.w * matrix._44)) );
}

AsuraTemplate AsuraInline void Transform(Vector2<T> &position, Matrix<T> &matrix, Vector2<T> &result)
{
	Vector2<T> temp = Transform(position, matrix);
	result = temp;
}
AsuraTemplate AsuraInline void Transform(Vector3<T> &position, Matrix<T> &matrix, Vector3<T> &result)
{
	Vector3<T> temp = Transform(position, matrix);
	result = temp;
}
AsuraTemplate AsuraInline void Transform(Vector4<T> &position, Matrix<T> &matrix, Vector4<T> &result)
{
	Vector4<T> temp = Transform(position, matrix);
	result = temp;
}

AsuraTemplate Vector2<T> TransformNormal(Vector2<T> normal, Matrix<T> matrix)
{
	return Vector2<T>( 
		(normal.x * matrix._11) + (normal.y * matrix._21),
		(normal.x * matrix._12) + (normal.y * matrix._22) );
}
AsuraTemplate Vector3<T> TransformNormal(Vector3<T> normal, Matrix<T> matrix)
{
	return Vector3<T>(
		((normal.x * matrix._11) + (normal.y * matrix._21)) + (normal.z * matrix._31),
		((normal.x * matrix._12) + (normal.y * matrix._22)) + (normal.z * matrix._32),
		((normal.x * matrix._13) + (normal.y * matrix._23)) + (normal.z * matrix._33) );

}
AsuraTemplate void TransformNormal(Vector2<T> &normal, Matrix<T> &matrix, Vector2<T> &result)
{
	Vector2<T> temp = TransformNormal(normal, matrix);
	result = temp;
}
AsuraTemplate void TransformNormal(Vector3<T> &normal, Matrix<T> &matrix, Vector3<T> &result)
{
	Vector3<T> temp = TransformNormal(normal, matrix);
	result = temp;
}

/////////////////////////////////////////////////////////////////////////
//　　Matrix Function
/////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
//　　Transpose
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> Transpose(Matrix<T> value)
{
	return Matrix<T>(
		value._11, value._21, value._31, value._41,
		value._12, value._22, value._32, value._42,
		value._13, value._23, value._33, value._43,
		value._14, value._24, value._34, value._44 );
}
AsuraTemplate AsuraInline void Transpose(Matrix<T> &value, Matrix<T> &result)
{
	Matrix<T> temp = Transpose(value);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　Multiply
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> Multiply(Matrix<T> value1, Matrix<T> value2)
{
	Matrix<T> temp;
	for ( int i=0; i<4; i++ )
		for ( int j=0; j<4; j++ )
			temp.m[i][j] = value1.m[i][0] * value2.m[0][j]
								+ value1.m[i][1] * value2.m[1][j]
								+ value1.m[i][2] * value2.m[2][j]
								+ value1.m[i][3] * value2.m[3][j];

	return temp;
}
AsuraTemplate AsuraInline void Multiply(Matrix<T> &value1, Matrix<T> &value2, Matrix<T> &result)
{
	Matrix<T> temp = Multiply(value1, value2);
	result = temp;
}
AsuraTemplate AsuraInline Matrix<T> Multply(Matrix<T> value, T sacleFactor)
{
	return Matrix<T>(
		value._11*scaleFactor, value._12*sacleFcator, value._13*scaleFactor, value._14*scaleFactor,
		value._21*scaleFactor, value._22*sacleFcator, value._23*scaleFactor, value._24*scaleFactor,
		value._31*scaleFactor, value._32*sacleFcator, value._33*scaleFactor, value._34*scaleFactor,
		value._41*scaleFactor, value._42*sacleFcator, value._43*scaleFactor, value._44*scaleFactor
		);
}
AsuraTemplate AsuraInline void Multiply(Matrix<T> &value, T scaleFactor, Matrix<T> &result)
{
	Matrix<T> temp = Multiply(value, scaleFactor);
	result = temp;
}


//------------------------------------------------------------------------------------------------------
//　　MultiplyTranspose
//------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> MultiplyTranspose(Matrix<T> value1, Matrix<T> value2)
{
	Matrix<T> result;
	Multiply(value1, value2, result);
	Transpose(result, result);
	return result;
}
AsuraTemplate AsuraInline void MultiplyTranspose(Matrix<T> &value1, Matrix<T> &value2, Matrix<T> &result)
{
	Matrix<T> temp = MultiplyTranspose(value1, value2);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　Invert
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> Invert(Matrix<T> value)
{
	Matrix<T> result;
	T det = value.Determinant();
	if ( det == NULL )
	{
		result.Zero();
		return result;
	}

	T invDet = (T)1.0/det;

	result._11 = value._22*value._33*value._44 + value._23*value._34*value._42 + value._24*value._32*value._43 - value._22*value._34*value._43 - value._23*value._32*value._44 - value._24*value._33*value._42;
	result._12 = value._12*value._34*value._43 + value._13*value._32*value._44 + value._14*value._33*value._42 - value._12*value._33*value._44 - value._13*value._34*value._42 - value._14*value._32*value._43;
	result._13 = value._12*value._23*value._44 + value._13*value._24*value._42 + value._14*value._22*value._43 - value._12*value._24*value._43 - value._13*value._22*value._44 - value._14*value._23*value._42;
	result._14 = value._12*value._24*value._33 + value._13*value._22*value._34 + value._14*value._23*value._32 - value._12*value._23*value._34 - value._13*value._24*value._32 - value._14*value._22*value._33;

	result._21 = value._21*value._34*value._43 + value._23*value._31*value._44 + value._24*value._33*value._41 - value._21*value._33*value._44 - value._23*value._34*value._41 - value._24*value._31*value._43;
	result._22 = value._11*value._33*value._44 + value._13*value._34*value._41 + value._14*value._31*value._43 - value._11*value._34*value._43 - value._13*value._31*value._44 - value._14*value._33*value._41;
	result._23 = value._11*value._24*value._43 + value._13*value._21*value._44 + value._14*value._23*value._41 - value._11*value._23*value._44 - value._13*value._24*value._41 - value._14*value._21*value._43;
	result._24 = value._11*value._23*value._34 + value._13*value._24*value._31 + value._14*value._21*value._33 - value._11*value._24*value._33 - value._13*value._21*value._34 - value._14*value._23*value._41;

	result._31 = value._21*value._32*value._44 + value._22*value._34*value._41 + value._24*value._31*value._42 - value._21*value._34*value._42 - value._22*value._31*value._44 - value._24*value._32*value._41;
	result._32 = value._11*value._34*value._42 + value._12*value._31*value._44 + value._14*value._32*value._41 - value._11*value._32*value._44 - value._12*value._34*value._41 - value._14*value._31*value._42;
	result._33 = value._11*value._22*value._44 + value._12*value._24*value._41 + value._14*value._21*value._42 - value._11*value._24*value._42 - value._12*value._21*value._44 - value._14*value._22*value._41;
	result._34 = value._11*value._24*value._32 + value._12*value._21*value._34 + value._14*value._22*value._31 - value._11*value._22*value._34 - value._12*value._24*value._31 - value._14*value._21*value._32;

	result._41 = value._21*value._33*value._42 + value._22*value._31*value._43 + value._23*value._32*value._41 - value._21*value._32*value._43 - value._22*value._33*value._41 - value._23*value._31*value._42;
	result._42 = value._11*value._32*value._43 + value._12*value._33*value._41 + value._13*value._31*value._42 - value._11*value._33*value._42 - value._12*value._31*value._43 - value._13*value._32*value._41;
	result._43 = value._11*value._23*value._42 + value._12*value._21*value._43 + value._13*value._22*value._41 - value._11*value._22*value._43 - value._12*value._23*value._41 - value._13*value._21*value._42;
	result._44 = value._11*value._22*value._33 + value._12*value._23*value._31 + value._13*value._21*value._32 - value._11*value._23*value._32 - value._12*value._21*value._33 - value._13*value._22*value._31;

	result = invDet * result;
	return result;
}
AsuraTemplate AsuraInline void Invert(Matrix<T> &value, Matrix<T> &result)
{
	Matrix<T> temp = Invert(value);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateScale
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateSacle(T scale)
{
	Matrix<T> result;
	result.Identity();
	result._11 = scale;
	result._22 = scale;
	result._33 = scale;
	return result;
}
AsuraTemplate AsuraInline void CreateSacle(T scale, Matrix<T> &result)
{
	result.Identity();
	result._11 = scale;
	result._22 = scale;
	result._33 = scale;
}
AsuraTemplate AsuraInline Matrix<T> CreateScale(T xScale, T yScale, T zScale)
{
	Matrix<T> result;
	result.Identity();
	result._11 = xScale;
	result._22 = yScale;
	result._33 = zScale;
	return result;
}
AsuraTemplate AsuraInline void CreateScale(T xScale, T yScale, T zScale, Matrix<T> &result)
{
	result.Identity();
	result._11 = xScale;
	result._22 = yScale;
	result._33 = zScale;
}
AsuraTemplate AsuraInline Matrix<T> CreateScale(Vector3<T> scales)
{
	Matrix<T> result;
	result.Identity();
	result._11 = scales.x;
	resutl._22 = scales.y;
	result._33 = scale.z;
	return result;
}
AsuraTemplate AsuraInline void CreateScale(Vector3<T> &scales, Matrix<T> &result)
{
	result.Identity();
	result._11 = scales.x;
	result._22 = scales.y;
	result._33 = scales.z;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateTranslation
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateTranslation(T xPosition, T yPosition, T zPosition)
{
	Matrix<T> result;
	result.Identity();
	result._41 = xPosition;
	result._42 = yPosition;
	result._43 = zPosition;
	return result;
}
AsuraTemplate AsuraInline void CreateTranslation(T xPosition, T yPosition, T zPosition, Matrix<T> &result)
{
	result.Identity();
	result._41 = xPosition;
	result._42 = yPosition;
	result._43 = zPosition;
}
AsuraTemplate AsuraInline Matrix<T> CreateTranslation(Vector3<T> position)
{
	Matrix<T> result;
	result.Identity();
	result._41 = position.x;
	result._42 = position.y;
	result._43 = position.z;
	return result;
}
AsuraTemplate AsuraInline void CreateTranslation(Vector3<T> &position, Matrix<T> &reslut)
{
	result.Identity();
	result._41 = position.x;
	result._42 = position.y;
	result._43 = position.z;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateRotationX
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateRotationX(T radians)
{
	Matrix<T> result;
	result.Identity();
	result._22 = cos(radians);
	result._23 = sin(radians);
	result._32 = -sin(radians);
	result._33 = cos(radians);
	return result;
}
AsuraTemplate AsuraInline void CreateRotationX(T radians, Matrix<T> &result)
{
	result.Identity();
	result._22 = cos(radians);
	result._23 = sin(radians);
	result._32 = -sin(radians);
	result._33 = cos(radians);
}

//-----------------------------------------------------------------------------------------------------
//　　CreateRoataionY
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateRotationY(T radians)
{
	Matrix<T> result;
	result.Identity();
	result._11 = cos(radians);
	result._13 = -sin(radians);
	result._31 = sin(radians);
	result._33 = cos(radians);
	return result;
}
AsuraTemplate AsuraInline void CreateRotationY(T radians, Matrix<T> &result)
{
	result.Identity();
	result._11 = cos(radians);
	result._13 = -sin(radians);
	result._31 = sin(radians);
	result._33 = cos(radians);
}

//-----------------------------------------------------------------------------------------------------
//　　CreateRotationZ
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateRotationZ(T radians)
{
	Matrix<T> result;
	result.Identity();
	result._11 = cos(radians);
	result._12 = sin(radians);
	result._21 = -sin(radians);
	result._22 = cos(radians);
	return result;
}
AsuraTemplate AsuraInline void CreateRotationZ(T radians, Matrix<T> &result)
{
	result.Identity();
	result._11 = cos(radians);
	result._12 = sin(radians);
	result._21 = -sin(radians);
	result._22 = cos(radians);
}

//-----------------------------------------------------------------------------------------------------
//　　CreateFromQuaternion
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateFromQuaternion(Quaternion<T> qua)
{
	Matrix<T> result;
	T xx = qua.x*qua.x;
	T yy = qua.y*qua.y;
	T yw = qua.y*qua.w;
	T yz = qua.y*qua.z;
	T xw = qua.x*qua.w;

	result._11 = 1.0 - (2.0 * (yy + zz));
	result._12 = 2.0 * (xy + zw);
	result._13 = 2.0 * (zx - yz);
	result._14 = (T)0.0;

	result._21 = 2.0 * (xy - zw);
	result._22 = 1.0 - (2.0 * (zz + xx)); 
	result._23 = 2.0 * (yz + xw);
	result._24 = (T)0.0;

	result._31 = 2.0 * (zx + yw); 
	result._32 = 2.0 * (yz - xw);
	result._33 = 1.0 - (2.0 * (yy + xx));
	result._34 = (T)0.0;

	result._41 = (T)0.0;
	result._42 = (T)0.0;
	result._43 = (T)0.0;
	result._44 = (T)1.0;
	
	return result;
}
AsuraTemplate AsuraInline void CreateFromQuaterinon(Quaternion<T> &qua, Matrix<T> &result)
{
	Matrix<T> temp = CreateFromQuaternion(qua);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateFromAxisAngle
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateFromAxisAngle(Vector3<T> axis, T radians)
{
	Matrix<T> result;
	T sine = sin((double)radians);
	T cosine = cos((double)radians);
	T ab, bc, ca, tx, ty, tz, a = 1.0 -cosine;
	ab = axis.x * axis.y * a;
	bc = axis.y * axis.z * a;
	ca = axis.z * axis.x * a;
	tx = axis.x * axis.x;
	ty = axis.y * axis.y;
	tz = axis.z * axis.z;

	result._11 = tx + cosine * (1.0 - tx);
	result._12 = ab + axis.z * sine;
	result._13 = ca - axis.y * sine;
	result._14 = (T)0.0;

	result._21 = ab - axis.z * sine;
	result._22 = ty + cosine * (1.0 - ty);
	result._23 = bc + axis.x * sine;
	result._24 = (T)0.0;

	result._31 = ca + axis.y * sine;
	result._32 = bc - axis.x * sine;
	result._33 = tz + cosine * (1.0 - tz);
	result._34 = (T)0.0;

	result._41 = (T)0.0;
	result._42 = (T)0.0;
	result._43 = (T)0.0;
	result._44 = (T)1.0;

	return result;
}
AsuraTemplate AsuraInline void CreateFromAxisAngle(Vector3<T> &axis, T radians, Matrix<T> &result)
{
	Matrix<T> temp = CreateFromAxisAngle(axis, radians);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateLookAt
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateLookAt(Vector3<T> cameraPosition, Vector3<T> cameraTarget, Vector3<T> cameraUpVector)
{
	Matrix<T> result;
	Vector3<T> zaxis = cameraPosition - cameraTarget;
	zaxis.Normalize();

	Vector3<T> xaxis = Cross(cameraUpVector, zaxis);
	xaxis.Normalize();

	Vector3<T> yaxis = Cross(zaxis, xaxis);
	yaxis.Normalize();

	result._11 = xaxis.x;
	result._12 = yaxis.x;
	result._13 = zaxis.x;
	result._14 = (T)0.0;

	result._21 = xaxis.y;
	result._22 = yaxis.y;
	result._23 = zaxis.y;
	result._24 =(T)0.0;

	result._31 = xaxis.z;
	result._32 = yaxis.z;
	result._33 = zaxis.z;
	result._34 = (T)0.0;

	result._41 = -Dot(xaxis, cameraPosition);
	result._42 = -Dot(yaxis, cameraPosition);
	result._43 = -Dot(zaxis, cameraPosition);
	result._44 = (T)1.0;

	return result;
}
AsuraTemplate void CreateLookAt(Vector3<T> &cameraPosition, Vector3<T> &cameraTarget, Vector3<T> &cameraUpVector, Matrix<T> &result)
{
	Matrix<T> temp = CreateLookAt(cameraPosition, cameraTarget, cameraUpVector);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　CreatePerspective
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreatePerspective(T width, T height, T nearPlaneDistance, T farPlaneDistance)
{
	Matrix<T> result
	result.Zero();
	result._11 = 2.0*nearPlaneDistance/width;
	result._22 = 2.0*nearPlaneDistance/height;
	result._33 = farPlaneDistance/(nearPlaneDistance - farPlaneDistance);
	result._34 = (nearPlaneDistance*farPlaneDistance)/(nearPlaneDistance -farPlaneDistance);
	result._43 = (T)-1.0;
	return result;
}
AsuraTemplate AsuraInline void CreatePerspective(T width, T height, T nearPlaneDistance, T  farPlaneDistance, Matrix<T> &result)
{
	Matrix<T> temp = CreatePerspective(width, height, nearPlaneDistance, farPlaneDistance);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　CreatePerspectiveFieldOfView
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreatePerspectiveFieldOfView(T fieldOfView, T aspectRatio, T nearPlaneDistance, T farPlaneDistance)
{
	Matrix<T> result;
	result.Zero();
	T yScale = (T)cot(fieldOfView/2.0);
	T xScale = yScale/aspectRatio;
	result._11 = xScale;
	result._22 = yScale;
	result._33 = farPlaneDistance/(nearPlaneDistance - farPlaneDistance);
	result._34 = (T)-1.0;
	result._43 = (nearPlaneDistance*farPlaneDistance)/(nearPlaneDistance - farPlaneDistance);
	return result;
}
AsuraTemplate AsuraInline void CreatePerspectiveFieldOfView(T fieldOfView, T aspectRatio, T nearPlaneDistance, T farPlaneDistance, Matrix<T> &result)
{
	Matrix<T> temp = CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　CreatePerspectiveOffcenter
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreatePerspectiveOffcenter(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane)
{
	Matrix<T> result;
	result.Zero();
	result._11 = 2.0*zNearPlane/(right - left);
	result._22 = 2.0*zNearPlane/(top - bottom);
	result._31 = (left + right)/(right - left);
	result._32 = (top + bottom)/(top -bottom);
	result._33 = zFarPlane/(zNearPlane - zFarPlane);
	result._34 = (T)-1.0;
	result._43 = zNearPlane*zFarPlane/(zNearPlane - zFarPlane);
	return output;
}
AsuraTemplate AsuraInline void CreatePerspectiveOffcenter(T left, T right, T bottom, T top, T nearPlaneDistance, T farPlaneDistance, Matrix<T> &result)
{
	Matrix<T> temp = CreatePerspectiveOffcenter(left, right, bottom, top, nearPlaneDistance, farPlaneDistance);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　CreateOrthographic
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateOrthographic(T width, T height, T zNearPlane, T zFarPlane)
{
	Matrix<T> result;
	result.Zero();
	result._11 = 2.0/width;
	result._22 = 2.0/height;
	result._33 = 1.0/(zNearPlane - zFarPlane);
	result._43 = zNearPlane/(zNearPlane - zFarPlane);
	result._44 = (T)1.0;
	return result;
}
AsuraTemplate AsuraInline void CreateOrthographic(T width, T height, T zNearPlane, T zFarPlane, Matrix<T> &result)
{
	Matrix<T> temp = CreateOrthographic(width, height, zNearPlane, zFarPlane);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateOrthographicOffcenter
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateOrthographicOffcenter(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane)
{
	Matrix<T> result;
	result.Zero();
	result._11 = 2.0/(right - left);
	result._22 = 2.0/(top -bottom);
	result._33 = 1.0/(zNearPlane - zFraPlane);
	result._41 = (left + right)/(left - right);
	result._42 = (top +bottom)/(bottom -top);
	result._43 = zNearPlane/(zNearPlane - zFarPlane);
	result._44 = (T)1.0;
	return result;
}
AsuraTemplate AsuraInline void CreateOrthographicOffcenter(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane, Matrix<T> &result)
{
	Matrix<T> temp = CreateOrthographicOffcenter(left, right, bottom, top, zNearPlane, zFarPlane);
	result = temp;
}


//-----------------------------------------------------------------------------------------------------
//　　CreateShadow
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateShadow(Vector4<T> lightDirection, Plane<T> plane)
{
	Plane<T> result;
	Plane<T> p = Normalize(plane);
	Vector4<T> l = Normalize(lightDirection);
	T = Dot(p, l);
	result._11 = p.a * l.x + d;
	result._12 = p.a * l.y;
	result._13 = p.a * l.z;
	result._14 = p.a * l.w;

	result._21 = p.b * l.x;
	result._22 = p.b * l.y + d;
	result._23 = p.b * l.z;
	result._24 = p.b * l.w;

	result._31 = p.c * l.x;
	result._32 = p.c + l.y;
	result._33 = p.c * l.z + d;
	result._34 = p.c * l.w;

	result._41 = p.d * l.x;
	result._42 = p.d * l.y;
	result._43 = p.d * l.z;
	result._44 = p.d * l.w + d;

	return result;
}
AsuraTemplate AsuraInline void CreateShadow(Vector4<T> &lightDirection, Plane<T> &plane, Matrix<T> &result)
{
	Matrix<T> temp = CreateShadow(lightDirection, plane);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　CreateReflect
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Matrix<T> CreateReflect(Plane<T> plane)
{
	Matrix<T> result;
	result._11 = -2.0 * plane.a * plane.a + 1.0;
	result._12 = -2.0 * plane.b * plane.a;
	result._13 = -2.0 * plane.c * plane.a;
	result._14 = (T)0.0;

	result._21 = -2.0 * plane.a * plane.b;
	result._22 = -2.0 * plane.b * plane.b + 1.0;
	result._23 = -2.0 * plane.c * plane.b;
	result._24 = (T)0.0;

	result._31 = -2.0 * plane.a * plane.c;
	result._32 = -2.0 * plane.b * plane.c;
	result._33 = -2.0 * plane.c * plane.c + 1.0;
	result._34 = (T)0.0;

	result._41 = -2.0 * plane.a * plane.d;
	result._42 = -2.0 * plane.b * plane.d;
	result._43 = -2.0 * plane.c * plane.d;
	result._44 = 1.0;
	return result;
}
AsuraTemplate AsuraInline void CreateReflect(Plane<T> &plane, Matrix<T> &result)
{
	Matrix<T> temp = CreateRefect(plane);
	result = temp;
}

//------------------------------------------------------------------------------------------------------
//　　Lerp
//------------------------------------------------------------------------------------------------------
AsuraTemplate Matrix<T> Lerp(Matrix<T> value1, Matrix<T> value2, T amout)
{
	Matrix<T> result;
	result = (1.0-amout)*value1 + amout*value2;
	return result;
}
AsuraTemplate void Lerp(Matrix<T> &value1, Matrix<T> &value2, T amount, Matrix<T> &result)
{
	Matrix<T> temp = Lerp(value1, value2, amount);
	result = temp;
}

////////////////////////////////////////////////////////////////////////////
//　　Plane Function
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------------
//　　Dot
//--------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T Dot(Plane<T> p, Vector4<T> v)
{
	return (p.a*v.x + p.b*v.y + p.c*v.z + p.d*v.w); 
}
AsuraTemplate AsuraInline void Dot(Plane<T> &p, Vector4<T> &v, T &result)
{
	result = (p.a*v.x + p.b*v.y + p.c*v.z + p.d* v.w);
}

//---------------------------------------------------------------------------------------------------------
//　　DotCoordinate
//---------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T DotCoordinate(Plane<T> p, Vector3<T> v)
{
	return (p.a*v.x + p.b*v.y + p.c*v.z + p.d); 
}
AsuraTemplate AsuraInline void DotCoordinate(Plane<T> &p, Vector3<T> &v, T &result)
{
	result = (p.a*v.x + p.b*v.y + p.c*v.z + p.d);
}

//--------------------------------------------------------------------------------------------------------
//　　DotNormal
//--------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T DotNormal(Plane<T> p, Vector3<T> v)
{
	return (p.a*v.x + p.b*v.y + p.c*v.z + p.d); 
}
AsuraTemplate AsuraInline void DotNormal(Plane<T> &p, Vector3<T> &v, T &result)
{
	result = (p.a*v.x + p.b*v.y + p.c*v.z + p.d); 
}

//-------------------------------------------------------------------------------------------------------
//　　Normalize
//-------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Plane<T> PlaneNormalize(Plane<T> p)
{
	Plane<T> result;
	T mag = sqrt(p.a*p.a + p.b*p.b + p.c*p.c);
	if ( mag > 0 )
	{
		result.a = p.a/mag;
		result.b = p.b/mag; 
		result.c = p.c/mag;
		result.d = p.d;
	}
	else
	{
		result.a = result.b = result.c = 0.0;
		result.d = p.d;
	}
	return result;
}
AsuraTemplate AsuraInline void Normalize(Plane<T> &v, Plane<T> &result)
{
	Plane<T> temp = Normalize(v);
	result = temp;
}

////////////////////////////////////////////////////////////////////////////
//　　Quaternion Function
////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
//　　Dot
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline T Dot(Quaternion<T> q1, Quaternion<T> q2)
{
	return (T)(q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w); 
}
AsuraTemplate AsuraInline void Dot(Quaternion<T> &q1, Quaternion<T> &q2, T &reslut)
{
	result = (q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w); 
}

//-----------------------------------------------------------------------------------------------------
//　　Conjugate
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> Conjugate(Quaternion<T> qua)
{
	return Quaternion<T>(-qua.x, -qua.y, -qua.z, qua.w);
}
AsuraTemplate AsuraInline void Conjugate(Quaternion<T> &qua, Quaternion<T> &result)
{
	Quaternion<T> temp = Conjugate(qua);
	result = temp;
}

//----------------------------------------------------------------------------------------------------
//　　Normalize
//----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> Normalize(Quaternion<T> qua)
{
	Quaterion<T> result;
	T mag = sqrt(qua.x*qua.x + qua.y*qua.y + qua.z*qua.z + qua.w* qua.w); 
	if ( mag > 0 )
	{
		T s = 1.0/mag;
		result.x = qua.x*s; 
		result.y = qua.y*s; 
		result.z = qua.z*s;
		result.w = qua.w*s;
	}
	else
	{
		result.x = result.y = result.z = result.w = (T)0.0;
	}
	return result; 
}
AsuraTemplate AsuraInline Quaternion<T> Normalize(Quaternion<T> &qua, Quaternion<T> &result)
{
	Quaternion<T> temp = Normalize(qua);
	result = temp;
}

//---------------------------------------------------------------------------------------------------
//　　Inverse
//---------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> Inverse(Quaternion<T> qua)
{
	Quaternion<T> result(-qua.x, -qua.y, -qua.z, qua.w); 
	result.Normlize(); 
	return result; 
}
AsuraTemplate AsuraInline void Inverse(Quaternion<T> &qua, Quaternion<T> &result)
{
	Quaternion<T> temp = Inverse(qua);
	result = temp;
}

//---------------------------------------------------------------------------------------------------
//　　CreateFromYawPitchRoll
//---------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> CreateFromYawPitchRoll(T yaw, T pitch, T roll) 
{ 
	Quaterinon<T> result;
	T sr = (T)sin(roll*0.5);
	T cr = (T)cos(roll*0.5);
	T sp = (T)sin(pitch*0.5);
	T cp = (T)cos(pitch*0.5);
	T sy = (T)sin(yaw*0.5);
	T cy = (T)cos(yaw*0.5);
	result.x = -(sy*sp*cr) + (cy*cp*sr);
	result.y = (cy*sp*cr) + (sy*cp*sr);
	result.z = -(cy*sp*sr) + (sy*cp*cr);
	result.w = (cy*cp*cr) + (sy*sp*sr);
	return result;
}
AsuraTemplate AsuraInline void CreateFromYawPitchRoll(T yaw, T pitch, T roll, Quaternion<T> &result)
{
	Quaternion<T> temp = CreateFromYawPitchRoll(yaw, pitch, roll);
	result = temp;
}

//------------------------------------------------------------------------------------------------------
//　　Slerp
//------------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> Slerp(Quaternion<T> q1, Quaternion<T> q2, T t)
{
	if ( t <= 0.0 ) return q1;
	if ( t >= 1.0 ) return q2;

	T cosOmega = DotProduct(q1, q2)
	T q1x = q1.x;
	T q1y = q1.y;
	T q1z = q1.z;
	T q1w = q1.w;

	if ( cosOmega < 0.0 )
	{
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega -= cosOmega;
	}

	T k1, k2;
	if ( cosOmega > 0.9999 )
	{
		k1 = 1.0 - t;
		k1 = t;
	}
	else
	{
		T sinOmega = (T)sqrt(1.0 - (cosOmega*cosOmega));
		T omega = (T)atan2(sinOmega, cosOmega);
		T sinOmegaInv  = 1.0/sinOmega;
		k1 = (T)sin((1.0-t)*omega)*sinOmegaInv;
		k2 = (T)sin(t*omega)*sinOmegaInv;
	}
	return Quaternion<T>( 
		(k1*q1.x) + (k2*q1x),
		(k1*q1.y) + (k2*q1y),
		(k1*q1.z) + (k2*q1z),
		(k1*q1w) + (k2*q1w)
		);
}
AsuraTemplate AsuraInline void Slerp(Quaternion<T> &q1, Quaternion<T> &q2, T t, Quaternion<T> &result)
{
	Quaternion<T> temp = Slerp(q1, q2, t);
	result = temp;
}

//-----------------------------------------------------------------------------------------------------
//　　Squad
//-----------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline Quaternion<T> Squad(
	Quaternion<T> q1, Quaternion<T> a,
	Quaternion<T> b, Quaternion<T> c, T t)
{
	return Slerp(Slerp(q1, c, t), Slerp(a, b, t), 2.0*t*(1.0 - t));
}
AsuraTemplate AsuraInline void Squad(
	 Quaternion<T> &q1, Quaternion<T> &a,
	 Quaternion<T> &b, Quaternion<T> &c, T t, Quaternion<T> &result)
{
	Quaternion<T> temp = Squad(q1, a, b, c, t);
	result = temp;
}

//--------------------------------------------------------------------------------------------------
//　　Negative
//--------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline
Color<T> Negative(Color<T> col)
{
	return Color<T>(1.0-col.r, 1.0-col.g, 1.0-col.b, col.a);
}
AsuraTemplate AsuraInline
void Negative(Color<T> &col, Color<T>& result)
{
	Color<T> temp=Negative(col);
	result = temp;
}

//-------------------------------------------------------------------------------------------------
//　　Lerp
//-------------------------------------------------------------------------------------------------
AsuraTemplate AsuraInline
Color<T> Lerp(Color<T> c1, Color<T> c2, T f)
{
	return Color<T>(
		c1.r + f  * (c2.r - c1.r),
		c1.g + f * (c2.g - c1.g),
		c1.b + f * (c2.b - c1.g),
		c1.a + f * (c2.a - c1.a)
		);
}
AsuraTemplate AsuraInline
void Lerp(Color<T>& c1, Color<T> &c2, T f, Color<T>& result)
{
	Color<T> temp = Lerp(c1, c2, f);
	result = temp;
}

AsuraInline
ulong ColorARGB(ulong a, ulong r, ulong g, ulong b)
{
	return ((ulong)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)));
}

AsuraInline
ulong ColorRGBA(ulong r, ulong g, ulong b, ulong a)
{
	return ColorARGB(a, r, g, b);
}

AsuraInline
ulong ColorXRGB(ulong r, ulong g, ulong b)
{
	return ColorARGB(0xff, r, g, b);
}

}	// namespace AsuraMath

#endif	//　_ASURA_MATH_INL_INCLUDED_