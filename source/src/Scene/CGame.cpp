#include "CGame.h"

#include "../Stage/CStage.h"
#include "../Stage/CChangeLegItem.h"
#include "../Stage/CChangeArmItem.h"

#include "../Player/CPlayer.h"
#include "../Player/CNitro.h"
#include "../Player/CJump.h"
#include "../Player/CPropeller.h"
#include "../Player/CStrong.h"

#include "../Library/CObjectManager.h"


CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init()
{
	//Stage���m��
	auto pStage = std::make_shared<CStage>();
	pStage->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pStage);//�A�b�v�L���X�g����Ă���ǉ�

	//ChangeLegItem���m��
	auto pChangeLegItem = std::make_shared<CChangeLegItem>();
	pChangeLegItem->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pChangeLegItem);//�A�b�v�L���X�g����Ă���ǉ�

	//ChangeArmItem���m��
	auto pChangeArmItem = std::make_shared<CChangeArmItem>();
	pChangeArmItem->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pChangeArmItem);//�A�b�v�L���X�g����Ă���ǉ�

	//Player���m��
	auto pPlayer = std::make_shared<CPlayer>();
	pPlayer->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pPlayer);//�A�b�v�L���X�g����Ă���ǉ�

	//Nitro���m��
	auto pNitro = std::make_shared<CNitro>();
	pNitro->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pNitro);//�A�b�v�L���X�g����Ă���ǉ�

	//Jump���m��
	auto pJump = std::make_shared<CJump>();
	pJump->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pJump);//�A�b�v�L���X�g����Ă���ǉ�

	//PropellerArm���m��
	auto pPropeller = std::make_shared<CPropeller>();
	pPropeller->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pPropeller);//�A�b�v�L���X�g����Ă���ǉ�

	//StrongArm���m��
	auto pStrong = std::make_shared<CStrong>();
	pStrong->Init();
	//�I�u�W�F�N�g���X�g�ɒǉ�
	ObjMgr.AddObject(pStrong);//�A�b�v�L���X�g����Ă���ǉ�
}

void CGame::Update()
{
	//�͈̓x�[�Xfor
	for (auto&& pobj : ObjMgr.GetObjects())
	{
		pobj->Update();
	}

	std::list<std::shared_ptr<CObject>> pObjects;
	ObjMgr.FindObjectsWithTag(pObjects, "player");
	for (auto&& tmp : ObjMgr.GetObjects())
	{
		D3DXMATRIX mPlayer;
		mPlayer = tmp->GetMatrix();
		//�S�[������
		if (mPlayer._41>90.0f &&mPlayer._43>70.0f)
		{
			csm.ChangeScene("RESULT");
		}
	}
}

void CGame::Render2D()
{
}

void CGame::Render3D()
{
	//�S�ẴI�u�W�F�N�g�̕`��
	//�͈̓x�[�Xfor
	for (auto&& pobj : ObjMgr.GetObjects())
	{
		pobj->Draw();
	}
}

void CGame::Camera()
{
	D3DXMATRIX mView, mProj;
	// ���_���v�Z

	// ���_�s��̐ݒ�
	D3DXVECTOR3 cameraPos(0.0f, 5.0f, -20.0f), cameraLook;
	D3DXMATRIX cameraRot;
	D3DXMATRIX playerTrans;
	//�ʒu
	std::list<std::shared_ptr<CObject>> pObjects;
	ObjMgr.FindObjectsWithTag(pObjects, "player");
	for (auto&& tmp : pObjects) 
	{
		//�_�E���L���X�g����
		std::shared_ptr<CPlayer> pla;
		pla = std::dynamic_pointer_cast<CPlayer>(tmp);
		//�v���C���[�̈ړ������m��
		playerTrans = pla->GetPlayerTrans();
		//�J�����̉�]�����m��
		cameraRot = pla->GetCameraRot();
	}
	//�J�����̈ʒu
	D3DXVec3TransformNormal(&cameraPos, &cameraPos, &cameraRot);
	cameraPos.x += playerTrans._41;
	cameraPos.y += playerTrans._42;
	cameraPos.z += playerTrans._43;

	//�����_
	cameraLook = D3DXVECTOR3(playerTrans._41, playerTrans._42 + 1.8f, playerTrans._43);

	D3DXMatrixLookAtLH(&mView,
		&cameraPos,// �J�����̈ʒu
		&cameraLook,	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
	cdg.GetDevice()->SetTransform(D3DTS_VIEW, &mView);
	cdg.GetDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}