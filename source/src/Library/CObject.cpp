#include "CObject.h"

void CObject::Init()
{
	//初期化
	D3DXMatrixIdentity(&m_mWorld);
	m_pMesh = std::make_shared<CMesh>();
	//生きている
	m_Alive = true;
}

void CObject::Table(const LPD3DXMESH lpMesh, const D3DXMATRIX * mMesh, const DWORD * NumFaces, D3DXVECTOR3 * WallVec)
{
	for (DWORD i = 0; i < *NumFaces; i++)
	{
		struct CLONEVERTEX
		{
			D3DXVECTOR3 Pos;
			D3DXVECTOR3 Normal;
			D3DXVECTOR2 Tex;
		};

		WORD *pI;
		lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);	// pI → インデックスバッファの0番目にアクセス
		// インデックス
		//  通し番号(連続した番号)

		// インデックスバッファ
		//　ポリゴン情報を、通し番号でバッファに保存
		//  ポリゴン情報の中身は、そのポリゴンの3つ頂点情報

		// 当たっているポリゴンの頂点を求める
		DWORD VertexNo[3];
		VertexNo[0] = *(pI + i * 3 + 0);
		VertexNo[1] = *(pI + i * 3 + 1);
		VertexNo[2] = *(pI + i * 3 + 2);

		lpMesh->UnlockIndexBuffer();

		CLONEVERTEX *pV;
		lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		// 当たっているポリゴンの頂点の座標を計算
		D3DXVECTOR3 VPos[3];
		VPos[0] = (pV + VertexNo[0])->Pos;
		VPos[1] = (pV + VertexNo[1])->Pos;
		VPos[2] = (pV + VertexNo[2])->Pos;

		lpMesh->UnlockVertexBuffer();

		// VPos[0]を原点とした(各頂点への)ベクトルを求める
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];

		// 法線を求める
		D3DXVec3Cross(&WallVec[i], &Vec1, &Vec2);
	}
}

void CObject::GetRayVec(
	D3DXVECTOR3* _RayVec	// レイの発射方向 (関数呼び出し後、計算結果を格納)
	, const float _AngleX	// レイ発射源のX角
	, const float _AngleY	// レイ発射源のY角
)
{
	// 回転行列の設定
	D3DXMATRIX RotMat;
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(_AngleY), D3DXToRadian(_AngleX), 0.0f);
	// レイ発射方向を計算
	D3DXVec3TransformCoord(_RayVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &RotMat);
}

void CObject::GetRayVec(
	D3DXVECTOR3 * _RayVec			// レイの発射方向 (関数呼び出し後、計算結果を格納)
	, const D3DXMATRIX * _RotMat	// レイ発射源の回転行列
)
{
	D3DXVec3TransformCoord(_RayVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), _RotMat);
}

bool CObject::HitJudge(
	const D3DXVECTOR3* _vPos1		// 板ポリ左下の頂点座標
	, const D3DXVECTOR3* _vPos2		// 板ポリ左上の頂点座標
	, const D3DXVECTOR3* _vPos3		// 板ポリ右上の頂点座標
	, const D3DXVECTOR3* _vPos4		// 板ポリ右下の頂点座標
	, const D3DXMATRIX* _Mat		// 板ポリの行列
	, const D3DXVECTOR3* _RayVec	// レイの発射方向
	, const D3DXVECTOR3* _Pos		// レイ発射源の座標
	, float* _Dis					// 板ポリとレイ発射源の距離 (関数呼び出し後、計算結果を格納)
)
{
	// 行列更新後の板ポリの座標を計算
	D3DXVECTOR3 VPos[4];
	D3DXVec3TransformCoord(&VPos[0], _vPos1, _Mat);
	D3DXVec3TransformCoord(&VPos[1], _vPos2, _Mat);
	D3DXVec3TransformCoord(&VPos[2], _vPos3, _Mat);
	D3DXVec3TransformCoord(&VPos[3], _vPos4, _Mat);

	// レイが板ポリに当たっていれば真を返す
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], _Pos, _RayVec, NULL, NULL, _Dis) || D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], _Pos, _RayVec, NULL, NULL, _Dis)) {
		return true;
	}

	return false;
}

