#pragma once
#include<d3dx9.h>

class CBaseScene
{
public:
	CBaseScene();
	~CBaseScene();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render2D() = 0;
	virtual void Render3D() = 0;
	virtual void Camera() = 0;

protected:
};

