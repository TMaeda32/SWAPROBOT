#pragma once



class CWall;
class CMesh;
class CPlayer;
class CWheel;
class CNitro;
class CJump;
class CStrong;
class CPropeller;
class CStage;

#include "../Library/CObject.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer();

	virtual void Init() override;
	virtual void Update() override;
	//���L�[�_�E��
	void LegDownUpdate();
	//���L�[�A�b�v
	void LegUpUpdate();
	//�r�L�[�_�E��
	void ArmDownUpdate();
	//�r�L�[�A�b�v
	void ArmUpUpdate();
	
	//�n�ʔ���
	void FloorCheck();
	//�ړ�����
	void Move();
	//�A�C�e������
	void ItemHitJudge();

	virtual void Draw() override;
	virtual void Draw2D() override;
	void DebugDraw();

	//�J�����̉�]
	const D3DXMATRIX& GetCameraRot() const { return mCameraRotationMat; };
	//�v���C���[�̈ړ��s��
	const D3DXMATRIX& GetPlayerTrans()const { return mTransMat; }

private:
	//�}�e���A�����
	D3DMATERIAL9 mMaterial;
	//�v���C���[�̍��W
	D3DXVECTOR3 mPos;
	float mAngle;
	//�v���C���[�̏��
	D3DXMATRIX mMat;
	//�v���C���[�̈ړ����
	D3DXMATRIX mTransMat;
	//�v���C���[�̉�]���
	D3DXMATRIX mRotationMat;
	//�������x
	float mGravitySpeed;
	
	//�J�����̉�]
	D3DXMATRIX mCameraRotationMat;
	//�J�����̌���
	float mCameraAngle;
	//�J����
	int PI;
	//���C�g
	D3DLIGHT9 light;

	//�̖{�̃��b�V��
	std::shared_ptr<CMesh> mBodyMesh = nullptr;

	//------------------���֌W----------------------
	//���݂̑��̎��
	int mLegNumber;//1:�j�g���A2:�W�����v�A3:
	//�j�g���̑���
	float mNSpeed;
	//�W�����v����(�������x�ɂ��Ȃ�)
	float mJSpeed;
	//�W�����v�ł��邩(true�ŃW�����v��)
	bool mJumpJudge;
	//���݃L�[�������Ă��邩(true�Ȃ牟���Ă���)
	bool nowLegKey;
	//�O��L�[�������Ă�����(true�Ȃ牟���Ă���)
	bool lastLegKey;

	//----------------�r�֘A-------------------------
	//���݂̘r�̎��
	int mArmNumber;//1:�p���[�A2:�v���y���A3:��Ɏ���
	//���݃L�[�������Ă��邩(true�Ȃ牟���Ă���)
	bool nowArmKey;
	//�O��L�[�������Ă�����(true�Ȃ牟���Ă���)
	bool lastArmKey;

	//�W�����v�ł��邩(true�ŃW�����v��)
	bool mStrongJudge;

	//�n�ʂɓ��������Ƃ���܂ł̋���
	float stageFloorDis;
	//�A�C�e������҂����ԁi1��ύX�����炷���ɂ͌������Ȃ��j
	int changeLegTime;
	int changeArmTime;

	//�p�x�v�Z�p
	D3DXVECTOR3 nowVec;
};