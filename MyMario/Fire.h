#pragma once
#include "Include.h"
#define FIRE_BBOX_WIDTH  8
#define FIRE_BBOX_HEIGHT 8

#define FIRE_STATE_ALIVE 100

#define FIRE_ANI_ALIVE 0

#define FIRE_FLYING_SPEED 0.1f;
#define FIRE_GRAVITY 0.0017f;

class Fire : public CGameObject
{
public:
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	int isFire = 0;
	int id = 0;
	bool isFiring = false;
	float start_x = 0;
	float start_y = 0;
	CMario* marioHandle = NULL;
	void Reset();
	void setPositionAfterMario(float x, float y, int nx)
	{
		this->x = x;
		this->y = y;
		this->nx = nx;
	}
};
