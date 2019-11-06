
#include "CResult.h"

CResult::CResult()
{
	D3DXMatrixIdentity(&m_mTex);
	m_pTex = std::make_shared<LPDIRECT3DTEXTURE9>();
	m_Texture.LoadText(&*m_pTex, "Resource/Result.png", SCRW, SCRH, NULL);
}

CResult::~CResult()
{
}

void CResult::Init()
{
}

void CResult::Update()
{
}

void CResult::Render2D()
{
	//�`��
	RECT rcTitle = { 0,0,SCRW,SCRH };
	cdg.GetDevice()->SetTransform(D3DTS_WORLD,&m_mTex);
	cdg.GetSprite()->Draw(*m_pTex, &rcTitle, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CResult::Render3D()
{
}

void CResult::Camera()
{
	D3DXMATRIX mView, mProj;
	// ���_���v�Z

	// ���_�s��̐ݒ�
	D3DXVECTOR3 cameraPos(0.0f, 10.0f, -30.0f), cameraLook, cameraHead;

	//�ʒu
	cameraLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����_
	cameraHead = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixLookAtLH(&mView,
		&cameraPos,// �J�����̈ʒu
		&cameraLook,	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
	cdg.GetDevice()->SetTransform(D3DTS_VIEW, &mView);
	cdg.GetDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}