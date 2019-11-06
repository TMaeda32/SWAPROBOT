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
	//重力
	mJSpeed -= 0.1f;

	FloorCheck();

	//アクション操作
	{
		//足
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
		//腕
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

	//移動キー操作
	Move();
	//アイテムに当たったか
	ItemHitJudge();
	//カメラ操作
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


	//ジャンプ分上昇
	mTransMat._42 += mJSpeed;
	//重力補正
	if (stageFloorDis > 5.2f)
	{
		mTransMat._42 -= mGravitySpeed;
	}
	//移動、回転結果を入れる
	mMat = mRotationMat * mTransMat;
	mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
	m_mWorld = mMat;

	//プレイヤーの位置情報を全てのパーツに渡す
	std::list<std::shared_ptr<CObject>> pParts;
	ObjMgr.FindObjectsWithTag(pParts, "nitro");
	ObjMgr.FindObjectsWithTag(pParts, "jump");
	ObjMgr.FindObjectsWithTag(pParts, "strong");
	ObjMgr.FindObjectsWithTag(pParts, "propeller");
	for (auto&& par : pParts)
	{
		par->SetMatrix(mMat);
	}

	//パワーは移動後に最後に通す
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
		//ニトロ
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
		//ジャンプ
	case 2:
		//ジャンプ力を溜める
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
		//ニトロ
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
		//ジャンプ
	case 2:
		//ジャンプ開始
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
		//パワー
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveArm, "strong");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CStrong> str;
			str = std::dynamic_pointer_cast<CStrong>(tmp);
			str->DrawOn();
			//パンチ
			str->Attack();
		}
		break;
		//プロペラ
	case 2:
		ObjMgr.FindObjectsWithTag(pHaveArm, "propeller");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CPropeller> pro;
			pro = std::dynamic_pointer_cast<CPropeller>(tmp);
			pro->DrawOn();
			//ゆっくりと降下
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
		//パワー
	case 1:
		ObjMgr.FindObjectsWithTag(pHaveArm, "strong");
		for (auto&& tmp : pHaveArm)
		{
			std::shared_ptr<CStrong> str;
			str = std::dynamic_pointer_cast<CStrong>(tmp);
			str->DrawOn();
			//戻す
			str->Return();
		}
		break;
		//プロペラ
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
	//ステージの情報取得
	std::list<std::shared_ptr<CObject>> pStage;
	ObjMgr.FindObjectsWithTag(pStage, "stage");
	//地面判定
	for (auto&& tmp : pStage)
	{
		std::shared_ptr<CStage> sta;
		sta = std::dynamic_pointer_cast<CStage>(tmp);
		//レイ発射方向
		D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//レイ発射位置
		mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
		if (HitJudge(sta->GetMesh()->GetMesh(), &sta->GetMatrix(), &Vec, &mPos, &stageFloorDis))
		{
			//当たった
			//地面補正
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
	//ステージの情報取得
	std::list<std::shared_ptr<CObject>> pStage;
	ObjMgr.FindObjectsWithTag(pStage, "stage");
	//プレイヤーの動くベクトル
	D3DXVECTOR3 moveVec(0.0f, 0.0f, 0.0f);
	//プレイヤーが動いているか
	bool moveFlg = false;
	//作業用ベクトル
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
		//移動処理
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= mNSpeed;
		D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
		mTransMat = tmpMat * mTransMat;

		//内積で残り何度回ればいいか計算(今向いている方向()と向きたい方向(moveVec))
		D3DXVec3TransformNormal(&nowVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &mRotationMat);
		D3DXVec3Normalize(&moveVec, &moveVec);
		float tmpAng;
		tmpAng = D3DXVec3Dot(&nowVec, &moveVec);
		tmpAng = D3DXToDegree(acos(tmpAng));
		if (tmpAng >= 0.1f)
		{
			//右回りか左回りか(外積)
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
		//前方に壁があるか
		for (auto&& tmp : pStage)
		{
			std::shared_ptr<CStage> sta;
			sta = std::dynamic_pointer_cast<CStage>(tmp);
			//レイ発射位置
			mPos = D3DXVECTOR3(mMat._41, mMat._42, mMat._43);
			//当たったところまでの距離
			float stageWallDis;
			//BOOL stageHit;
			//LPD3DXMESH tmpMesh = pStageMesh->GetMesh();
			if (HitJudge(sta->GetMesh()->GetMesh(), &sta->GetMatrix(), &nowVec, &mPos, &stageWallDis))
			{
				//壁に当たった
				if (stageWallDis < 7.0f && stageWallDis != -1.0f)
				{
					//目の前に壁がある
					//補正処理
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
	//足のアイテム交換できる
	if (changeLegTime <= 0)
	{
		//アイテムの情報取得
		std::list<std::shared_ptr<CObject>> pChangeLegItem;
		ObjMgr.FindObjectsWithTag(pChangeLegItem, "changeLegItem");
		for (auto&& tmp : pChangeLegItem)
		{
			//どれくらいの距離でヒットと判断するか
			float hitDis = 6.0f;
			std::shared_ptr<CChangeLegItem> cha;
			cha = std::dynamic_pointer_cast<CChangeLegItem>(tmp);
			if (HitJudge(&cha->GetMatrix(), &mMat, &hitDis))
			{
				mLegNumber = cha->Change(mLegNumber);
				//3秒間交換を止める
				changeLegTime = 180;
			}
		}
	}
	//腕のアイテム交換できる
	if (changeArmTime <= 0)
	{
		//アイテムの情報取得
		std::list<std::shared_ptr<CObject>> pChangeArmItem;
		ObjMgr.FindObjectsWithTag(pChangeArmItem, "changeArmItem");
		for (auto&& tmp : pChangeArmItem)
		{
			//どれくらいの距離でヒットと判断するか
			float hitDis = 6.0f;
			std::shared_ptr<CChangeArmItem> cha;
			cha = std::dynamic_pointer_cast<CChangeArmItem>(tmp);
			if (HitJudge(&cha->GetMatrix(), &mMat, &hitDis))
			{
				mArmNumber = cha->Change(mArmNumber);
				//3秒間交換を止める
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