#pragma once
#include "../Library/CObject.h"

class CStage : public CObject
{
public:
	CStage();
	~CStage();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;

	const std::shared_ptr<CMesh> GetCMesh() const { return m_pMesh; }
	
private:
	//std::shared_ptr<CMesh> m_pMesh;
	//ステージの情報
	//D3DXMATRIX mMat;
	//マテリアル情報
	D3DMATERIAL9 mMaterial;
	//ライト
	D3DLIGHT9 light;
};