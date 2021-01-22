#pragma once
#include "Include.h"
#define BBANI_BBOX_WIDTH  0
#define BBANI_BBOX_HEIGHT 0

#define BBANI_STATE_ALIVE 100

#define BBANI_ANI_ALIVE 0

#define BBANI_FLYING_SPEED 0.017f;
#define BBANI_GRAVITY 0.002f;

class breakBrickAni : public CGameObject
{
public:

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	CMario* marioHandle = NULL;
	void Reset();
	void setPositionAfterMario(float x, float y, int nx)
	{
		this->x = x;
		this->y = y;
		this->nx = nx;
	}
	float firedTime = 0;
	int id = -1;
	bool isActive = false;
};
