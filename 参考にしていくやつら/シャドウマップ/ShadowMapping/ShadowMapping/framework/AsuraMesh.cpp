/**********************************************************************
　　AsuraMesh.cpp

　　Asura Mesh Loader Library

　　Date : Dec. 02, 2007
　　Version : 1.5
　　Author : Pocol
***********************************************************************/

//　Disable Warning C4996
#define _CRT_SECURE_NO_WARNINGS

//
//　include
//
#include <iostream>
#include <fstream>
#include <list>
#include "AsuraMesh.h"
using namespace std;

//
//　global
//
static char* Pointer;
static char Token[1024];

//
//　define
//
#define SafeDelete(x) { if (x) { delete x; x=NULL; } }
#define SafeDeleteArray(x) { if (x) { delete [] x; x=NULL; } }
#define SafeFree(x) { if (x) { free(x); x=NULL; } }

class NormalHash
{
public:
	list<int> index;
};

//--------------------------------------------------------------------------------------------------
//　　GetBaseNameA
//　　Desc : 文字列からディレクトリを取得
//--------------------------------------------------------------------------------------------------
char * GetBaseNameA(char *filename)
{
	char *strings = NULL;
	char *base;
	base = new char [strlen(filename)+1];
	strcpy(base, filename);
	if ( strings = strrchr(base, '.' ) ) 
	{
		strings[1] = '\0';
		return base;
	}
	else 
	{
		base[0] = '\0';
		return base;
	}
}

//--------------------------------------------------------------------------------------------------
//　　GetBaseNameW
//　　Desc : 文字列からディレクトリを取得
//--------------------------------------------------------------------------------------------------
wchar_t * GetBaseNameW(wchar_t *filename)
{
	wchar_t *strings = NULL;
	wchar_t *base;
	base = new wchar_t [wcslen(filename)+1];
	wcscpy(base, filename);
	if ( strings = wcschr(base, L'.' ) ) 
	{
		strings[1] = L'\0';
		return base;
	}
	else 
	{
		base[0] = L'\0';
		return base;
	}
}

//--------------------------------------------------------------------------------------------------------
//　　CutDirectoryNameA
//　　Desc : 文字列からディレクトリを削除
//--------------------------------------------------------------------------------------------------------
char *CutDirectoryNameA( const char *filename )
{
	char *s=NULL;
	char *base=NULL;
	base = new char [strlen(filename)+1];
	strcpy( base, filename );
	if ( s = strrchr(base, '\\') )
	{
		s++;
		return s;
	}
	else if ( s = strrchr(base, '/') )
	{
		s++;
		return s;
	}
	else
	{ 
		return base;
	}
}

//--------------------------------------------------------------------------------------------------------
//　　CutDirectoryNameW
//　　Desc : 文字列からディレクトリを削除
//--------------------------------------------------------------------------------------------------------
wchar_t *CutDirectoryNameW( const wchar_t *filename )
{
	wchar_t *s=NULL;
	wchar_t *base=NULL;
	base = new wchar_t [wcslen(filename)+1];
	wcscpy( base, filename );
	if ( s = wcschr(base, L'\\') )
	{
		s++;
		return s;
	}
	else if ( s = wcschr(base, L'/') )
	{
		s++;
		return s;
	}
	else
	{ 
		return base;
	}
}

////////////////////////////////////////////////////////////////////////
//　　AsuraFace class
////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//　　AsuraFace
//　　Desc : コンストラクタ
//-------------------------------------------------------------------------------------------------
AsuraFace::AsuraFace(uint e, int m, int v[], int n[], int u[])
{
	element = e;
	indexM = m;
	for ( int i=0; i<4; i++ )
	{
		if ( v != NULL )
			indexV[i] = v[i];
		else
			indexV[i] = -1;
		if ( n != NULL )
			indexN[i] = n[i];
		else
			indexN[i] = -1;
		if ( u != NULL )
			indexU[i] = u[i];
		else
			indexU[i] = -1;
	}
}

//-------------------------------------------------------------------------------------------------
//　　operator =
//-------------------------------------------------------------------------------------------------
AsuraFace &AsuraFace::operator = (AsuraFace &f)
{
	element = f.element;
	indexM = f.indexM;
	for ( int i=0; i<4; i++ )
	{
		indexV[i] = f.indexV[i];
		indexN[i] = f.indexN[i];
		indexU[i] = f.indexU[i];
	}
	return (*this);
}

//-------------------------------------------------------------------------------------------------
//　　SetElement　　
//　　Desc : 要素数をセット
//-------------------------------------------------------------------------------------------------
void AsuraFace::SetElement(uint elem)
{ element=elem; }

//--------------------------------------------------------------------------------------------------
//　　SetMaterialIndex
//　　Desc : マテリアルインデックスをセット
//--------------------------------------------------------------------------------------------------
void AsuraFace::SetMaterialIndex(int index)
{ indexM=index; }

//---------------------------------------------------------------------------------------------------
//　　SetVertexIndex
//　　Desc : 頂点インデックスをセット
//---------------------------------------------------------------------------------------------------
void AsuraFace::SetVertexIndex(int index[])
{ indexV[0]=index[0]; indexV[1]=index[1]; indexV[2]=index[2]; indexV[3]=index[3]; }

//----------------------------------------------------------------------------------------------------
//　　SetNormalIndex
//　　Desc : 法線インデックスをセット
//----------------------------------------------------------------------------------------------------
void AsuraFace::SetNormalIndex(int index[])
{ indexN[0]=index[0]; indexN[1]=index[1]; indexN[2]=index[2]; indexN[3]=index[3]; }

//----------------------------------------------------------------------------------------------------
//　　SetUvIndex
//　　Desc : テクスチャ座標インデックスをセット
//----------------------------------------------------------------------------------------------------
void AsuraFace::SetUvIndex(int index[])
{ indexU[0]=index[0]; indexU[1]=index[1]; indexU[2]=index[2]; indexU[3]=index[3]; }

//----------------------------------------------------------------------------------------------------
//　　GetElement
//　　Desc : 要素数を取得
//----------------------------------------------------------------------------------------------------
uint AsuraFace::GetElement()
{ return element; }

//----------------------------------------------------------------------------------------------------
//　　GetMaterialIndex
//　　Desc : マテリアルインデックスを取得
//----------------------------------------------------------------------------------------------------
int AsuraFace::GetMaterailIndex()
{ return indexM; }

//----------------------------------------------------------------------------------------------------
//　　GetVertexIndex
//　　Desc : 頂点インデックスを取得
//----------------------------------------------------------------------------------------------------
int* AsuraFace::GetVertexIndex()
{ return &indexV[0]; }

//----------------------------------------------------------------------------------------------------
//　　GetNormalIndex
//　　Desc : 法線インデックスを取得
//---------------------------------------------------------------------------------------------------
int* AsuraFace::GetNormalIndex()
{ return &indexN[0]; }

//----------------------------------------------------------------------------------------------------
//　　GetUvIndex
//　　Desc : テクスチャ座標インデックスを取得
//----------------------------------------------------------------------------------------------------
int* AsuraFace::GetUvIndex()
{ return &indexU[0]; }

//----------------------------------------------------------------------------------------------------
//　　GetVertexIndex
//　　Desc : 頂点インデックスを取得
//----------------------------------------------------------------------------------------------------
void AsuraFace::GetVertexIndex(int v[])
{
	v[0] = indexV[0];
	v[1] = indexV[1];
	v[2] = indexV[2];
	v[3] = indexV[3];
}

//----------------------------------------------------------------------------------------------------
//　　GetNormalIndex
//　　Desc : 法線インデックスを取得
//----------------------------------------------------------------------------------------------------
void AsuraFace::GetNormalIndex(int n[])
{
	n[0] = indexN[0];
	n[1] = indexN[1];
	n[2] = indexN[2];
	n[3] = indexN[3];
}

//---------------------------------------------------------------------------------------------------
//　　GetUvIndex
//　　Desc : テクスチャ座標インデックスを取得
//---------------------------------------------------------------------------------------------------
void AsuraFace::GetUvIndex(int t[])
{
	t[0] = indexU[0];
	t[1] = indexU[1];
	t[2] = indexU[2];
	t[3] = indexU[3];
}

////////////////////////////////////////////////////////////////////////
//　　AsuraMaterial
////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------
//　　AsuraMaterial
//　　Desc : コンストラクタ
//--------------------------------------------------------------------------------------------------
AsuraMaterial::AsuraMaterial()
{
	diffuse.Zero();
	ambient.Zero();
	specular.Zero();
	emissive.Zero();
	power = 0.0f;
	texture = AsuraTexture(NULL);
	strcpy(nameA, "default");
	wcscpy(nameW, L"default");
}

//--------------------------------------------------------------------------------------------------
//　　operator =
//--------------------------------------------------------------------------------------------------
AsuraMaterial &AsuraMaterial::operator =(AsuraMaterial &m) 
{
	diffuse = m.diffuse;
	ambient = m.ambient;
	specular = m.specular;
	emissive = m.emissive;
	power = m.power;
	texture = m.texture;
	strcpy(nameA, m.nameA);
	wcscpy(nameW, m.nameW);
	return (*this);
}

//--------------------------------------------------------------------------------------------------
//　　SetNameA
//　　Desc : マテリアル名をセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetNameA(char *fname)
{ strcpy(nameA, fname); }

//--------------------------------------------------------------------------------------------------
//　　SetNameW
//　　Desc : マテリアル名をセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetNameW(wchar_t *fname)
{ wcscpy(nameW, fname); }

//--------------------------------------------------------------------------------------------------
//　　SetAmbient
//　　Desc : アンビエントをセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetAmbient(Color4f famb)
{ ambient=famb; }

//--------------------------------------------------------------------------------------------------
//　　SetDiffuse
//　　Desc : ディフューズをセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetDiffuse(Color4f fdif)
{ diffuse=fdif; }

//--------------------------------------------------------------------------------------------------
//　　SetSpecular
//　　Desc : スペキュラーをセット
//---------------------------------------------------------------------------------------------------
void AsuraMaterial::SetSpecular(Color4f fspe)
{ specular=fspe; }

//---------------------------------------------------------------------------------------------------
//　　SetEmissive
//　　Desc : エミッシブをセット
//---------------------------------------------------------------------------------------------------
void AsuraMaterial::SetEmissive(Color4f femi)
{ emissive=femi; }

//--------------------------------------------------------------------------------------------------
//　　SetPower
//　　Desc : パワーをセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetPower(float fpow)
{ power=fpow; }

//--------------------------------------------------------------------------------------------------
//　　SetTexture
//　　Desc : テクスチャをセット
//--------------------------------------------------------------------------------------------------
void AsuraMaterial::SetTexture(AsuraTexture ftex)
{ texture=ftex; }

//--------------------------------------------------------------------------------------------------
//　　GetNameA
//　　Desc : マテリアル名を取得
//--------------------------------------------------------------------------------------------------
char* AsuraMaterial::GetNameA()
{ return nameA; }

//--------------------------------------------------------------------------------------------------
//　　GetNameW
//　　Desc : マテリアル名を取得
//--------------------------------------------------------------------------------------------------
wchar_t* AsuraMaterial::GetNameW()
{ return nameW; }

//--------------------------------------------------------------------------------------------------
//　　GetAmbient
//　　Desc : アンビエントを取得
//--------------------------------------------------------------------------------------------------
Color4f AsuraMaterial::GetAmbient()
{ return ambient; }

//---------------------------------------------------------------------------------------------------
//　　GetDiffuse
//　　Desc : ディフューズを取得
//---------------------------------------------------------------------------------------------------
Color4f AsuraMaterial::GetDiffuse()
{ return diffuse; }

