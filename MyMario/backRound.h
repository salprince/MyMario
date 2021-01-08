#pragma once
#include "GameObject.h"
#define BACKROUND_BBOX_WIDTH  16
#define BACKROUND_BBOX_HEIGHT 16

#define BACKROUND_ANI_COLOR_BLACK		0
#define BACKROUND_ANI_COLOR_YELLO			1
#define BACKROUND_ANI_NONE			2

#define BACKROUND_TYPE_GO_UP	1	// object move from top to bot in begin scene
#define BACKROUND_TYPE_GO_DOWN	2	// object move from bot to top in begin scene
#define BACKROUND_TYPE_CAN_HIDE	3	// object can hide at some specific time

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
	float start_x = 0;
	float start_y = 0;
};
