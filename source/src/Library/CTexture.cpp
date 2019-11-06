#include "CTexture.h"
#include "Library.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

void CTexture::LoadText(LPDIRECT3DTEXTURE9 * lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
		if (W == 0)W = D3DX_DEFAULT;
		if (H == 0)H = D3DX_DEFAULT;
		D3DXCreateTextureFromFileEx(cdg.GetDevice(), fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}