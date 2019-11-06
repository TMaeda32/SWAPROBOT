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
	//�W�����v�J�n
	void JumpStart();
	//����������Charge
	void Charge();
	//���l�̃��Z�b�g
	void Reset();
	//���x�m��
	const float& GetSpeed() { return mSpeed; }
	//�`�悳����
	void DrawOn() { m_flg = true; }

private:
	//�`�悷�邩
	bool m_flg;

	//�s��
	D3DXMATRIX mMat;
	//�X�s�[�h
	float mSpeed;
	//����
	float mAccel;
	//����������
	int mChargeTime;
};