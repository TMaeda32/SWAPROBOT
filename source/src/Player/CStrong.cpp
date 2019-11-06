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

	//������
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
	//�E
	//����Ă����v���C���[�̏��������
	m_RightArm.m_mKnuckle = m_mWorld;
	m_RightArm.m_mShoulder = m_mWorld;
	//�ʒu��␳
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, 2.8f, 0.0f, 0.0f);
	m_RightArm.m_mShoulder = tmpMat * m_RightArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, 4.3f, 0.0f, 2.0f);
	m_RightArm.m_mKnuckle = tmpMat * m_RightArm.m_mKnuckle;

	//--------------------------------���A�j���[�V����----------------------------------------
	m_RightArm.m_mShoulderStart = m_RightArm.m_mShoulder;
	//�N�H�[�^�j�I��
	D3DXQUATERNION	StartQua, EndQua, NowQua;
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mShoulderStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMATRIX TransMat, RotMat;
	D3DXMatrixTranslation(&TransMat, 2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(-90), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mEndShoulder = TransMat * RotMat * m_RightArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mEndShoulder);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mShoulderNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	D3DXVECTOR3	StartPos, EndPos, NowPos;
	StartPos = D3DXVECTOR3(m_RightArm.m_mShoulderStart._41, m_RightArm.m_mShoulderStart._42, m_RightArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mEndShoulder._41, m_RightArm.m_mEndShoulder._42, m_RightArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_RightArm.m_mShoulderNow._41 = NowPos.x;
	m_RightArm.m_mShoulderNow._42 = NowPos.y;
	m_RightArm.m_mShoulderNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//-------------------------------��A�j���[�V����------------------------------------
	m_RightArm.m_mKnuckleStart = m_RightArm.m_mKnuckle;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mKnuckleStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, -3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mKnuckleEnd = TransMat * RotMat * m_RightArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mKnuckleEnd);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mKnuckleNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_RightArm.m_mKnuckleStart._41, m_RightArm.m_mKnuckleStart._42, m_RightArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mKnuckleEnd._41, m_RightArm.m_mKnuckleEnd._42, m_RightArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_RightArm.m_mKnuckleNow._41 = NowPos.x;
	m_RightArm.m_mKnuckleNow._42 = NowPos.y;
	m_RightArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//----------------------------------------------------------------------------------------
	//--------------------------------------���r----------------------------------------------

	m_LeftArm.m_mKnuckle = m_mWorld;
	m_LeftArm.m_mShoulder = m_mWorld;
	D3DXMatrixTranslation(&tmpMat, -2.8f, 0.0f, 0.0f);
	m_LeftArm.m_mShoulder = tmpMat * m_LeftArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, -4.3f, 0.0f, 2.0f);
	m_LeftArm.m_mKnuckle = tmpMat * m_LeftArm.m_mKnuckle;

	//--------------------------------���A�j���[�V����----------------------------------------
	m_LeftArm.m_mShoulderStart = m_LeftArm.m_mShoulder;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mShoulderStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, -2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(90), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mEndShoulder = TransMat * RotMat * m_LeftArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mEndShoulder);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mShoulderNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_LeftArm.m_mShoulderStart._41, m_LeftArm.m_mShoulderStart._42, m_LeftArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mEndShoulder._41, m_LeftArm.m_mEndShoulder._42, m_LeftArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_LeftArm.m_mShoulderNow._41 = NowPos.x;
	m_LeftArm.m_mShoulderNow._42 = NowPos.y;
	m_LeftArm.m_mShoulderNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//-------------------------------��A�j���[�V����------------------------------------
	m_LeftArm.m_mKnuckleStart = m_LeftArm.m_mKnuckle;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mKnuckleStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, 3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mKnuckleEnd = TransMat * RotMat * m_LeftArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mKnuckleEnd);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mKnuckleNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleStart._41, m_LeftArm.m_mKnuckleStart._42, m_LeftArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleEnd._41, m_LeftArm.m_mKnuckleEnd._42, m_LeftArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_LeftArm.m_mKnuckleNow._41 = NowPos.x;
	m_LeftArm.m_mKnuckleNow._42 = NowPos.y;
	m_LeftArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�
	//�A�j���[�V�����t���[�����グ��
	animeFrame += 0.1f;
	if (animeFrame >= 1.0f)
	{
		animeFrame = 1.0f;
	}
}

