#pragma once
#include<d3dx9.h>
#include"../Library/CObject.h"

class CChangeLegItem : public CObject
{
public:
	CChangeLegItem();
	~CChangeLegItem();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	//�ύX����
	const int& Change(const int& Ltype)
	{
		int t;
		t = type;
		type = Ltype;
		return t;
	}

private:
	//�j�g��
	std::shared_ptr<CMesh> m_pNitroMesh;
	//�W�����v
	std::shared_ptr<CMesh> m_pJumpMesh;

	//�}�e���A�����
	D3DMATERIAL9 mMaterial;
	//���C�g
	D3DLIGHT9 light;
	//��� 1:�j�g���A2:�W�����v�A3:
	int type;
};