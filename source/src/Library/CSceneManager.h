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
	//�J����
	void Camera();
	//�V�[���J��
	void ChangeScene(std::string Nextscene);

public:
	CSceneManager();

	// �V���O���g���̎���
	static CSceneManager &getInstance() {
		static CSceneManager Instance;
		return Instance;
	}
};

// �}�N����`
#define csm CSceneManager::getInstance()