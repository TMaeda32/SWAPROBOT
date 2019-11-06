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
	//Stageを確保
	auto pStage = std::make_shared<CStage>();
	pStage->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pStage);//アップキャストされてから追加

	//ChangeLegItemを確保
	auto pChangeLegItem = std::make_shared<CChangeLegItem>();
	pChangeLegItem->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pChangeLegItem);//アップキャストされてから追加

	//ChangeArmItemを確保
	auto pChangeArmItem = std::make_shared<CChangeArmItem>();
	pChangeArmItem->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pChangeArmItem);//アップキャストされてから追加

	//Playerを確保
	auto pPlayer = std::make_shared<CPlayer>();
	pPlayer->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pPlayer);//アップキャストされてから追加

	//Nitroを確保
	auto pNitro = std::make_shared<CNitro>();
	pNitro->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pNitro);//アップキャストされてから追加

	//Jumpを確保
	auto pJump = std::make_shared<CJump>();
	pJump->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pJump);//アップキャストされてから追加

	//PropellerArmを確保
	auto pPropeller = std::make_shared<CPropeller>();
	pPropeller->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pPropeller);//アップキャストされてから追加

	//StrongArmを確保
	auto pStrong = std::make_shared<CStrong>();
	pStrong->Init();
	//オブジェクトリストに追加
	ObjMgr.AddObject(pStrong);//アップキャストされてから追加
}

void CGame::Update()
{
	//範囲ベースfor
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
		//ゴール判定
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
	//全てのオブジェクトの描画
	//範囲ベースfor
	for (auto&& pobj : ObjMgr.GetObjects())
	{
		pobj->Draw();
	}
}

void CGame::Camera()
{
	D3DXMATRIX mView, mProj;
	// 視点を計算

	// 視点行列の設定
	D3DXVECTOR3 cameraPos(0.0f, 5.0f, -20.0f), cameraLook;
	D3DXMATRIX cameraRot;
	D3DXMATRIX playerTrans;
	//位置
	std::list<std::shared_ptr<CObject>> pObjects;
	ObjMgr.FindObjectsWithTag(pObjects, "player");
	for (auto&& tmp : pObjects) 
	{
		//ダウンキャスト注意
		std::shared_ptr<CPlayer> pla;
		pla = std::dynamic_pointer_cast<CPlayer>(tmp);
		//プレイヤーの移動情報を確保
		playerTrans = pla->GetPlayerTrans();
		//カメラの回転情報を確保
		cameraRot = pla->GetCameraRot();
	}
	//カメラの位置
	D3DXVec3TransformNormal(&cameraPos, &cameraPos, &cameraRot);
	cameraPos.x += playerTrans._41;
	cameraPos.y += playerTrans._42;
	cameraPos.z += playerTrans._43;

	//注視点
	cameraLook = D3DXVECTOR3(playerTrans._41, playerTrans._42 + 1.8f, playerTrans._43);

	D3DXMatrixLookAtLH(&mView,
		&cameraPos,// カメラの位置
		&cameraLook,	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//行列設定
	cdg.GetDevice()->SetTransform(D3DTS_VIEW, &mView);
	cdg.GetDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}