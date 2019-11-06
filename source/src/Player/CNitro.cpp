#include "CNitro.h"
#include "../Library/CObjectManager.h"


CNitro::CNitro()
{
}


CNitro::~CNitro()
{
}

void CNitro::Init()
{
	tag = "nitro";

	m_Accel = 1.03f;
	m_Speed = 0.5f;

	CObject::Init();
	
	m_pMesh->LoadMesh("Resource/Nitro.x");
}

void CNitro::Update()
{
}

void CNitro::Draw()
{
	if (m_flg)
	{
		//ƒZƒbƒg
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
		//•`‰æ
		m_pMesh->DrawMesh();
	}
	m_flg = false;
}

void CNitro::Draw2D()
{
}

void CNitro::Accelerate()
{
	//‰Á‘¬
	m_Speed *= m_Accel;
	if (m_Speed > 2.0f)
	{
		m_Speed = 2.0f;
	}
}

void CNitro::Decelerate()
{
	//Œ¸‘¬
	if (m_Speed > 0.5f)
	{
		m_Speed *= 0.96f;
	}
	else
	{
		m_Speed = 0.5f;
	}
}

