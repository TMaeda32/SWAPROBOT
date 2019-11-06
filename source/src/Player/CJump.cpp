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
		//セット
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
		//描画
		m_pMesh->DrawMesh();
	}
	m_flg = false;
}

void CJump::Draw2D()
{
}

void CJump::JumpStart()
{
	//貯めた分ジャンプ
	mSpeed = mAccel + mChargeTime * 0.018f;	
}

void CJump::Charge()
{
	//貯める
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
