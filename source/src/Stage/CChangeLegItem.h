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
	//変更処理
	const int& Change(const int& Ltype)
	{
		int t;
		t = type;
		type = Ltype;
		return t;
	}

private:
	//ニトロ
	std::shared_ptr<CMesh> m_pNitroMesh;
	//ジャンプ
	std::shared_ptr<CMesh> m_pJumpMesh;

	//マテリアル情報
	D3DMATERIAL9 mMaterial;
	//ライト
	D3DLIGHT9 light;
	//種類 1:ニトロ、2:ジャンプ、3:
	int type;
};