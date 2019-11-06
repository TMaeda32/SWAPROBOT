#include "CChangeArmItem.h"


CChangeArmItem::CChangeArmItem()
{
}


CChangeArmItem::~CChangeArmItem()
{
}

void CChangeArmItem::Init()
{
	tag = "changeArmItem";

	m_pPropellerMesh = std::make_shared<CMesh>();
	m_pPropellerMesh->LoadMesh("Resource/PropellerItem.x");

	m_pStrongMesh = std::make_shared<CMesh>();
	m_pStrongMesh->LoadMesh("Resource/StrongItem.x");

	D3DXMatrixTranslation(&m_mWorld, -20.0f, 25.0f, 100.0f);

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	light.Specular.a = 1.0f;
	light.Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;

	cdg.GetDevice()->SetLight(0, &light);
	cdg.GetDevice()->LightEnable(0, TRUE);

	//プロペラをセット
	type = 2;
}

void CChangeArmItem::Update()
{
}

void CChangeArmItem::Draw()
{
	//ライトOn
	cdg.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	cdg.GetDevice()->SetFVF(FVF_VERTEX);
	//セット
	cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
	//マテリアルセット
	cdg.GetDevice()->SetMaterial(&mMaterial);
	switch (type)
	{
		//パワー
	case 1:
		m_pStrongMesh->DrawMesh();
		break;
	case 2:
		//プロペラ
		m_pPropellerMesh->DrawMesh();
	default:
		break;
	}
}

void CChangeArmItem::Draw2D()
{
}
