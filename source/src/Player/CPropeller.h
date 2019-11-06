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
	//�v���y��������
	void Active();
	//���x�擾
	const float& GetSpeed() const { return mSpeed; }
	//�`�悳����
	void DrawOn() { m_flg = true; }

private:
	//�r
	std::shared_ptr<CMesh> m_pArmMesh;
	//�r�̍s��
	D3DXMATRIX m_mArm;
	//�v���y��
	std::shared_ptr<CMesh> m_pPropellerMesh;
	//�v���y���̍s��
	D3DXMATRIX m_mPropeller;
	//�`�攻�f
	bool drawFlg;
	//�`�悷�邩
	bool m_flg;

	//�X�s�[�h
	float mSpeed;
	//��]�X�s�[�h
	float mRotSpeed;
};