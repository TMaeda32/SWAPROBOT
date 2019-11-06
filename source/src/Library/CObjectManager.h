#pragma once

#include "CObject.h"

class CObjectManager
{
private:

	void CheckDelete();

public:

	//-------------------- リスト操作用関数 --------------------//

	// リストを丸々返す(危険なので最終手段)
	std::list< std::shared_ptr<CObject> > &GetObjects() { return m_Objects; }
	// 指定されたオブジェクトをリストに入れる
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

	// シングルトンの実装
	static CObjectManager &GetInstance()
	{
		static CObjectManager Instance;
		return Instance;
	}
};

// マクロの定義
#define ObjMgr CObjectManager::GetInstance()