﻿//-------------------------------------------------------------------------------------
// File : asdxGeometry.inl
// wesc : Geometry Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------

#ifndef __ASDX_GEOMETRY_INL__
#define __ASDX_GEOMETRY_INL__


namespace asdx {

///////////////////////////////////////////////////////////////////////////////////////
// Vector3x8 class
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8::Vector3x8()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="v0">1番目の点</param>
///<param name="v1">2番目の点</param>
///<param name="v2">3番目の点</param>
///<param name="v3">4番目の点</param>
///<param name="v4">5番目の点</param>
///<param name="v5">6番目の点</param>
///<param name="v6">7番目の点</param>
///<param name="v7">8番目の点</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8::Vector3x8
(
    const Vector3& v0,
    const Vector3& v1,
    const Vector3& v2,
    const Vector3& v3,
    const Vector3& v4,
    const Vector3& v5,
    const Vector3& v6,
    const Vector3& v7
)
{
    points[0] = v0;
    points[1] = v1;
    points[2] = v2;
    points[3] = v3;
    points[4] = v4;
    points[5] = v5;
    points[6] = v6;
    points[7] = v7;
}

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="pValues">要素数8の3次元ベクトル配列です.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8::Vector3x8( Vector3* pValues )
{
    for( u32 i=0; i<NUM_COUNT; ++i )
    { points[ i ] = pValues[ i ]; }
}

///------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name="value">コピー元の値.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8::Vector3x8( const Vector3x8 &value )
{
    for( u32 i=0; i<NUM_COUNT; ++i )
    { points[ i ] = value.points[ i ]; }
}

///------------------------------------------------------------------------------------
///<summary>デストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8::~Vector3x8()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>インデクサです.</summary>
///<param name="index">取得する要素番号</param>
///<return>指定された要素番号の3次元ベクトルを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3& Vector3x8::operator [] ( u32 index )
{
    assert( index < NUM_COUNT );
    return points[ index ];
}

///------------------------------------------------------------------------------------
///<summary>インデクサです(const版).</summary>
///<param name="index">取得する要素番号</param>
///<return>指定された要素番号の3次元ベクトルを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
const Vector3& Vector3x8::operator [] ( u32 index ) const
{
    assert( index < NUM_COUNT );
    return points[ index ];
}

///------------------------------------------------------------------------------------
///<summary>サイズを取得します.</summary>
///<return>常に8を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
u32     Vector3x8::GetSize() const 
{ return NUM_COUNT; }

///------------------------------------------------------------------------------------
///<summary>指定された要素番号の3次元ベクトルの値を取得します.</summary>
///<param name="index">取得する要素番号</param>
///<return>指定された要素番号の3次元ベクトルを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3& Vector3x8::GetAt( u32 index ) 
{
    assert( index < NUM_COUNT );
    return points[ index ];
}

///------------------------------------------------------------------------------------
///<summary>指定された要素番号の3次元ベクトルに値を設定します.</summary>
///<param name="index">設定する要素番号</param>
///<param name="value">設定する3次元ベクトルの値</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Vector3x8::SetAt( u32 index, const Vector3& value )
{
    assert( index < NUM_COUNT );
    points[ index ] = value;
}

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値</param>
///<return>代入結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8&  Vector3x8::operator = ( const Vector3x8& value )
{
    for( u32 i=0; i<NUM_COUNT; ++i )
    { points[ i ] = value.points[ i ]; }
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>等価であればtrue, 非等価であればfalseを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    Vector3x8::operator == ( const Vector3x8& value ) const
{
    if ( this != (&value) )
    { return true; }

    return ( memcmp( points, value.points, sizeof( Vector3 ) * NUM_COUNT ) == 0 );
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>非等価であればtrue, 等価であればfalseを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    Vector3x8::operator != ( const Vector3x8& value ) const
{
    if ( this == (&value) )
    { return false; }

    return ( memcmp( points, value.points, sizeof( Vector3 ) * NUM_COUNT ) != 0 );
}



///////////////////////////////////////////////////////////////////////////////////////
// Plane class
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>乗算演算子です.</summary>
///<param name="scalar">乗算するスカラー値</param>
///<param name="value">乗算される平面式</param>
///<return>スカラー乗算した結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane operator * ( const f32 scalar, const Plane& value )
{
    return Plane(
        value.normal.x * scalar,
        value.normal.y * scalar,
        value.normal.z * scalar,
        value.d        * scalar
    );
}

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane()
{ /* wO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="pValues">要素数4の配列です</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane( const f32* pValues )
{
    assert( pValues != NULL );
    normal.x = pValues[ 0 ];
    normal.y = pValues[ 1 ];
    normal.z = pValues[ 2 ];
    d        = pValues[ 3 ];
}

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="nx">法線ベクトルのX成分です.</param>
///<param name="ny">法線ベクトルのY成分です.</param>
///<param name="nz">法線ベクトルのZ成分です.</param>
///<param name="nd">原点からの距離です.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane( const f32 nx, const f32 ny, const f32 nz, const f32 nd )
{
    normal.x = nx;
    normal.y = ny;
    normal.z = nz;
    d        = nd;
}

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="n">法線ベクトルです</param>
///<param name="d">原点からの距離です</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane( const Vector3& n, const f32 nd )
{
    normal.x = n.x;
    normal.y = n.y;
    normal.z = n.z;
    d        = nd;
}

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="value">4次元ベクトルです</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane( const Vector4& value )
{
    normal.x = value.x;
    normal.y = value.y;
    normal.z = value.z;
    d        = value.w;
}

///-------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name="value">コピー元の値です.</param>
///-------------------------------------------------------------------------------------
ASDX_INLINE
Plane::Plane( const Plane& value )
: normal( value.normal )
, d     ( value.d )
{
    /* DO_MOTHING */
}

///------------------------------------------------------------------------------------
///<summary>デストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::~Plane()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>f32*型へのキャストです.</summary>
///<return>最初の要素へのポインタを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::operator f32* ()
{ return &normal.x; }

///------------------------------------------------------------------------------------
///<summary>const f32*型へのキャストです.</summary>
///<return>最初の要素へのポインタを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane::operator const f32* () const
{ return &normal.x; }

///------------------------------------------------------------------------------------
///<summary>乗算代入演算子です.</summary>
///<param name="scalar">乗算するスカラー値</param>
///<return>スカラー乗算した結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane&  Plane::operator *= ( const f32 scalar )
{
    normal.x *= scalar;
    normal.y *= scalar;
    normal.z *= scalar;
    d        *= scalar;
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>除算代入演算子です.</summary>
///<param name="scalar">除算するスカラー値</param>
///<return>スカラー除算した結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane&  Plane::operator /= ( const f32 scalar )
{
    assert( scalar != 0.0f );
    register f32 invScalar = 1.0f / scalar;
    normal.x *= invScalar;
    normal.y *= invScalar;
    normal.z *= invScalar;
    d        *= invScalar;
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>正符号演算子です.</summary>
///<return>自分自身の値を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::operator + () const
{
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>負符号演算子です.</summary>
///<return>負符号をつけた値を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::operator - () const
{
    return Plane( -normal.x, -normal.y, -normal.z, -d );
}

///------------------------------------------------------------------------------------
///<summary>乗算演算子です.</summary>
///<param name="scalar">乗算するスカラー値</param>
///<return>スカラー乗算した結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::operator * ( const f32 scalar ) const
{
    return Plane( 
        normal.x * scalar,
        normal.y * scalar,
        normal.z * scalar,
        d        * scalar 
    );
}

///------------------------------------------------------------------------------------
///<summary>除算演算子です.</summary>
///<param name="scalar">除算するスカラー値</param>
///<return>スカラー除算した結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::operator / ( const f32 scalar ) const
{
    assert( scalar != 0.0f );
    register f32 invScalar = 1.0f / scalar;
    return Plane(
        normal.x * invScalar,
        normal.y * invScalar,
        normal.z * invScalar,
        d        * invScalar
    );
}

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値</param>
///<return>代入結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane&  Plane::operator = ( const Plane& value )
{
    normal.x = value.normal.x;
    normal.y = value.normal.y;
    normal.z = value.normal.z;
    d        = value.d;
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>等価であればtrue，非等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    Plane::operator == ( const Plane& value ) const
{
    return ( normal.x == value.normal.x )
        && ( normal.y == value.normal.y )
        && ( normal.z == value.normal.z )
        && ( d        == value.d );
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>非等価であればtrue, 等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    Plane::operator != ( const Plane& value ) const
{
    return ( normal.x != value.normal.x )
        || ( normal.y != value.normal.y )
        || ( normal.z != value.normal.z )
        || ( d        != value.d );
}

///------------------------------------------------------------------------------------
///<summary>正規化を行います.</summary>
///<return>正規化した結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane&  Plane::Normalize()
{
    register f32 mag = sqrtf( 
        ( normal.x * normal.x ) 
      + ( normal.y * normal.y )
      + ( normal.z * normal.z )
      + ( d * d ) );
    assert( mag != 0.0f );
    register f32 invMag = 1.0f / mag;
    normal.x *= invMag;
    normal.y *= invMag;
    normal.z *= invMag;
    d        *= invMag;
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>零除算を考慮して正規化を試みます.</summary>
///<param name="set">長さが0の場合に設定する値.</param>
///<return>長さが0でなければ正規化した結果，そうでなければsetを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane&  Plane::SafeNormalize( const Plane& set )
{
    register f32 mag = sqrtf( ( normal.x * normal.x ) + ( normal.y * normal.y ) + ( normal.z * normal.z ) + ( d * d ) );
    if ( mag != 0.0f )
    {
        register f32 invMag = 1.0f / mag;
        normal.x *= invMag;
        normal.y *= invMag;
        normal.z *= invMag;
        d        *= invMag;
    }
    else
    {
        normal.x = set.normal.x;
        normal.y = set.normal.y;
        normal.z = set.normal.z;
        d        = set.d;
    }
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>内積を求めます.</summary>
///<param name="value">内積を求める4次元ベクトル</param>
///<return>4次元ベクトルとの内積を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::Dot( const Vector4& value ) const
{
    return ( normal.x * value.x ) + ( normal.y * value.y ) + ( normal.z * value.z ) + ( d * value.w );
}

///------------------------------------------------------------------------------------
///<summary>内積の値に平面の距離を足した値を求めます.</summary>
///<param name="value">内積を求める3次元ベクトル</param>
///<return>3次元ベクトルとの内積に平面の距離を足した値を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::DotCoordinate( const Vector3& value ) const
{
    return ( normal.x * value.x ) + ( normal.y * value.y ) + ( normal.z * value.z ) + d;
}

///------------------------------------------------------------------------------------
///<summary>内積を求めます.</summary>
///<param name="value">内積を求める3次元ベクトル</param>
///<return>法線ベクトルと3次元ベクトルの内積の値を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::DotNormal( const Vector3& value ) const
{
    return ( normal.x * value.x ) + ( normal.y * value.y ) + ( normal.z * value.z );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する点</param>
///<return>点との交差判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType Plane::Intersects( const Vector3& point ) const
{
    register f32 dist = ( normal.x * point.x )
                      + ( normal.y * point.y )
                      + ( normal.z * point.z )
                      + d;

    if ( dist > 0.0f )
    { return PlaneIntersectionType::FRONT; }
    
    if ( dist < 0.0f )
    { return PlaneIntersectionType::BACK; }

    return PlaneIntersectionType::INTERSECTING;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界箱</param>
///<return>境界箱との交差判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType   Plane::Intersects( const BoundingBox& value ) const
{
    // 境界箱の8角の点を取得.
    Vector3x8 corners = value.GetCorners();

    // 最初の点との交差判定.
    register f32 lastDist = DotCoordinate( corners.GetAt( 0 ) );

    for ( u32 i=1; i<corners.GetSize(); ++i )
    {
        f32 dist = DotCoordinate( corners.GetAt( i ) );

        if ( ( dist <= 0.0f && lastDist > 0.0f ) 
          || ( dist >= 0.0f && lastDist < 0.0f ) )
        { return PlaneIntersectionType::INTERSECTING; }

        // 更新.
        lastDist = dist;
    }

    if ( lastDist > 0.0f )
    { return PlaneIntersectionType::FRONT; }

    return PlaneIntersectionType::BACK;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界球</param>
///<return>境界球との交差判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType   Plane::Intersects( const BoundingSphere& value ) const
{
    register f32 dist = ( normal.x * value.center.x ) + ( normal.y * value.center.y ) + ( normal.z * value.center.z ) + d;

    if ( dist > value.radius )
    { return PlaneIntersectionType::FRONT; }

    if ( dist < -value.radius )
    { return PlaneIntersectionType::BACK; }

    return PlaneIntersectionType::INTERSECTING;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界錘台</param>
///<return>境界錘台との交差判定結果を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType   Plane::Intersects( const BoundingFrustum& value ) const
{
    Vector3x8 corners = value.GetCorners();

    register f32 lastDist = DotCoordinate( corners.GetAt( 0 ) );

    for ( u32 i=1; i<corners.GetSize(); ++i )
    {
        f32 dist = DotCoordinate( corners.GetAt( i ) );

        if ( ( dist <= 0.0f && lastDist > 0.0f )
          || ( dist >= 0.0f && lastDist < 0.0f ) )
        { return PlaneIntersectionType::INTERSECTING; }

        lastDist = dist;
    }

    if ( lastDist > 0.0f )
    { return PlaneIntersectionType::FRONT; }

    return PlaneIntersectionType::BACK;
}

///------------------------------------------------------------------------------------
///<summary>内積の値を求めます.</summary>
///<param name="plane">平面式</param>
///<param name="vec">4次元ベクトル</param>
///<return>4次元ベクトルとの内積の値を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::Dot( const Plane& plane, const Vector4& vec )
{
    return ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ) + ( plane.d * vec.w );
}

///------------------------------------------------------------------------------------
///<summary>内積の値を求めます.</summary>
///<param name="plane">平面式</param>
///<param name="vec">4次元ベクトル</param>
///<param name="result">内積</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Plane::Dot( const Plane& plane, const Vector4& vec, f32& result )
{
    result = ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ) + ( plane.d * vec.w );
}

///------------------------------------------------------------------------------------
///<summary>内積の値に平面の距離を足した値を求めます.</summary>
///<param name="plane">平面式</param>
///<param name="vec">3次元ベクトル</param>
///<return>平面式と3次元ベクトルの内積の値に平面の距離を足した値を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::DotCoordinate( const Plane& plane, const Vector3& vec )
{
    return ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ) + plane.d;
}

///------------------------------------------------------------------------------------
///<summary>内積の値に平面の距離を足した値を求めます.</summary>
///<param name="palne">平面式</param>
///<param name="vec">3次元ベクトル</param>
///<param name="result">内積の値に平面の距離を足した値</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Plane::DotCoordinate( const Plane& plane, const Vector3& vec, f32& result )
{
    result = ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ) + plane.d;
}

///------------------------------------------------------------------------------------
///<summary>内積を求めます.</summary>
///<param name="plane">平面式</param>
///<param name="vec">3次元ベクトル</param>
///<return>法線ベクトルと3次元ベクトルとの内積の値を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32     Plane::DotNormal( const Plane& plane, const Vector3& vec )
{
    return ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ); 
}

///------------------------------------------------------------------------------------
///<summary>内積を求めます.</summary>
///<param name="plane">平面式</param>
///<param name="vec">3次元ベクトル</param>
///<param name="result">法線ベクトルと3次元ベクトルの内積</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Plane::DotNormal( const Plane& plane, const Vector3& vec, f32& result )
{
    result = ( plane.normal.x * vec.x ) + ( plane.normal.y * vec.y ) + ( plane.normal.z * vec.z ); 
}

///------------------------------------------------------------------------------------
///<summary>正規化を行います.</summary>
///<param name="value">正規化を行う平面式</param>
///<return>正規化した結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::Normalize( const Plane& value )
{
    register f32 mag = sqrtf( 
        ( value.normal.x * value.normal.x )
      + ( value.normal.y * value.normal.y )
      + ( value.normal.z * value.normal.z )
      + ( value.d        * value.d ) );
    assert( mag != 0.0f );
    register f32 invMag = 1.0f / mag;

    return Plane(
        value.normal.x * invMag,
        value.normal.y * invMag,
        value.normal.z * invMag,
        value.d        * invMag 
    );
}

///------------------------------------------------------------------------------------
///<summary>正規化を行います.</summary>
///<param name="value">正規化を行う平面式</param>
///<param name="result">正規化した結果</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Plane::Normalize( const Plane& value, Plane& result )
{
    register f32 mag = sqrtf( 
        ( value.normal.x * value.normal.x )
      + ( value.normal.y * value.normal.y )
      + ( value.normal.z * value.normal.z )
      + ( value.d        * value.d ) );
    assert( mag != 0.0f );
    register f32 invMag = 1.0f / mag;

    result.normal.x = value.normal.x * invMag;
    result.normal.y = value.normal.y * invMag;
    result.normal.z = value.normal.z * invMag;
    result.d        = value.d * invMag;
}

///------------------------------------------------------------------------------------
///<summary>零除算を考慮して正規化を試みます.</summary>
///<param name="value">正規化する平面式</param>
///<param name="set">長さが0の場合に設定する値</param>
///<return>長さが0でなければ正規化した結果，0であればsetを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Plane   Plane::SafeNormalize( const Plane& value, const Plane& set )
{
    register f32 mag = sqrtf( 
        ( value.normal.x * value.normal.x )
      + ( value.normal.y * value.normal.y )
      + ( value.normal.z * value.normal.z )
      + ( value.d        * value.d ) );

    if ( mag != 0.0f )
    {
        register f32 invMag = 1.0f / mag;
        return Plane( 
            value.normal.x * invMag,
            value.normal.y * invMag,
            value.normal.z * invMag,
            value.d        * invMag 
        );
    }
    else
    {
        return Plane(
            set.normal.x,
            set.normal.y,
            set.normal.z,
            set.d 
        );
    }
}

///------------------------------------------------------------------------------------
///<summary>零除算を考慮して正規化を試みます.</summary>
///<param name="value">正規化する平面式</param>
///<param name="set">長さが0の場合に設定する値</param>
///<param name="result">長さが0でなければ正規化した結果, 0であればset</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    Plane::SafeNormalize( const Plane& value, const Plane& set, Plane& result )
{
    register f32 mag = sqrtf( 
        ( value.normal.x * value.normal.x )
      + ( value.normal.y * value.normal.y )
      + ( value.normal.z * value.normal.z )
      + ( value.d        * value.d ) );

    if ( mag != 0.0f )
    {
        register f32 invMag = 1.0f / mag;
        result.normal.x = value.normal.x * invMag;
        result.normal.y = value.normal.y * invMag;
        result.normal.z = value.normal.z * invMag;
        result.d        = value.d * invMag;
    }
    else
    {
        result.normal.x = set.normal.x;
        result.normal.y = set.normal.y;
        result.normal.z = set.normal.z;
        result.d        = set.d;
    }
}


///////////////////////////////////////////////////////////////////////////////////////
// Ray class
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Ray::Ray()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="pos">位置ベクトル</param>
///<param name="dir">方向ベクトル</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Ray::Ray( const Vector3& pos, const Vector3& dir )
{
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    direction.x = dir.x;
    direction.y = dir.y;
    direction.z = dir.z;
}

///------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name="value">コピー元の値</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
Ray::Ray( const Ray& value )
{
    position.x = value.position.x;
    position.y = value.position.y;
    position.z = value.position.z;

    direction.x = value.direction.x;
    direction.y = value.direction.y;
    direction.z = value.direction.z;
}

///------------------------------------------------------------------------------------
///<summary>デストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
Ray::~Ray()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値</param>
///<return>代入結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Ray& Ray::operator = ( const Ray& value )
{
    position.x = value.position.x;
    position.y = value.position.y;
    position.z = value.position.z;

    direction.x = value.direction.x;
    direction.y = value.direction.y;
    direction.z = value.direction.z;

    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>等価であればtrue, 非等価であればfalseを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::operator == ( const Ray& value ) const
{
    return ( position  == value.position )
        && ( direction == value.direction );
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>非等価であればtrue, 等価であればfalseを返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::operator != ( const Ray& value ) const
{
    return ( position  != value.position )
        || ( direction != value.direction );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">境界箱</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::Intersects( const BoundingBox& value, f32& distance ) const
{
    distance = 0.0f;
    register f32 tmax = F32_MAX;
    
    // X成分.
    if ( fabs( direction.x ) < F32_EPSILON )
    {
        if ( ( position.x < value.mini.x ) || ( position.x > value.mini.x ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( direction.x != 0.0f );
        register f32 inverse = 1.0f / direction.x;
        register f32 t1 = ( value.mini.x - position.x ) * inverse;
        register f32 t2 = ( value.maxi.x - position.x ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    // Y成分.
    if ( fabs( direction.y ) < F32_EPSILON )
    {
        if ( ( position.y < value.mini.y ) || ( position.y > value.mini.y ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( direction.y != 0.0f );
        register f32 inverse = 1.0f / direction.y;
        register f32 t1 = ( value.mini.y - position.y ) * inverse;
        register f32 t2 = ( value.maxi.y - position.y ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    // Z成分.
    if ( fabs( direction.z ) < F32_EPSILON )
    {
        if ( ( position.z < value.mini.z ) || ( position.z > value.mini.z ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( direction.z != 0.0f );
        register f32 inverse = 1.0f / direction.z;
        register f32 t1 = ( value.mini.z - position.z ) * inverse;
        register f32 t2 = ( value.maxi.z - position.z ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">境界錘台</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::Intersects( const BoundingFrustum& value, f32& distance ) const
{
    register f32 tnear = -F32_MAX;
    register f32 tfar  =  F32_MAX;
    for ( u32 i=0; i<6; ++i )
    {
        register f32 dir = ( value.plane[ i ].normal.x * direction.x ) + ( value.plane[ i ].normal.y * direction.y ) + ( value.plane[ i ].normal.z * direction.z );

        if ( fabs( dir ) < F32_EPSILON )
        {
            distance = 0.0f;
            return false;
        }

        register f32 pos = (  value.plane[ i ].normal.x * position.x ) + ( value.plane[ i ].normal.y * position.y ) + ( value.plane[ i ].normal.z * position.z );
        register f32 t   = ( -value.plane[ i ].d - pos ) / dir;
        
        if ( dir < 0.0f )
        {
            if ( t > tfar )
            {
                distance = 0.0f;
                return false;
            }
            if ( t > tnear )
            { tnear = t; }
        }
        else
        {
            if ( t < tnear )
            {
                distance = 0.0f;
                return false;
            }
            if ( t < tfar )
            { tfar = t; }
        }
    }

    register f32 dist = ( tnear >= 0.0f ) ? tnear : tfar;
    if ( dist >= 0.0f )
    {
        distance = dist;
        return true;
    }

    distance = 0.0f;
    return false;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">境界球</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::Intersects( const BoundingSphere& value, f32& distance ) const
{
    Vector3 v( 
        value.center.x - position.x,
        value.center.y - position.y,
        value.center.z - position.z );


    register f32 b = Vector3::Dot( v, direction );
    register f32 c = Vector3::Dot( v, v ) - ( value.radius * value.radius );
    register f32 discrimiant = ( b * b ) - c;
    
    if ( discrimiant < 0.0f )
    {
        distance = 0.0f;
        return false;
    }

    register f32 sqrtD4 = sqrtf( discrimiant );
    register f32 t1 = b - sqrtD4;
    register f32 t2 = b + sqrtD4;

    if ( t1 < F32_EPSILON && t2 < F32_EPSILON )
    {
        distance = 0.0f;
        return false;
    }

    if ( t1 > F32_EPSILON )
    {
        distance = t1;
    }
    else
    {
        distance = t2;
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">平面式</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::Intersects( const Plane& value, f32& distance ) const
{
    register f32 dir = ( value.normal.x * direction.x ) + ( value.normal.y * direction.y ) + ( value.normal.z * direction.z );

    if ( fabs( dir ) < F32_EPSILON )
    {
        distance = 0.0f;
        return false;
    }

    register f32 pos = ( value.normal.x * position.x ) + ( value.normal.y * position.y ) + ( value.normal.z * position.z );
    distance = ( -value.d - pos ) / dir;

    if ( distance < 0.0f )
    {
        if ( distance < - F32_EPSILON )
        {
            distance = 0.0f;
            return false;
        }

        distance = 0.0f;
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="p0">三角形を構成する点</param>
///<param name="p1">三角形を構成する点</param>
///<param name="p2">三角形を構成する点</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool Ray::Intersects( const Vector3& p0, const Vector3& p1, const Vector3& p2, f32& distance ) const
{
    Vector3 e1  = p1 - p0;
    Vector3 e2  = p2 - p0;
    Vector3 dir = direction;
    Vector3 s1  = Vector3::Cross( dir, e2 );
    register f32 div = Vector3::Dot( s1, e1 );
    
    if ( -FLT_EPSILON <= div && div <= FLT_EPSILON )
    { return false; }

    Vector3 d = position - p0;
    register f32 beta = Vector3::Dot( d, s1 ) / div;
    if ( beta <= 0.0 || beta >= 1.0 )
    { return false; }
    
    Vector3 s2 = Vector3::Cross( d, e1 );
    register f32 gamma = Vector3::Dot( dir, s2 ) / div;
    if ( gamma <= 0.0 || ( beta + gamma ) >= 1.0 )
    { return false; }

    register f32 dist = Vector3::Dot( e2, s2 ) / div;

    distance = dist;

    return true;
}


///////////////////////////////////////////////////////////////////////////////////////
// BoundingBox
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox::BoundingBox()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="mini">最小値.</param>
///<param name="maxi">最大値.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox::BoundingBox( const Vector3& mini, const Vector3& maxi )
: mini( mini )
, maxi( maxi )
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name="value">コピー元の値.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox::BoundingBox( const BoundingBox& value )
: mini( value.mini )
, maxi( value.maxi )
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>デストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox::~BoundingBox()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値</param>
///<return>代入結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox& BoundingBox::operator = ( const BoundingBox& value )
{
    mini.x = value.mini.x;
    mini.y = value.mini.y;
    mini.z = value.mini.z;

    maxi.x = value.maxi.x;
    maxi.y = value.maxi.y;
    maxi.z = value.maxi.z;

    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>等価であればtrue, 非等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool BoundingBox::operator == ( const BoundingBox& value ) const
{
    return ( mini == value.mini )
        && ( maxi == value.maxi );
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>非等価であればtrue, 等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool BoundingBox::operator != ( const BoundingBox& value ) const
{
    return ( mini != value.mini )
        || ( maxi != value.maxi );
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する点</param>
///<return>境界箱に点が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingBox::Contains( const Vector3& value ) const
{
    if ( ( ( mini.x <= value.x ) && ( value.x <= maxi.x ) )
      && ( ( mini.y <= value.y ) && ( value.y <= maxi.y ) )
      && ( ( mini.z <= value.z ) && ( value.z <= maxi.z ) )
    )
    { return ContainmentType::CONTAINS; }

    return ContainmentType::DISJOINT;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界箱</param>
///<return>境界箱に境界箱が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingBox::Contains( const BoundingBox& value ) const
{
    if ( ( value.maxi.x < mini.x ) || ( value.mini.x < maxi.x )
      || ( value.maxi.y < mini.y ) || ( value.mini.y < maxi.y )
      || ( value.maxi.z < mini.z ) || ( value.mini.z < maxi.z ) 
    )
    { return ContainmentType::DISJOINT; }
    else if (
        ( value.mini.x >= mini.x ) && ( value.maxi.x <= maxi.x )
     && ( value.mini.y >= mini.y ) && ( value.maxi.y <= maxi.y )
     && ( value.mini.z >= mini.z ) && ( value.maxi.z <= maxi.z ) 
    )
    { return ContainmentType::CONTAINS; }

    return ContainmentType::INTERSECTS;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界球.</param>
///<return>境界箱に境界球が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingBox::Contains( const BoundingSphere& value ) const
{
    register f32 cmX = value.center.x - mini.x;
    register f32 cmY = value.center.y - mini.y;
    register f32 cmZ = value.center.z - mini.z;
    register f32 mcX = maxi.x - value.center.x;
    register f32 mcY = maxi.y - value.center.y;
    register f32 mcZ = maxi.z - value.center.z;

    if ( ( cmX > value.radius )
      && ( cmY > value.radius )
      && ( cmZ > value.radius )
      && ( mcX > value.radius )
      && ( mcY > value.radius )
      && ( mcZ > value.radius )
    )
    { return ContainmentType::CONTAINS; }

    register f32 fmin = 0.0f;

    if ( cmX <= value.radius )
    { fmin += ( cmX * cmX ); }
    else if ( mcX <= value.radius )
    { fmin += ( mcX * mcX ); }

    if ( cmY <= value.radius )
    { fmin += ( cmY * cmY ); }
    else if ( mcY <= value.radius )
    { fmin += ( mcY * mcY ); }

    if ( cmZ <= value.radius )
    { fmin += ( cmZ * cmZ ); }
    else if ( mcZ <= value.radius )
    { fmin += ( mcZ * mcZ ); }

    if ( fmin <= ( value.radius * value.radius ) )
    { return ContainmentType::INTERSECTS; }

    return ContainmentType::DISJOINT;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界錘台</param>
///<return>境界箱に境界錘台が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingBox::Contains( const BoundingFrustum& value ) const
{
    ContainmentType result;
    Vector3x8 corners = value.GetCorners();
    bool isContainsAny = false;
    bool isContainsAll = true;

    for( u32 i=0; i<corners.GetSize(); ++i )
    {
        result = Contains( corners.GetAt( i ) );
        switch( result )
        {
        case ContainmentType::CONTAINS:
        case ContainmentType::INTERSECTS:
            isContainsAny = true;
            break;

        case ContainmentType::DISJOINT:
            isContainsAll = false;
            break;
        }
    }

    if ( isContainsAny )
    {
        if ( isContainsAll )
        { return ContainmentType::CONTAINS; }
        else
        { return ContainmentType::INTERSECTS; }
    }
    else
    { return ContainmentType::DISJOINT; }
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界箱</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingBox::Intersects( const BoundingBox& value ) const
{
    if ( ( mini.x > value.maxi.x ) || ( mini.x > value.maxi.x ) )
    { return false; }

    if ( ( mini.y > value.maxi.y ) || ( mini.y > value.maxi.y ) )
    { return false; }

    if ( ( mini.z > value.maxi.z ) || ( mini.z > value.maxi.z ) )
    { return false; }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界球</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingBox::Intersects( const BoundingSphere& value ) const
{
    Vector3 vec = Clamp( value.center, mini, maxi );
    register f32 dist = Vector3::DistanceSq( value.center, vec );
    return ( dist <= ( value.radius * value.radius ) );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界錐台</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingBox::Intersects( const BoundingFrustum& value ) const
{
    ContainmentType result;
    Vector3x8 corners = value.GetCorners();
    bool isContainsAny = false;
    bool isContainsAll = true;

    for( u32 i=0; i<corners.GetSize(); ++i )
    {
        result = Contains( corners.GetAt( i ) );
        switch( result )
        {
        case ContainmentType::CONTAINS:
        case ContainmentType::INTERSECTS:
            isContainsAny = true;
            break;

        case ContainmentType::DISJOINT:
            isContainsAll = false;
            break;
        }
    }

    if ( isContainsAny )
    { return true; }
    else
    { return false; }

}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する平面式</param>
///<return>境界箱と平面との交差判定の結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType BoundingBox::Intersects( const Plane& value ) const
{
    Vector3 _mini;
    Vector3 _maxi;

    _maxi.x = ( value.normal.x >= 0.0f ) ? _mini.x : maxi.x;
    _maxi.y = ( value.normal.y >= 0.0f ) ? _mini.y : maxi.y;
    _maxi.z = ( value.normal.z >= 0.0f ) ? _mini.z : maxi.z;

    _mini.x = ( value.normal.x >= 0.0f ) ? _maxi.x : mini.x;
    _mini.y = ( value.normal.y >= 0.0f ) ? _maxi.y : mini.y;
    _mini.z = ( value.normal.z >= 0.0f ) ? _maxi.z : mini.z;

    register f32 dist = Vector3::Dot( value.normal, _maxi );

    if ( dist + value.d > 0.0f )
    { return PlaneIntersectionType::FRONT; }

    dist = Vector3::Dot( value.normal, _mini );

    if ( dist + value.d < 0.0f )
    { return PlaneIntersectionType::BACK; }

    return PlaneIntersectionType::INTERSECTING;

}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定するレイ</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingBox::Intersects( const Ray& value, f32& distance ) const
{
    distance = 0.0f;
    register f32 tmax = F32_MAX;
    
    // X成分.
    if ( fabs( value.direction.x ) < F32_EPSILON )
    {
        if ( ( value.position.x < mini.x )
          || ( value.position.x > mini.x ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( value.direction.x != 0.0f );
        register f32 inverse = 1.0f / value.direction.x;
        register f32 t1 = ( mini.x - value.position.x ) * inverse;
        register f32 t2 = ( maxi.x - value.position.x ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    // Y成分.
    if ( fabs( value.direction.y ) < F32_EPSILON )
    {
        if ( ( value.position.y < mini.y ) || ( value.position.y > mini.y ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( value.direction.y != 0.0f );
        register f32 inverse = 1.0f / value.direction.y;
        register f32 t1 = ( mini.y - value.position.y ) * inverse;
        register f32 t2 = ( maxi.y - value.position.y ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    // Z成分.
    if ( fabs( value.direction.z ) < F32_EPSILON )
    {
        if ( ( value.position.z < mini.z ) || ( value.position.z > mini.z ) )
        {
            distance = 0.0f;
            return false;
        }
    }
    else
    {
        assert( value.direction.z != 0.0f );
        register f32 inverse = 1.0f / value.direction.z;
        register f32 t1 = ( mini.z - value.position.z ) * inverse;
        register f32 t2 = ( maxi.z - value.position.z ) * inverse;

        if ( t1 > t2 )
        {
            register f32 tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        distance = Max<f32>( t1, distance );
        tmax = Min<f32>( t2, tmax );

        if ( distance > tmax )
        {
            distance = 0.0f;
            return false;
        }
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>境界箱を構成する8角の点を取得します.</summary>
///<return>境界箱を構成する8角の点を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8   BoundingBox::GetCorners() const
{
    Vector3x8 result;

    result.SetAt( 0, Vector3( mini.x, maxi.y, maxi.z ) );
    result.SetAt( 1, Vector3( maxi.x, maxi.y, maxi.z ) );
    result.SetAt( 2, Vector3( maxi.x, mini.y, maxi.z ) );
    result.SetAt( 3, Vector3( mini.x, mini.y, maxi.z ) );
    result.SetAt( 4, Vector3( mini.x, maxi.y, mini.z ) );
    result.SetAt( 5, Vector3( maxi.x, maxi.y, mini.z ) );
    result.SetAt( 6, Vector3( maxi.x, mini.y, mini.z ) );
    result.SetAt( 7, Vector3( mini.x, mini.y, mini.z ) );
    
    return result;
}

///------------------------------------------------------------------------------------
///<summary>境界箱を構成する8角の点を取得します.</summary>
///<param name="result">境界箱を構成する8角の点</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingBox::GetCorners( Vector3x8& result ) const
{
    result.SetAt( 0, Vector3( mini.x, maxi.y, maxi.z ) );
    result.SetAt( 1, Vector3( maxi.x, maxi.y, maxi.z ) );
    result.SetAt( 2, Vector3( maxi.x, mini.y, maxi.z ) );
    result.SetAt( 3, Vector3( mini.x, mini.y, maxi.z ) );
    result.SetAt( 4, Vector3( mini.x, maxi.y, mini.z ) );
    result.SetAt( 5, Vector3( maxi.x, maxi.y, mini.z ) );
    result.SetAt( 6, Vector3( maxi.x, mini.y, mini.z ) );
    result.SetAt( 7, Vector3( mini.x, mini.y, mini.z ) );
}

///------------------------------------------------------------------------------------
///<summary>2つの境界箱をマージします.</summary>
///<param name="a">入力境界箱</param>
///<param name="b">入力境界箱</param>
///<return>2つの境界箱をマージした結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox     BoundingBox::CreateMerged( const BoundingBox& a, const BoundingBox& b )
{
    return BoundingBox(
        Min( a.mini, b.mini ),
        Max( a.maxi, b.maxi )
    );
}

///------------------------------------------------------------------------------------
///<summary>2つの境界箱をマージします.</summary>
///<param name="a">入力境界箱</param>
///<param name="b">入力境界箱</param>
///<param name="result">2つの境界箱をマージした結果を返却します.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingBox::CreateMerged( const BoundingBox& a, const BoundingBox& b, BoundingBox& result )
{
    result.mini = Min( a.mini, b.mini );
    result.maxi = Max( a.maxi, b.maxi );
}

///------------------------------------------------------------------------------------
///<summary>境界球から境界箱を生成します.</summary>
///<param name="value">境界球</param>
///<return>境界球から生成した境界箱を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox     BoundingBox::CreateFromSphere( const BoundingSphere& value )
{
    return BoundingBox(
        Vector3( value.center.x - value.radius, value.center.y - value.radius, value.center.z - value.radius ),
        Vector3( value.center.x + value.radius, value.center.y + value.radius, value.center.z + value.radius ) 
    );
}

///------------------------------------------------------------------------------------
///<summary>境界球から境界箱を生成します.</summary>
///<param name="value">境界球</param>
///<param name="result">生成した境界箱</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingBox::CreateFromSphere( const BoundingSphere& value, BoundingBox& result )
{
    result.mini = Vector3( value.center.x - value.radius, value.center.y - value.radius, value.center.z - value.radius );
    result.maxi = Vector3( value.center.x + value.radius, value.center.y + value.radius, value.center.z + value.radius );
}

///------------------------------------------------------------------------------------
///<summary>点群から境界箱を生成します.</summary>
///<param name="numPoints">点の数</param>
///<param name="pPoints">点群データの配列</param>
///<param name="offset">配列の先頭からオフセット</param>
///<return>点群から生成された境界箱を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox     BoundingBox::CreateFromPoints( const u32 numPoints, const Vector3* pPoints, const u32 offset )
{
    assert( pPoints != NULL );
    assert( numPoints > 0 );

    Vector3 mini = pPoints[ offset ];
    Vector3 maxi = pPoints[ offset ];

    for( u32 i=(offset+1); i<numPoints; ++i )
    {
        mini = Vector3::Min( mini, pPoints[ i ] );
        maxi = Vector3::Max( maxi, pPoints[ i ] );
    }

    return BoundingBox( mini, maxi );
}

///------------------------------------------------------------------------------------
///<summary>点群から境界箱を生成します.</summary>
///<param name="numPoints">点の数</param>
///<param name="pPoints">点群データの配列</param>
///<param name="offset">配列の先頭からのオフセット</param>
///<param name="result">点群から生成された境界箱</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingBox::CreateFromPoints( const u32 numPoints, const Vector3* pPoints, const u32 offset, BoundingBox& result )
{
    assert( pPoints != NULL );
    assert( numPoints > 0 );

    Vector3 mini = pPoints[ offset ];
    Vector3 maxi = pPoints[ offset ];

    for( u32 i=(offset+1); i<numPoints; ++i )
    {
        mini = Min( mini, pPoints[ i ] );
        maxi = Max( maxi, pPoints[ i ] );
    }

    result.mini = mini;
    result.maxi = maxi;
}

///------------------------------------------------------------------------------------
///<summary>8角の点から境界箱を生成します.</summary>
///<param name="corners">8角の点</param>
///<return>8角の点から生成された境界箱を返却します</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingBox BoundingBox::CreateFromCorners( const Vector3x8& corners )
{
    Vector3 mini( corners[ 0 ] );
    Vector3 maxi( corners[ 0 ] );

    for( u32 i=0; i<8; ++i )
    {
        mini = Min( mini, corners[ i ] );
        maxi = Max( maxi, corners[ i ] );
    }

    return BoundingBox( mini, maxi );
}

///------------------------------------------------------------------------------------
///<summary>8角の点から境界箱を生成します.</summary>
///<param name="corners">8角の点</param>
///<param name="result">8角の点から生成された境界箱</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void BoundingBox::CreateFromCorners( const Vector3x8& corners, BoundingBox& result )
{
    Vector3 mini( corners[ 0 ] );
    Vector3 maxi( corners[ 0 ] );

    for( u32 i=0; i<8; ++i )
    {
        mini = Min( mini, corners[ i ] );
        maxi = Max( maxi, corners[ i ] );
    }

    result.maxi = maxi;
    result.mini = mini;
}


///////////////////////////////////////////////////////////////////////////////////////
// BoundingSphere class
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere::BoundingSphere()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="nc">中心位置</param>
///<param name="nr">半径</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere::BoundingSphere( const Vector3& nc, const f32 nr )
: center( nc )
, radius( nr )
{ /* DO_NOTHING */ }

///-------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name="value">コピー元の値</param>
///-------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere::BoundingSphere( const BoundingSphere& value )
: center( value.center )
, radius( value.radius )
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>デストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere::~BoundingSphere()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値</param>
///<return>代入結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere& BoundingSphere::operator = ( const BoundingSphere& value )
{
    center = value.center;
    radius = value.radius;
    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>等価であればtrue, 非等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool BoundingSphere::operator == ( const BoundingSphere& value ) const
{
    return ( center == value.center )
        && ( radius == value.radius );
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値</param>
///<return>非等価であればtrue, 等価であればtrueを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool BoundingSphere::operator != ( const BoundingSphere& value ) const
{
    return ( center != value.center )
        || ( radius != value.radius );
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界球</param>
///<return>境界球に点が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingSphere::Contains( const Vector3& value ) const
{
    if ( Vector3::DistanceSq( value, center ) <= radius * radius )
    { return ContainmentType::CONTAINS; }

    return ContainmentType::DISJOINT;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行ないます.</summary>
///<param name="value">判定する境界箱</param>
///<return>境界球に境界箱が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingSphere::Contains( const BoundingBox& value ) const
{
    Vector3 vec = Clamp( center, value.mini, value.maxi );
    register f32 dist = Vector3::DistanceSq( center, vec );
    register f32 radiusSq = radius * radius;

    if ( dist <= radiusSq )
    { return ContainmentType::DISJOINT; }

    vec.x = center.x - value.mini.x;
    vec.y = center.y - value.maxi.y;
    vec.z = center.z - value.maxi.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.maxi.x;
    vec.y = center.y - value.maxi.y;
    vec.z = center.z - value.maxi.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.maxi.x;
    vec.y = center.y - value.mini.y;
    vec.z = center.z - value.maxi.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.mini.x;
    vec.y = center.y - value.mini.y;
    vec.z = center.z - value.maxi.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.mini.x;
    vec.y = center.y - value.maxi.y;
    vec.z = center.z - value.mini.z;
    
    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.maxi.x;
    vec.y = center.y - value.maxi.y;
    vec.z = center.z - value.mini.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.maxi.x;
    vec.y = center.y - value.mini.y;
    vec.z = center.z - value.mini.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    vec.x = center.x - value.mini.x;
    vec.y = center.y - value.mini.y;
    vec.z = center.z - value.mini.z;

    if ( vec.LengthSq() > radiusSq )
    { return ContainmentType::INTERSECTS; }

    return ContainmentType::CONTAINS;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界球</param>
///<return>境界球に境界球が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingSphere::Contains( const BoundingSphere& value ) const
{
    register f32 dist = Vector3::Distance( center, value.center );

    if ( radius + value.radius < dist )
    { return ContainmentType::DISJOINT; }

    if ( radius - value.radius < dist )
    { return ContainmentType::INTERSECTS; }

    return ContainmentType::CONTAINS;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定境界錐台</param>
///<return>境界球に境界錐台が含まれているかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingSphere::Contains( const BoundingFrustum& value ) const
{
    PlaneIntersectionType ret  = PlaneIntersectionType::FRONT;
    PlaneIntersectionType pRet = PlaneIntersectionType::FRONT;

    for( u32 i=0; i<6; i++ )
    {
        pRet = value.plane[ i ].Intersects( (*this) );
        switch( pRet )
        {
        case PlaneIntersectionType::BACK:
            return ContainmentType::DISJOINT;
           
        case PlaneIntersectionType::INTERSECTING:
            ret = PlaneIntersectionType::INTERSECTING;
            break;
        }
    }

    switch( ret )
    {
    case PlaneIntersectionType::INTERSECTING:
        return ContainmentType::INTERSECTS;

    default:
        return ContainmentType::CONTAINS;
    }
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する箱</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingSphere::Intersects( const BoundingBox& value ) const
{
    Vector3 vec = Clamp( center, value.mini, value.maxi );
    register f32 dist = Vector3::DistanceSq( center, vec );
    return ( dist <= ( radius * radius ) );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界球</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingSphere::Intersects( const BoundingSphere& value ) const
{
    register f32 distSq = Vector3::DistanceSq( center, value.center );
    if ( ( (( radius * radius ) + ( ( 2.0f * radius ) * value.radius )) + ( value.radius * value.radius ) ) <= distSq )
    { return false; }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界錐台</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingSphere::Intersects( const BoundingFrustum& value ) const
{
    PlaneIntersectionType ret  = PlaneIntersectionType::FRONT;
    PlaneIntersectionType pRet = PlaneIntersectionType::FRONT;

    for( u32 i=0; i<6; i++ )
    {
        pRet = value.plane[ i ].Intersects( (*this) );
        switch( pRet )
        {
        case PlaneIntersectionType::BACK:
            return false;
           
        case PlaneIntersectionType::INTERSECTING:
            ret = PlaneIntersectionType::INTERSECTING;
            break;
        }
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する平面式</param>
///<return>交差判定の結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType BoundingSphere::Intersects( const Plane& value ) const
{
    register f32 dist = ( value.normal.x * center.x ) + ( value.normal.y * center.y ) + ( value.normal.z * center.z ) + value.d;

    if ( dist > radius )
    { return PlaneIntersectionType::FRONT; }

    if ( dist < -radius )
    { return PlaneIntersectionType::BACK; }

    return PlaneIntersectionType::INTERSECTING;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定するレイ</param>
///<param name="distance">交差点までの距離</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingSphere::Intersects( const Ray& value, f32& distance ) const
{
    Vector3 v( 
        center.x - value.position.x,
        center.y - value.position.y,
        center.z - value.position.z );

    register f32 b = Vector3::Dot( v, value.direction );
    register f32 c = Vector3::Dot( v, v ) - ( radius * radius );
    register f32 discrimiant = ( b * b ) - c;
    
    if ( discrimiant < 0.0f )
    {
        distance = 0.0f;
        return false;
    }

    register f32 sqrtD4 = sqrtf( discrimiant );
    register f32 t1 = b - sqrtD4;
    register f32 t2 = b + sqrtD4;

    if ( t1 < F32_EPSILON && t2 < F32_EPSILON )
    {
        distance = 0.0f;
        return false;
    }

    if ( t1 > F32_EPSILON )
    {
        distance = t1;
    }
    else
    {
        distance = t2;
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>2つの境界球をマージします.</summary>
///<param name="a">入力境界球.</param>
///<param name="b">入力境界球.</param>
///<return>2つの境界球をマージした結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere  BoundingSphere::CreateMerged( const BoundingSphere& a, const BoundingSphere& b )
{
    Vector3 dif( 
        b.center.x - a.center.x,
        b.center.y - a.center.y,
        b.center.z - a.center.z );

    register f32 len = dif.Length();
    
    if ( a.radius + b.radius >= len )
    {
        if ( a.radius - b.radius >= len )
        { return a; }

        if ( b.radius - a.radius >= len )
        { return b; }
    }

    assert( len != 0.0f );
    Vector3 v = dif * ( 1.0f / len );
    register f32 fmin = asdx::Min<f32>( -a.radius, len - b.radius );
    register f32 fmax = asdx::Max<f32>(  a.radius, len + b.radius ) * 0.5f;

    return BoundingSphere(
        Vector3( a.center.x + v.x * ( fmax + fmin ),
                 a.center.y + v.y * ( fmax + fmin ),
                 a.center.z + v.z * ( fmax + fmin )
        ),
        fmax
    );
}

///------------------------------------------------------------------------------------
///<summary>2つの境界球をマージします.</summary>
///<param name="a">入力境界球.</param>
///<param name="b">入力境界球.</param>
///<param name="result">マージした境界球.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingSphere::CreateMerged( const BoundingSphere& a, const BoundingSphere& b, BoundingSphere& result )
{
    Vector3 dif( 
        b.center.x - a.center.x,
        b.center.y - a.center.y,
        b.center.z - a.center.z );

    register f32 len = dif.Length();
    
    if ( a.radius + b.radius >= len )
    {
        if ( a.radius - b.radius >= len )
        {
            result = a;
            return;
        }

        if ( b.radius - a.radius >= len )
        {
            result = b;
            return; 
        }
    }

    assert( len != 0.0f );
    Vector3 v = dif * ( 1.0f / len );
    register f32 fmin = asdx::Min<f32>( -a.radius, len - b.radius );
    register f32 fmax = asdx::Max<f32>(  a.radius, len + b.radius ) * 0.5f;

    result.center = a.center + v * ( fmax + fmin );
    result.radius = fmax;
}

///------------------------------------------------------------------------------------
///<summary>境界箱から境界球を生成します.</summary>
///<param name="value">境界箱</param>
///<return>境界箱から生成した境界球を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere BoundingSphere::CreateFromBoundingBox( const BoundingBox& value )
{
    register f32 X = value.mini.x - value.maxi.x;
    register f32 Y = value.mini.y - value.maxi.y;
    register f32 Z = value.mini.z - value.maxi.z;

    return BoundingSphere(
        Vector3( ( value.mini.x + value.maxi.x ) * 0.5f
               , ( value.mini.y + value.maxi.y ) * 0.5f
               , ( value.mini.z + value.maxi.z ) * 0.5f
        ),
        sqrtf( ( X * X ) + ( Y * Y ) + ( Z * Z ) ) * 0.5f
    );
}

///------------------------------------------------------------------------------------
///<summary>境界箱から境界球を生成します.</summary>
///<param name="value">境界箱</param>
///<param name="result">境界箱から生成した境界球.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingSphere::CreateFromBoundingBox( const BoundingBox& value, BoundingSphere& result )
{
    result.center.x = ( value.mini.x + value.maxi.x ) * 0.5f;
    result.center.y = ( value.mini.y + value.maxi.y ) * 0.5f;
    result.center.z = ( value.mini.z + value.maxi.z ) * 0.5f;

    register f32 X = value.mini.x - value.maxi.x;
    register f32 Y = value.mini.y - value.maxi.y;
    register f32 Z = value.mini.z - value.maxi.z;

    result.radius = sqrtf( ( X * X ) + ( Y * Y ) + ( Z * Z ) ) * 0.5f;
}

///------------------------------------------------------------------------------------
///<summary>点群から境界球を生成します.</summary>
///<param name="numPoints">点の数.</param>
///<param name="pPoints">点群データの配列</param>
///<param name="offset">配列の先頭からのオフセット</param>
///<return>点群から生成された境界球を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere  BoundingSphere::CreateFromPoints( const u32 numPoints, const Vector3* pPoints, const u32 offset )
{
    assert( numPoints > 0 );
    assert( pPoints != NULL );

    Vector3 c = pPoints[ offset ];

    for( u32 i=(offset+1); i<numPoints; ++i )
    { c += pPoints[ i ]; }

    c /= static_cast<f32>( numPoints );

    register f32 r = Vector3::DistanceSq( c, pPoints[ offset ] );

    for( u32 i=(offset+1); i<numPoints; ++i )
    {
        register f32 dist = Vector3::DistanceSq( c, pPoints[ i ] );
        if ( dist > r )
        { r = dist; }
    }

    r = sqrtf( r );
    return BoundingSphere( c, r );
}

///------------------------------------------------------------------------------------
///<summary>点群から境界球を生成します.</summary>
///<param name="numPoints">点の数.</param>
///<param name="pPoints">点群データの配列.</param>
///<param name="offset">配列の先頭からオフセット</param>
///<param name="result">生成された境界球.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingSphere::CreateFromPoints( const u32 numPoints, const Vector3* pPoints, const u32 offset, BoundingSphere& result )
{
    assert( numPoints > 0 );
    assert( pPoints != NULL );

    Vector3 c = pPoints[ offset ];

    for( u32 i=(offset+1); i<numPoints; ++i )
    { c += pPoints[ i ]; }

    c /= static_cast<f32>( numPoints );

    register f32 r = Vector3::DistanceSq( c, pPoints[ offset ] );

    for( u32 i=(offset+1); i<numPoints; ++i )
    {
        register f32 dist = Vector3::DistanceSq( c, pPoints[ i ] );
        if ( dist > r )
        { r = dist; }
    }

    result.center = c;
    result.radius = sqrtf( r );
}

///------------------------------------------------------------------------------------
///<summary>8角の点から境界球を生成します.</summary>
///<param name="corners">8角の点.</param>
///<return>8角の点から生成された境界球を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingSphere  BoundingSphere::CreateFromCorners( const Vector3x8& corners )
{
    Vector3 c = corners[ 0 ];

    for( u32 i=0; i<8; ++i )
    { c += corners[ i ]; }

    c /= 8.0f;

    register f32 r = Vector3::DistanceSq( c, corners[ 0 ] );

    for( u32 i=0; i<8; ++i )
    {
        register f32 dist = Vector3::DistanceSq( c, corners[ i ] );
        if ( dist > r )
        { r = dist; }
    }

    r = sqrtf( r );
    return BoundingSphere( c, r );
}

///------------------------------------------------------------------------------------
///<summary>8角の点から境界球を生成します.</summary>
///<param name="corners">8角の点.</param>
///<param name="result">生成された境界球.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void BoundingSphere::CreateFromCorners( const Vector3x8& corners, BoundingSphere& result )
{
    Vector3 c = corners[ 0 ];

    for( u32 i=0; i<8; ++i )
    { c += corners[ i ]; }

    c /= 8.0f;

    register f32 r = Vector3::DistanceSq( c, corners[ 0 ] );

    for( u32 i=0; i<8; ++i )
    {
        register f32 dist = Vector3::DistanceSq( c, corners[ i ] );
        if ( dist > r )
        { r = dist; }
    }

    r = sqrtf( r );
    result.center = c;
    result.radius = r;
}


///////////////////////////////////////////////////////////////////////////////////////
// BoundingFrustum class
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>コンストラクタです.</summary>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingFrustum::BoundingFrustum()
{ /* DO_NOTHING */ }

///------------------------------------------------------------------------------------
///<summary>引数付きコンストラクタです.</summary>
///<param name="value">行列</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingFrustum::BoundingFrustum( const Matrix& value )
: matrix( value )
{
    ComputePlanesFromMatrix( matrix, plane[0], plane[1], plane[2], plane[3], plane[4], plane[5]  );
}

///------------------------------------------------------------------------------------
///<summary>コピーコンストラクタです.</summary>
///<param name-"value">コピー元の値</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingFrustum::BoundingFrustum( const BoundingFrustum& value )
{
    matrix = value.matrix;
    for( u32 i=0; i<6; ++i )
    { plane[ i ] = value.plane[ i ]; }
}

///------------------------------------------------------------------------------------
///<summary>行列から6平面を算出します.</summary>
///<param name="mat">行列</param>
///<param name="leftPlane">左側面</param>
///<param name="rightPlane">右側面</param>
///<param name="topPlane">上面</param>
///<param name="bottomPlane">底面</param>
///<param name="nearPlane">近平面</param>
///<param name="farPlane">遠平面</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingFrustum::ComputePlanesFromMatrix
(
    const Matrix& mat,
    Plane& leftPlane,
    Plane& rightPlane,
    Plane& topPlane,
    Plane& bottomPlane,
    Plane& nearPlane,
    Plane& farPlane
)
{
    // 左.
    leftPlane.normal.x = mat._14 + mat._11;
    leftPlane.normal.y = mat._24 + mat._21;
    leftPlane.normal.z = mat._34 + mat._31;
    leftPlane.d = mat._44 + mat._41;
    leftPlane.Normalize();

    // 右.
    rightPlane.normal.x = mat._14 - mat._11;
    rightPlane.normal.y = mat._24 - mat._21;
    rightPlane.normal.z = mat._34 - mat._31;
    rightPlane.d = mat._44 - mat._41;
    rightPlane.Normalize();

    // 上
    topPlane.normal.x = mat._14 - mat._12;
    topPlane.normal.y = mat._24 - mat._22;
    topPlane.normal.z = mat._34 - mat._32;
    topPlane.d = mat._44 - mat._42;
    topPlane.Normalize();

    // 下
    bottomPlane.normal.x = mat._14 + mat._12;
    bottomPlane.normal.y = mat._24 + mat._22;
    bottomPlane.normal.z = mat._34 + mat._32;
    bottomPlane.d = mat._44 + mat._42;
    bottomPlane.Normalize();

    // 手前
    nearPlane.normal.x = mat._13;
    nearPlane.normal.y = mat._23;
    nearPlane.normal.z = mat._33;
    nearPlane.d = mat._43;
    nearPlane.Normalize();

    // 奥
    farPlane.normal.x = mat._14 - mat._13;
    farPlane.normal.y = mat._24 - mat._23;
    farPlane.normal.z = mat._34 - mat._33;
    farPlane.d = mat._44 - mat._43;
    farPlane.Normalize();
}

///------------------------------------------------------------------------------------
///<summary>代入演算子です.</summary>
///<param name="value">代入する値.</param>
///<return>代入結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
BoundingFrustum& BoundingFrustum::operator = ( const BoundingFrustum& value )
{
    matrix = value.matrix;
    for( u32 i=0; i<6; ++i )
    { plane[ i ] = value.plane[ i ]; }

    return (*this);
}

///------------------------------------------------------------------------------------
///<summary>等価比較演算子です.</summary>
///<param name="value">比較する値.</param>
///<return>等価であればtrue, 非等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::operator == ( const BoundingFrustum& value ) const
{
    if ( matrix != value.matrix )
    { return false; }

    for( u32 i=0; i<6; ++i )
    {
        if ( plane[ i ] != value.plane[ i ] )
        { return false; }
    }

    return true;
}

///------------------------------------------------------------------------------------
///<summary>非等価比較演算子です.</summary>
///<param name="value">比較する値.</param>
///<return>非等価であればtrue, 等価であればfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::operator != ( const BoundingFrustum& value ) const
{
    if ( matrix != value.matrix )
    { return true; }

    for( u32 i=0; i<6; ++i )
    {
        if ( plane[ i ] != value.plane[ i ] )
        { return true; }
    }

    return false;
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する点.</param>
///<return>境界錐台に点が含まれるかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingFrustum::Contains( const Vector3& value ) const
{
    PlaneIntersectionType ret = PlaneIntersectionType::FRONT;
    PlaneIntersectionType pRet = PlaneIntersectionType::FRONT;

    for( u32 i=0; i<6; ++i )
    {
        pRet = plane[ i ].Intersects( value );
        switch( pRet )
        {
        case PlaneIntersectionType::BACK:
            return ContainmentType::DISJOINT;

        case PlaneIntersectionType::INTERSECTING:
            ret = PlaneIntersectionType::INTERSECTING;
            break;
        }
    }

    switch( ret )
    {
    case PlaneIntersectionType::INTERSECTING:
        return ContainmentType::INTERSECTS;

    default:
        return ContainmentType::CONTAINS;
    }
}

///------------------------------------------------------------------------------------
///<summary>平面の交差判定に用いるパラメータを取得します.</summary>
///<param name="box">境界箱.</param>
///<param name="planeNormal">平面の法線ベクトル</param>
///<param name="p">交差判定に用いるパラメータ</param>
///<param name="n">交差判定に用いるパラメータ</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void BoundingFrustum::GetPlaneIntersectParam
(
    const BoundingBox&  box,
    const Vector3&      planeNormal,
    Vector3&            p,
    Vector3&            n
)
{
    p = box.mini;
    if ( planeNormal.x >= 0.0f )
    { p.x = box.maxi.x; }
    if ( planeNormal.y >= 0.0f )
    { p.y = box.maxi.y; }
    if ( planeNormal.z >= 0.0f )
    { p.z = box.maxi.z; }

    n = box.maxi;
    if ( planeNormal.x >= 0.0f )
    { n.x = box.mini.x; }
    if ( planeNormal.y >= 0.0f )
    { n.y = box.mini.y; }
    if ( planeNormal.z >= 0.0f )
    { n.z = box.mini.z; }
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">判定する境界箱</param>
///<return>境界錐台に境界箱が含まれるかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingFrustum::Contains( const BoundingBox& value ) const
{
    Vector3 p, n;
    ContainmentType result = ContainmentType::CONTAINS;

    for( u32 i=0; i<6; ++i )
    {
        GetPlaneIntersectParam( value, plane[i].normal, p, n );
        if ( plane[i].Intersects( p ) == PlaneIntersectionType::BACK )
        { return ContainmentType::DISJOINT; }

        if ( plane[i].Intersects( n ) == PlaneIntersectionType::BACK )
        { result = ContainmentType::INTERSECTS; }
    }

    return result;
}


///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">境界球.</param>
///<return>境界錐台に境界球が含まれるかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingFrustum::Contains( const BoundingSphere& value ) const
{
    PlaneIntersectionType ret = PlaneIntersectionType::FRONT;
    PlaneIntersectionType pRet = PlaneIntersectionType::FRONT;

    for( u32 i=0; i<6; ++i )
    {
        pRet = plane[ i ].Intersects( value );
        switch( pRet )
        {
        case PlaneIntersectionType::BACK:
            return ContainmentType::DISJOINT;

        case PlaneIntersectionType::INTERSECTING:
            ret = PlaneIntersectionType::INTERSECTING;
            break;
        }
    }

    switch( ret )
    {
    case PlaneIntersectionType::INTERSECTING:
        return ContainmentType::INTERSECTS;

    default:
        return ContainmentType::CONTAINS;
    }
}

///------------------------------------------------------------------------------------
///<summary>包含判定を行います.</summary>
///<param name="value">境界錐台.</param>
///<return>境界錐台に境界錐台が含まれるかどうかの判定結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
ContainmentType BoundingFrustum::Contains( const BoundingFrustum& value ) const
{
    ContainmentType result;
    Vector3x8 corners = value.GetCorners();
    bool isContainsAny = false;
    bool isContainsAll = true;

    for( u32 i=0; i<corners.GetSize(); ++i )
    {
        result = Contains( corners.GetAt( i ) );
        switch( result )
        {
        case ContainmentType::CONTAINS:
        case ContainmentType::INTERSECTS:
            isContainsAny = true;
            break;

        case ContainmentType::DISJOINT:
            isContainsAll = false;
            break;
        }
    }

    if ( isContainsAny )
    {
        if ( isContainsAll )
        { return ContainmentType::CONTAINS; }
        else
        { return ContainmentType::INTERSECTS; }
    }
    else
    { return ContainmentType::DISJOINT; }
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界箱.</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::Intersects( const BoundingBox& value ) const
{
    return ( Contains( value ) != ContainmentType::DISJOINT );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する境界球.</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::Intersects( const BoundingSphere& value ) const
{
    return ( Contains( value ) != ContainmentType::DISJOINT );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">境界錐台.</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::Intersects( const BoundingFrustum& value ) const
{
    return ( Contains( value ) != ContainmentType::DISJOINT );
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定する平面式.</param>
///<return>交差判定の結果を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
PlaneIntersectionType BoundingFrustum::Intersects( const Plane& value ) const
{
    Vector3x8 corners = GetCorners();
    PlaneIntersectionType result = value.Intersects( corners.GetAt( 0 ) );

    for( u32 i=1; i<corners.GetSize(); ++i )
    {
        if ( value.Intersects( corners.GetAt( i ) ) != result )
        { return PlaneIntersectionType::INTERSECTING; }
    }

    return result;
}

///------------------------------------------------------------------------------------
///<summary>交差判定を行います.</summary>
///<param name="value">判定すレイ.</param>
///<param name="distance">交差点までの距離.</param>
///<return>交差していればtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool    BoundingFrustum::Intersects( const Ray& value, f32& distance ) const
{
    register f32 tnear = -F32_MAX;
    register f32 tfar  =  F32_MAX;
    for ( u32 i=0; i<6; ++i )
    {
        register f32 dir = ( plane[ i ].normal.x * value.direction.x ) 
                         + ( plane[ i ].normal.y * value.direction.y )
                         + ( plane[ i ].normal.z * value.direction.z );

        if ( fabs( dir ) < F32_EPSILON )
        {
            distance = 0.0f;
            return false;
        }

        register f32 pos = ( plane[ i ].normal.x * value.position.x )
                         + ( plane[ i ].normal.y * value.position.y )
                         + ( plane[ i ].normal.z * value.position.z );
        register f32 t   = ( -plane[ i ].d - pos ) / dir;
        
        if ( dir < 0.0f )
        {
            if ( t > tfar )
            {
                distance = 0.0f;
                return false;
            }
            if ( t > tnear )
            { tnear = t; }
        }
        else
        {
            if ( t < tnear )
            {
                distance = 0.0f;
                return false;
            }
            if ( t < tfar )
            { tfar = t; }
        }
    }

    register f32 dist = ( tnear >= 0.0f ) ? tnear : tfar;
    if ( dist >= 0.0f )
    {
        distance = dist;
        return true;
    }

    distance = 0.0f;
    return false;
}

///------------------------------------------------------------------------------------
///<summary>3平面の交差点を求めます.</summary>
///<param name="a">入力平面.</param>
///<param name="b">入力平面.</param>
///<param name="c">入力平面.</param>
///<return>3平面の交差点を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3 BoundingFrustum::IntersectionPoint( const Plane& a, const Plane& b, const Plane& c )
{
    register f32 f = -Vector3::Dot( a.normal, Vector3::Cross( b.normal, c.normal ) );
    assert( f != 0.0f );
    register f32 invF = 1.0f / f;

    Vector3 v1 = ( a.d * Vector3::Cross( b.normal, c.normal ) );
    Vector3 v2 = ( b.d * Vector3::Cross( c.normal, a.normal ) );
    Vector3 v3 = ( c.d * Vector3::Cross( a.normal, b.normal ) );

    return Vector3(
        ( v1.x + v2.x + v3.x ) * invF,
        ( v1.y + v2.y + v3.y ) * invF,
        ( v1.z + v2.z + v3.z ) * invF
    );
}

///------------------------------------------------------------------------------------
///<summary>境界錐台を構成する8角の点を取得します.</summary>
///<return>境界錐台を構成する8角の点を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector3x8   BoundingFrustum::GetCorners() const
{
    Vector3x8 result;
    result.SetAt( 0, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_BOTTOM], plane[PLANE_RIGHT] ) );
    result.SetAt( 1, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_TOP],    plane[PLANE_RIGHT] ) );
    result.SetAt( 2, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_TOP],    plane[PLANE_LEFT]  ) );
    result.SetAt( 3, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_BOTTOM], plane[PLANE_LEFT]  ) );
    result.SetAt( 4, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_BOTTOM], plane[PLANE_RIGHT] ) );
    result.SetAt( 5, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_TOP],    plane[PLANE_RIGHT] ) );
    result.SetAt( 6, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_TOP],    plane[PLANE_LEFT]  ) );
    result.SetAt( 7, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_BOTTOM], plane[PLANE_LEFT]  ) );

    return result;
}

///------------------------------------------------------------------------------------
///<summary>境界錐台を構成する8角の点を取得します.</summary>
///<param name="result">境界錐台を構成する8角の点</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void    BoundingFrustum::GetCorners( Vector3x8& result ) const
{
    result.SetAt( 0, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_BOTTOM], plane[PLANE_RIGHT] ) );
    result.SetAt( 1, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_TOP],    plane[PLANE_RIGHT] ) );
    result.SetAt( 2, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_TOP],    plane[PLANE_LEFT]  ) );
    result.SetAt( 3, IntersectionPoint( plane[PLANE_NEAR], plane[PLANE_BOTTOM], plane[PLANE_LEFT]  ) );
    result.SetAt( 4, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_BOTTOM], plane[PLANE_RIGHT] ) );
    result.SetAt( 5, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_TOP],    plane[PLANE_RIGHT] ) );
    result.SetAt( 6, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_TOP],    plane[PLANE_LEFT]  ) );
    result.SetAt( 7, IntersectionPoint( plane[PLANE_FAR],  plane[PLANE_BOTTOM], plane[PLANE_LEFT]  ) );
}


///////////////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------------
///<summary>2次元上の三角形の面積を求めます.</summary>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<return>2次元上の三角形の面積を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32 ComputeTriangleArea
(
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2
)
{ return 0.5f * ( ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y ) ); }

///------------------------------------------------------------------------------------
///<summary>2次元上の三角形の面積を求めます.</summary>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<param name="result">2次元上の三角形の面積</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void ComputeTriangleArea
(
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2,
    f32& result
)
{ result = 0.5f * ( ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y ) ); }

///------------------------------------------------------------------------------------
///<summary>3次元上の三角形の面積を求めます.</summary>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<return>3次元上の三角形の面積を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
f32 ComputeTriangleArea
(
    const Vector3& p0,
    const Vector3& p1,
    const Vector3& p2
)
{
   register f32 X = ( p1.y - p0.y ) * ( p2.z - p0.z ) - ( p2.y - p0.y ) * ( p1.z - p0.z );
   register f32 Y = ( p1.z - p0.z ) * ( p2.x - p0.x ) - ( p2.z - p0.z ) * ( p1.x - p0.x );
   register f32 Z = ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y );
   return 0.5f * sqrtf( ( X * X ) + ( Y * Y ) + ( Z * Z ) );
}

///------------------------------------------------------------------------------------
///<summary3次元上の三角形の面積を求めます.</summary>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<param name="result">3次元上の三角形の面積.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void ComputeTriangleArea
(
    const Vector3& p0,
    const Vector3& p1,
    const Vector3& p2,
    f32& result
)
{
   register f32 X = ( p1.y - p0.y ) * ( p2.z - p0.z ) - ( p2.y - p0.y ) * ( p1.z - p0.z );
   register f32 Y = ( p1.z - p0.z ) * ( p2.x - p0.x ) - ( p2.z - p0.z ) * ( p1.x - p0.x );
   register f32 Z = ( p1.x - p0.x ) * ( p2.y - p0.y ) - ( p2.x - p0.x ) * ( p1.y - p0.y );
   result = 0.5f * sqrtf( ( X * X ) + ( Y * Y ) + ( Z * Z ) );
}

///------------------------------------------------------------------------------------
///<summary>外接円の中心を求めます.</summary>
///<param name="p0">入力点.</param>
///<param name="p1">入力点.</param>
///<param name="p2">入力点.</param>
///<return>外接円の中心座標を返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
Vector2 ComputeCircumcircleCenter
(
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2
)
{
   register f32 S = ComputeTriangleArea( p0, p1, p2 );
   assert( S != 0.0f );
   register f32 inv16S2 = 1.0f / ( S * S * 16.0f );

   register f32 len0 = Vector2::DistanceSq( p1, p2 );
   register f32 len1 = Vector2::DistanceSq( p0, p2 );
   register f32 len2 = Vector2::DistanceSq( p0, p1 );

   register f32 term0 = inv16S2 * len0 * ( len1 + len2 - len0 );
   register f32 term1 = inv16S2 * len1 * ( len0 + len2 - len1 );
   register f32 term2 = inv16S2 * len2 * ( len0 + len1 - len2 );

   return Vector2(
       term0 * p0.x + term1 * p1.x + term2 * p2.x,
       term0 * p0.y + term1 * p1.y + term2 * p2.y
   );
}

///------------------------------------------------------------------------------------
///<summary>外接円の中心を求めます.</summary>
///<param name="p0">入力点.</param>
///<param name="p1">入力点.</param>
///<param name="p2">入力点.</param>
///<param name="result">外接円のち中心座標.</param>
///------------------------------------------------------------------------------------
ASDX_INLINE
void ComputeCircumcircleCenter
(
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2,
    Vector2& result
)
{
   register f32 S = ComputeTriangleArea( p0, p1, p2 );
   assert( S != 0.0f );
   register f32 inv16S2 = 1.0f / ( S * S * 16.0f );

   register f32 len0 = Vector2::DistanceSq( p1, p2 );
   register f32 len1 = Vector2::DistanceSq( p0, p2 );
   register f32 len2 = Vector2::DistanceSq( p0, p1 );

   register f32 term0 = inv16S2 * len0 * ( len1 + len2 - len0 );
   register f32 term1 = inv16S2 * len1 * ( len0 + len2 - len1 );
   register f32 term2 = inv16S2 * len2 * ( len0 + len1 - len2 );

    result.x = term0 * p0.x + term1 * p1.x + term2 * p2.x;
    result.y = term0 * p0.y + term1 * p1.y + term2 * p2.y;
}

///------------------------------------------------------------------------------------
///<summary>ドローネ三角形の条件を満たすかどうか判定します.</summary>
///<param name="value">判定点.</param>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<return>ドローネ三角形の条件を満たす場合はtrue, そうでなければfalseを返却します.</return>
///------------------------------------------------------------------------------------
ASDX_INLINE
bool IsDelaunayTriangle
(
    const Vector2& value,
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2 
)
{
   register f32 a[ 6 ] = {
       value.x - p2.x,
       p0.x    - p2.x,
       p1.x    - p2.x,
       value.y - p2.y,
       p0.y    - p2.y,
       p1.y    - p2.y
   };

   register f32 ret =
        ( a[ 0 ] * ( value.x + p2.x ) + a[ 3 ] * ( value.y + p2.y ) ) * ( a[ 1 ] * a[ 5 ] - a[ 2 ] * a[ 4 ] )
      - ( a[ 1 ] * ( p0.x    + p2.x ) + a[ 4 ] * ( p0.y    + p2.y ) ) * ( a[ 0 ] * a[ 5 ] - a[ 2 ] * a[ 3 ] )
      + ( a[ 2 ] * ( p1.x    + p2.x ) + a[ 5 ] * ( p1.y    + p2.y ) ) * ( a[ 0 ] * a[ 4 ] - a[ 1 ] * a[ 3 ] );

   return IsEqual( ret, 0.0f );
}

///------------------------------------------------------------------------------------
///<summary>ドローネ三角形の条件を満たすかどうか判定します.</summary>
///<param name="value">判定点.</param>
///<param name="p0">三角形を構成する点.</param>
///<param name="p1">三角形を構成する点.</param>
///<param name="p2">三角形を構成する点.</param>
///<param name="result">ドローネ三角形の条件を満たす場合はtrue, そうでなければfalse.</param<
///------------------------------------------------------------------------------------
ASDX_INLINE
void IsDelaunayTriangle
(
    const Vector2& value,
    const Vector2& p0,
    const Vector2& p1,
    const Vector2& p2,
    bool& result
)
{
   register f32 a[ 6 ] = {
       value.x - p2.x,
       p0.x    - p2.x,
       p1.x    - p2.x,
       value.y - p2.y,
       p0.y    - p2.y,
       p1.y    - p2.y
   };

   register f32 ret =
        ( a[ 0 ] * ( value.x + p2.x ) + a[ 3 ] * ( value.y + p2.y ) ) * ( a[ 1 ] * a[ 5 ] - a[ 2 ] * a[ 4 ] )
      - ( a[ 1 ] * ( p0.x    + p2.x ) + a[ 4 ] * ( p0.y    + p2.y ) ) * ( a[ 0 ] * a[ 5 ] - a[ 2 ] * a[ 3 ] )
      + ( a[ 2 ] * ( p1.x    + p2.x ) + a[ 5 ] * ( p1.y    + p2.y ) ) * ( a[ 0 ] * a[ 4 ] - a[ 1 ] * a[ 3 ] );

   result = IsEqual( ret, 0.0f );
}


} // namespace asdx

#endif//__ASDX_GEOMETRY_INL__
