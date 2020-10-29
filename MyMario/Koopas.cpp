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
	//x += dx;
	//y += dy;
	vy += 0.002 * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (state != KOOPAS_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
			
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];		
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
		//height = 16;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		height = 14;
		DebugOut(L" SET Koopa is shell\n");
		break;
	case KOOPAS_STATE_SHELL_RUNNING:
		//vx=-KOOPAS_WALKING_SPEED;
		break;

	}

}