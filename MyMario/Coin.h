#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

#define COIN_STATE_ALIVE 100
#define COIN_STATE_DIE 200

#define COIN_ANI_ALIVE 0
#define COIN_ANI_DIE 1

#define COIN_GRAVITY 0.01f

class Coin : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	int width = 5;
	int height = 5;
	int id = 0;
	bool isCheck = false;
	float time = 0;
};