#include "CStage.h"
#include "../Library/CObjectManager.h"

CStage::CStage()
{
	/*m_pMesh = std::make_shared<CMesh>();
	m_pMesh->LoadMesh("Resource/stage8.x");
	D3DXMatrixIdentity(&mMat);

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;

	cdg.GetDevice()->SetLight(0, &light);
	cdg.GetDevice()->LightEnable(0, TRUE);*/
}


CStage::~CStage()
{
	
}

void CStage::Init()
{
	tag = "stage";
	m_pMesh = std::make_shared<CMesh>();
	m_pMesh->LoadMesh("Resource/stage1.x");
	D3DXMatrixIdentity(&m_mWorld);

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;

	cdg.GetDevice()->SetLight(0, &light);
	cdg.GetDevice()->LightEnable(0, TRUE);
}

void CStage::Update()
{
}

void CStage::Draw()
{
	//ライトOn
	cdg.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	cdg.GetDevice()->SetFVF(FVF_VERTEX);
	//セット
	cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_mWorld);
	//マテリアルセット
	cdg.GetDevice()->SetMaterial(&mMaterial);
	m_pMesh->DrawMesh();
}

void CStage::Draw2D()
{
}
