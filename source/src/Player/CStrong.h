#pragma once
#include "../Library/CObject.h"

class CMesh;

class CStrong : public CObject
{
public:
	CStrong();
	~CStrong();

	virtual void Init() override;
	virtual void Update() override;
	void Attack();
	void Return();
	virtual void Draw() override;
	virtual void Draw2D() override;
	//�A�j���[�V�����t���[��
	const float& GetFrame() const { return animeFrame; };
	//�`�悳����
	void DrawOn() { m_flg = true; }

private:
	//�r
	struct Arm
	{
		//������I�܂�
		std::shared_ptr<CMesh> m_ShoulderMesh;
		//���
		D3DXMATRIX m_mShoulder;
		//�A�j���[�V�����i�N�H�[�^�j�I���j
		D3DXMATRIX m_mShoulderStart, m_mEndShoulder, m_mShoulderNow;//�ŏ��A�Ō�A����

		//�I�����܂�
		std::shared_ptr<CMesh> m_KnuckleMesh;
		//���
		D3DXMATRIX m_mKnuckle;
		//�A�j���[�V�����i�N�H�[�^�j�I���j
		D3DXMATRIX m_mKnuckleStart, m_mKnuckleEnd, m_mKnuckleNow;//�ŏ��A�Ō�A����
	};

	//���r
	Arm m_LeftArm;
	
	//�E�r
	Arm m_RightArm ;

	//�`�悷�邩
	bool m_flg;
	
	float animeFrame;//�A�j���[�V�����i�s�x(0�`1)
};