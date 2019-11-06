#pragma once
#include"Library.h"

class CObject
{
protected:

	// 当たり判定用　データ
	struct SphereData
	{
		D3DXVECTOR3 vCheckPos;
		float r;
	};

	struct HitRes
	{
		bool hit;
		float length;
	};

public:

	virtual void Init();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Draw2D() = 0;

	// 行列
	const D3DXMATRIX& GetMatrix() const { return m_mWorld; }
	void SetMatrix(const D3DXMATRIX& _Mat) { m_mWorld = _Mat; }

	// 座標
	const D3DXVECTOR3& GetPos() const { return &m_mWorld._41; }
	
	// メッシュの情報
	const std::shared_ptr<CMesh>& GetMesh() { return m_pMesh; }

	// タグ情報
	const std::string& GetTag() const { return tag; }

	// テーブル
	void Table(const LPD3DXMESH lpMesh, const D3DXMATRIX* mMesh, const DWORD* NumFaces, D3DXVECTOR3* WallVec);
	
	// 生存確認
	const bool& GetAlive() const { return m_Alive; }

	//球データ
	const SphereData& GetSphereData() const { return m_data; }

	const D3DXVECTOR3& GetAngle() const { return Ang; }

	//----------------------------------- 当たり判定 -----------------------------------//

	// レイの発射方向(角度)
	void GetRayVec(D3DXVECTOR3* _RayVec, const float _AngleX, const float _AngleY);

	// レイの発射方向(行列)
	void GetRayVec(D3DXVECTOR3* _RayVec, const D3DXMATRIX* _RotMat);
	
	// 板ポリのレイ判定
	bool HitJudge(const D3DXVECTOR3* _vPos1, const D3DXVECTOR3* _vPos2, const D3DXVECTOR3* _vPos3, const D3DXVECTOR3* _vPos4, const D3DXMATRIX* _Mat, const D3DXVECTOR3* _RayVec, const D3DXVECTOR3* _Pos, float* _Dis);
	
	// メッシュのレイ判定
	BOOL HitJudge(const LPD3DXMESH _lpMesh, const D3DXMATRIX* _Mat, const D3DXVECTOR3* _RayVec, const D3DXVECTOR3* _Pos, float* _Dis);
	
	// メッシュのレイ判定
	BOOL HitJudge(const LPD3DXMESH lpMesh, const D3DXMATRIX* Mat, const D3DXVECTOR3* RayVec, const D3DXVECTOR3* Pos, float* Dis, DWORD* PolyNo);
	
	// 球と球の当たり判定
	bool HitJudge(const D3DXMATRIX* _Mat1, const D3DXMATRIX* _Mat2, const float* _radius);

	// 球と球の当たり判定(データ構造体)
	void HitJudge(const SphereData& data, HitRes& hit);
	
	// メッシュでの壁ずり
	bool Wall(const D3DXVECTOR3* WallVec, D3DXVECTOR3 Vec, const float* Dis, D3DXVECTOR3* Pos);

	void GetWallVec(const DWORD* PolyNo, D3DXVECTOR3* Vec);

protected:

	// タグ
	std::string tag;
	// 生死
	bool m_Alive;
	//行列
	D3DXMATRIX m_mWorld;
	//D3DXMATRIX m_mRot;
	//D3DXMATRIX m_mTrans;
	std::shared_ptr<CMesh> m_pMesh = nullptr;

	SphereData m_data;

	D3DXVECTOR3* WallVec;

	D3DXVECTOR3 Ang;
	//速度
	//float speed;
	//現在、キーが押されているか
	//bool nowKeyflg;
};