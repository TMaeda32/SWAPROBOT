#include "CPlayer.h"
#include "CNitro.h"
#include "CJump.h"
#include "CStrong.h"
#include "CPropeller.h"
#include "../Stage/CStage.h"
#include "../Stage/CChangeLegItem.h"
#include "../Stage/CChangeArmItem.h"
#include "../Library/CObjectManager.h"
#include <stdio.h>

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	tag = "player";

	mBodyMesh = std::make_shared<CMesh>();
	mBodyMesh->LoadMesh("Resource/playerBodySP.x");

	D3DXMatrixIdentity(&mRotationMat);
	D3DXMatrixTranslation(&mTransMat, 0.0f, 5.0f, -80.0f);
	D3DXMatrixIdentity(&mCameraRotationMat);

	mPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mAngle = 0;
	PI = 0;
	mCameraAngle = 0;
	

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	light.Ambient.r = 0.2f;
	light.Ambient.g = 0.2f;
	light.Ambient.b = 0.2f;

	cdg.GetDevice()->SetLight(0, &light);
	cdg.GetDevice()->LightEnable(0, TRUE);

	mGravitySpeed = 1.0f;
	mNSpeed = 0.5f;
	mJSpeed = 0.0f;

	mArmNumber = 1;
	mLegNumber = 2;
	mJumpJudge = true;
	lastLegKey = false;
	changeLegTime = 0;
	changeArmTime = 0;
}

void CPlayer::Update()
{
	//�d��
	mJSpeed -= 0.1f;

	FloorCheck();

	//�A�N�V��������
	{
		//��
		if (GetAsyncKeyState('Z') & 0x8000)
		{
			nowLegKey = true;
			LegDownUpdate();
		}
		else
		{
			nowLegKey = false;
			LegUpUpdate();
		}
		//�r
		if (GetAsyncKeyState('X') & 0x8000)
		{
			if (mArmNumber != 1)
			{
				nowArmKey = true;
				ArmDownUpdate();
			}
		}
		else
		{
			if (mArmNumber != 1)
			{
				nowArmKey = false;
				ArmUpUpdate();
			}
		}
		lastLegKey = nowLegKey;
	}

	//�ړ��L�[����
	Move();
	//�A�C�e���ɓ���������
	ItemHitJudge();
	//�J��������
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mCameraAngle += 2.0f;
		if (mCameraAngle > PI)
			mCameraAngle -= 2 * PI;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mCameraAngle -= 2.0f;
		if (mCameraAngle < -PI)
			mCameraAngle += 2 * PI;
	}
	D3DXMatrixRotationY(&mCameraRotationMat, D3DXToRadian(mCameraAngle));


	//�W�����v���㏸
	mTransMat._42 += mJSpeed;
	//�d�͕␳
	if (stageFloorDis > 5.2f)
	{
		mTransMat._42 -= mGravitySpeed;
	}
	//�ړ��A��]���ʂ�����
	mMat = mRotationMat * mTransMat;
	mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
	m_mWorld = mMat;

	//�v���C���[�̈ʒu����S�Ẵp�[�c�ɓn��
	std::list<std::shared_ptr<CObject>> pParts;
	ObjMgr.FindObjectsWithTag(pParts, "nitro");
	ObjMgr.FindObjectsWithTag(pParts, "jump");
	ObjMgr.FindObjectsWithTag(pParts, "strong");
	ObjMgr.FindObjectsWithTag(pParts, "propeller");
	for (auto&& par : pParts)
	{
		par->SetMatrix(mMat);
	}

	//�p���[�͈ړ���ɍŌ�ɒʂ�
	if (mArmNumber == 1)
	{
		if (GetAsyncKeyState('X') & 0x8000)
		{
			nowArmKey = true;
			ArmDownUpdate();
		}
		else
		{
			nowArmKey = false;
			ArmUpUpdate();
		}
	}
}

void CPlayer::LegDownUpdate()
{
	std::list<std::shared_ptr<CObject>> pHaveLeg;
	switch (mLegNumber)
	{
		//�j�g��
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveLeg, "nitro");
		for (auto&& tmp : pHaveLeg)
		{
			std::shared_ptr<CNitro> nit;
			nit = std::dynamic_pointer_cast<CNitro>(tmp);
			nit->DrawOn();
			nit->Accelerate();
			mNSpeed = nit->GetSpeed();
		}
		break;
		//�W�����v
	case 2:
		//�W�����v�͂𗭂߂�
		ObjMgr.FindObjectsWithTag(pHaveLeg, "jump");
		for (auto&& tmp : pHaveLeg)
		{
			std::shared_ptr<CJump> jum;
			jum = std::dynamic_pointer_cast<CJump>(tmp);
			jum->DrawOn();
			jum->Charge();
		}
		break;
	default:
		break;
	}
}

