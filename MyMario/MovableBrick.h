#pragma once
#include "GameObject.h"

#define MOVE_BRICK_BBOX_WIDTH  16
#define MOVE_BRICK_BBOX_HEIGHT 16

#define MOVE_BRICK_STATE_ALIVE 100
#define MOVE_BRICK_STATE_FALL 200
#define MOVE_BRICK_STATE_DIE 300

#define MOVE_BRICK_ANI_ALIVE 0
#define MOVE_BRICK_ANI_DIE 2
class MovableBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void moveBlockBrick(int id, float x0, float x1);
	void fallBlockBrick(int id);
	int width = 16;
	int height = 16;
	int id = -1;
	bool isCheck = false;
	float time = 0;
	int relativePosition = -1;
	float x0 = 0;
	float x1 = 0;
	bool isActive = false;
};

