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
	//�X�e�[�W�̏��
	//D3DXMATRIX mMat;
	//�}�e���A�����
	D3DMATERIAL9 mMaterial;
	//���C�g
	D3DLIGHT9 light;
};