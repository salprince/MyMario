#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING	100
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_DIE 300
#define KOOPAS_STATE_SHELL_RUNNING 400

#define GREEN_KOOPAS_ANI_WALKING_LEFT 0
#define GREEN_KOOPAS_ANI_WALKING_RIGHT 1
#define GREEN_KOOPAS_ANI_DIE 2
#define GREEN_KOOPAS_ANI_RENEW 3
#define GREEN_KOOPAS_ANI_SHELL 4

class Koopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int shellIn = 0;
	int shellOut = 0;
public:
	Koopas();
	int width = 16;
	int height = 26;
	bool isShell = false;	
	virtual void SetState(int state);
	void setShellIn(int value) { shellIn = value; }
	int getShellIn() { return shellIn; }
	void setShellOut(int value) { shellOut = value; }
	int getShellOut() { return shellOut; }

};