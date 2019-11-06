#include "CJump.h"


CJump::CJump()
{
}


CJump::~CJump()
{
}

void CJump::Init()
{
	tag = "jump";

	mAccel = 2.0f;
	mSpeed = 0.0f;
	mChargeTime = 0;

	CObject::Init();

	m_pMesh->LoadMesh("Resource/Jump.x");
}

void CJump::Update()
{
}

void CJump::Draw()
{
	if (m_flg)
	{
		//�Z�b�g
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
		//�`��
		m_pMesh->DrawMesh();
	}
	m_flg = false;
}

void CJump::Draw2D()
{
}

void CJump::JumpStart()
{
	//���߂����W�����v
	mSpeed = mAccel + mChargeTime * 0.018f;	
}

void CJump::Charge()
{
	//���߂�
	mChargeTime++;
	if (mChargeTime>100)
	{
		mChargeTime = 100;
	}
}

void CJump::Reset()
{
	mAccel = 2.0f;
	mSpeed = 0.0f;
	mChargeTime = 0;
}
