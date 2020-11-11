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
		this->Reset();
		this->isFire = GetTickCount();
		
		if (abs(marioHandle->vx) > 0.07f)
			this->vx = marioHandle->vx;
		else 
			this->vx = marioHandle->nx * FIRE_FLYING_SPEED;
		this->setPositionAfterMario(marioHandle->x + 10, marioHandle->y, marioHandle->nx);
	}
		
	if (isFire != 0)
	{
		if ((GetTickCount() - isFire) < 3000)
		{	
			marioHandle->setIsFire(false);
		}
		else
		{			
			isFire = 0;
		}
		
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
		if (nx != 0)
			y = 500;
		if (ny != 0)
		{			
			if (vy > 0.12 / 2)
			{
				vy = vy - abs(vy / 3);
			}
			else if (vy < -0.12/ 2)
			{
				vy = vy + abs(vy / 3);
			}
			else
			{
				vy = 0;
			}
			ny = -ny;
			vy = -vy;
			//DebugOut(L"%f \n", vy);
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
				else if (dynamic_cast<CGoomba*>(e->obj))
				{
					//e->obj->SetState(GOOMBA_STATE_CLEAR);
					e->obj->y += 12;
					e->obj->vx += 0.05 * nx;
					y = 300;
				}
				else if (dynamic_cast<ColorBrick*>(e->obj))
				{
					//DebugOut(L"collis color brick\n");
					x++;
				}
				else if (dynamic_cast<backRound*>(e->obj));
				else if (dynamic_cast<CBrick*>(e->obj));
				else 
				{
					y = 500;
				}
				
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
void Fire::Reset()
{
	this->SetState(FIRE_STATE_ALIVE);
	this->SetSpeed(0.05, 0.05);
	this->isFire = 0;
}