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
	LPDIRECT3D9				mpD3D;		// Direct3D�C���^�[�t�F�C�X
	LPDIRECT3DDEVICE9		mpD3DDevice;// Direct3DDevice�C���^�[�t�F�C�X

	D3DPRESENT_PARAMETERS   d3dpp;

	LPD3DXSPRITE mpSprite;		// �X�v���C�g
	LPD3DXFONT mpFont;			// �t�H���g

public:
	
	CDirectXGraphics();

	// �V���O���g���̎���
	static CDirectXGraphics &getInstance() {
		static CDirectXGraphics Instance;
		return Instance;
	}
};

// �}�N����`
#define cdg CDirectXGraphics::getInstance()