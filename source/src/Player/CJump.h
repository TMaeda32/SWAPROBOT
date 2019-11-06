#pragma once
#include "../Library/CObject.h"

class CMesh;

class CJump : public CObject
{
public:
	CJump();
	~CJump();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	//ジャンプ開始
	void JumpStart();
	//長押し中のCharge
	void Charge();
	//数値のリセット
	void Reset();
	//速度確保
	const float& GetSpeed() { return mSpeed; }
	//描画させる
	void DrawOn() { m_flg = true; }

private:
	//描画するか
	bool m_flg;

	//行列
	D3DXMATRIX mMat;
	//スピード
	float mSpeed;
	//加速
	float mAccel;
	//押した長さ
	int mChargeTime;
};