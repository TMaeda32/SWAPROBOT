#pragma once
#include<d3dx9.h>
class CTexture
{
public:
	CTexture();
	~CTexture();
	//�f�o�b�N�p�e�L�X�g
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
};