void CPlayer::LegUpUpdate()
{
	std::list<std::shared_ptr<CObject>> pHaveLeg;
	switch (mLegNumber)
	{
		//�j�g��
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveLeg, "nitro");
		for (auto&& tmp : pHaveLeg)
		{
			std::shared_ptr<CNitro> nit;
			nit = std::dynamic_pointer_cast<CNitro>(tmp);
			nit->DrawOn();
			nit->Decelerate();
			mNSpeed = nit->GetSpeed();
		}
		break;
		//�W�����v
	case 2:
		//�W�����v�J�n
		ObjMgr.FindObjectsWithTag(pHaveLeg, "jump");
		for (auto&& tmp : pHaveLeg)
		{
			std::shared_ptr<CJump> jum;
			jum = std::dynamic_pointer_cast<CJump>(tmp);
			jum->DrawOn();
			if (mJumpJudge && lastLegKey && !nowLegKey) {
				jum->JumpStart();
				mJSpeed = jum->GetSpeed();
				jum->Reset();
				mJumpJudge = false;
			}
		}

	default:
		break;
	}
}

void CPlayer::ArmDownUpdate()
{
	std::list<std::shared_ptr<CObject>> pHaveArm;
	switch (mArmNumber)
	{
		//�p���[
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveArm, "strong");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CStrong> str;
			str = std::dynamic_pointer_cast<CStrong>(tmp);
			str->DrawOn();
			//�p���`
			str->Attack();
		}
		break;
		//�v���y��
	case 2:
		ObjMgr.FindObjectsWithTag(pHaveArm, "propeller");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CPropeller> pro;
			pro = std::dynamic_pointer_cast<CPropeller>(tmp);
			pro->DrawOn();
			//�������ƍ~��
			pro->Active();
			mJSpeed = pro->GetSpeed();
		}
		mGravitySpeed = 0.1f;
	default:
		break;
	}
}

void CPlayer::ArmUpUpdate()
{
	std::list<std::shared_ptr<CObject>> pHaveArm;
	switch (mArmNumber)
	{
		//�p���[
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveArm, "strong");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CStrong> str;
			str = std::dynamic_pointer_cast<CStrong>(tmp);
			str->DrawOn();
			//�߂�
			str->Return();
		}
		break;
		//�v���y��
	case 2:
		ObjMgr.FindObjectsWithTag(pHaveArm, "propeller");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CPropeller> pro;
			pro = std::dynamic_pointer_cast<CPropeller>(tmp);
			pro->DrawOn();
		}
		break;
	default:
		break;
	}
}

void CPlayer::FloorCheck()
{
	//�X�e�[�W�̏��擾
	std::list<std::shared_ptr<CObject>> pStage;
	ObjMgr.FindObjectsWithTag(pStage, "stage");
	//�n�ʔ���
	for (auto&& tmp : pStage)
	{
		std::shared_ptr<CStage> sta;
		sta = std::dynamic_pointer_cast<CStage>(tmp);
		//���C���˕���
		D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//���C���ˈʒu
		mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
		if (HitJudge(sta->GetMesh()->GetMesh(), &sta->GetMatrix(), &Vec, &mPos, &stageFloorDis))
		{
			//��������
			//�n�ʕ␳
			if (stageFloorDis <= 5.2f)
			{
				mTransMat._42 += 5.0f - stageFloorDis;
				mGravitySpeed = 0.0f;
				mJSpeed = 0.0f;
				mJumpJudge = true;
			}
			else
			{
				mGravitySpeed = 1.0f;
			}
		}
	}
}

