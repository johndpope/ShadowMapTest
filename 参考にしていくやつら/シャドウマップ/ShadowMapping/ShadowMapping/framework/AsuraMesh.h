/**********************************************************************
　　AsuraMesh.h

　　Asura Mesh Loader Library

　　Date : Dec. 01, 2007
　　Version : 1.5
　　Author : Pocol
***********************************************************************/

#ifndef _ASURA_MESH_H_INCLUDED_
#define _ASURA_MESH_H_INCLUDED_

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
//　include
//
#include "AsuraMath.h"
#include "AsuraTexture.h"
#include <vector>
#include <windows.h>
using namespace std;
using namespace AsuraMath;

//
//　prototype
//
class AsuraFace;
class AsuraObject;
class AsuraMaterial;
class AsuraMesh;

/////////////////////////////////////////////////////////////////////////
//　　AsuraFace class
/////////////////////////////////////////////////////////////////////////
class AsuraFace
{
protected:
	uint element;
	int indexM;
	int indexV[4];
	int indexN[4];
	int indexU[4];
	friend void AsuraComputeNormals(AsuraMesh &mesh);
public:
	AsuraFace(uint e=0, int m=-1, int v[]=NULL, int n[]=NULL, int u[]=NULL);
	AsuraFace &operator=(AsuraFace &f);
	void SetElement(uint elem);
	void SetMaterialIndex(int index);
	void SetVertexIndex(int index[]);
	void SetNormalIndex(int index[]);
	void SetUvIndex(int index[]);
	uint GetElement();
	int GetMaterailIndex();
	int* GetVertexIndex();
	int* GetNormalIndex();
	int* GetUvIndex();
	void GetVertexIndex(int v[]);
	void GetNormalIndex(int n[]);
	void GetUvIndex(int t[]);
};

/////////////////////////////////////////////////////////////////////////
//　　AsuraMaterial
/////////////////////////////////////////////////////////////////////////
class AsuraMaterial
{
protected:
	char nameA[MAX_PATH];
	wchar_t nameW[MAX_PATH];
	Color4f ambient;
	Color4f diffuse;
	Color4f specular;
	Color4f emissive;
	float power;
	AsuraTexture texture;
public:
	AsuraMaterial();
	AsuraMaterial &operator=(AsuraMaterial &mat);
	void SetNameA(char* fname);
	void SetNameW(wchar_t* fname);
	void SetAmbient(Color4f famb);
	void SetDiffuse(Color4f fdif);
	void SetSpecular(Color4f fspe);
	void SetEmissive(Color4f femi);
	void SetPower(float fpow);
	void SetTexture(AsuraTexture ftex);
	char* GetNameA();
	wchar_t* GetNameW();
	Color4f GetAmbient();
	Color4f GetDiffuse();
	Color4f GetSpecular();
	Color4f GetEmissive();
	float GetPower();
	AsuraTexture GetTexture();
#ifdef UNICODE
#define SetName SetNameW
#define GetName GetNameW
#else
#define SetName SetNameA
#define GetName GetNameA
#endif

};

/////////////////////////////////////////////////////////////////////////
//　　AsuraObject class
/////////////////////////////////////////////////////////////////////////
class AsuraObject
{
protected:
	char nameA[MAX_PATH];
	wchar_t nameW[MAX_PATH];
	uint num_vertex;
	uint num_normal;
	uint num_uv;
	uint num_face;
	Vector3f* vertex;
	Vector3f* normal;
	Vector2f* uv;
	AsuraFace* face;
	friend void AsuraComputeNormals(AsuraMesh &mesh);
public:
	AsuraObject();
	~AsuraObject();
	AsuraObject &operator=(AsuraObject &obj);
	void Release();
	void SetNameA(char* fname);
	void SetNameW(wchar_t* fname);
	uint AddVertex(Vector3f vert);
	uint AddNormal(Vector3f norm);
	uint AddUv(Vector2f texc);
	uint AddFace(AsuraFace surf);
	uint GetNumVertex();
	uint GetNumNormal();
	uint GetNumUv();
	uint GetNumFace();
	char* GetNameA();
	wchar_t* GetNameW();
	Vector3f GetVertex(uint index);
	Vector3f GetNormal(uint index);
	Vector2f GetUv(uint index);
	AsuraFace GetFace(uint index);
#ifdef UNICODE
#define SetName SetNameW
#define GetName GetNameW
#else
#define SetName SetNameA
#define GetName GetNameA
#endif

};

/////////////////////////////////////////////////////////////////////////
//　　AsuraMesh
/////////////////////////////////////////////////////////////////////////
class AsuraMesh
{
protected:
	uint num_object;
	uint num_material;
	AsuraObject *object;
	AsuraMaterial* material;
	friend void AsuraComputeNormals(AsuraMesh &mesh);
public:
	AsuraMesh();
	~AsuraMesh();
	void Release();
	void Render(int objcet_index);
	void Render();
	uint AddObject(AsuraObject &obj);
	uint AddMaterial(AsuraMaterial &mat);
	uint GetNumObject();
	uint GetNumMaterial();
	AsuraObject GetObjectData(uint index);
	AsuraMaterial GetMaterialData(uint index);	
	void CloneMesh(AsuraMesh &pCloneMesh);
};

//
// Functions
//
void AsuraComputeBoundingSphere(AsuraMesh &mesh, Vector3f &center, float &radius);
void AsuraComputeBoundingBox(AsuraMesh &mesh, Vector3f &minimum, Vector3f &maximum);
void AsuraComputeNormals(AsuraMesh &mesh);
GLuint AsuraCreateDisplayList(AsuraMesh &mesh);
// Char
bool AsuraLoadMeshFromX_A(char *filename, AsuraMesh &mesh);
bool AsuraLoadMeshFromOBJ_A(char *filename, AsuraMesh &mesh);
bool AsuraSaveMeshToX_A(char *filename, AsuraMesh &mesh);
bool AsuraSaveMeshToOBJ_A(char *filename, AsuraMesh &mesh);
// Wide Char
bool AsuraLoadMeshFromX_W(wchar_t *filename, AsuraMesh &mesh);
bool AsuraLoadMeshFromOBJ_W(wchar_t* filename, AsuraMesh &mesh);
bool AsuraSaveMeshToX_W(wchar_t* filename, AsuraMesh &mesh);
bool AsuraSaveMeshToOBJ_W(wchar_t *filename, AsuraMesh &mesh);

//　Unicode Version
#ifdef UNICODE
#define AsuraLoadMeshFromX AsuraLoadMeshFromX_W
#define AsuraLoadMeshFromOBJ AsuraLoadMeshFromOBJ_W
#define AsuraSaveMeshToX AsuraSaveMeshToX_W
#define AsuraSaveMeshToOBJ AsuraSaveMeshToOBJ_W
//　Ascii Version
#else
#define AsuraLoadMeshFromX AsuraLoadMeshFromX_A
#define AsuraLoadMeshFormOBJ AsuraLoadMeshFromOBJ_A
#define AsuraSaveMeshToX AsuraSaveMeshToX_A
#define AsuraSaveMeshToOBJ AsuraSaveMeshToOBJ_A
#endif

#endif