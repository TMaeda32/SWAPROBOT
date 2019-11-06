#pragma once
#include"Library.h"

class CObject
{
protected:

	// �����蔻��p�@�f�[�^
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

	// �s��
	const D3DXMATRIX& GetMatrix() const { return m_mWorld; }
	void SetMatrix(const D3DXMATRIX& _Mat) { m_mWorld = _Mat; }

	// ���W
	const D3DXVECTOR3& GetPos() const { return &m_mWorld._41; }
	
	// ���b�V���̏��
	const std::shared_ptr<CMesh>& GetMesh() { return m_pMesh; }

	// �^�O���
	const std::string& GetTag() const { return tag; }

	// �e�[�u��
	void Table(const LPD3DXMESH lpMesh, const D3DXMATRIX* mMesh, const DWORD* NumFaces, D3DXVECTOR3* WallVec);
	
	// �����m�F
	const bool& GetAlive() const { return m_Alive; }

	//���f�[�^
	const SphereData& GetSphereData() const { return m_data; }

	const D3DXVECTOR3& GetAngle() const { return Ang; }

	//----------------------------------- �����蔻�� -----------------------------------//

	// ���C�̔��˕���(�p�x)
	void GetRayVec(D3DXVECTOR3* _RayVec, const float _AngleX, const float _AngleY);

	// ���C�̔��˕���(�s��)
	void GetRayVec(D3DXVECTOR3* _RayVec, const D3DXMATRIX* _RotMat);
	
	// �|���̃��C����
	bool HitJudge(const D3DXVECTOR3* _vPos1, const D3DXVECTOR3* _vPos2, const D3DXVECTOR3* _vPos3, const D3DXVECTOR3* _vPos4, const D3DXMATRIX* _Mat, const D3DXVECTOR3* _RayVec, const D3DXVECTOR3* _Pos, float* _Dis);
	
	// ���b�V���̃��C����
	BOOL HitJudge(const LPD3DXMESH _lpMesh, const D3DXMATRIX* _Mat, const D3DXVECTOR3* _RayVec, const D3DXVECTOR3* _Pos, float* _Dis);
	
	// ���b�V���̃��C����
	BOOL HitJudge(const LPD3DXMESH lpMesh, const D3DXMATRIX* Mat, const D3DXVECTOR3* RayVec, const D3DXVECTOR3* Pos, float* Dis, DWORD* PolyNo);
	
	// ���Ƌ��̓����蔻��
	bool HitJudge(const D3DXMATRIX* _Mat1, const D3DXMATRIX* _Mat2, const float* _radius);

	// ���Ƌ��̓����蔻��(�f�[�^�\����)
	void HitJudge(const SphereData& data, HitRes& hit);
	
	// ���b�V���ł̕ǂ���
	bool Wall(const D3DXVECTOR3* WallVec, D3DXVECTOR3 Vec, const float* Dis, D3DXVECTOR3* Pos);

	void GetWallVec(const DWORD* PolyNo, D3DXVECTOR3* Vec);

protected:

	// �^�O
	std::string tag;
	// ����
	bool m_Alive;
	//�s��
	D3DXMATRIX m_mWorld;
	//D3DXMATRIX m_mRot;
	//D3DXMATRIX m_mTrans;
	std::shared_ptr<CMesh> m_pMesh = nullptr;

	SphereData m_data;

	D3DXVECTOR3* WallVec;

	D3DXVECTOR3 Ang;
	//���x
	//float speed;
	//���݁A�L�[��������Ă��邩
	//bool nowKeyflg;
};