void CPlayer::Move()
{
	//�X�e�[�W�̏��擾
	std::list<std::shared_ptr<CObject>> pStage;
	ObjMgr.FindObjectsWithTag(pStage, "stage");
	//�v���C���[�̓����x�N�g��
	D3DXVECTOR3 moveVec(0.0f, 0.0f, 0.0f);
	//�v���C���[�������Ă��邩
	bool moveFlg = false;
	//��Ɨp�x�N�g��
	D3DXVECTOR3 tmpVec;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mCameraRotationMat);
		moveVec += tmpVec;
		moveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &mCameraRotationMat);
		moveVec += tmpVec;
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mCameraRotationMat);
		moveVec += tmpVec;
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXVec3TransformNormal(&tmpVec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &mCameraRotationMat);
		moveVec += tmpVec;
		moveFlg = true;
	}

	D3DXMATRIX tmpMat;
	if (moveFlg)
	{
		//�ړ�����
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= mNSpeed;
		D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
		mTransMat = tmpMat * mTransMat;

		//���ςŎc�艽�x���΂������v�Z(�������Ă������()�ƌ�����������(moveVec))
		D3DXVec3TransformNormal(&nowVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRotationMat);
		D3DXVec3Normalize(&moveVec, &moveVec);
		float tmpAng;
		tmpAng = D3DXVec3Dot(&nowVec, &moveVec);
		tmpAng = D3DXToDegree(acos(tmpAng));
		if (tmpAng >= 0.1f)
		{
			//�E��肩����肩(�O��)
			D3DXVECTOR3 crossVec;
			D3DXVec3Cross(&crossVec, &nowVec, &moveVec);
			if (tmpAng >= 10.0f)
			{
				tmpAng = 10.0f;
			}
			if (crossVec.y > 0.1f)
			{
				mAngle += tmpAng;
			}
			else if (crossVec.y < 0.1f)
			{
				mAngle -= tmpAng;
			}
			else
			{
				mAngle += tmpAng;
			}
			//D3DXVec3Normalize(&crossVec,&crossVec);
			D3DXMatrixRotationY(&mRotationMat, D3DXToRadian(mAngle));
		}
		//�O���ɕǂ����邩
		for (auto&& tmp : pStage)
		{
			std::shared_ptr<CStage> sta;
			sta = std::dynamic_pointer_cast<CStage>(tmp);
			//���C���ˈʒu
			mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
			//���������Ƃ���܂ł̋���
			float stageWallDis;
			//BOOL stageHit;
			//LPD3DXMESH tmpMesh = pStageMesh->GetMesh();
			if (HitJudge(sta->GetMesh()->GetMesh(), &sta->GetMatrix(), &nowVec, &mPos, &stageWallDis))
			{
				//�ǂɓ�������
				if (stageWallDis < 7.0f && stageWallDis != -1.0f)
				{
					//�ڂ̑O�ɕǂ�����
					//�␳����
					D3DXVec3Normalize(&moveVec, &moveVec);
					moveVec.x *= -mNSpeed;
					moveVec.y *= -mNSpeed;
					moveVec.z *= -mNSpeed;
					D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
					mTransMat = tmpMat * mTransMat;
				}
			}
		}
	}
}

void CPlayer::ItemHitJudge()
{
	changeLegTime--;
	changeArmTime--;
	//���̃A�C�e�������ł���
	if (changeLegTime <= 0)
	{
		//�A�C�e���̏��擾
		std::list<std::shared_ptr<CObject>> pChangeLegItem;
		ObjMgr.FindObjectsWithTag(pChangeLegItem, "changeLegItem");
		for (auto&& tmp : pChangeLegItem)
		{
			//�ǂꂭ�炢�̋����Ńq�b�g�Ɣ��f���邩
			float hitDis = 6.0f;
			std::shared_ptr<CChangeLegItem> cha;
			cha = std::dynamic_pointer_cast<CChangeLegItem>(tmp);
			if (HitJudge(&cha->GetMatrix(), &mMat, &hitDis))
			{
				mLegNumber = cha->Change(mLegNumber);
				//3�b�Ԍ������~�߂�
				changeLegTime = 180;
			}
		}
	}
	//�r�̃A�C�e�������ł���
	if (changeArmTime <= 0)
	{
		//�A�C�e���̏��擾
		std::list<std::shared_ptr<CObject>> pChangeArmItem;
		ObjMgr.FindObjectsWithTag(pChangeArmItem, "changeArmItem");
		for (auto&& tmp : pChangeArmItem)
		{
			//�ǂꂭ�炢�̋����Ńq�b�g�Ɣ��f���邩
			float hitDis = 6.0f;
			std::shared_ptr<CChangeArmItem> cha;
			cha = std::dynamic_pointer_cast<CChangeArmItem>(tmp);
			if (HitJudge(&cha->GetMatrix(), &mMat, &hitDis))
			{
				mArmNumber = cha->Change(mArmNumber);
				//3�b�Ԍ������~�߂�
				changeArmTime = 180;
			}
		}
	}
}

void CPlayer::Draw()
{
	cdg.GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	cdg.GetDevice()->SetFVF(FVF_VERTEX);
	cdg.GetDevice()->SetTransform(D3DTS_WORLD, &mMat);
	mBodyMesh->DrawMesh();
	DebugDraw();
}

void CPlayer::Draw2D()
{
}

void CPlayer::DebugDraw()
{
}