#include "Koopas.h"
#include "Utils.h"
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Portal.h"
#include "Brick.h"
#include "backRound.h"
#include "ColorBrick.h"
#include "Coin.h"
#include "MicsBrick.h"
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

/*void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (vx < 0 && x < 15) vx = -vx;
	coEvents.clear();
	if (state != KOOPAS_STATE_DIE )
		
	if (state == KOOPAS_STATE_WALKING)
	{
		CalcPotentialCollisions(coObjects, coEvents);
		vy += 0.02*dt ;
	}
	else if (state == KOOPAS_STATE_SHELL)
	{
		vy = 0;
	}
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
				
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
			
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];		
	//DebugOut(L"shell %d\n", isShell);
}*/

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != KOOPAS_STATE_DIE)
	{
		vy += 0.0008 * dt;
		CalcPotentialCollisions(coObjects, coEvents);
	}	

	if (x < 15 && vx < 0) {
		x = 15; vx = -vx;
	}

	//make koopa waling after some seconds
	if (isShell == true && state != KOOPAS_STATE_SHELL_RUNNING)
	{
		if (getShellIn() == 0)
		{
			setShellIn(GetTickCount());
			setShellOut(GetTickCount());
		}

		else
		{
			if (getShellOut() - getShellIn() < 4000)
			{
				setShellOut(getShellOut() + 10);
			}
			else
			{ 
				SetState(KOOPAS_STATE_WALKING);
				height = 26;
				y -= 16;
				isShell = false;				
				CalcPotentialCollisions(coObjects, coEvents);
			}				
		}
	}
	else
	{
		setShellIn(0);
		setShellOut(0);
	}
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
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		CalcPotentialCollisions(coObjects, coEvents);
		x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (nx != 0);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}
		// block object
		//x += min_tx * dx + nx * 0.4f;

	}
	/*if (state == KOOPAS_STATE_SHELL_RUNNING )
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];			
			if (dynamic_cast<Koopas*>(e->obj))
			{
				e->obj->SetState(KOOPAS_STATE_SHELL);
			}
		}
	}*/
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	

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
		vy = 0;
		vx = 0;
		height = 14;
		DebugOut(L" SET Koopa is shell\n");
		break;
	case KOOPAS_STATE_SHELL_RUNNING:
		//vx=-KOOPAS_WALKING_SPEED;
		break;

	}

}