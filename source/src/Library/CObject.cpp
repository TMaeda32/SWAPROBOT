#include "CObject.h"

void CObject::Init()
{
	//������
	D3DXMatrixIdentity(&m_mWorld);
	m_pMesh = std::make_shared<CMesh>();
	//�����Ă���
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
		lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);	// pI �� �C���f�b�N�X�o�b�t�@��0�ԖڂɃA�N�Z�X
		// �C���f�b�N�X
		//  �ʂ��ԍ�(�A�������ԍ�)

		// �C���f�b�N�X�o�b�t�@
		//�@�|���S�������A�ʂ��ԍ��Ńo�b�t�@�ɕۑ�
		//  �|���S�����̒��g�́A���̃|���S����3���_���

		// �������Ă���|���S���̒��_�����߂�
		DWORD VertexNo[3];
		VertexNo[0] = *(pI + i * 3 + 0);
		VertexNo[1] = *(pI + i * 3 + 1);
		VertexNo[2] = *(pI + i * 3 + 2);

		lpMesh->UnlockIndexBuffer();

		CLONEVERTEX *pV;
		lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

		// �������Ă���|���S���̒��_�̍��W���v�Z
		D3DXVECTOR3 VPos[3];
		VPos[0] = (pV + VertexNo[0])->Pos;
		VPos[1] = (pV + VertexNo[1])->Pos;
		VPos[2] = (pV + VertexNo[2])->Pos;

		lpMesh->UnlockVertexBuffer();

		// VPos[0]�����_�Ƃ���(�e���_�ւ�)�x�N�g�������߂�
		D3DXVECTOR3 Vec1, Vec2;
		Vec1 = VPos[1] - VPos[0];
		Vec2 = VPos[2] - VPos[0];

		// �@�������߂�
		D3DXVec3Cross(&WallVec[i], &Vec1, &Vec2);
	}
}

void CObject::GetRayVec(
	D3DXVECTOR3* _RayVec	// ���C�̔��˕��� (�֐��Ăяo����A�v�Z���ʂ��i�[)
	, const float _AngleX	// ���C���ˌ���X�p
	, const float _AngleY	// ���C���ˌ���Y�p
)
{
	// ��]�s��̐ݒ�
	D3DXMATRIX RotMat;
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(_AngleY), D3DXToRadian(_AngleX), 0.0f);
	// ���C���˕������v�Z
	D3DXVec3TransformCoord(_RayVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &RotMat);
}

void CObject::GetRayVec(
	D3DXVECTOR3 * _RayVec			// ���C�̔��˕��� (�֐��Ăяo����A�v�Z���ʂ��i�[)
	, const D3DXMATRIX * _RotMat	// ���C���ˌ��̉�]�s��
)
{
	D3DXVec3TransformCoord(_RayVec, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), _RotMat);
}

bool CObject::HitJudge(
	const D3DXVECTOR3* _vPos1		// �|�������̒��_���W
	, const D3DXVECTOR3* _vPos2		// �|������̒��_���W
	, const D3DXVECTOR3* _vPos3		// �|���E��̒��_���W
	, const D3DXVECTOR3* _vPos4		// �|���E���̒��_���W
	, const D3DXMATRIX* _Mat		// �|���̍s��
	, const D3DXVECTOR3* _RayVec	// ���C�̔��˕���
	, const D3DXVECTOR3* _Pos		// ���C���ˌ��̍��W
	, float* _Dis					// �|���ƃ��C���ˌ��̋��� (�֐��Ăяo����A�v�Z���ʂ��i�[)
)
{
	// �s��X�V��̔|���̍��W���v�Z
	D3DXVECTOR3 VPos[4];
	D3DXVec3TransformCoord(&VPos[0], _vPos1, _Mat);
	D3DXVec3TransformCoord(&VPos[1], _vPos2, _Mat);
	D3DXVec3TransformCoord(&VPos[2], _vPos3, _Mat);
	D3DXVec3TransformCoord(&VPos[3], _vPos4, _Mat);

	// ���C���|���ɓ������Ă���ΐ^��Ԃ�
	if (D3DXIntersectTri(&VPos[0], &VPos[1], &VPos[2], _Pos, _RayVec, NULL, NULL, _Dis) || D3DXIntersectTri(&VPos[0], &VPos[2], &VPos[3], _Pos, _RayVec, NULL, NULL, _Dis)) {
		return true;
	}

	return false;
}

BOOL CObject::HitJudge(
	const LPD3DXMESH _lpMesh		// ���b�V��
	, const D3DXMATRIX* _Mat		// ���b�V���̍s��
	, const D3DXVECTOR3* _RayVec	// ���C�̔��˕���
	, const D3DXVECTOR3* _Pos		// ���C���ˌ��̍��W
	, float* _Dis					// ���b�V���ƃ��C���ˌ��̋��� (�֐��Ăяo����A�v�Z���ʂ��i�[)
)
{
	BOOL Hit;

	// �t�s��̍쐬
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, _Mat);
	// ���[�J�����W�ɕύX
	D3DXVECTOR3 LocalPos, LocalVec;
	D3DXVec3TransformCoord(&LocalPos, _Pos, &InvMat);
	D3DXVec3TransformNormal(&LocalVec, _RayVec, &InvMat);

	// ���b�V���ƃ��C�̓����蔻��
	D3DXIntersect(_lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, _Dis, NULL, NULL);

	// �v�Z���ʂ�Ԃ� (TRUE,FALSE)
	return Hit;
}

BOOL CObject::HitJudge(
	const LPD3DXMESH lpMesh			// ���b�V��
	, const D3DXMATRIX * mMesh		// ���b�V���̍s��
	, const D3DXVECTOR3 * RayVec	// ���C�̔��˕���
	, const D3DXVECTOR3 * Pos		// ���C���ˌ��̍��W
	, float * Dis					// ���b�V���ƃ��C���ˌ��̋��� (�֐��Ăяo����A�v�Z���ʂ��i�[)
	, DWORD * PolyNo				// ���C�̓��������|���S���̔ԍ� (�֐��Ăяo����A�v�Z���ʂ��i�[)
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
	const D3DXMATRIX* _Mat1		// ���̂P�̍s��
	, const D3DXMATRIX* _Mat2	// ���̂Q�̍��W
	, const float* _radius		// ���̂P�ƕ��̂Q�̔��a�̍��v
)
{
	// 2�_�Ԃ̃x�N�g�������߂�
	D3DXVECTOR3 lengthVec = D3DXVECTOR3(_Mat1->_41 - _Mat2->_41, _Mat1->_42 - _Mat2->_42, _Mat1->_43 - _Mat2->_43);
	// �x�N�g���̍���
	float length = D3DXVec3Length(&lengthVec);

	if (length < *_radius) {
		return true;
	}
	else {
		return false;
	}
}

void CObject::HitJudge(
	const SphereData& data	// �ΏۃI�u�W�F�N�g��(���W�E���a)�f�[�^
	, HitRes& hit			// �q�b�g���̏����i�[����
)
{
	// 2�_�Ԃ̃x�N�g�������߂�
	D3DXVECTOR3 lengthVec = m_data.vCheckPos - data.vCheckPos;
	// ���������߂�

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