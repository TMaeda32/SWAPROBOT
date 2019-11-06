#include "CStrong.h"


CStrong::CStrong()
{
}


CStrong::~CStrong()
{
}

void CStrong::Init()
{
	tag = "strong";

	m_LeftArm.m_ShoulderMesh = std::make_shared<CMesh>();
	m_LeftArm.m_ShoulderMesh->LoadMesh("Resource/StrongArmShoulderL.x");

	m_LeftArm.m_KnuckleMesh = std::make_shared<CMesh>();
	m_LeftArm.m_KnuckleMesh->LoadMesh("Resource/StrongArmKnuckle.x");

	m_RightArm.m_ShoulderMesh = std::make_shared<CMesh>();
	m_RightArm.m_ShoulderMesh->LoadMesh("Resource/StrongArmShoulderR.x");

	m_RightArm.m_KnuckleMesh = std::make_shared<CMesh>();
	m_RightArm.m_KnuckleMesh->LoadMesh("Resource/StrongArmKnuckle.x");

	animeFrame = 0.0f;

	//初期化
	D3DXMatrixIdentity(&m_LeftArm.m_mShoulder);
	D3DXMatrixIdentity(&m_LeftArm.m_mKnuckle);
	D3DXMatrixIdentity(&m_RightArm.m_mShoulder);
	D3DXMatrixIdentity(&m_RightArm.m_mKnuckle);

	D3DXMatrixIdentity(&m_mWorld);
}

void CStrong::Update()
{
}

void CStrong::Attack()
{
	//右
	//取ってきたプレイヤーの情報をいれる
	m_RightArm.m_mKnuckle = m_mWorld;
	m_RightArm.m_mShoulder = m_mWorld;
	//位置を補正
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, 2.8f, 0.0f, 0.0f);
	m_RightArm.m_mShoulder = tmpMat * m_RightArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, 4.3f, 0.0f, 2.0f);
	m_RightArm.m_mKnuckle = tmpMat * m_RightArm.m_mKnuckle;

	//--------------------------------肩アニメーション----------------------------------------
	m_RightArm.m_mShoulderStart = m_RightArm.m_mShoulder;
	//クォータニオン
	D3DXQUATERNION	StartQua, EndQua, NowQua;
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mShoulderStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMATRIX TransMat, RotMat;
	D3DXMatrixTranslation(&TransMat, 2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(-90), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mEndShoulder = TransMat * RotMat * m_RightArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mEndShoulder);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mShoulderNow, &NowQua);
	//クォータニオンを行列に

	//座標
	D3DXVECTOR3	StartPos, EndPos, NowPos;
	StartPos = D3DXVECTOR3(m_RightArm.m_mShoulderStart._41, m_RightArm.m_mShoulderStart._42, m_RightArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mEndShoulder._41, m_RightArm.m_mEndShoulder._42, m_RightArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_RightArm.m_mShoulderNow._41 = NowPos.x;
	m_RightArm.m_mShoulderNow._42 = NowPos.y;
	m_RightArm.m_mShoulderNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//-------------------------------手アニメーション------------------------------------
	m_RightArm.m_mKnuckleStart = m_RightArm.m_mKnuckle;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mKnuckleStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, -3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mKnuckleEnd = TransMat * RotMat * m_RightArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mKnuckleEnd);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mKnuckleNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_RightArm.m_mKnuckleStart._41, m_RightArm.m_mKnuckleStart._42, m_RightArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mKnuckleEnd._41, m_RightArm.m_mKnuckleEnd._42, m_RightArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_RightArm.m_mKnuckleNow._41 = NowPos.x;
	m_RightArm.m_mKnuckleNow._42 = NowPos.y;
	m_RightArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//----------------------------------------------------------------------------------------
	//--------------------------------------左腕----------------------------------------------

	m_LeftArm.m_mKnuckle = m_mWorld;
	m_LeftArm.m_mShoulder = m_mWorld;
	D3DXMatrixTranslation(&tmpMat, -2.8f, 0.0f, 0.0f);
	m_LeftArm.m_mShoulder = tmpMat * m_LeftArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, -4.3f, 0.0f, 2.0f);
	m_LeftArm.m_mKnuckle = tmpMat * m_LeftArm.m_mKnuckle;

	//--------------------------------肩アニメーション----------------------------------------
	m_LeftArm.m_mShoulderStart = m_LeftArm.m_mShoulder;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mShoulderStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, -2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(90), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mEndShoulder = TransMat * RotMat * m_LeftArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mEndShoulder);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mShoulderNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_LeftArm.m_mShoulderStart._41, m_LeftArm.m_mShoulderStart._42, m_LeftArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mEndShoulder._41, m_LeftArm.m_mEndShoulder._42, m_LeftArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_LeftArm.m_mShoulderNow._41 = NowPos.x;
	m_LeftArm.m_mShoulderNow._42 = NowPos.y;
	m_LeftArm.m_mShoulderNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//-------------------------------手アニメーション------------------------------------
	m_LeftArm.m_mKnuckleStart = m_LeftArm.m_mKnuckle;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mKnuckleStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, 3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mKnuckleEnd = TransMat * RotMat * m_LeftArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mKnuckleEnd);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mKnuckleNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleStart._41, m_LeftArm.m_mKnuckleStart._42, m_LeftArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleEnd._41, m_LeftArm.m_mKnuckleEnd._42, m_LeftArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_LeftArm.m_mKnuckleNow._41 = NowPos.x;
	m_LeftArm.m_mKnuckleNow._42 = NowPos.y;
	m_LeftArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる
	//アニメーションフレームを上げる
	animeFrame += 0.1f;
	if (animeFrame >= 1.0f)
	{
		animeFrame = 1.0f;
	}
}

