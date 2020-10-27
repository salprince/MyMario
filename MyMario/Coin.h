#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_ALIVE 100
#define COIN_STATE_DIE 200

#define COIN_ANI_ALIVE 0
#define COIN_ANI_DIE 1

class Coin : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	int width = 0;
	int height = 0;
};