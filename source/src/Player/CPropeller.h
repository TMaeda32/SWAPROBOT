#pragma once
#include "../Library/CObject.h"

class CMesh;

class CPropeller : public CObject
{
public:
	CPropeller();
	~CPropeller();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	//プロペラ発動中
	void Active();
	//速度取得
	const float& GetSpeed() const { return mSpeed; }
	//描画させる
	void DrawOn() { m_flg = true; }

private:
	//腕
	std::shared_ptr<CMesh> m_pArmMesh;
	//腕の行列
	D3DXMATRIX m_mArm;
	//プロペラ
	std::shared_ptr<CMesh> m_pPropellerMesh;
	//プロペラの行列
	D3DXMATRIX m_mPropeller;
	//描画判断
	bool drawFlg;
	//描画するか
	bool m_flg;

	//スピード
	float mSpeed;
	//回転スピード
	float mRotSpeed;
};