BOOL CObject::HitJudge(
	const LPD3DXMESH _lpMesh		// メッシュ
	, const D3DXMATRIX* _Mat		// メッシュの行列
	, const D3DXVECTOR3* _RayVec	// レイの発射方向
	, const D3DXVECTOR3* _Pos		// レイ発射源の座標
	, float* _Dis					// メッシュとレイ発射源の距離 (関数呼び出し後、計算結果を格納)
)
{
	BOOL Hit;

	// 逆行列の作成
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, _Mat);
	// ローカル座標に変更
	D3DXVECTOR3 LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, _Pos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, _RayVec, &InvMat);

	// メッシュとレイの当たり判定
	D3DXIntersect(_lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, _Dis, NULL, NULL);

	// 計算結果を返す (TRUE,FALSE)
	return Hit;
}

BOOL CObject::HitJudge(
	const LPD3DXMESH lpMesh			// メッシュ
	, const D3DXMATRIX * mMesh		// メッシュの行列
	, const D3DXVECTOR3 * RayVec	// レイの発射方向
	, const D3DXVECTOR3 * Pos		// レイ発射源の座標
	, float * Dis					// メッシュとレイ発射源の距離 (関数呼び出し後、計算結果を格納)
	, DWORD * PolyNo				// レイの当たったポリゴンの番号 (関数呼び出し後、計算結果を格納)
)
{
	BOOL Hit;

	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, mMesh);
	D3DXVECTOR3 LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, Pos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, RayVec, &InvMat);

	D3DXIntersect(lpMesh, &LocalPos, &LocalVec, &Hit, PolyNo, NULL, NULL, Dis, NULL, NULL);

	return Hit;
}

bool CObject::HitJudge(
	const D3DXMATRIX* _Mat1		// 物体１の行列
	, const D3DXMATRIX* _Mat2	// 物体２の座標
	, const float* _radius		// 物体１と物体２の半径の合計
)
{
	// 2点間のベクトルを求める
	D3DXVECTOR3 lengthVec = D3DXVECTOR3(_Mat1->_41 - _Mat2->_41, _Mat1->_42 - _Mat2->_42, _Mat1->_43 - _Mat2->_43);
	// ベクトルの合成
	float length = D3DXVec3Length(&lengthVec);

	if (length < *_radius) {
		return true;
	}
	else {
		return false;
	}
}

void CObject::HitJudge(
	const SphereData& data	// 対象オブジェクトの(座標・半径)データ
	, HitRes& hit			// ヒット時の情報を格納する
)
{
	// 2点間のベクトルを求める
	D3DXVECTOR3 lengthVec = m_data.vCheckPos - data.vCheckPos;
	// 距離を求める

	hit.length = D3DXVec3Length(&lengthVec);

	if (hit.length < (m_data.r + data.r))
	{
		hit.hit = true;
	}
	else
	{
		hit.hit = false;
	}
}

bool CObject::Wall(const D3DXVECTOR3 * WallVec, D3DXVECTOR3 Vec, const float * Dis, D3DXVECTOR3 * Pos)
{
	float Dot = D3DXVec3Dot(WallVec, &-Vec);
	float Limit = 1.5f / Dot;
	if (Limit < 0.0f) Limit *= -1.0f;
	if (*Dis < Limit)
	{
		*Pos = *WallVec * ((Limit - *Dis) * Dot);
		return true;
	}
	return false;
}

void CObject::GetWallVec(const DWORD* PolyNo, D3DXVECTOR3* Vec)
{
	*Vec = WallVec[*PolyNo];

	D3DXVec3TransformNormal(Vec, Vec, &m_mWorld);
	D3DXVec3Normalize(Vec, Vec);
}