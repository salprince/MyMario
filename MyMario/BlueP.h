#pragma once
#include "GameObject.h"
#define BLUE_P_BBOX_WIDTH  16
#define BLUE_P_BBOX_HEIGHT 16

#define BLUE_P_STATE_ALIVE 100
#define BLUE_P_STATE_DIE 200

#define BLUE_P_ANI_ALIVE 0
#define BLUE_P_ANI_DIE 1
class BlueP : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	float oldY = 0;
	int width = 0;
	int height = 0;
	int id = -1;
	bool isCheck = false;
	float time = 0;
	int idCoin = -1;

};