//--------------------------------------------------------------------------------------------------
//　　GetSpecular
//　　Desc : スペキュラーを取得
//--------------------------------------------------------------------------------------------------
Color4f AsuraMaterial::GetSpecular()
{ return specular; }

//---------------------------------------------------------------------------------------------------
//　　GetEmissive
//　　Desc : エミッシブを取得
//---------------------------------------------------------------------------------------------------
Color4f AsuraMaterial::GetEmissive()
{ return emissive; }

//---------------------------------------------------------------------------------------------------
//　　GetPower
//　　Desc : パワーを取得
//---------------------------------------------------------------------------------------------------
float AsuraMaterial::GetPower()
{ return power; }

//---------------------------------------------------------------------------------------------------
//　　GetTexture
//　　Desc : テクスチャを取得
//---------------------------------------------------------------------------------------------------
AsuraTexture AsuraMaterial::GetTexture()
{ return texture; }

////////////////////////////////////////////////////////////////////////
//　　AsuraObject class
////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------
//　　AsuraObject
//　　Desc : コンストラクタ
//--------------------------------------------------------------------------------------------------
AsuraObject::AsuraObject()
{
	num_vertex=0;
	num_normal=0;
	num_uv=0;
	num_face=0;
	vertex = (Vector3f*)malloc(1*sizeof(Vector3f));
	normal = (Vector3f*)malloc(1*sizeof(Vector3f));
	uv = (Vector2f*)malloc(1*sizeof(Vector2f));
	face = (AsuraFace*)malloc(1*sizeof(AsuraFace));
	strcpy(nameA, "default");
	wcscpy(nameW, L"defulat");
}

//--------------------------------------------------------------------------------------------------
//　　~AsuraObject
//　　Desc : デストラクタ
//--------------------------------------------------------------------------------------------------
AsuraObject::~AsuraObject()
{
	//Release();
}

//--------------------------------------------------------------------------------------------------
//　　operator=
//--------------------------------------------------------------------------------------------------
AsuraObject &AsuraObject::operator =(AsuraObject &obj) 
{
	strcpy(nameA, obj.nameA);
	wcscpy(nameW, obj.nameW);
	num_vertex=obj.num_vertex;
	num_normal=obj.num_normal;
	num_uv=obj.num_uv;
	num_face=obj.num_face;

	vertex = (Vector3f*)malloc(num_vertex*sizeof(Vector3f));
	normal = (Vector3f*)malloc(num_normal*sizeof(Vector3f));
	uv = (Vector2f*)malloc(num_uv*sizeof(Vector2f));
	face = (AsuraFace*)malloc(num_face*sizeof(AsuraFace));
	for ( uint i=0; i<num_vertex; i++ )
		vertex[i] = obj.GetVertex(i);
	for ( uint i=0; i<num_normal; i++ )
		normal[i] = obj.GetNormal(i);
	for ( uint i=0; i<num_uv; i++ )
		uv[i] = obj.GetUv(i);
	for ( uint i=0; i<num_face; i++ )
		face[i] = obj.GetFace(i);
	return (*this);
}

//--------------------------------------------------------------------------------------------------
//　　Release
//　　Desc : メモリを解放
//--------------------------------------------------------------------------------------------------
void AsuraObject::Release()
{
	if ( num_vertex > 0 )
		SafeDeleteArray(vertex);
	if ( num_normal > 0 )
		SafeDeleteArray(normal);
	if ( num_uv > 0 )
		SafeDeleteArray(uv);
	if ( num_face > 0 )
		SafeDeleteArray(face);

	num_vertex=0;
	num_normal=0;
	num_uv=0;
	num_face=0;
}

//--------------------------------------------------------------------------------------------------
//　　SetNameA
//　　Desc : オブジェクト名をセット
//--------------------------------------------------------------------------------------------------
void AsuraObject::SetNameA(char *fname)
{ strcpy(nameA, fname); }

//--------------------------------------------------------------------------------------------------
//　　SetNameW
//　　Desc : オブジェクト名をセット
//--------------------------------------------------------------------------------------------------
void AsuraObject::SetNameW(wchar_t *fname)
{ wcscpy(nameW, fname); }

//--------------------------------------------------------------------------------------------------
//　　AddVertex
//　　Desc : 頂点座標を追加
//--------------------------------------------------------------------------------------------------
uint AsuraObject::AddVertex(Vector3f v)
{
	num_vertex++;
	vertex = (Vector3f*)realloc(vertex, num_vertex*sizeof(Vector3f));
	vertex[num_vertex-1] = v;
	return num_vertex;
}

//--------------------------------------------------------------------------------------------------
//　　AddNormal
//　　Desc : 法線ベクトルを追加
//--------------------------------------------------------------------------------------------------
uint AsuraObject::AddNormal(Vector3f n)
{
	num_normal++;
	normal = (Vector3f*)realloc(normal, num_normal*sizeof(Vector3f));
	normal[num_normal-1] = n;
	return num_normal;
}

//--------------------------------------------------------------------------------------------------
//　　AddUv
//　　Desc : テクスチャ座標を追加
//--------------------------------------------------------------------------------------------------
uint AsuraObject::AddUv(Vector2f u)
{
	num_uv++;
	uv = (Vector2f*)realloc(uv, num_uv*sizeof(Vector2f));
	uv[num_uv-1] = u;
	return num_uv;
}

//--------------------------------------------------------------------------------------------------
//　　AddFace
//　　Desc : 面を追加
//-------------------------------------------------------------------------------------------------
uint AsuraObject::AddFace(AsuraFace f)
{
	num_face++;
	face = (AsuraFace*)realloc(face, num_face*sizeof(AsuraFace));
	face[num_face-1] = f;
	return num_face;
}

//--------------------------------------------------------------------------------------------------
//　　GetNumVertex
//　　Desc : 頂点数を取得
//--------------------------------------------------------------------------------------------------
uint AsuraObject::GetNumVertex()
{ return num_vertex; }

//--------------------------------------------------------------------------------------------------
//　　GetNumNormal
//　　Desc : 法線数を取得
//--------------------------------------------------------------------------------------------------
uint AsuraObject::GetNumNormal()
{ return num_normal; }

//--------------------------------------------------------------------------------------------------
//　　GetNameA
//　　Desc : オブジェクト名を取得
//--------------------------------------------------------------------------------------------------
char* AsuraObject::GetNameA()
{ return nameA; }

//--------------------------------------------------------------------------------------------------
//　　GetNameW
//　　Desc : オブジェクト名を取得
//--------------------------------------------------------------------------------------------------
wchar_t* AsuraObject::GetNameW()
{ return nameW; }


//--------------------------------------------------------------------------------------------------
//　　GetNumUv
//　　Desc : テクスチャ座標数を取得
//---------------------------------------------------------------------------------------------------
uint AsuraObject::GetNumUv()
{ return num_uv; }

//---------------------------------------------------------------------------------------------------
//　　GetNumFace
//　　Desc : 面数を取得
//---------------------------------------------------------------------------------------------------
uint AsuraObject::GetNumFace()
{ return num_face; }

//---------------------------------------------------------------------------------------------------
//　　GetVertex
//　　Desc : 頂点データを取得
//---------------------------------------------------------------------------------------------------
Vector3f AsuraObject::GetVertex(uint index)
{
	if ( index < num_vertex )
		return vertex[index]; 
	else 
		return vertex[num_vertex-1];
}

//---------------------------------------------------------------------------------------------------
//　　GetNormal
//　　Desc : 法線データを取得
//---------------------------------------------------------------------------------------------------
Vector3f AsuraObject::GetNormal(uint index)
{ 
	if ( index < num_normal )
		return normal[index];
	else
		return normal[num_normal-1];
}

//---------------------------------------------------------------------------------------------------
//　　GetUv
//　　Desc : テクスチャ座標データを取得
//---------------------------------------------------------------------------------------------------
Vector2f AsuraObject::GetUv(uint index)
{ 
	if ( index < num_uv )
		return uv[index];
	else
		return uv[num_uv-1];
}

//--------------------------------------------------------------------------------------------------
//　　GetFace
//　　Desc : 面データを取得
//--------------------------------------------------------------------------------------------------
AsuraFace AsuraObject::GetFace(uint index)
{ 
	if ( index < num_face )
		return face[index];
	else
		return face[num_face-1];
}

////////////////////////////////////////////////////////////////////////
//　　AsuraMesh class
////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------------
//　　AsuraMesh
//　　Desc : コンストラクタ
//--------------------------------------------------------------------------------------------------
AsuraMesh::AsuraMesh()
{
	num_object =0;
	num_material = 0;
	object = (AsuraObject*)malloc(1*sizeof(AsuraObject));
	material = (AsuraMaterial*)malloc(1*sizeof(AsuraMaterial));
}

//-------------------------------------------------------------------------------------------------
//　　~AsuraMesh
//　　Desc : デストラクタ
//-------------------------------------------------------------------------------------------------
AsuraMesh::~AsuraMesh()
{
	Release();
}

//-------------------------------------------------------------------------------------------------
//　　Release
//　　Desc : メモリを解放
//-------------------------------------------------------------------------------------------------
void AsuraMesh::Release()
{
	//　テクスチャを削除
	for ( uint i=0; i<num_material; i++ )
	{
		if ( material[i].GetTexture().GetHandle() != 0 )
		{
			AsuraTexture tmp = material[i].GetTexture();
			tmp.Delete();
		}
	}

	//　メモリを解放
	if (material)
	{
		free ((AsuraMaterial*)material);
		material = NULL;
	}
	if ( object )
	{
		free((AsuraObject*)object);
		object = NULL;
	}

	//　カウントをゼロにする
	num_material = 0;
	num_object = 0;
}

//--------------------------------------------------------------------------------------------------
//　　AddMaterial
//　　Desc : マテリアルを追加
//-------------------------------------------------------------------------------------------------
uint AsuraMesh::AddMaterial(AsuraMaterial &mat)
{
	num_material++;
	material = (AsuraMaterial*)realloc(material, num_material*sizeof(AsuraMaterial));
	material[num_material-1] = mat;
	return num_material;
}

//--------------------------------------------------------------------------------------------------
//　　AddObject
//　　Desc : オブジェクトを追加
//--------------------------------------------------------------------------------------------------
uint AsuraMesh::AddObject(AsuraObject &obj)
{
	num_object++;
	object = (AsuraObject*)realloc(object, num_object*sizeof(AsuraObject));
	object[num_object-1] = obj;
	return num_object;
}

//--------------------------------------------------------------------------------------------------
//　　GetNumObject
//　　Desc : オブジェクト数を取得
//--------------------------------------------------------------------------------------------------
uint AsuraMesh::GetNumObject()
{ return num_object; }

//--------------------------------------------------------------------------------------------------
//　　GetNumMaterial
//　　Desc : マテリアル数を取得
//--------------------------------------------------------------------------------------------------
uint AsuraMesh::GetNumMaterial()
{ return num_material; }

//--------------------------------------------------------------------------------------------------
//　　GetObjectData
//　　Desc : オブジェクトを取得
//--------------------------------------------------------------------------------------------------
AsuraObject AsuraMesh::GetObjectData(uint index)
{
	if ( index <= num_object )
		return object[index]; 
	else
		return object[num_object-1];
}

//--------------------------------------------------------------------------------------------------
//　　GetMaterialData
//　　Desc : マテリアルを取得
//--------------------------------------------------------------------------------------------------
AsuraMaterial AsuraMesh::GetMaterialData(uint index)
{
	if ( index <= num_material )
		return material[index];
	else
		return material[num_material-1];
}

