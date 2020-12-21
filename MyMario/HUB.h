#pragma once
#include "GameObject.h"
#define HUB_WIDTH 0
#define HUB_HEIGHT 0
#define HUB_STATE_NORMAL 100


#define HUB_ANI_NORMAL 0
class MyHUB : public CGameObject
{
public:
	virtual void Render() ;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
