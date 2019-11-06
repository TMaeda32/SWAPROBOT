#include "CChangeLegItem.h"


CChangeLegItem::CChangeLegItem()
{
}


CChangeLegItem::~CChangeLegItem()
{
}

void CChangeLegItem::Init()
{
	tag = "changeLegItem";

	m_pNitroMesh = std::make_shared<CMesh>();
	m_pNitroMesh->LoadMesh("Resource/NitroItem.x");

	m_pJumpMesh = std::make_shared<CMesh>();
	m_pJumpMesh->LoadMesh("Resource/JumpItem.x");

	D3DXMatrixTranslation(&m_mWorld, 20.0f, 5.0f, -80.0f);

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

	//�j�g�����Z�b�g
	type = 1;
}

void CChangeLegItem::Update()
{
}

void CChangeLegItem::Draw()
{
	//���C�gOn
	cdg.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	cdg.GetDevice()->SetFVF(FVF_VERTEX);
	//�Z�b�g
	cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
	//�}�e���A���Z�b�g
	cdg.GetDevice()->SetMaterial(&mMaterial);
	switch (type)
	{
		//�j�g��
	case 1:
		m_pNitroMesh->DrawMesh();
		break;
		//�W�����v
	case 2:
		m_pJumpMesh->DrawMesh();
	default:
		break;
	}
}

void CChangeLegItem::Draw2D()
{
}
