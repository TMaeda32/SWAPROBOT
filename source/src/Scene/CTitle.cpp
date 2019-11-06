#include "../Library/Library.h"
#include "CTitle.h"

CTitle::CTitle()
{
	D3DXMatrixIdentity(&m_mTex);
	m_pTex = std::make_shared<LPDIRECT3DTEXTURE9>();
	m_Texture.LoadText(&*m_pTex, "Resource/Title.png", SCRW, SCRH, NULL);
}

CTitle::~CTitle()
{
}

void CTitle::Init()
{
}

void CTitle::Update()
{
	if (GetAsyncKeyState(VK_RETURN)&0x8000)
	{
		csm.ChangeScene("GAME");
	}
}

void CTitle::Render2D()
{
	//描画
	RECT rcTitle = { 0,0,SCRW,SCRH };
	cdg.GetDevice()->SetTransform(D3DTS_WORLD,&m_mTex);
	cdg.GetSprite()->Draw(*m_pTex, &rcTitle, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CTitle::Render3D()
{
}

void CTitle::Camera()
{
	D3DXMATRIX mView, mProj;
	// 視点を計算

	// 視点行列の設定
	D3DXVECTOR3 cameraPos(0.0f, 10.0f, -30.0f), cameraLook, cameraHead;

	//位置
	cameraLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//注視点
	cameraHead = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixLookAtLH(&mView,
		&cameraPos,// カメラの位置
		&cameraLook,	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//行列設定
	cdg.GetDevice()->SetTransform(D3DTS_VIEW, &mView);
	cdg.GetDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}