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
	//����
	void Accelerate();
	//����
	void Decelerate();

	//���x�擾
	const float& GetSpeed() const { return m_Speed; }
	//�`�悳����
	void DrawOn() { m_flg = true; }

private:
	//�`�悷�邩
	bool m_flg;
	
	//�X�s�[�h
	float m_Speed;
	//����
	float m_Accel;
};