void CStrong::Return()
{
	//右
	//取ってきたプレイヤーの情報をいれる
	m_RightArm.m_mKnuckle = m_mWorld;
	m_RightArm.m_mShoulder = m_mWorld;
	//位置を補正
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, 2.8f, 0.0f, 0.0f);
	m_RightArm.m_mShoulder = tmpMat * m_RightArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, 4.3f, 0.0f, 2.0f);
	m_RightArm.m_mKnuckle = tmpMat * m_RightArm.m_mKnuckle;

	//--------------------------------肩アニメーション----------------------------------------
	m_RightArm.m_mShoulderStart = m_RightArm.m_mShoulder;
	//クォータニオン
	D3DXQUATERNION	StartQua, EndQua, NowQua;
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mShoulderStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMATRIX TransMat, RotMat;
	D3DXMatrixTranslation(&TransMat, 2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(-90), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mEndShoulder = TransMat * RotMat * m_RightArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mEndShoulder);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mShoulderNow, &NowQua);
	//クォータニオンを行列に

	//座標
	D3DXVECTOR3	StartPos, EndPos, NowPos;
	StartPos = D3DXVECTOR3(m_RightArm.m_mShoulderStart._41, m_RightArm.m_mShoulderStart._42, m_RightArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mEndShoulder._41, m_RightArm.m_mEndShoulder._42, m_RightArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_RightArm.m_mShoulderNow._41 = NowPos.x;
	m_RightArm.m_mShoulderNow._42 = NowPos.y;
	m_RightArm.m_mShoulderNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//-------------------------------手アニメーション------------------------------------
	m_RightArm.m_mKnuckleStart = m_RightArm.m_mKnuckle;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mKnuckleStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, -3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mKnuckleEnd = TransMat * RotMat * m_RightArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mKnuckleEnd);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mKnuckleNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_RightArm.m_mKnuckleStart._41, m_RightArm.m_mKnuckleStart._42, m_RightArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mKnuckleEnd._41, m_RightArm.m_mKnuckleEnd._42, m_RightArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_RightArm.m_mKnuckleNow._41 = NowPos.x;
	m_RightArm.m_mKnuckleNow._42 = NowPos.y;
	m_RightArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//----------------------------------------------------------------------------------------
	//--------------------------------------左腕----------------------------------------------

	m_LeftArm.m_mKnuckle = m_mWorld;
	m_LeftArm.m_mShoulder = m_mWorld;
	D3DXMatrixTranslation(&tmpMat, -2.8f, 0.0f, 0.0f);
	m_LeftArm.m_mShoulder = tmpMat * m_LeftArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, -4.3f, 0.0f, 2.0f);
	m_LeftArm.m_mKnuckle = tmpMat * m_LeftArm.m_mKnuckle;

	//--------------------------------肩アニメーション----------------------------------------
	m_LeftArm.m_mShoulderStart = m_LeftArm.m_mShoulder;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mShoulderStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, -2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(90), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mEndShoulder = TransMat * RotMat * m_LeftArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mEndShoulder);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mShoulderNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_LeftArm.m_mShoulderStart._41, m_LeftArm.m_mShoulderStart._42, m_LeftArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mEndShoulder._41, m_LeftArm.m_mEndShoulder._42, m_LeftArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_LeftArm.m_mShoulderNow._41 = NowPos.x;
	m_LeftArm.m_mShoulderNow._42 = NowPos.y;
	m_LeftArm.m_mShoulderNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる

	//-------------------------------手アニメーション------------------------------------
	m_LeftArm.m_mKnuckleStart = m_LeftArm.m_mKnuckle;
	//クォータニオン
	//開始位置
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mKnuckleStart);
	//行列をクォータニオンに
	//終了位置
	D3DXMatrixTranslation(&TransMat, 3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mKnuckleEnd = TransMat * RotMat * m_LeftArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mKnuckleEnd);
	//中間位置
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua 中間の状態  StartQua 最初の状態 &EndQua 最後の状態　AnimeFrame　アニメの進行具合(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mKnuckleNow, &NowQua);
	//クォータニオンを行列に

	//座標
	StartPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleStart._41, m_LeftArm.m_mKnuckleStart._42, m_LeftArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleEnd._41, m_LeftArm.m_mKnuckleEnd._42, m_LeftArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//中間の位置　最初の位置　最後の位置　アニメの進行具合(0-1)
	m_LeftArm.m_mKnuckleNow._41 = NowPos.x;
	m_LeftArm.m_mKnuckleNow._42 = NowPos.y;
	m_LeftArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMatに位置と状態をまとめる
	//アニメーションフレームを下げる
	animeFrame -= 0.01f;
	if (animeFrame <= 0.0f)
	{
		animeFrame = 0.0f;
	}
}

void CStrong::Draw()
{
	if (m_flg)
	{
		//左腕
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_LeftArm.m_mShoulderNow);
		m_LeftArm.m_ShoulderMesh->DrawMesh();
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_LeftArm.m_mKnuckleNow);
		m_LeftArm.m_KnuckleMesh->DrawMesh();
		//右腕
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_RightArm.m_mShoulderNow);
		m_RightArm.m_ShoulderMesh->DrawMesh();
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_RightArm.m_mKnuckleNow);
		m_RightArm.m_KnuckleMesh->DrawMesh();
	}
	m_flg = false;
}

void CStrong::Draw2D()
{
}