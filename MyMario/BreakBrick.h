#pragma once
#include "GameObject.h"

#define BREAK_BRICK_BBOX_WIDTH  16
#define BREAK_BRICK_BBOX_HEIGHT 16

#define BREAK_BRICK_STATE_ALIVE 100
#define BREAK_BRICK_STATE_DIE 200
#define BREAK_BRICK_STATE_COIN 300

#define BREAK_BRICK_ANI_ALIVE 0
#define BREAK_BRICK_ANI_DIE 2
#define BREAK_BRICK_ANI_COIN 3

#define BREAK_BRICK_GRAVITY 0.01f
class BreakBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int width = 16;
	int height = 16;
	int id = -1;
	bool isCheck = false;
	float time = 0;
};
