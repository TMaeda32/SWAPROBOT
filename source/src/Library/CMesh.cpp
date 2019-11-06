#include "CMesh.h"
#include "Library.h"

CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

void CMesh::LoadMesh(const char FName[])
{
	LPD3DXBUFFER lpD3DXBuffer;

	D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, cdg.GetDevice(), NULL, &lpD3DXBuffer, NULL, &(mNumMaterial), &(mpMesh));

	mpMaterial = new D3DMATERIAL9[mNumMaterial];
	mpTex = new LPDIRECT3DTEXTURE9[mNumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i < mNumMaterial; i++) {
		mpMaterial[i] = D3DXMat[i].MatD3D;
		mpMaterial[i].Ambient = mpMaterial[i].Diffuse;
		if (FAILED(D3DXCreateTextureFromFile(cdg.GetDevice(), D3DXMat[i].pTextureFilename, &(mpTex[i])))) {
			mpTex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();
}

void CMesh::ReleaseMesh()
{
	if (mpMesh != NULL) {
		DWORD i;

		delete[] mpMaterial;
		for (i = 0; i < mNumMaterial; i++) {
			if (mpTex[i] != NULL) {
				mpTex[i]->Release();
				mpTex[i] = NULL;
			}
		}
		delete[] mpTex;
		mpMesh->Release();

		mpMesh = NULL;
	}
}

void CMesh::DrawMesh()
{
	for (DWORD i = 0; i < mNumMaterial; i++)
	{
		// メッシュに要素の情報を渡す
		cdg.GetDevice()->SetMaterial(&mpMaterial[i]);
		cdg.GetDevice()->SetTexture(0, mpTex[i]);

		// メッシュの表示
		mpMesh->DrawSubset(i);
	}
}
