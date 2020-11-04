#pragma once

#include "GameObject.h"

class ChimneyPortal : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	ChimneyPortal();
	int width = 16;
	int height = 16;
	bool isShell = false;
	virtual void SetState(int state);

};