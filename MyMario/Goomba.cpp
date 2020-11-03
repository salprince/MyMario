#include "Goomba.h"
#include "Utils.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + height;
	else
		bottom = y + height;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	
	if (state == GOOMBA_STATE_WALKING)
	{
		vy = 0.2;		
		CalcPotentialCollisions(coObjects, coEvents);
		this->setStartDying(GetTickCount());
		this->setEndDying(GetTickCount());
	}
		
	else if(state == GOOMBA_STATE_DIE)
	{				
		if ((getEndDying() - getStartDying()) < 200)
		{
			this->setEndDying(GetTickCount() + 50);
		}
		else
			this->setIsDie(true);
			
	}
	if (getIsDie())
		SetState(GOOMBA_STATE_CLEAR);
	
	/*int n = (getEndDying() - getStartDying());
	DebugOut(L"aaaa %d\n ", n/ 1000);*/
		
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (vx < 0 && x < 0) {
			x = 0; vx = -vx;
		}

		if (vx > 0 && x > 490) {
			x = 290; vx = -vx;
		}
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		x += min_tx * dx + nx*0.4f ;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"shell %d\n", isShell);


	
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING_LEFT;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	else if (state == GOOMBA_STATE_CLEAR)
		ani = GOOMBA_ANI_CLEAR;
	else ani = GOOMBA_ANI_WALKING_RIGHT;
	/*{
		if (nx > 0)
			ani = GOOMBA_ANI_WALKING_RIGHT;
		else ani = GOOMBA_ANI_WALKING_LEFT;
	}*/		
	animation_set->at(ani)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		//y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		//y += 50;
		y += 8;
		vx = 0;
		vy = 0;
		width = 8;
		height = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;		
		break;
	case GOOMBA_STATE_CLEAR:
		vx = 0;
		vy = 0;
		x = 0;
		//y = 0;
		y += 50;
		//width = 0;
		//height = 0;
		break;
	}
}
