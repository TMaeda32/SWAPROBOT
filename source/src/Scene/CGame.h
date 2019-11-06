#pragma once
#include "../Library/CBaseScene.h"


#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight

class CWall;
class CMesh;
class CPlayer;
class CRock;
class CStage;
class CObject;

class CGame : public CBaseScene
{
public:
	CGame();
	~CGame();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
	virtual void Camera() override;
	
private:
};

