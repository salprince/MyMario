#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_CLEAR 300

#define GOOMBA_ANI_WALKING_LEFT 0
#define GOOMBA_ANI_WALKING_RIGHT 1
#define GOOMBA_ANI_DIE 3
#define GOOMBA_ANI_RENEW 4
#define GOOMBA_ANI_SHELL 5

class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int width = 16;
	int height = 16;

public:
	CGoomba();
	virtual void SetState(int state);
};