#pragma once
#include<d3dx9.h>
#include"../Library/CObject.h"

class CChangeArmItem : public CObject
{
public:
	CChangeArmItem();
	~CChangeArmItem();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	//�ύX����
	const int& Change(const int& Atype)
	{ 
		int t;
		t = type;
		type = Atype;
		return t;
	}

private:
	//�v���y��
	std::shared_ptr<CMesh> m_pPropellerMesh;
	//�p���[
	std::shared_ptr<CMesh> m_pStrongMesh;

	//�}�e���A�����
	D3DMATERIAL9 mMaterial;
	//���C�g
	D3DLIGHT9 light;
	//��� 1:�p���[�A2:�v���y���A3:��Ɏ���
	int type;
};