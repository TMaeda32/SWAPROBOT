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
	//変更処理
	const int& Change(const int& Atype)
	{ 
		int t;
		t = type;
		type = Atype;
		return t;
	}

private:
	//プロペラ
	std::shared_ptr<CMesh> m_pPropellerMesh;
	//パワー
	std::shared_ptr<CMesh> m_pStrongMesh;

	//マテリアル情報
	D3DMATERIAL9 mMaterial;
	//ライト
	D3DLIGHT9 light;
	//種類 1:パワー、2:プロペラ、3:手に持つ
	int type;
};