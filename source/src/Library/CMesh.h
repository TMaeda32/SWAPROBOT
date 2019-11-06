#pragma once
#include<d3dx9.h>

class CMesh
{
public:
	CMesh();
	~CMesh();

	const LPD3DXMESH GetMesh() const { return mpMesh; }

	// メッシュ読み込み
	void LoadMesh(const char FName[]);
	// メッシュ解放
	void ReleaseMesh();
	// メッシュ描画
	void DrawMesh();

protected:
	
	LPD3DXMESH mpMesh;		 // メッシュの形状
	DWORD mNumMaterial;		 // グループの数
	D3DMATERIAL9* mpMaterial;	// マテリアルの内容
	LPDIRECT3DTEXTURE9* mpTex; // テクスチャの内容
};
