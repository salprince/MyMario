#pragma once
#include "GameObject.h"
#define BACKROUND_BBOX_WIDTH  16
#define BACKROUND_BBOX_HEIGHT 16

class backRound:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
