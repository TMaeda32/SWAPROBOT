#pragma once

class CMesh;

#include "../Library/CObject.h"

class CNitro : public CObject
{
public:
	CNitro();
	~CNitro();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	//加速
	void Accelerate();
	//減速
	void Decelerate();

	//速度取得
	const float& GetSpeed() const { return m_Speed; }
	//描画させる
	void DrawOn() { m_flg = true; }

private:
	//描画するか
	bool m_flg;
	
	//スピード
	float m_Speed;
	//加速
	float m_Accel;
};