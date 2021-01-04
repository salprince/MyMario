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
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int width = 0;
	int height = 0;
	int id = 0;
	bool isCheck = false;
};