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
	//足キーダウン
	void LegDownUpdate();
	//足キーアップ
	void LegUpUpdate();
	//腕キーダウン
	void ArmDownUpdate();
	//腕キーアップ
	void ArmUpUpdate();
	
	//地面判定
	void FloorCheck();
	//移動処理
	void Move();
	//アイテム判定
	void ItemHitJudge();

	virtual void Draw() override;
	virtual void Draw2D() override;
	void DebugDraw();

	//カメラの回転
	const D3DXMATRIX& GetCameraRot() const { return mCameraRotationMat; };
	//プレイヤーの移動行列
	const D3DXMATRIX& GetPlayerTrans()const { return mTransMat; }

private:
	//マテリアル情報
	D3DMATERIAL9 mMaterial;
	//プレイヤーの座標
	D3DXVECTOR3 mPos;
	float mAngle;
	//プレイヤーの情報
	D3DXMATRIX mMat;
	//プレイヤーの移動情報
	D3DXMATRIX mTransMat;
	//プレイヤーの回転情報
	D3DXMATRIX mRotationMat;
	//落下速度
	float mGravitySpeed;
	
	//カメラの回転
	D3DXMATRIX mCameraRotationMat;
	//カメラの向き
	float mCameraAngle;
	//カメラ
	int PI;
	//ライト
	D3DLIGHT9 light;

	//体本体メッシュ
	std::shared_ptr<CMesh> mBodyMesh = nullptr;

	//------------------足関係----------------------
	//現在の足の種類
	int mLegNumber;//1:ニトロ、2:ジャンプ、3:
	//ニトロの速さ
	float mNSpeed;
	//ジャンプ速さ(落下速度にもなる)
	float mJSpeed;
	//ジャンプできるか(trueでジャンプ可)
	bool mJumpJudge;
	//現在キーを押しているか(trueなら押している)
	bool nowLegKey;
	//前回キーを押していたか(trueなら押していた)
	bool lastLegKey;

	//----------------腕関連-------------------------
	//現在の腕の種類
	int mArmNumber;//1:パワー、2:プロペラ、3:手に持つ
	//現在キーを押しているか(trueなら押している)
	bool nowArmKey;
	//前回キーを押していたか(trueなら押していた)
	bool lastArmKey;

	//ジャンプできるか(trueでジャンプ可)
	bool mStrongJudge;

	//地面に当たったところまでの距離
	float stageFloorDis;
	//アイテム判定待ち時間（1回変更したらすぐには交換しない）
	int changeLegTime;
	int changeArmTime;

	//角度計算用
	D3DXVECTOR3 nowVec;
};