//---------------------------------------------------------------------------------------------------
//　　Render
//　　Desc : 描画処理
//---------------------------------------------------------------------------------------------------
void AsuraMesh::Render(int object_index)
{
	int pre_mat = -1;
	int cur_mat = 0;
	bool exist_material = false;
	bool exist_uv = false;
	bool exist_normal = false;

	if ( num_material > 0 ) exist_material = true;
	if ( object[object_index].GetNumUv() > 0 ) exist_uv = true;
	if ( object[object_index].GetNumNormal() > 0 ) exist_normal = true;

	for ( uint i=0; i<object[object_index].GetNumFace(); i++ )
	{
		if ( exist_material )
		{
			cur_mat = object[object_index].GetFace(i).GetMaterailIndex();
			if ( cur_mat != pre_mat )
			{
				glColor4fv(material[cur_mat].GetDiffuse());
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material[cur_mat].GetAmbient());
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material[cur_mat].GetDiffuse());
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material[cur_mat].GetSpecular());
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material[cur_mat].GetEmissive());
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material[cur_mat].GetPower());
				if ( material[cur_mat].GetTexture().GetHandle() != 0 )
				{
					material[cur_mat].GetTexture().Enable();
				}
				else
				{
					glDisable(GL_TEXTURE_2D);
				}
				pre_mat = cur_mat;
			}
		}

		uint count = object[object_index].GetFace(i).GetElement();
		int *indexVert, *indexUv, *indexNorm;
		indexVert = object[object_index].GetFace(i).GetVertexIndex();
		if ( exist_uv ) indexUv = object[object_index].GetFace(i).GetUvIndex();
		if ( exist_normal) indexNorm = object[object_index].GetFace(i).GetNormalIndex();

		if ( count == 3 ) glBegin(GL_TRIANGLES);
		else if ( count == 4 ) glBegin(GL_QUADS);
		for ( uint j=0; j<count; j++ )
		{
			if ( exist_uv ) glTexCoord2fv(object[object_index].GetUv(indexUv[j]));
			if ( exist_normal ) glNormal3fv(object[object_index].GetNormal(indexNorm[j]));
			glVertex3fv(object[object_index].GetVertex(indexVert[j]));
		}
		glEnd();
	}

	if ( exist_material )
	{
		if ( material[cur_mat].GetTexture().GetHandle() !=0 )
		{
			material[cur_mat].GetTexture().Disable();
		}
	}
}

//--------------------------------------------------------------------------------------------------
//　　Render
//　　Desc : 描画処理
//--------------------------------------------------------------------------------------------------
void AsuraMesh::Render()
{
	for ( uint i=0; i<num_object; i++ )
		Render(i);
}

//-------------------------------------------------------------------------------------------------
//　　CloneMesh
//　　Desc : クローンを作成
//--------------------------------------------------------------------------------------------------
void AsuraMesh::CloneMesh(AsuraMesh &pCloneMesh)
{
	pCloneMesh.Release();
	for ( int i=0; i<(int)num_object; i++ )
		pCloneMesh.AddObject(object[i]);
	for ( int i=0; i<(int)num_material; i++ )
		pCloneMesh.AddMaterial(material[i]);
}

//--------------------------------------------------------------------------------------------------
//　　AsuraComputeNormals
//　　Desc : 法線ベクトルを作成
//--------------------------------------------------------------------------------------------------
void AsuraComputeNormals(AsuraMesh &mesh)
{
	Vector3f temp;
	Vector3f **fn;
	Vector3f **vn;
	NormalHash **nlist;

	fn = new Vector3f *[mesh.num_object];
	vn = new Vector3f *[mesh.num_object];
	nlist = new NormalHash *[mesh.num_object];

	for ( int i=0; i<(int)mesh.num_object; i++ )
	{
		fn[i] = new Vector3f [mesh.object[i].num_face];
		vn[i] = new Vector3f [mesh.object[i].num_vertex];
		nlist[i] = new NormalHash [mesh.object[i].num_vertex];
		if ( mesh.object[i].num_normal > 0 )
		{
			if ( mesh.object[i].normal )
			{
				free ((Vector3f*)mesh.object[i].normal);
				mesh.object[i].normal = NULL;
			}
			mesh.object[i].normal = (Vector3f*)malloc(mesh.object[i].num_vertex*sizeof(Vector3f));
		}
	}

	for ( int i=0; i<(int)mesh.num_object; i++ )
	{
		int fc = mesh.object[i].num_face;
		int vi[4];
		for ( int j=0; j<fc; j++ )
		{
			int pc =  mesh.object[i].face[j].element;
			for ( int k=0; k<pc; k++ )
			{
				vi[k] = mesh.object[i].face[j].indexV[k];
				nlist[i][vi[k]].index.push_back(j);
			}
			switch ( pc )
			{
			case 3:
				fn[i][j] = GetNormal(
					mesh.object[i].vertex[vi[0]],
					mesh.object[i].vertex[vi[1]],
					mesh.object[i].vertex[vi[2]] );
				break;

			case 4:
				fn[i][j] = GetQuadNormal(
					mesh.object[i].vertex[vi[0]],
					mesh.object[i].vertex[vi[1]],
					mesh.object[i].vertex[vi[2]],
					mesh.object[i].vertex[vi[3]] );
				break;

			default:
				break;
			}
			//　fn[i][j].Normalize();
		}
	}

	for ( uint i=0; i<mesh.num_object; i++ )
	{
		uint vc = mesh.object[i].num_vertex;
		for ( uint j=0; j<vc; j++ )
		{
			mesh.object[i].normal[j].Zero();
			list<int>::iterator p;
			p = nlist[i][j].index.begin();
			temp.Zero();
			while ( p != nlist[i][j].index.end() )
			{
				temp += fn[i][*p];
				p++;
			}
			vn[i][j].Zero();
			temp.Normalize();
			vn[i][j] = temp;
		}
	}

	for ( uint i=0; i<mesh.num_object; i++ )
	{
		uint fc = mesh.object[i].num_face;
		for ( uint j=0; j<fc; j++ )
		{
			uint pc = mesh.object[i].face[j].element;
			int vi[4];
			for ( uint k=0; k<pc; k++ )
			{
				vi[k] = mesh.object[i].face[j].indexV[k];
				float c1 = Dot(fn[i][j], vn[i][vi[k]]);
				float c2 = cos(ToDegree<float>(54.5f));
				if ( c1 >= c2 ) mesh.object[i].normal[vi[k]] = vn[i][vi[k]];
				else mesh.object[i].normal[vi[k]] = fn[i][j];
			}
		}
	}

	for ( int i=0; i<(int)mesh.num_object; i++ )
	{
		SafeDeleteArray(vn[i]);
		SafeDeleteArray(fn[i]);
		SafeDeleteArray(nlist[i]);
	}
	SafeDeleteArray(vn);
	SafeDeleteArray(fn);
	SafeDeleteArray(nlist);
}

