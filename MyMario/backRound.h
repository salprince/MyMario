#pragma once
#include "GameObject.h"
#include "Include.h"
#define BACKROUND_BBOX_WIDTH  16
#define BACKROUND_BBOX_HEIGHT 16

class backRound:public CGameObject
{
public:
	int isAnimation = 0;
	float beginTime = 0; 
	float endTime = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
