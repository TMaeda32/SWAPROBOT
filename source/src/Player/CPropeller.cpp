#include "CPropeller.h"


CPropeller::CPropeller()
{
}


CPropeller::~CPropeller()
{
}

void CPropeller::Init()
{
	tag = "propeller";

	m_pArmMesh = std::make_shared<CMesh>();
	m_pArmMesh->LoadMesh("Resource/PropellerArm.x");

	m_pPropellerMesh = std::make_shared<CMesh>();
	m_pPropellerMesh->LoadMesh("Resource/Propeller.x");

	D3DXMatrixIdentity(&m_mArm);
	D3DXMatrixIdentity(&m_mPropeller);

	drawFlg = false;
	mSpeed = 0.0f;
	mRotSpeed = 0.0f;
}

void CPropeller::Update()
{
}

void CPropeller::Draw()
{
	if (m_flg)
	{
		//腕
		m_mArm = m_mWorld;
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mArm);
		m_pArmMesh->DrawMesh();

		//プロペラ
		m_mPropeller = m_mWorld;
		D3DXMATRIX TmpMat, TmpRotMat;
		D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(mRotSpeed));
		D3DXMatrixTranslation(&TmpMat, -3.1f, 4.5f, 0.0f);
		m_mPropeller = TmpRotMat * TmpMat * m_mArm;
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mPropeller);
		m_pPropellerMesh->DrawMesh();

		//プロペラ2
		D3DXMatrixTranslation(&TmpMat, 3.1f, 4.5f, 0.0f);
		D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(-mRotSpeed));
		m_mPropeller = TmpRotMat * TmpMat * m_mArm;
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mPropeller);
		m_pPropellerMesh->DrawMesh();
	}
	m_flg = false;
}

void CPropeller::Draw2D()
{
}

void CPropeller::Active()
{
	//プロペラの回転
	mSpeed = 0.0f;
	mRotSpeed += 20.0f;
	if (mRotSpeed>359.0f)
	{
		mRotSpeed = 0.0f;
	}
}
