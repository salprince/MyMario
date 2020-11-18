#include "Fire.h"

void Fire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIRE_BBOX_WIDTH;
	b = y + FIRE_BBOX_HEIGHT;
	this->marioHandle = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vy += 0.005f;
	coEvents.clear();
	
	this->SetState(FIRE_STATE_ALIVE);

	if (this->state == FIRE_STATE_ALIVE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	
	if (marioHandle->getIsFire())
	{
		//DebugOut(L"isShooting %d, getIsFire %d \n", marioHandle->timeShooting, marioHandle->getIsFire());
		//if(this->id == marioHandle->FireID)
		{
			for (int i = 1; i < 10; i++)
			{
				//DebugOut(L" id of fire %d \n", id);
				if (!this->isFiring && this->id == marioHandle->FireID)
				{
					this->Reset();
					this->isFire = GetTickCount();
					if (abs(marioHandle->vx) > 0.07f)

						this->vx = marioHandle->vx;
					else
						this->vx = marioHandle->nx * FIRE_FLYING_SPEED;
					if (marioHandle->nx > 0)
						this->setPositionAfterMario(marioHandle->x + 10, marioHandle->y, marioHandle->nx);
					else if (marioHandle->nx < 0)
						this->setPositionAfterMario(marioHandle->x - 3, marioHandle->y, marioHandle->nx);
					//vy = -0.08;
					this->isFiring = true;

					//DebugOut(L"BREAK id of fire %d \n", id);
					//DebugOut(L"mario y %f \n", marioHandle->y);
					DebugOut(L"%f  %f ///// %f %f \n", vx, vy, x,y);
					break;

				}
			}

			/*if (marioHandle->FireID < 10)
				marioHandle->FireID++;*/

		}
	}
	else;
		//DebugOut(L"\n");
		
	if (isFire != 0)
	{
		if ((GetTickCount() - isFire) < 3000)
		{	
			if (y > 240 && y != 500)
				y = 240;
		}
		else
		{			
			isFire = 0;
			this->isFiring = false;
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
		{
			Reset();
			x = 0;
			y = 500;
			isFiring = false;
			isFire = 0;
		}
			
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
					e->obj->vx += (float)0.05 * nx;
					SetState(KOOPAS_STATE_DIE);
					isFiring = false;
					isFire = 0;
					Reset();

				}
				else if (dynamic_cast<CGoomba*>(e->obj))
				{
					//e->obj->SetState(GOOMBA_STATE_CLEAR);
					e->obj->y += 12;
					e->obj->vx += (float)0.05 * nx;
					isFiring = false;
					isFire = 0;
					Reset();
				}
				else if (dynamic_cast<ColorBrick*>(e->obj) || dynamic_cast<Coin*>(e->obj))
				{
					//DebugOut(L"collis color brick\n");
					x++;
				}
				else if (dynamic_cast<backRound*>(e->obj));
				else if (dynamic_cast<CMario*>(e->obj))
				{
					nx = 0; ny = 0;
					x++;
				}
				else if (dynamic_cast<CBrick*>(e->obj));
				else 
				{
					isFiring = false;
					isFire = 0;
					Reset();
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
	this->SetSpeed(0.0, 0.0);
	this->isFire = 0;
	this->vx = 0;
	this->vy = 0;
	this->x = 0;
	this->y = 0;
	this->ax = 0;
	this->ay = 0;
	this->dx = 0;
	this->dy = 0;
	this->nx = 0;
	this->ny = 0;

	//isFiring = false;
}