void CStrong::Return()
{
	//�E
	//����Ă����v���C���[�̏��������
	m_RightArm.m_mKnuckle = m_mWorld;
	m_RightArm.m_mShoulder = m_mWorld;
	//�ʒu��␳
	D3DXMATRIX tmpMat;
	D3DXMatrixTranslation(&tmpMat, 2.8f, 0.0f, 0.0f);
	m_RightArm.m_mShoulder = tmpMat * m_RightArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, 4.3f, 0.0f, 2.0f);
	m_RightArm.m_mKnuckle = tmpMat * m_RightArm.m_mKnuckle;

	//--------------------------------���A�j���[�V����----------------------------------------
	m_RightArm.m_mShoulderStart = m_RightArm.m_mShoulder;
	//�N�H�[�^�j�I��
	D3DXQUATERNION	StartQua, EndQua, NowQua;
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mShoulderStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMATRIX TransMat, RotMat;
	D3DXMatrixTranslation(&TransMat, 2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(-90), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mEndShoulder = TransMat * RotMat * m_RightArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mEndShoulder);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mShoulderNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	D3DXVECTOR3	StartPos, EndPos, NowPos;
	StartPos = D3DXVECTOR3(m_RightArm.m_mShoulderStart._41, m_RightArm.m_mShoulderStart._42, m_RightArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mEndShoulder._41, m_RightArm.m_mEndShoulder._42, m_RightArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_RightArm.m_mShoulderNow._41 = NowPos.x;
	m_RightArm.m_mShoulderNow._42 = NowPos.y;
	m_RightArm.m_mShoulderNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//-------------------------------��A�j���[�V����------------------------------------
	m_RightArm.m_mKnuckleStart = m_RightArm.m_mKnuckle;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_RightArm.m_mKnuckleStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, -3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_RightArm.m_mKnuckleEnd = TransMat * RotMat * m_RightArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_RightArm.m_mKnuckleEnd);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_RightArm.m_mKnuckleNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_RightArm.m_mKnuckleStart._41, m_RightArm.m_mKnuckleStart._42, m_RightArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_RightArm.m_mKnuckleEnd._41, m_RightArm.m_mKnuckleEnd._42, m_RightArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_RightArm.m_mKnuckleNow._41 = NowPos.x;
	m_RightArm.m_mKnuckleNow._42 = NowPos.y;
	m_RightArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//----------------------------------------------------------------------------------------
	//--------------------------------------���r----------------------------------------------

	m_LeftArm.m_mKnuckle = m_mWorld;
	m_LeftArm.m_mShoulder = m_mWorld;
	D3DXMatrixTranslation(&tmpMat, -2.8f, 0.0f, 0.0f);
	m_LeftArm.m_mShoulder = tmpMat * m_LeftArm.m_mShoulder;
	D3DXMatrixTranslation(&tmpMat, -4.3f, 0.0f, 2.0f);
	m_LeftArm.m_mKnuckle = tmpMat * m_LeftArm.m_mKnuckle;

	//--------------------------------���A�j���[�V����----------------------------------------
	m_LeftArm.m_mShoulderStart = m_LeftArm.m_mShoulder;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mShoulderStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, -2.0f, 0.0f, 1.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(90), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mEndShoulder = TransMat * RotMat * m_LeftArm.m_mShoulder;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mEndShoulder);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mShoulderNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_LeftArm.m_mShoulderStart._41, m_LeftArm.m_mShoulderStart._42, m_LeftArm.m_mShoulderStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mEndShoulder._41, m_LeftArm.m_mEndShoulder._42, m_LeftArm.m_mEndShoulder._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_LeftArm.m_mShoulderNow._41 = NowPos.x;
	m_LeftArm.m_mShoulderNow._42 = NowPos.y;
	m_LeftArm.m_mShoulderNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�

	//-------------------------------��A�j���[�V����------------------------------------
	m_LeftArm.m_mKnuckleStart = m_LeftArm.m_mKnuckle;
	//�N�H�[�^�j�I��
	//�J�n�ʒu
	D3DXQuaternionRotationMatrix(&StartQua, &m_LeftArm.m_mKnuckleStart);
	//�s����N�H�[�^�j�I����
	//�I���ʒu
	D3DXMatrixTranslation(&TransMat, 3.0f, 0.0f, 3.5f);
	D3DXMatrixRotationYawPitchRoll(&RotMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	m_LeftArm.m_mKnuckleEnd = TransMat * RotMat * m_LeftArm.m_mKnuckle;
	D3DXQuaternionRotationMatrix(&EndQua, &m_LeftArm.m_mKnuckleEnd);
	//���Ԉʒu
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);
	//NowQua ���Ԃ̏��  StartQua �ŏ��̏�� &EndQua �Ō�̏�ԁ@AnimeFrame�@�A�j���̐i�s�(0-1)
	D3DXMatrixRotationQuaternion(&m_LeftArm.m_mKnuckleNow, &NowQua);
	//�N�H�[�^�j�I�����s���

	//���W
	StartPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleStart._41, m_LeftArm.m_mKnuckleStart._42, m_LeftArm.m_mKnuckleStart._43);
	EndPos = D3DXVECTOR3(m_LeftArm.m_mKnuckleEnd._41, m_LeftArm.m_mKnuckleEnd._42, m_LeftArm.m_mKnuckleEnd._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);
	//���Ԃ̈ʒu�@�ŏ��̈ʒu�@�Ō�̈ʒu�@�A�j���̐i�s�(0-1)
	m_LeftArm.m_mKnuckleNow._41 = NowPos.x;
	m_LeftArm.m_mKnuckleNow._42 = NowPos.y;
	m_LeftArm.m_mKnuckleNow._43 = NowPos.z;
	//NowMat�Ɉʒu�Ə�Ԃ��܂Ƃ߂�
	//�A�j���[�V�����t���[����������
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
		//���r
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_LeftArm.m_mShoulderNow);
		m_LeftArm.m_ShoulderMesh->DrawMesh();
		cdg.GetDevice()->SetTransform(D3DTS_WORLD, &m_LeftArm.m_mKnuckleNow);
		m_LeftArm.m_KnuckleMesh->DrawMesh();
		//�E�r
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