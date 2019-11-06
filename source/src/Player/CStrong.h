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
	//アニメーションフレーム
	const float& GetFrame() const { return animeFrame; };
	//描画させる
	void DrawOn() { m_flg = true; }

private:
	//腕
	struct Arm
	{
		//肩から肘まで
		std::shared_ptr<CMesh> m_ShoulderMesh;
		//情報
		D3DXMATRIX m_mShoulder;
		//アニメーション（クォータニオン）
		D3DXMATRIX m_mShoulderStart, m_mEndShoulder, m_mShoulderNow;//最初、最後、現在

		//肘から手まで
		std::shared_ptr<CMesh> m_KnuckleMesh;
		//情報
		D3DXMATRIX m_mKnuckle;
		//アニメーション（クォータニオン）
		D3DXMATRIX m_mKnuckleStart, m_mKnuckleEnd, m_mKnuckleNow;//最初、最後、現在
	};

	//左腕
	Arm m_LeftArm;
	
	//右腕
	Arm m_RightArm ;

	//描画するか
	bool m_flg;
	
	float animeFrame;//アニメーション進行度(0～1)
};