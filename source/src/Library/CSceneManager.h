#pragma once
#include "CDirectXGraphics.h"
#include <iostream>

class CBaseScene;

class CSceneManager
{
public:
	~CSceneManager();

	CBaseScene* scene;

	void Init();
	void Update();
	void Render2D();
	void Render3D();
	//カメラ
	void Camera();
	//シーン遷移
	void ChangeScene(std::string Nextscene);

public:
	CSceneManager();

	// シングルトンの実装
	static CSceneManager &getInstance() {
		static CSceneManager Instance;
		return Instance;
	}
};

// マクロ定義
#define csm CSceneManager::getInstance()