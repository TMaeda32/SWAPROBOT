#pragma once

#include "CObject.h"

class CObjectManager
{
private:

	void CheckDelete();

public:

	//-------------------- ���X�g����p�֐� --------------------//

	// ���X�g���ہX�Ԃ�(�댯�Ȃ̂ōŏI��i)
	std::list< std::shared_ptr<CObject> > &GetObjects() { return m_Objects; }
	// �w�肳�ꂽ�I�u�W�F�N�g�����X�g�ɓ����
	void AddObject(std::shared_ptr<CObject> _obj) { m_Objects.push_back(_obj); }

	void FindObjectsWithTag(std::list< std::shared_ptr<CObject> >& out, const std::string& tag)
	{
		for (auto&& obj : m_Objects)
		{
			if (obj->GetTag() == tag) { out.push_back(obj); }
		}
	}

private:

	std::list< std::shared_ptr<CObject> > m_Objects;

private:

	CObjectManager() {};

public:

	// �V���O���g���̎���
	static CObjectManager &GetInstance()
	{
		static CObjectManager Instance;
		return Instance;
	}
};

// �}�N���̒�`
#define ObjMgr CObjectManager::GetInstance()