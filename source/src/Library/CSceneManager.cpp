#include "CSceneManager.h"
#include "CBaseScene.h"
#include "../Scene/CGame.h"
#include "../Scene/CTitle.h"
#include "../Scene/CResult.h"

CSceneManager::CSceneManager()
{
	//タイトルから
	scene = new CTitle();
	scene->Init();
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Init()
{
	scene->Init();
}

void CSceneManager::Update()
{
	scene->Update();
}

void CSceneManager::Render2D()
{
	cdg.GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	scene->Render2D();
	cdg.GetSprite()->End();
}

void CSceneManager::Render3D()
{
	scene->Render3D();
}

void CSceneManager::Camera()
{
	scene->Camera();
}

void CSceneManager::ChangeScene(std::string Nextscene)
{
	if (Nextscene == "")return;
	//シーンへ
	if (Nextscene =="TITLE"){scene = new CTitle();}
	else if (Nextscene == "GAME") { scene = new CGame(); scene->Init(); }
	else if (Nextscene == "RESULT") { scene = new CResult(); scene->Init(); }

}
