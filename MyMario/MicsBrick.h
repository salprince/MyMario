#pragma once
#include "GameObject.h"
#define MICSBRICK_BBOX_WIDTH  16
#define MICSBRICK_BBOX_HEIGHT 16

#define MICSBRICK_STATE_ALIVE 100
#define MICSBRICK_STATE_DIE 200

#define MICSBRICK_ANI_ALIVE 0
#define MICSBRICK_ANI_DIE 1

class MicsBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int width = 16;
	int height = 16;
	int id = 0;
};