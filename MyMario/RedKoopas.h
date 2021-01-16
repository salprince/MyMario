#pragma once
#include "Koopas.h"
#define RED_KOOPAS_ANI_WALKING_LEFT 0
#define RED_KOOPAS_ANI_WALKING_RIGHT 1
#define RED_KOOPAS_ANI_SHELL 2
#define RED_KOOPAS_ANI_HOLD 3
class RedKoopas :    public Koopas
{
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

