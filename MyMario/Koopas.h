#pragma once

#include "Include.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_RUNNING_SPEED 0.2f;
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING	100
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_HOLD 250
#define KOOPAS_STATE_DIE 300
#define KOOPAS_STATE_SHELL_RUNNING 400
#define KOOPAS_STATE_WING 500

#define GREEN_KOOPAS_ANI_WALKING_LEFT 0
#define GREEN_KOOPAS_ANI_WALKING_RIGHT 1
#define GREEN_KOOPAS_ANI_DIE 2
#define GREEN_KOOPAS_ANI_RENEW 3
#define GREEN_KOOPAS_ANI_SHELL 4
#define GREEN_KOOPAS_ANI_HOLD 5
#define GREEN_KOOPAS_ANI_WING_LEFT 6
#define GREEN_KOOPAS_ANI_WING_RIGHT 7
#define RED_KOOPAS_ANI_WALKING_LEFT 8
#define RED_KOOPAS_ANI_WALKING_RIGHT	9
#define RED_KOOPAS_ANI_SHELL 10
#define RED_KOOPAS_ANI_HOLD 11

#define GRAVITY 0.001f
#define JUMP_SPEECH 0.12f
#define KOOPAS_LEVEL_NORMAL	1
#define KOOPAS_LEVEL_WING	2

class Koopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int shellIn = 0;
	int shellOut = 0;
	bool isHold = false;
public:
	Koopas();
	int width = 16;
	int height = 26;
	bool isShell = false;	
	float startx = 0;
	int starty = 0;
	float gravity = 0;
	CMario* marioHandle= NULL;
	virtual void SetState(int state);
	void setShellIn(int value) { shellIn = value; }
	int getShellIn() { return shellIn; }
	void setShellOut(int value) { shellOut = value; }
	int getShellOut() { return shellOut; }
	void setIsHold(bool value) { isHold = value; }
	bool getIsHold() { return isHold; }

	void setPositionWhileHolding(float x0,float y0, float vx0, int nx)
	{
		if (nx > 0)
		{
			this->x = x0 + 10;
			this->y = y0 + 10;
			this->vx = vx0;
		}
		else 
		{
			this->x = x0 - 10;
			this->y = y0 + 10;
			this->vx = vx0;
		}
		
	}
	int typeKoopas = 0;
	int level = 1;
	bool isJump = false;
	float appearTime = 0;
	void BeginSceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};