//--------------------------------------------------------------------------------------------------
//　　AsuraComputeBoundingSphere
//　　Desc : 境界球を計算する
//--------------------------------------------------------------------------------------------------
void AsuraComputeBoundingSphere(AsuraMesh &mesh, Vector3f &center, float &radius)
{
	Vector3f result_min;
	Vector3f result_max;

	AsuraComputeBoundingBox(mesh, result_min, result_max);
	Vector3f result_center = (result_max + result_min)/2.0f;
	float result_radius = (result_max - result_center).Length();

	center = result_center;
	radius = result_radius;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraComputeBoundingBox
//　　Desc : 境界ボックスを計算する
//--------------------------------------------------------------------------------------------------
void AsuraComputeBoundingBox(AsuraMesh &mesh, Vector3f &minimum, Vector3f &maximum)
{
	Vector3f result_min;
	Vector3f result_max;

	result_min = mesh.GetObjectData(0).GetVertex(0);
	result_max = result_min;

	for ( int i=0; i<(int)mesh.GetNumObject(); i++ )
	{
		for ( int j=0; j<(int)mesh.GetObjectData(i).GetNumVertex(); j++ )
		{
			result_max = Max(mesh.GetObjectData(i).GetVertex(j), result_max);
			result_min = Min(mesh.GetObjectData(i).GetVertex(j), result_min);
		}
	}

	minimum = result_min;
	maximum = result_max;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraCreateDisplayList
//　　Desc : ディスプレイリストを作成
//--------------------------------------------------------------------------------------------------
GLuint AsuraCreateDisplayList(AsuraMesh &mesh)
{
	GLuint handle;
	handle = glGenLists(1);
	glNewList(handle, GL_COMPILE);
	mesh.Render();
	glEndList();
	return handle;
}

////////////////////////////////////////////////////////////////////////
//　　Functions
////////////////////////////////////////////////////////////////////////

//
//　For X File Functions
//

//-------------------------------------------------------------------------------------------------
//　　GetTokenX
//　　Desc : トークンの取得
//-------------------------------------------------------------------------------------------------
static void GetTokenX()
{
	//　pは読み込み位置を，qは読み込んだトークンを指す
	char *p=Pointer;
	char *q=Token;

	//　区切り文字を読み飛ばす
	//　(空白，タブ，復帰，改行，「,」「;」「"」)
	while ( *p !='\0' && strchr(" \t\r\n,;\"", *p) ) p++;

	//　「{」または「}」を読み込んだときには単体でトークンとして返す
	if ( *p == '{' || *p == '}' )
	{
		(*q++) = (*p++);
	}
	//　「{」「}」以外を読み込んだときには，
	//　再び区切り文字が現れるまでの部分をトークンとして返す
	else
	{
		while ( *p != '\0' && !strchr(" \t\r\n,;\"{}", *p) ) (*q++) = (*p++);
	}

	//　ファイルの読み込み位置を更新する
	Pointer=p;

	//　読み込んだトークンの末尾にNULL文字を追加する
	*q='\0';
}

//--------------------------------------------------------------------------------------------------
//　　GetTokenX
//　　Desc : トークンを取得し，Tokenとtokenの値を比較
//--------------------------------------------------------------------------------------------------
static bool GetTokenX(const char* token)
{
	GetTokenX();
	if ( strcmp(Token, token) != 0 )
	{
		cout << "Error : 想定トークン：" << token << endl;
		cout << "　　　読み込みトークン：" << Token << endl;
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
//　　GetFloatTokenX
//　　Desc : トークンを読み込みfloat型に変換
//-------------------------------------------------------------------------------------------------
static float GetFloatTokenX()
{
	GetTokenX();
	return atof(Token);
}

//-------------------------------------------------------------------------------------------------
//　　GetIntTokenX
//　　Desc : トークンを読み込みint型に変換
//-------------------------------------------------------------------------------------------------
static int GetIntTokenX()
{
	GetTokenX();
	return atoi(Token);
}

//--------------------------------------------------------------------------------------------------
//　　SkipNodeX
//　　Desc : ノードを読み飛ばす
//--------------------------------------------------------------------------------------------------
static void SkipNodeX()
{
	while (*Pointer != '\0' )
	{
		GetTokenX();
		if ( strchr(Token, '{') ) break;
	}
	int count = 1;
	while (*Pointer != '\0' && count> 0 )
	{
		GetTokenX();
		if ( strchr(Token, '{') ) count++; 
		else if ( strchr(Token, '}') ) count--;
	}
	if ( count > 0 )
	{
		cout << "Error : 括弧の非対応\n";
		return;
	}
}


//--------------------------------------------------------------------------------------------------
//　　AsuraLoadMeshFromX_A
//　　Desc : Xファイルからメッシュをロード
//--------------------------------------------------------------------------------------------------
bool AsuraLoadMeshFromX_A(char *filename, AsuraMesh &mesh)
{
	HANDLE file=CreateFileA(
		filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	bool b_Mesh = false;
	uint materialCount = 0;
	uint vertexCount = 0;
	uint faceCount = 0;		
	uint normalCount = 0;
	uint uvCount=0;
	uint objCount= -1;
	AsuraFace *temp_face;
	AsuraObject temp_object;

	if ( file==INVALID_HANDLE_VALUE)
	{
		cout << "Error : 指定されたファイルの読み込みに失敗しました\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	DWORD size = GetFileSize(file, NULL);
	char *buffer = new char[size+1];
	buffer[size] = '\0';

	DWORD read_size;
	ReadFile(file, buffer, size, &read_size, NULL);

	CloseHandle(file);

	if ( read_size != size ) 
	{
		cout << "Error : サイズが一致していません\n";
		return false;
	}

	Pointer = buffer;

	while ( *Pointer != '\0' )
	{
		GetTokenX();
	
		if ( strcmp(Token, "template") == 0 )
		{
			SkipNodeX();
		}
		else if ( strcmp(Token, "Mesh") == 0 )
		{
			
			GetTokenX();
			if ( 0 != strcmp(Token, "{" ) )
			{
				temp_object.SetNameA(Token);
				GetTokenX("{");
			}		
			else 
			{
				char strName[MAX_PATH] = "obj";
				sprintf(strName, "%s%d", strName, objCount);
				temp_object.SetNameA(strName);
			}

			objCount++;
			if ( objCount > 0 )
			{
				for ( uint i=0; i<faceCount; i++ )
					temp_object.AddFace(temp_face[i]);
				mesh.AddObject(temp_object);
				SafeDeleteArray(temp_face);
				ZeroMemory(&temp_object, sizeof(temp_object));
			}
	
			vertexCount=0;		
			vertexCount = GetIntTokenX();
			for ( uint i=0; i<vertexCount; i++ )
			{
				Vector3f temp_vertex;
				temp_vertex.x = GetFloatTokenX();
				temp_vertex.y = GetFloatTokenX();
				temp_vertex.z = GetFloatTokenX();
				temp_object.AddVertex(temp_vertex);
			}

			if ( temp_object.GetNumVertex() != vertexCount )
			{
				cout << "Error : 頂点数が一致していません\n";
				return false;
			}
		
			faceCount = 0;
			faceCount = GetIntTokenX();
			temp_face = new AsuraFace[faceCount];

			for  (uint i=0; i<faceCount; i++ )
			{
				GetTokenX();
				int temp_index[4];
				if ( strcmp(Token, "3" ) == 0 )
				{
					temp_face[i].SetElement(3);
					for ( int j=0; j<3; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_index[3] = -1;
					temp_face[i].SetVertexIndex(temp_index);
					temp_face[i].SetUvIndex(temp_index);
				}
				else if ( strcmp(Token, "4" ) == 0 )
				{
					temp_face[i].SetElement(4);
					for ( int j=0; j<4; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_face[i].SetVertexIndex(temp_index);
				}
			}
		}
		else if ( strcmp(Token, "MeshNormals") == 0 )
		{
			GetTokenX("{");

			normalCount = 0;
			normalCount = GetIntTokenX();
			for ( uint i=0; i<normalCount; i++ )
			{
				Vector3f temp_normal;
				temp_normal.x = GetFloatTokenX();
				temp_normal.y = GetFloatTokenX();
				temp_normal.z = GetFloatTokenX();
				temp_object.AddNormal(temp_normal);
			}

			if ( temp_object.GetNumNormal() != normalCount )
			{
				cout << "Error : 法線数が一致していません/n";
				return false;
			}

			if ( GetIntTokenX() != faceCount )
			{
				cout << "Error : 面数と法線インデックス数が不一致です\n";
				return false;
			}

			for ( uint i=0; i<normalCount; i++ )
			{
				GetTokenX();
				int temp_index[4];
				if ( strcmp(Token, "3") ==  0 )
				{
					for ( int j=0; j<3; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_index[3] = -1;
					temp_face[i].SetNormalIndex(temp_index);
				}
				else if ( strcmp(Token, "4" ) == 0 )
				{
					for ( int j=0; j<4; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_face[i].SetNormalIndex(temp_index);
				}
			}
		}
		else if ( strcmp(Token, "MeshTextureCoords") == 0 )
		{
			GetTokenX("{");

			uvCount = 0;
			uvCount = GetIntTokenX();

			for ( uint i=0; i<uvCount; i++ )
			{
				Vector2f temp_uv;
				temp_uv.x = GetFloatTokenX();
				temp_uv.y = GetFloatTokenX();
				temp_object.AddUv(temp_uv);
			}	
		}

		else if ( strcmp(Token, "MeshMaterialList") == 0 )
		{
			GetTokenX("{");
			materialCount=0;
			materialCount=GetIntTokenX();

			if ( GetIntTokenX() != faceCount )
			{
				cout << "Error : 面数とマテリアルリスト数が不一致です\n";
				return false;
			}

			for ( uint i=0; i<faceCount; i++ )
			{
				temp_face[i].SetMaterialIndex(GetIntTokenX());
			}

			for ( uint i=0; i<materialCount; i++ )
			{
				AsuraMaterial temp_material;
				Color4f temp_color;
				GetTokenX("Material");
				GetTokenX();
				if ( 0 != strcmp(Token, "{") )
				{	
					temp_material.SetNameA(Token);
					GetTokenX("{");
				}
				else
				{
					char strName[MAX_PATH] = "mat";
					sprintf(strName, "%s%d", strName, i+1);
					temp_material.SetNameA(strName);
				}

				//　Ambient
				temp_material.SetAmbient(Color4f(0.6f, 0.6f, 0.6f, 1.0f));
				
				//　Diffuse
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = GetFloatTokenX();
				temp_material.SetDiffuse(temp_color);
				
				//　Power
				temp_material.SetPower(GetFloatTokenX());
				
				//　Specular
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = 1.0f;
				temp_material.SetSpecular(temp_color);
				
				//　Emissive
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = 1.0f;
				temp_material.SetEmissive(temp_color);
				
				GetTokenX();
				if ( strcmp(Token, "TextureFileName") == 0)
				{
					GetTokenX("{");
					GetTokenX();
					AsuraTexture temp_texture;
					AsuraCreateTextureFromFileA(Token, temp_texture);
					GetTokenX("}");
					temp_material.SetTexture(temp_texture);
				}
				else if ( strcmp(Token, "}") == 0  )
					mesh.AddMaterial(temp_material);
			}
		}
	}

	if ( objCount >= 0 )
	{
		for ( uint i=0; i<faceCount; i++ )
			temp_object.AddFace(temp_face[i]);
		mesh.AddObject(temp_object);
		SafeDeleteArray(temp_face);
	}

	return true;
}


//--------------------------------------------------------------------------------------------------
//　　AsuraLoadMeshFromX_W
//　　Desc : Xファイルからメッシュをロード
//--------------------------------------------------------------------------------------------------
bool AsuraLoadMeshFromX_W(wchar_t *filename, AsuraMesh &mesh)
{
	HANDLE file=CreateFileW(
		filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	bool b_Mesh = false;
	uint materialCount = 0;
	uint vertexCount = 0;
	uint faceCount = 0;		
	uint normalCount = 0;
	uint uvCount=0;
	uint objCount= -1;
	AsuraFace *temp_face;
	AsuraObject temp_object;

	if ( file==INVALID_HANDLE_VALUE)
	{
		wcout << L"Error : 指定されたファイルの読み込みに失敗しました\n";
		wcout << L"File Name : " << filename << endl;
		return false;
	}

	DWORD size = GetFileSize(file, NULL);
	char *buffer = new char[size+1];
	buffer[size] = '\0';

	DWORD read_size;
	ReadFile(file, buffer, size, &read_size, NULL);

	CloseHandle(file);

	if ( read_size != size ) 
	{
		wcout << L"Error : サイズが一致していません\n";
		return false;
	}

	Pointer = buffer;

	while ( *Pointer != '\0' )
	{
		GetTokenX();
	
		if ( strcmp(Token, "template") == 0 )
		{
			SkipNodeX();
		}
		else if ( strcmp(Token, "Mesh") == 0 )
		{
			
			GetTokenX();
			if ( 0 != strcmp(Token, "{" ) )
			{
				wchar_t tempName[MAX_PATH] = {0};
				int wlength = MultiByteToWideChar(CP_ACP, 0, Token, -1, tempName, 0 );
				MultiByteToWideChar(CP_ACP, 0, Token, -1, tempName, wlength);
				temp_object.SetNameW(tempName);
				GetTokenX("{");
			}		
			else 
			{
				wchar_t strName[MAX_PATH] = L"obj";
				wsprintf(strName, L"%s%d", strName, objCount);
				temp_object.SetNameW(strName);
			}

			objCount++;
			if ( objCount > 0 )
			{
				for ( uint i=0; i<faceCount; i++ )
					temp_object.AddFace(temp_face[i]);
				mesh.AddObject(temp_object);
				SafeDeleteArray(temp_face);
				ZeroMemory(&temp_object, sizeof(temp_object));
			}
	
			vertexCount=0;		
			vertexCount = GetIntTokenX();
			for ( uint i=0; i<vertexCount; i++ )
			{
				Vector3f temp_vertex;
				temp_vertex.x = GetFloatTokenX();
				temp_vertex.y = GetFloatTokenX();
				temp_vertex.z = GetFloatTokenX();
				temp_object.AddVertex(temp_vertex);
			}

			if ( temp_object.GetNumVertex() != vertexCount )
			{
				wcout << L"Error : 頂点数が一致していません\n";
				return false;
			}
		
			faceCount = 0;
			faceCount = GetIntTokenX();
			temp_face = new AsuraFace[faceCount];

			for  (uint i=0; i<faceCount; i++ )
			{
				GetTokenX();
				int temp_index[4];
				if ( strcmp(Token, "3" ) == 0 )
				{
					temp_face[i].SetElement(3);
					for ( int j=0; j<3; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_index[3] = -1;
					temp_face[i].SetVertexIndex(temp_index);
					temp_face[i].SetUvIndex(temp_index);
				}
				else if ( strcmp(Token, "4" ) == 0 )
				{
					temp_face[i].SetElement(4);
					for ( int j=0; j<4; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_face[i].SetVertexIndex(temp_index);
				}
			}
		}
		else if ( strcmp(Token, "MeshNormals") == 0 )
		{
			GetTokenX("{");

			normalCount = 0;
			normalCount = GetIntTokenX();
			for ( uint i=0; i<normalCount; i++ )
			{
				Vector3f temp_normal;
				temp_normal.x = GetFloatTokenX();
				temp_normal.y = GetFloatTokenX();
				temp_normal.z = GetFloatTokenX();
				temp_object.AddNormal(temp_normal);
			}

			if ( temp_object.GetNumNormal() != normalCount )
			{
				wcout << L"Error : 法線数が一致していません/n";
				return false;
			}

			if ( GetIntTokenX() != faceCount )
			{
				wcout << L"Error : 面数と法線インデックス数が不一致です\n";
				return false;
			}

			for ( uint i=0; i<normalCount; i++ )
			{
				GetTokenX();
				int temp_index[4];
				if ( strcmp(Token, "3") ==  0 )
				{
					for ( int j=0; j<3; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_index[3] = -1;
					temp_face[i].SetNormalIndex(temp_index);
				}
				else if ( strcmp(Token, "4" ) == 0 )
				{
					for ( int j=0; j<4; j++ )
					{
						temp_index[j] = GetIntTokenX();
					}
					temp_face[i].SetNormalIndex(temp_index);
				}
			}
		}
		else if ( strcmp(Token, "MeshTextureCoords") == 0 )
		{
			GetTokenX("{");

			uvCount = 0;
			uvCount = GetIntTokenX();

			for ( uint i=0; i<uvCount; i++ )
			{
				Vector2f temp_uv;
				temp_uv.x = GetFloatTokenX();
				temp_uv.y = GetFloatTokenX();
				temp_object.AddUv(temp_uv);
			}	
		}

		else if ( strcmp(Token, "MeshMaterialList") == 0 )
		{
			GetTokenX("{");
			materialCount=0;
			materialCount=GetIntTokenX();

			if ( GetIntTokenX() != faceCount )
			{
				wcout << L"Error : 面数とマテリアルリスト数が不一致です\n";
				return false;
			}

			for ( uint i=0; i<faceCount; i++ )
			{
				temp_face[i].SetMaterialIndex(GetIntTokenX());
			}

			for ( uint i=0; i<materialCount; i++ )
			{
				AsuraMaterial temp_material;
				Color4f temp_color;
				GetTokenX("Material");
				GetTokenX();
				if ( 0 != strcmp(Token, "{") )
				{	
					wchar_t tempStr[MAX_PATH] = {0};
					int wlength = MultiByteToWideChar(CP_ACP, 0, Token, -1, tempStr, 0);
					MultiByteToWideChar(CP_ACP, 0, Token, -1, tempStr, wlength);
					temp_material.SetNameW(tempStr);
					GetTokenX("{");
				}
				else
				{
					wchar_t strName[MAX_PATH] = L"mat";
					wsprintf(strName, L"%s%d", strName, i+1);
					temp_material.SetNameW(strName);
				}

				//　Ambient
				temp_material.SetAmbient(Color4f(0.6f, 0.6f, 0.6f, 1.0f));
				
				//　Diffuse
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = GetFloatTokenX();
				temp_material.SetDiffuse(temp_color);
				
				//　Power
				temp_material.SetPower(GetFloatTokenX());
				
				//　Specular
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = 1.0f;
				temp_material.SetSpecular(temp_color);
				
				//　Emissive
				temp_color.r = GetFloatTokenX();
				temp_color.g = GetFloatTokenX();
				temp_color.b = GetFloatTokenX();
				temp_color.a = 1.0f;
				temp_material.SetEmissive(temp_color);
				
				GetTokenX();
				if ( strcmp(Token, "TextureFileName") == 0)
				{
					GetTokenX("{");
					GetTokenX();
					AsuraTexture temp_texture;
					wchar_t tempName[MAX_PATH] = {0};
					int wlength = MultiByteToWideChar(CP_ACP, 0, Token, -1, tempName, 0);
					MultiByteToWideChar(CP_ACP, 0, Token, -1, tempName, wlength);
					AsuraCreateTextureFromFileW(tempName, temp_texture);
					GetTokenX("}");
					temp_material.SetTexture(temp_texture);
				}
				else if ( strcmp(Token, "}") == 0  )
					mesh.AddMaterial(temp_material);
			}
		}
	}

	if ( objCount >= 0 )
	{
		for ( uint i=0; i<faceCount; i++ )
			temp_object.AddFace(temp_face[i]);
		mesh.AddObject(temp_object);
		SafeDeleteArray(temp_face);
	}

	return true;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraSaveMeshToX_A
//　　Desc : Xファイルにメッシュを保存
//--------------------------------------------------------------------------------------------------
bool AsuraSaveMeshToX_A(char *filename, AsuraMesh &mesh)
{
	ofstream file(filename);

	if ( !file )
	{
		cout << "Error : 指定されたファイルが開けませんでした\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	//　Magic
	file << "xof 0303txt 0032\n";

	//　Template

	//　Vector
	file << "template Vector {\n";
	file << " <3d82ab5e-62da-11cf-ab39-0020af71e433>\n";
	file << " FLOAT x;\n";
	file << " FLOAT y;\n";
	file << " FLOAT z;\n";
	file << "}\n\n";

	//　Coords2d
	file << "template Coords2d {\n";
	file << " <f6f23f44-7686-11cf-8f52-0040333594a3>\n";
	file << " FLOAT u;\n";
	file << " FLOAT v;\n";
	file << "}\n\n";

	//　Matrix4x4
	file << "template Matrix4x4 {\n";
	file << " <f6f23f45-7686-11cf-8f52-0040333594a3>\n";
	file << " array FLOAT matrix[16];\n";
	file << "}\n\n";

	//　ColorRGBA
	file << "template ColorRGBA {\n";
	file << " <35ff44e0-6c7c-11cf-8f52-0040333594a3>\n";
	file << " FLOAT red;\n";
	file << " FLOAT green;\n";
	file << " FLOAT blue;\n";
	file << " FLOAT alpha;\n";
	file << "}\n\n";

	//　ColorRGB
	file << "template ColorRGB {\n";
	file << " <d3e16e81-7835-11cf-8f52-0040333594a3>\n";
	file << " FLOAT red;\n";
	file << " FLOAT green;\n";
	file << " FLOAT blue;\n";
	file << "}\n\n";

	//　IndexedColor
	file << "template IndexedColor {\n";
	file << " <1630b820-7842-11cf-8f52-0040333594a3>\n";
	file << " DWORD index;\n";
	file << " ColorRGBA indexColor;\n";
	file << "}\n\n";

	//　TextureFilename
	file << "template TextureFilename {\n";
	file << " <a42790e1-7810-11cf-8f52-0040333594a3>\n";
	file << " STRING filename;\n";
	file << "}\n\n";

	//　Material
	file << "template Material {\n";
	file << " <3d82ab4d-62da-11cf-ab39-0020af71e433>\n";
	file << " ColorRGBA faceColor;\n";
	file << " FLOAT power;\n";
	file << " ColorRGB specularColor;\n";
	file << " ColorRGB emissiveColor;\n";
	file << " [...]\n";
	file << "}\n\n";

	//　MeshFace
	file << "template MeshFace {\n";
	file << " <3d82ab5f-62da-11cf-ab39-0020af71e433>\n";
	file << " DWORD nFaceVertexIndices;\n";
	file << " array DWORD faceVertexIndices[nFaceVertexIndices];\n";
	file << "}\n\n";

	//　MeshMaterialList
	file << "template MeshMaterialList {\n";
	file << " <f6f23f42-7686-11cf-8f52-0040333594a3>\n";
	file << " DWORD nMaterials;\n";
	file << " DWORD nFaceIndexes;\n";
	file << " array DWORD faceIndexes[nFaceIndexes];\n";
	file << " [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]\n";
	file << "}\n\n";

	//　MeshNormals
	file << "template MeshNormals {\n";
	file << " <f6f23f43-7686-11cf-8f52-0040333594a3>\n";
	file << " DWORD nNormals;\n";
	file << " array Vector normals[nNormals];\n";
	file << " DWORD nFaceNormals;\n";
	file << " array MeshFace faceNormals[nFaceNormals];\n";
	file << "}\n\n";

	//　Mesh
	file << "template Mesh {\n";
	file << " <3d82ab44-62da-11cf-ab39-0020af71e433>\n";
	file << " DWORD nVertices;\n";
	file << " array Vector vertices[nVertices];\n";
	file << " DWORD nFaces;\n";
	file << " array MeshFace faces[nFaces];\n";
	file << " [...]\n";
	file << "}\n\n";

	file.setf(ios::fixed);
	file.precision(5);
	//　Mesh Data
	for ( uint i=0; i<mesh.GetNumObject(); i++ )
	{
		file << "Mesh " << mesh.GetObjectData(i).GetName() << " {\n";
		file << "\t" << mesh.GetObjectData(i).GetNumVertex() << ";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumVertex(); j++ )
		{
			file << "\t";
			file << mesh.GetObjectData(i).GetVertex(j).x << ";";
			file << mesh.GetObjectData(i).GetVertex(j).y << ";";
			file << mesh.GetObjectData(i).GetVertex(j).z << ";";
			if ( j != mesh.GetObjectData(i).GetNumVertex()-1 )
				file << ",\n";
			else 
				file << ";\n";
		}
		file << endl;
		file << "\t" << mesh.GetObjectData(i).GetNumFace() << ";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << "\t";
			file << mesh.GetObjectData(i).GetFace(j).GetElement() << ";";
			int indexV[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetVertexIndex(indexV);
			for ( uint k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << indexV[k];
				if ( k != mesh.GetObjectData(i).GetFace(j).GetElement() -1 )
					file << ",";
				else 
					file << ";,";
			}
			file << endl;
		}
		file << endl;

		file << "\tMeshMaterialList {\n";
		file << "\t\t" << mesh.GetNumMaterial() << ";\n";
		file << "\t\t" << mesh.GetObjectData(i).GetNumFace() << ";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << "\t\t";
			file << mesh.GetObjectData(i).GetFace(j).GetMaterailIndex();
			if ( j != mesh.GetObjectData(i).GetNumFace()-1 )
				file << ",\n";
			else 
				file << ";;\n";
		}
		for ( uint j=0; j<mesh.GetNumMaterial(); j++ )
		{
			file << "\tMaterial " << mesh.GetMaterialData(j).GetName() << " {\n";
			file << "\t\t";
			file << mesh.GetMaterialData(j).GetDiffuse().r << ";";
			file << mesh.GetMaterialData(j).GetDiffuse().g << ";";
			file << mesh.GetMaterialData(j).GetDiffuse().b << ";";
			file << mesh.GetMaterialData(j).GetDiffuse().a << ";;\n";
			file << "\t\t";
			file << mesh.GetMaterialData(j).GetPower() << ";\n";
			file << "\t\t";
			file << mesh.GetMaterialData(j).GetSpecular().r << ";";
			file << mesh.GetMaterialData(j).GetSpecular().g << ";";
			file << mesh.GetMaterialData(j).GetSpecular().b << ";;\n";
			file << "\t\t";
			file << mesh.GetMaterialData(j).GetEmissive().r << ";";
			file << mesh.GetMaterialData(j).GetEmissive().g << ";";
			file << mesh.GetMaterialData(j).GetEmissive().b << ";;\n";
			file << "\t}\n";

			if ( mesh.GetMaterialData(j).GetTexture().GetHandle() != 0 )
			{
				file << "\tTextureFilename {\n";
				file << "\t\t";
				file << "\"";
				file << mesh.GetMaterialData(j).GetTexture().GetName();
				file << "\";\n";
				file << "\t}\n";
			}
		}
		file << "}\n";

		file << "MeshNormals {\n";
		file << "\t";
		file << mesh.GetObjectData(i).GetNumNormal() << ";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumNormal(); j++ )
		{
			file << "\t";
			file << mesh.GetObjectData(i).GetNormal(j).x << ";";
			file << mesh.GetObjectData(i).GetNormal(j).y << ";";
			file << mesh.GetObjectData(i).GetNormal(j).z << ";";
			if ( j!=mesh.GetObjectData(i).GetNumNormal()-1 )
				file << ",\n";
			else
				file << ";\n";
		}
		file << endl;
		file << "\t";
		file << mesh.GetObjectData(i).GetNumFace() << ";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << "\t";
			file << mesh.GetObjectData(i).GetFace(j).GetElement() << ";";
			int indexN[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetNormalIndex(indexN);
			for ( uint k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << indexN[k];
				if ( k != mesh.GetObjectData(i).GetFace(j).GetElement()-1 )
					file << ",";
				else
					file << ";";
			}
			if ( j != mesh.GetObjectData(i).GetNumFace()-1 )
				file << ",\n";
			else
				file << ";\n";
		}
		file << "\t}\n";
	}
	file << "}\n";

	return true;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraSaveMeshToX_W
//　　Desc : Xファイルにメッシュを保存
//--------------------------------------------------------------------------------------------------
bool AsuraSaveMeshToX_W(wchar_t *filename, AsuraMesh &mesh)
{
	wofstream file(filename);

	if ( !file )
	{
		wcout << L"Error : 指定されたファイルが開けませんでした\n";
		wcout << L"File Name : " << filename << endl;
		return false;
	}

	//　Magic
	file << L"xof 0303txt 0032\n";

	//　Template

	//　Vector
	file << L"template Vector {\n";
	file << L" <3d82ab5e-62da-11cf-ab39-0020af71e433>\n";
	file << L" FLOAT x;\n";
	file << L" FLOAT y;\n";
	file << L" FLOAT z;\n";
	file << L"}\n\n";

	//　Coords2d
	file << L"template Coords2d {\n";
	file << L" <f6f23f44-7686-11cf-8f52-0040333594a3>\n";
	file << L" FLOAT u;\n";
	file << L" FLOAT v;\n";
	file << L"}\n\n";

	//　Matrix4x4
	file << L"template Matrix4x4 {\n";
	file << L" <f6f23f45-7686-11cf-8f52-0040333594a3>\n";
	file << L" array FLOAT matrix[16];\n";
	file << L"}\n\n";

	//　ColorRGBA
	file << L"template ColorRGBA {\n";
	file << L" <35ff44e0-6c7c-11cf-8f52-0040333594a3>\n";
	file << L" FLOAT red;\n";
	file << L" FLOAT green;\n";
	file << L" FLOAT blue;\n";
	file << L" FLOAT alpha;\n";
	file << L"}\n\n";

	//　ColorRGB
	file << L"template ColorRGB {\n";
	file << L" <d3e16e81-7835-11cf-8f52-0040333594a3>\n";
	file << L" FLOAT red;\n";
	file << L" FLOAT green;\n";
	file << L" FLOAT blue;\n";
	file << L"}\n\n";

	//　IndexedColor
	file << L"template IndexedColor {\n";
	file << L" <1630b820-7842-11cf-8f52-0040333594a3>\n";
	file << L" DWORD index;\n";
	file << L" ColorRGBA indexColor;\n";
	file << L"}\n\n";

	//　TextureFilename
	file << L"template TextureFilename {\n";
	file << L" <a42790e1-7810-11cf-8f52-0040333594a3>\n";
	file << L" STRING filename;\n";
	file << L"}\n\n";

	//　Material
	file << L"template Material {\n";
	file << L" <3d82ab4d-62da-11cf-ab39-0020af71e433>\n";
	file << L" ColorRGBA faceColor;\n";
	file << L" FLOAT power;\n";
	file << L" ColorRGB specularColor;\n";
	file << L" ColorRGB emissiveColor;\n";
	file << L" [...]\n";
	file << L"}\n\n";

	//　MeshFace
	file << L"template MeshFace {\n";
	file << L" <3d82ab5f-62da-11cf-ab39-0020af71e433>\n";
	file << L" DWORD nFaceVertexIndices;\n";
	file << L" array DWORD faceVertexIndices[nFaceVertexIndices];\n";
	file << L"}\n\n";

	//　MeshMaterialList
	file << L"template MeshMaterialList {\n";
	file << L" <f6f23f42-7686-11cf-8f52-0040333594a3>\n";
	file << L" DWORD nMaterials;\n";
	file << L" DWORD nFaceIndexes;\n";
	file << L" array DWORD faceIndexes[nFaceIndexes];\n";
	file << L" [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]\n";
	file << L"}\n\n";

	//　MeshNormals
	file << L"template MeshNormals {\n";
	file << L" <f6f23f43-7686-11cf-8f52-0040333594a3>\n";
	file << L" DWORD nNormals;\n";
	file << L" array Vector normals[nNormals];\n";
	file << L" DWORD nFaceNormals;\n";
	file << L" array MeshFace faceNormals[nFaceNormals];\n";
	file << L"}\n\n";

	//　Mesh
	file << L"template Mesh {\n";
	file << L" <3d82ab44-62da-11cf-ab39-0020af71e433>\n";
	file << L" DWORD nVertices;\n";
	file << L" array Vector vertices[nVertices];\n";
	file << L" DWORD nFaces;\n";
	file << L" array MeshFace faces[nFaces];\n";
	file << L" [...]\n";
	file << L"}\n\n";

	file.setf(ios::fixed);
	file.precision(5);
	//　Mesh Data
	for ( uint i=0; i<mesh.GetNumObject(); i++ )
	{
		file << L"Mesh " << mesh.GetObjectData(i).GetName() << L" {\n";
		file << L"\t" << mesh.GetObjectData(i).GetNumVertex() << L";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumVertex(); j++ )
		{
			file << L"\t";
			file << mesh.GetObjectData(i).GetVertex(j).x << L";";
			file << mesh.GetObjectData(i).GetVertex(j).y << L";";
			file << mesh.GetObjectData(i).GetVertex(j).z << L";";
			if ( j != mesh.GetObjectData(i).GetNumVertex()-1 )
				file << L",\n";
			else 
				file << L";\n";
		}
		file << endl;
		file << L"\t" << mesh.GetObjectData(i).GetNumFace() << L";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << L"\t";
			file << mesh.GetObjectData(i).GetFace(j).GetElement() << L";";
			int indexV[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetVertexIndex(indexV);
			for ( uint k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << indexV[k];
				if ( k != mesh.GetObjectData(i).GetFace(j).GetElement() -1 )
					file << L",";
				else 
					file << L";,";
			}
			file << endl;
		}
		file << endl;

		file << L"\tMeshMaterialList {\n";
		file << L"\t\t" << mesh.GetNumMaterial() << L";\n";
		file << L"\t\t" << mesh.GetObjectData(i).GetNumFace() << L";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << L"\t\t";
			file << mesh.GetObjectData(i).GetFace(j).GetMaterailIndex();
			if ( j != mesh.GetObjectData(i).GetNumFace()-1 )
				file << L",\n";
			else 
				file << L";;\n";
		}
		for ( uint j=0; j<mesh.GetNumMaterial(); j++ )
		{
			file << L"\tMaterial " << mesh.GetMaterialData(j).GetName() << L" {\n";
			file << L"\t\t";
			file << mesh.GetMaterialData(j).GetDiffuse().r << L";";
			file << mesh.GetMaterialData(j).GetDiffuse().g << L";";
			file << mesh.GetMaterialData(j).GetDiffuse().b << L";";
			file << mesh.GetMaterialData(j).GetDiffuse().a << L";;\n";
			file << L"\t\t";
			file << mesh.GetMaterialData(j).GetPower() << L";\n";
			file << L"\t\t";
			file << mesh.GetMaterialData(j).GetSpecular().r << L";";
			file << mesh.GetMaterialData(j).GetSpecular().g << L";";
			file << mesh.GetMaterialData(j).GetSpecular().b << L";;\n";
			file << L"\t\t";
			file << mesh.GetMaterialData(j).GetEmissive().r << L";";
			file << mesh.GetMaterialData(j).GetEmissive().g << L";";
			file << mesh.GetMaterialData(j).GetEmissive().b << L";;\n";
			file << L"\t}\n";

			if ( mesh.GetMaterialData(j).GetTexture().GetHandle() != 0 )
			{
				file << L"\tTextureFilename {\n";
				file << L"\t\t";
				file << L"\"";
				file << mesh.GetMaterialData(j).GetTexture().GetName();
				file << L"\";\n";
				file << L"\t}\n";
			}
		}
		file << L"}\n";

		file << L"MeshNormals {\n";
		file << L"\t";
		file << mesh.GetObjectData(i).GetNumNormal() << L";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumNormal(); j++ )
		{
			file << L"\t";
			file << mesh.GetObjectData(i).GetNormal(j).x << L";";
			file << mesh.GetObjectData(i).GetNormal(j).y << L";";
			file << mesh.GetObjectData(i).GetNormal(j).z << L";";
			if ( j!=mesh.GetObjectData(i).GetNumNormal()-1 )
				file << L",\n";
			else
				file << L";\n";
		}
		file << endl;
		file << L"\t";
		file << mesh.GetObjectData(i).GetNumFace() << L";\n";
		for ( uint j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			file << L"\t";
			file << mesh.GetObjectData(i).GetFace(j).GetElement() << L";";
			int indexN[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetNormalIndex(indexN);
			for ( uint k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << indexN[k];
				if ( k != mesh.GetObjectData(i).GetFace(j).GetElement()-1 )
					file << L",";
				else
					file << L";";
			}
			if ( j != mesh.GetObjectData(i).GetNumFace()-1 )
				file << L",\n";
			else
				file << L";\n";
		}
		file << L"\t}\n";
	}
	file << L"}\n";

	return true;
}


//
//　For OBJ File Functions
//

//--------------------------------------------------------------------------------------------------
//　　GetDirectoryNameA
//　　Desc : ディレクトリ名を取得
//--------------------------------------------------------------------------------------------------
char* GetDirectoryNameA(const char *filename)
{
	char *s="";
	char *dir;
	dir = new char [strlen(filename)+1];
	strcpy(dir, filename);
	if ( s = strrchr(dir, '/') ) s[1] = '\0';
	else if ( s=strrchr(dir, '\\') )s[1]='0';
	else dir[0] ='\0';
	return dir;
}

//--------------------------------------------------------------------------------------------------
//　　GetDirectoryNameW
//　　Desc : ディレクトリ名を取得
//--------------------------------------------------------------------------------------------------
wchar_t* GetDirectoryNameW(const wchar_t *filename)
{
	wchar_t *s=L"";
	wchar_t *dir;
	dir = new wchar_t [wcslen(filename)+1];
	wcscpy(dir, filename);
	if ( s = wcschr(dir, L'/') ) s[1] = L'\0';
	else if ( s = wcschr(dir, L'\\') ) s[1] = L'0';
	else dir[0] =L'\0';
	return dir;
}

//--------------------------------------------------------------------------------------------------
//　　SetDirectoryNameA
//　　Desc : ディレクトリ名を付加する
//--------------------------------------------------------------------------------------------------
char* SetDirectoryNameA(char *filename, char *directory)
{
	char *s="";
	s = new char[strlen(directory)+ strlen(filename)+1];
	strcpy(s, directory);
	strcat(s, filename);
	return s;
}

//--------------------------------------------------------------------------------------------------
//　　SetDirectoryNameW
//　　Desc : ディレクトリ名を付加する
//--------------------------------------------------------------------------------------------------
wchar_t* SetDirectoryNameW(wchar_t *filename, wchar_t *directory)
{
	wchar_t *s=L"";
	s = new wchar_t[wcslen(directory)+ wcslen(filename)+1];
	wcscpy(s, directory);
	wcscat(s, filename);
	return s;
}

//--------------------------------------------------------------------------------------------------
//　　LoadMaterialFromMTL_A
//　　Desc : MTLファイルからマテリアルをロード
//--------------------------------------------------------------------------------------------------
bool LoadMaterialFromMTL_A(const char *filename, AsuraMesh &mesh)
{
	AsuraMaterial temp_material;
	ifstream file(filename);
	char command[1024]={0};
	int cur_index = -1;

	if ( !file )
	{
		cout << "Error : 指定されたファイルを開けませんでした\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	for (;;)
	{
		file >> command;
		if ( !file )
			break;

		//　New Material
		if ( 0 == strcmp(command, "newmtl") )
		{
			char strName[MAX_PATH] = {0};
			file >> strName;
			cur_index++;
			if ( cur_index != 0 )
				mesh.AddMaterial(temp_material);
			temp_material.SetNameA(strName);
		}
		//　Comment
		else if ( 0 == strcmp(command, "#") )
		{			
		}
		//　Ambient Color
		else if ( 0 == strcmp(command, "Ka") )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetAmbient(Color4f(r, g, b, 1.0f));
		}
		//　Diffuse Color
		else if ( 0 == strcmp(command, "Kd" ) )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetDiffuse(Color4f(r, g, b, 1.0f));
		}
		//　Specular Color
		else if ( 0 == strcmp(command, "Ks") )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetSpecular(Color4f(r, g, b, 1.0f));
		}
		//　Alpha
		else if ( 0 == strcmp(command, "d" ) || 0 == strcmp(command, "Tr" ) )
		{
			float a;
			file >> a;
		}
		//　Shininess
		else if ( 0 == strcmp(command, "Ns") )
		{
			float shininess;
			file >> shininess;
			temp_material.SetPower(shininess);
		}
		//　Specular on/off
		else if ( 0 == strcmp(command, "illum") )
		{
			int illumination;
			file >> illumination;
		}
		//　Ambient Map
		else if ( 0 == strcmp(command, "map_Ka") )
		{
			char textureName[MAX_PATH];
			file >> textureName;
		}
		//　Diffuse Map
		else if ( 0 == strcmp(command, "map_Kd" ) )
		{
			char textureName[MAX_PATH];
			AsuraTexture temp_texture;
			file >> textureName;
			AsuraCreateTextureFromFileA(textureName, temp_texture);
			temp_material.SetTexture(temp_texture);
		}
		//　Specular Map
		else if ( 0 == strcmp(command, "map_Ks" ))
		{
			char textureName[MAX_PATH];
			file >> textureName;
		}
		//　Bump Map
		else if ( 0 == strcmp(command, "map_Bump") )
		{
			char textureName[MAX_PATH];
			file >> textureName;
		}

		file.ignore(1000, '\n');
	}

	if ( cur_index > -1 )
	{
		mesh.AddMaterial(temp_material);
	}

	file.close();

	return true;
}

//--------------------------------------------------------------------------------------------------
//　　LoadMaterialFromMTL_W
//　　Desc : MTLファイルからマテリアルをロード
//--------------------------------------------------------------------------------------------------
bool LoadMaterialFromMTL_W(const wchar_t *filename, AsuraMesh &mesh)
{
	AsuraMaterial temp_material;
	wifstream file(filename);
	wchar_t command[1024]={0};
	int cur_index = -1;

	if ( !file )
	{
		wcout << L"Error : 指定されたファイルを開けませんでした\n";
		wcout << L"File Name : " << filename << endl;
		return false;
	}

	for (;;)
	{
		file >> command;
		if ( !file )
			break;

		//　New Material
		if ( 0 == wcscmp(command, L"newmtl") )
		{
			wchar_t strName[MAX_PATH] = {0};
			file >> strName;
			cur_index++;
			if ( cur_index != 0 )
				mesh.AddMaterial(temp_material);
			temp_material.SetNameW(strName);
		}
		//　Comment
		else if ( 0 == wcscmp(command, L"#") )
		{			
		}
		//　Ambient Color
		else if ( 0 == wcscmp(command, L"Ka") )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetAmbient(Color4f(r, g, b, 1.0f));
		}
		//　Diffuse Color
		else if ( 0 == wcscmp(command, L"Kd" ) )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetDiffuse(Color4f(r, g, b, 1.0f));
		}
		//　Specular Color
		else if ( 0 == wcscmp(command, L"Ks") )
		{
			float r, g, b;
			file >> r >> g >> b;
			temp_material.SetSpecular(Color4f(r, g, b, 1.0f));
		}
		//　Alpha
		else if ( 0 == wcscmp(command, L"d" ) || 0 == wcscmp(command, L"Tr" ) )
		{
			float a;
			file >> a;
		}
		//　Shininess
		else if ( 0 == wcscmp(command, L"Ns") )
		{
			float shininess;
			file >> shininess;
			temp_material.SetPower(shininess);
		}
		//　Specular on/off
		else if ( 0 == wcscmp(command, L"illum") )
		{
			int illumination;
			file >> illumination;
		}
		//　Ambient Map
		else if ( 0 == wcscmp(command, L"map_Ka") )
		{
			wchar_t textureName[MAX_PATH];
			file >> textureName;
		}
		//　Diffuse Map
		else if ( 0 == wcscmp(command, L"map_Kd" ) )
		{
			wchar_t textureName[MAX_PATH];
			AsuraTexture temp_texture;
			file >> textureName;
			AsuraCreateTextureFromFileW(textureName, temp_texture);
			temp_material.SetTexture(temp_texture);
		}
		//　Specular Map
		else if ( 0 == wcscmp(command, L"map_Ks" ))
		{
			wchar_t textureName[MAX_PATH];
			file >> textureName;
		}
		//　Bump Map
		else if ( 0 == wcscmp(command, L"map_Bump") )
		{
			wchar_t textureName[MAX_PATH];
			file >> textureName;
		}

		file.ignore(1000, L'\n');
	}

	if ( cur_index > -1 )
	{
		mesh.AddMaterial(temp_material);
	}

	file.close();

	return true;
}


//-------------------------------------------------------------------------------------------------
//　　LoadGeometoryFromOBJ_A
//　　Desc : OBJファイルから幾何形状をロード
//-------------------------------------------------------------------------------------------------
bool LoadGeometoryFromOBJ_A(const char *filename, AsuraMesh &mesh)
{
	AsuraObject temp_object;
	ifstream file(filename);
	char command[1024] = {0};
	char strMaterialFileName[MAX_PATH] = {0};
	char directoryName[MAX_PATH]={0};
	strcpy(directoryName, GetDirectoryNameA(filename));
	int m_index = 0;

	if ( !file ) 
	{
		cout << "Error : 指定されたファイルが開けませんでした\n";
		cout << "File Name : " << filename << endl;
		return false;
	}	

	for (;;)
	{
		file >> command;
		if ( !file )
			break;

		//　Comment
		if ( 0 == strcmp(command, "#" ) )
		{
		}
		//　Vertex
		else if ( 0 == strcmp(command, "v") )
		{
			float x, y, z;
			file >> x >> y >> z;
			temp_object.AddVertex(Vector3f(x, y, z));			
		}
		//　Texture Coordinate
		else if ( 0 == strcmp(command, "vt") )
		{
			float u, v;
			file >> u >> v;
			temp_object.AddUv(Vector2f(u, v));
		}
		//　Normal
		else if ( 0 == strcmp(command, "vn") )
		{
			float x, y, z;
			file >> x >> y >> z;
			temp_object.AddNormal(Vector3f(x, y, z));
		}
		//　Face
		else if ( 0 == strcmp(command, "f") )
		{
			AsuraFace temp_face;
			uint count = 0;
			int v_index[4] = {-1}, t_index[4] = {-1}, n_index[4] = {-1};
			for ( uint i=0; i<4; i++ )
			{
				count=i;
				file >> v_index[i];
				v_index[i]--;
				if ( '/' == file.peek() )
				{
					file.ignore();

					if ( '/' != file.peek() )
					{
						file >> t_index[i];
						t_index[i]--;
					}

					if ( '/' == file.peek() )
					{
						file.ignore();

						file >> n_index[i];
						n_index[i]--;
					}
				}
				if ( '\n' == file.peek() )
				{
					count++;
					break;
				}
			}
			temp_face.SetElement(count);
			temp_face.SetVertexIndex(v_index);
			temp_face.SetNormalIndex(n_index);
			temp_face.SetUvIndex(t_index);
			temp_face.SetMaterialIndex(m_index);
			temp_object.AddFace(temp_face);			
		}
		//　Material Library
		else if ( 0 == strcmp(command, "mtllib") )
		{
			file >> strMaterialFileName;
			strcpy(strMaterialFileName, SetDirectoryNameA(strMaterialFileName, directoryName));
			if ( !LoadMaterialFromMTL_A(strMaterialFileName, mesh))
				return false;
		}
		//　Material
		else if ( 0 == strcmp(command, "usemtl") )
		{
			char strName[256] = {0};		
			file >> strName;
			for ( uint i=0; i<mesh.GetNumMaterial(); i++ )
			{
				if ( 0 == strcmp(mesh.GetMaterialData(i).GetNameA(), strName) )
				{
					m_index = i;
				}
			}
		}
		//　Group
		else if ( 0 == strcmp(command, "g" ) )
		{
		}
		//　Object
		else if ( 0 == strcmp(command, "o" ) )
		{
		}

		file .ignore( 1000, '\n' );
	}

	mesh.AddObject(temp_object);

	file.close();

	return true;
}

//-------------------------------------------------------------------------------------------------
//　　LoadGeometoryFromOBJ_W
//　　Desc : OBJファイルから幾何形状をロード
//-------------------------------------------------------------------------------------------------
bool LoadGeometoryFromOBJ_W(const wchar_t *filename, AsuraMesh &mesh)
{
	AsuraObject temp_object;
	wifstream file(filename);
	wchar_t command[1024] = {0};
	wchar_t strMaterialFileName[MAX_PATH] = {0};
	wchar_t directoryName[MAX_PATH]={0};
	wcscpy(directoryName, GetDirectoryNameW(filename));
	int m_index = 0;

	if ( !file ) 
	{
		cout << "Error : 指定されたファイルが開けませんでした\n";
		cout << "File Name : " << filename << endl;
		return false;
	}	

	for (;;)
	{
		file >> command;
		if ( !file )
			break;

		//　Comment
		if ( 0 == wcscmp(command, L"#" ) )
		{
		}
		//　Vertex
		else if ( 0 == wcscmp(command, L"v") )
		{
			float x, y, z;
			file >> x >> y >> z;
			temp_object.AddVertex(Vector3f(x, y, z));			
		}
		//　Texture Coordinate
		else if ( 0 == wcscmp(command, L"vt") )
		{
			float u, v;
			file >> u >> v;
			temp_object.AddUv(Vector2f(u, v));
		}
		//　Normal
		else if ( 0 == wcscmp(command, L"vn") )
		{
			float x, y, z;
			file >> x >> y >> z;
			temp_object.AddNormal(Vector3f(x, y, z));
		}
		//　Face
		else if ( 0 == wcscmp(command, L"f") )
		{
			AsuraFace temp_face;
			uint count = 0;
			int v_index[4] = {-1}, t_index[4] = {-1}, n_index[4] = {-1};
			for ( uint i=0; i<4; i++ )
			{
				count=i;
				file >> v_index[i];
				v_index[i]--;
				if ( L'/' == file.peek() )
				{
					file.ignore();

					if ( L'/' != file.peek() )
					{
						file >> t_index[i];
						t_index[i]--;
					}

					if ( L'/' == file.peek() )
					{
						file.ignore();

						file >> n_index[i];
						n_index[i]--;
					}
				}
				if ( L'\n' == file.peek() )
				{
					count++;
					break;
				}
			}
			temp_face.SetElement(count);
			temp_face.SetVertexIndex(v_index);
			temp_face.SetNormalIndex(n_index);
			temp_face.SetUvIndex(t_index);
			temp_face.SetMaterialIndex(m_index);
			temp_object.AddFace(temp_face);			
		}
		//　Material Library
		else if ( 0 == wcscmp(command, L"mtllib") )
		{
			file >> strMaterialFileName;
			wcscpy(strMaterialFileName, SetDirectoryNameW(strMaterialFileName, directoryName));
			if ( !LoadMaterialFromMTL_W(strMaterialFileName, mesh))
				return false;
		}
		//　Material
		else if ( 0 == wcscmp(command, L"usemtl") )
		{
			wchar_t strName[256] = {0};		
			file >> strName;
			for ( uint i=0; i<mesh.GetNumMaterial(); i++ )
			{
				if ( 0 == wcscmp(mesh.GetMaterialData(i).GetNameW(), strName) )
				{
					m_index = i;
				}
			}
		}
		//　Group
		else if ( 0 == wcscmp(command, L"g" ) )
		{
		}
		//　Object
		else if ( 0 == wcscmp(command, L"o" ) )
		{
		}

		file .ignore( 1000, L'\n' );
	}

	mesh.AddObject(temp_object);

	file.close();

	return true;
}


//--------------------------------------------------------------------------------------------------
//　　AsuraLoadMeshFromOBJ_A
//　　Desc : OBJファイルからメッシュをロード
//--------------------------------------------------------------------------------------------------
bool AsuraLoadMeshFromOBJ_A(char *filename, AsuraMesh &mesh)
{
	if ( !LoadGeometoryFromOBJ_A(filename, mesh) )
	{
		cout << "Error : メッシュのロードに失敗しました\n";
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraLoadMeshFromOBJ_W
//　　Desc : OBJファイルからメッシュをロード
//--------------------------------------------------------------------------------------------------
bool AsuraLoadMeshFromOBJ_W(wchar_t *filename, AsuraMesh &mesh)
{
	if ( !LoadGeometoryFromOBJ_W(filename, mesh) )
	{
		wcout << L"Error : メッシュのロードに失敗しました\n";
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraSaveMeshToOBJ_A
//　　Desc : OBJファイルにしてメッシュを保存
//--------------------------------------------------------------------------------------------------
bool AsuraSaveMeshToOBJ(char *filename, AsuraMesh &mesh)
{
	ofstream file(filename);
	uint i=0, j=0, k=0, count=0;
	int vc=0, tc=0, nc=0;
	int cmi=-1;
	char *mtl_name = NULL;
	char *mtllib_name = NULL;

	mtl_name = new char [strlen(filename)+(strlen(".mtl"))+2];
	strcpy( mtl_name, GetBaseNameA(filename) );
	strcat( mtl_name, "mtl" );
	mtllib_name = new char[strlen(filename)];
	strcpy( mtllib_name, CutDirectoryNameA(mtl_name) );

	if ( !file )
	{
		cout << "Error : 指定されたファイルが開けませんでした\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	file << "#　Create by AsuraLibrary\n";
	file << endl;

	file.setf(ios::fixed);
	file.precision(5);

	file << "mtllib " << mtllib_name << endl;
	file << endl;

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumVertex(); j++ )
		{
			file << "v ";
			file << mesh.GetObjectData(i).GetVertex(j).x << " ";
			file << mesh.GetObjectData(i).GetVertex(j).y << " ";
			file << mesh.GetObjectData(i).GetVertex(j).z << endl;
			count ++;
		}
	}
	file << "# " << count << " vertices\n\n";

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumUv(); j++ )
		{
			file << "vt ";
			file << mesh.GetObjectData(i).GetUv(j).x << " ";
			file << mesh.GetObjectData(i).GetUv(j).y << endl;
			count++;
		}
	}
	file << "# " << count << " texcoords\n\n";

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumNormal(); j++ )
		{
			file << "vn ";
			file << mesh.GetObjectData(i).GetNormal(j).x << " ";
			file << mesh.GetObjectData(i).GetNormal(j).y << " ";
			file << mesh.GetObjectData(i).GetNormal(j).z << endl;
		}
	}
	file << "# " << count << " normals\n\n";

	bool b_Normal = false;
	bool b_Uv = false;

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		if ( mesh.GetObjectData(i).GetNumNormal() > 0 )
			b_Normal = true;
		if ( mesh.GetObjectData(i).GetNumUv() > 0 )
			b_Uv = true;
		for ( j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			if ( cmi != mesh.GetObjectData(i).GetFace(j).GetMaterailIndex() )
			{
				file << "usemtl ";
				file << mesh.GetMaterialData(mesh.GetObjectData(i).GetFace(j).GetMaterailIndex()).GetNameA() << endl;
				cmi = mesh.GetObjectData(i).GetFace(j).GetMaterailIndex();
			}

			file << "f";
			int indexV[4]={-1}, indexN[4]={-1}, indexU[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetVertexIndex(indexV);
			mesh.GetObjectData(i).GetFace(j).GetNormalIndex(indexN);
			mesh.GetObjectData(i).GetFace(j).GetUvIndex(indexU);
			for ( k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << " " << indexV[k]+vc+1;
				if ( b_Uv )
					file << "/" << indexU[k]+tc+1;
				if ( b_Normal && b_Uv )
					file << "/" << indexN[k]+nc+1;
				else if ( b_Normal && !b_Uv )
					file << "//" << indexN[k]+nc+1;
			}
			file << endl;
		}
		vc += mesh.GetObjectData(i).GetNumVertex();
		tc += mesh.GetObjectData(i).GetNumUv();
		nc += mesh.GetObjectData(i).GetNumNormal();
	}
	file << "# " << vc << " elements\n\n";
	file.close();

	ofstream file2(mtl_name);

	if ( !file2 )
	{
		cout << "Error : 指定されたファイルを開けませんでした\n";
		cout << "File Name : "<< mtl_name << endl;
		SafeDelete(mtl_name);
		SafeDelete(mtllib_name);
		return false;
	}

	file2 << "#　Create by AsuraLibraray\n";
	file2 << endl;

	file2.setf(ios::fixed);
	file2.precision(5);

	for ( i=0; i<mesh.GetNumMaterial(); i++ )
	{
		file2 << "newmtl ";
		file2 << mesh.GetMaterialData(i).GetNameA() << endl;

		file2 << "Ka ";
		file2 << mesh.GetMaterialData(i).GetAmbient().r << " ";
		file2 << mesh.GetMaterialData(i).GetAmbient().g << " ";
		file2 << mesh.GetMaterialData(i).GetAmbient().b << endl;

		file2 << "Kd ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().r << " ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().g << " ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().b << endl;

		file2 << "Ks ";
		file2 << mesh.GetMaterialData(i).GetSpecular().r << " ";
		file2 << mesh.GetMaterialData(i).GetSpecular().g << " ";
		file2 << mesh.GetMaterialData(i).GetSpecular().b << endl;

		file2 << "Ns ";
		file2 << mesh.GetMaterialData(i).GetPower() << endl;

		file2 << "illum 2\n";

		if ( mesh.GetMaterialData(i).GetTexture().GetHandle() != 0 )
		{
			file2 << "map_Kd ";
			file2 << mesh.GetMaterialData(i).GetTexture().GetNameA() << endl;
		}

		file2 << endl;
	}
	file2 << "# " << mesh.GetNumMaterial() << " elements\n\n";

	file2.close();
	return true;
}

//--------------------------------------------------------------------------------------------------
//　　AsuraSaveMeshToOBJ_W
//　　Desc : OBJファイルにしてメッシュを保存
//--------------------------------------------------------------------------------------------------
bool AsuraSaveMeshToOBJ(wchar_t *filename, AsuraMesh &mesh)
{
	wofstream file(filename);
	uint i=0, j=0, k=0, count=0;
	int vc=0, tc=0, nc=0;
	int cmi=-1;
	wchar_t *mtl_name = NULL;
	wchar_t *mtllib_name = NULL;

	mtl_name = new wchar_t [wcslen(filename)+(wcslen(L".mtl"))+2];
	wcscpy( mtl_name, GetBaseNameW(filename) );
	wcscat( mtl_name, L"mtl" );
	mtllib_name = new wchar_t[wcslen(filename)];
	wcscpy( mtllib_name, CutDirectoryNameW(mtl_name) );

	if ( !file )
	{
		wcout << L"Error : 指定されたファイルが開けませんでした\n";
		wcout << L"File Name : " << filename << endl;
		return false;
	}

	file << L"#　Create by AsuraLibrary\n";
	file << endl;

	file.setf(ios::fixed);
	file.precision(5);

	file << L"mtllib " << mtllib_name << endl;
	file << endl;

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumVertex(); j++ )
		{
			file << L"v ";
			file << mesh.GetObjectData(i).GetVertex(j).x << L" ";
			file << mesh.GetObjectData(i).GetVertex(j).y << L" ";
			file << mesh.GetObjectData(i).GetVertex(j).z << endl;
			count ++;
		}
	}
	file << L"# " << count << L" vertices\n\n";

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumUv(); j++ )
		{
			file << L"vt ";
			file << mesh.GetObjectData(i).GetUv(j).x << L" ";
			file << mesh.GetObjectData(i).GetUv(j).y << endl;
			count++;
		}
	}
	file << L"# " << count << L" texcoords\n\n";

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		for ( j=0; j<mesh.GetObjectData(i).GetNumNormal(); j++ )
		{
			file << L"vn ";
			file << mesh.GetObjectData(i).GetNormal(j).x << L" ";
			file << mesh.GetObjectData(i).GetNormal(j).y << L" ";
			file << mesh.GetObjectData(i).GetNormal(j).z << endl;
		}
	}
	file << L"# " << count << L" normals\n\n";

	bool b_Normal = false;
	bool b_Uv = false;

	for ( i=0, count=0; i<mesh.GetNumObject(); i++ )
	{
		if ( mesh.GetObjectData(i).GetNumNormal() > 0 )
			b_Normal = true;
		if ( mesh.GetObjectData(i).GetNumUv() > 0 )
			b_Uv = true;
		for ( j=0; j<mesh.GetObjectData(i).GetNumFace(); j++ )
		{
			if ( cmi != mesh.GetObjectData(i).GetFace(j).GetMaterailIndex() )
			{
				file << L"usemtl ";
				file << mesh.GetMaterialData(mesh.GetObjectData(i).GetFace(j).GetMaterailIndex()).GetNameW() << endl;
				cmi = mesh.GetObjectData(i).GetFace(j).GetMaterailIndex();
			}

			file << L"f";
			int indexV[4]={-1}, indexN[4]={-1}, indexU[4]={-1};
			mesh.GetObjectData(i).GetFace(j).GetVertexIndex(indexV);
			mesh.GetObjectData(i).GetFace(j).GetNormalIndex(indexN);
			mesh.GetObjectData(i).GetFace(j).GetUvIndex(indexU);
			for ( k=0; k<mesh.GetObjectData(i).GetFace(j).GetElement(); k++ )
			{
				file << L" " << indexV[k]+vc+1;
				if ( b_Uv )
					file << L"/" << indexU[k]+tc+1;
				if ( b_Normal && b_Uv )
					file << L"/" << indexN[k]+nc+1;
				else if ( b_Normal && !b_Uv )
					file << L"//" << indexN[k]+nc+1;
			}
			file << endl;
		}
		vc += mesh.GetObjectData(i).GetNumVertex();
		tc += mesh.GetObjectData(i).GetNumUv();
		nc += mesh.GetObjectData(i).GetNumNormal();
	}
	file << L"# " << vc << L" elements\n\n";
	file.close();

	wofstream file2(mtl_name);

	if ( !file2 )
	{
		wcout << L"Error : 指定されたファイルを開けませんでした\n";
		wcout << L"File Name : "<< mtl_name << endl;
		SafeDelete(mtl_name);
		SafeDelete(mtllib_name);
		return false;
	}

	file2 << L"#　Create by AsuraLibraray\n";
	file2 << endl;

	file2.setf(ios::fixed);
	file2.precision(5);

	for ( i=0; i<mesh.GetNumMaterial(); i++ )
	{
		file2 << L"newmtl ";
		file2 << mesh.GetMaterialData(i).GetNameW() << endl;

		file2 << L"Ka ";
		file2 << mesh.GetMaterialData(i).GetAmbient().r << L" ";
		file2 << mesh.GetMaterialData(i).GetAmbient().g << L" ";
		file2 << mesh.GetMaterialData(i).GetAmbient().b << endl;

		file2 << L"Kd ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().r << L" ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().g << L" ";
		file2 << mesh.GetMaterialData(i).GetDiffuse().b << endl;

		file2 << L"Ks ";
		file2 << mesh.GetMaterialData(i).GetSpecular().r << L" ";
		file2 << mesh.GetMaterialData(i).GetSpecular().g << L" ";
		file2 << mesh.GetMaterialData(i).GetSpecular().b << endl;

		file2 << L"Ns ";
		file2 << mesh.GetMaterialData(i).GetPower() << endl;

		file2 << L"illum 2\n";

		if ( mesh.GetMaterialData(i).GetTexture().GetHandle() != 0 )
		{
			file2 << L"map_Kd ";
			file2 << mesh.GetMaterialData(i).GetTexture().GetNameW() << endl;
		}

		file2 << endl;
	}
	file2 << L"# " << mesh.GetNumMaterial() << L" elements\n\n";

	file2.close();
	return true;
}