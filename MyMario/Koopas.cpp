#include "Koopas.h"
#include "Utils.h"

Koopas::Koopas()
{
	SetState(KOOPAS_STATE_WALKING);
	vx = -KOOPAS_WALKING_SPEED;
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;	
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	/*
	if (state ==KOOPAS_STATE_SHELL)
		DebugOut(L"Koopa is shell \n");
	if (state == KOOPAS_STATE_SHELL_RUNNING)
		DebugOut(L"Koopa is shell running\n");*/
	DebugOut(L"shell %d\n", isShell);
}

void Koopas::Render()
{
	int ani = GREEN_KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE) {
		ani = GREEN_KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_SHELL|| state == KOOPAS_STATE_SHELL_RUNNING)
		ani = GREEN_KOOPAS_ANI_SHELL;
	else if (vx > 0) ani = GREEN_KOOPAS_ANI_WALKING_RIGHT;
	else if (vx < 0) ani = GREEN_KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void Koopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		//y += 16;
		vx = 0;
		vy = 0;
		height = 16;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		DebugOut(L" SET Koopa is shell\n");
		break;
	case KOOPAS_STATE_SHELL_RUNNING:
		//vx=-KOOPAS_WALKING_SPEED;
		break;

	}

}