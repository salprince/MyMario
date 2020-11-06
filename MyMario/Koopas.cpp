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

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state != KOOPAS_STATE_DIE)
	{
		vy += 0.0008 * dt;
		if (startx == 0)
			startx = x;
		if (vx < 0 && x < 15)
		{
			vx = -vx;
			x = 15;
		}
		if (state != KOOPAS_STATE_SHELL_RUNNING)
		{
			if (vx > 0 && x >= length + startx)
			{
				vx = -vx;
				x = length + startx;
			}
			if (vx < 0 && x <= startx - length)
			{
				vx = -vx;
				x = -length + startx;
			}
		}
		
		CalcPotentialCollisions(coObjects, coEvents);
	}	
	
	DebugOut(L"%f %f \n", x, startx);
	//make koopa waling after some seconds
	if (isShell == true && state != KOOPAS_STATE_SHELL_RUNNING  && state != KOOPAS_STATE_HOLD)
	{
		if (getIsHold())
		{
			SetState(KOOPAS_STATE_HOLD);
		}
		else
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
		
	}
	else
	{
		setShellIn(0);
		setShellOut(0);
	}

	if (getIsHold())
		state == KOOPAS_STATE_HOLD;
	else 
		state == KOOPAS_STATE_SHELL;
	
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
		if (state != KOOPAS_STATE_HOLD)
		{
			x += min_tx * dx + nx * 0.4f;
			if (ny != 0) vy = 0;
			if (nx != 0);
		}
		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
		}

	}
	
	if (state == KOOPAS_STATE_SHELL_RUNNING )
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];			
			if (dynamic_cast<Koopas*>(e->obj))
			{
				e->obj->SetState(KOOPAS_STATE_DIE);
				e->obj->y += 12;
				e->obj->vx += 0.05*ny;
				SetState(KOOPAS_STATE_DIE);
				vx = -0.05 * ny;
			}
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				//e->obj->SetState(GOOMBA_STATE_CLEAR);
				e->obj->y += 12;
				e->obj->vx += 0.05 * ny;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Koopas::Render()
{
	int ani = GREEN_KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_HOLD) {
		ani = GREEN_KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_SHELL|| state == KOOPAS_STATE_SHELL_RUNNING )
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
		y += 10;
		vx = 0;
		vy = 0.1;
		height = 14;
		width=16;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		width = 16;
		height = 26;
		break;
	case KOOPAS_STATE_SHELL:
		vy = 0;
		vx = 0;
		height = 14;
		width = 16;
		//DebugOut(L" SET Koopa is shell\n");
		break;
	case KOOPAS_STATE_HOLD:
		vy = 0;
		vx = 0;
		height = 14;
		width = 16;
		DebugOut(L" Koopa is HOLD\n");
		break;
	case KOOPAS_STATE_SHELL_RUNNING:
		//vx=-KOOPAS_WALKING_SPEED;
		height = 14;
		width = 16;
		break;

	}

}