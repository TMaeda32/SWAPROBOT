#pragma once
#include<d3dx9.h>

class CMesh
{
public:
	CMesh();
	~CMesh();

	const LPD3DXMESH GetMesh() const { return mpMesh; }

	// ���b�V���ǂݍ���
	void LoadMesh(const char FName[]);
	// ���b�V�����
	void ReleaseMesh();
	// ���b�V���`��
	void DrawMesh();

protected:
	
	LPD3DXMESH mpMesh;		 // ���b�V���̌`��
	DWORD mNumMaterial;		 // �O���[�v�̐�
	D3DMATERIAL9* mpMaterial;	// �}�e���A���̓��e
	LPDIRECT3DTEXTURE9* mpTex; // �e�N�X�`���̓��e
};
