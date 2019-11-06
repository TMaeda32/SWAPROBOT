#pragma once
#include<d3dx9.h>

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


class CDirectXGraphics
{
public:

	bool Init(HWND hWnd, int Width, int Height, bool FullScreen);
	void Release();
	void SetBillBoard(BOOL FLAG) { mpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FLAG); }
	const LPDIRECT3DDEVICE9 GetDevice() { return mpD3DDevice; }
	const LPD3DXSPRITE& GetSprite() const { return mpSprite; }
	const LPD3DXFONT& GetFont() const { return mpFont; }

private:
	LPDIRECT3D9				mpD3D;		// Direct3Dインターフェイス
	LPDIRECT3DDEVICE9		mpD3DDevice;// Direct3DDeviceインターフェイス

	D3DPRESENT_PARAMETERS   d3dpp;

	LPD3DXSPRITE mpSprite;		// スプライト
	LPD3DXFONT mpFont;			// フォント

public:
	
	CDirectXGraphics();

	// シングルトンの実装
	static CDirectXGraphics &getInstance() {
		static CDirectXGraphics Instance;
		return Instance;
	}
};

// マクロ定義
#define cdg CDirectXGraphics::getInstance()