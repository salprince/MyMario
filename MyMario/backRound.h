#pragma once
#include "GameObject.h"
#define BACKROUND_BBOX_WIDTH  16
#define BACKROUND_BBOX_HEIGHT 16

#define BACKROUND_ANI_COLOR_BLACK		0
#define MARIO_ANI_BIG_COLOR_YELLO			1
class backRound:public CGameObject
{
public:
	int isAnimation = 0;
	float beginTime = 0; 
	float Time = 0;
	int isColorBackround = 0;	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
