#pragma once
#include "../Library/CBaseScene.h"
#include "../Library/CSceneManager.h"
#include "../Library/Library.h"

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

class CResult : public CBaseScene
{
public:
	CResult();
	~CResult();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
	virtual void Camera() override;

private:
	//2D画像
	D3DXMATRIX m_mTex;
	CTexture m_Texture;
	std::shared_ptr<LPDIRECT3DTEXTURE9> m_pTex = nullptr;
	
};

