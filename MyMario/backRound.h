#pragma once
#include "GameObject.h"
#define BACKROUND_BBOX_WIDTH  0
#define BACKROUND_BBOX_HEIGHT 0

class backRound:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
