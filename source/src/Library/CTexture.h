#pragma once
#include<d3dx9.h>
class CTexture
{
public:
	CTexture();
	~CTexture();
	//デバック用テキスト
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
};

