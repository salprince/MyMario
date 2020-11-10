#include "Fire.h"

void Fire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDTH;
	b = y + FIRE_BBOX_HEIGHT;
}
void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->marioHandle= ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vy += 0.005;
	coEvents.clear();
	this->SetState(FIRE_STATE_ALIVE);
	if (this->state == FIRE_STATE_ALIVE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	if (marioHandle->getIsFire())
	{
		this->isFire = GetTickCount();
		this->setPositionAfterMario(marioHandle->x, marioHandle->y, marioHandle->nx);
	}
		
	if (isFire != 0)
	{
		this->vx =marioHandle->nx * FIRE_FLYING_SPEED;
		this->vy = -0.00002;
		marioHandle->setIsFire(false);
		isFire = 0;
	}
	//DebugOut(L"%d \n", ny);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//DebugOut(L"not collis\n ");
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		
		/*if (isFire ==0)
		{
			x += min_tx * dx + nx * 0.4f;
			if (ny != 0) vy = 0;
			if (nx != 0);
		}*/
		if (nx != 0)
			y = 500;
		if (ny != 0)
		{
			ny = -ny;
			//if (abs(vy) <= 0.2)
				vy = -(vy-0.002);
				DebugOut(L"%f \n", vy);
		}
		
	}
	if (state == FIRE_STATE_ALIVE)
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Koopas*>(e->obj))
			{
				e->obj->SetState(KOOPAS_STATE_DIE);
				e->obj->y += 12;
				e->obj->vx += 0.05 * nx;
				SetState(KOOPAS_STATE_DIE);
				y = 300;

			}
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				//e->obj->SetState(GOOMBA_STATE_CLEAR);
				e->obj->y += 12;
				e->obj->vx += 0.05 * nx;
				y = 300;
			}
			
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Fire::Render()
{
	int ani = FIRE_ANI_ALIVE;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Fire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_STATE_ALIVE:
		break;
	}
}
