#pragma once
#include "GameObject.h"

#define MUSHROOM_STATE_ALIVE 100
#define MUSHROOM_STATE_DIE 200

#define MUSHROOM_ANI_ALIVE 0
#define MUSHROOM_ANI_DIE 1

class LevelMushroom : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	int width = 16;
	int height = 16;
};