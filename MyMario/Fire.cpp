#include "Fire.h"
#include "BreakBrick.h"
//id form 1 ->5 : mario 
//id form 10->6 : for shooting red tree
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
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	vy += 0.005f;
	coEvents.clear();
	//DebugOut(L"firedTime %f \n", (GetTickCount64() - firedTime)/1000);
	this->SetState(FIRE_STATE_ALIVE);

	if (this->state == FIRE_STATE_ALIVE && id!=6)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}	
	if (marioHandle->getIsFire())
	{
		aliveTime = 3000;
		for (int i = 1; i <= 2; i++)
		{
			if (!this->isFiring && this->id == marioHandle->FireID )
			{
				this->Reset();
				this->isFire = (int)GetTickCount64();
				if (abs(marioHandle->vx) > 0.07f)
					this->vx = marioHandle->vx;
				else
					this->vx = marioHandle->nx * FIRE_FLYING_SPEED;
				if (marioHandle->nx > 0)
					this->setPositionAfterMario(marioHandle->x + 10, marioHandle->y, marioHandle->nx);
				else if (marioHandle->nx < 0)
					this->setPositionAfterMario(marioHandle->x - 3, marioHandle->y, marioHandle->nx);
				this->isFiring = true;
				break;
			}
		}
	}
	else //if (marioHandle->treeFireID !=-1)
	{
		if (!this->isFiring && this->id == 6 )
		{
			aliveTime = 8000;
			this->Reset();
			this->nx = marioHandle->treeNx;
			this->isFire = (int)GetTickCount64();
			this->vx = nx*0.06;
			this->vy +=0.02;
			this->isFiring = true;
			this->x = marioHandle->treeX + nx*10;
			this->y = marioHandle->treeY;
			firedTime = GetTickCount64();
		}
	}
	if (isFire != 0)
	{
		if ((GetTickCount64() - isFire) < aliveTime)
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
		y += dy*2;
	}
	else
	{
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			if (id != 6)
			{
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
				CalcPotentialCollisions(coObjects, coEvents);
			}
			
			if (nx != 0)
			{
				Reset();
				x = 0;
				y = 500;
				isFiring = false;
				isFire = 0;
			}
			{
				if (ny != 0)
				{
					if (vy > 0.12 / 2)
					{
						vy = vy - abs(vy / 3);
					}
					else if (vy < -0.12 / 2)
					{
						vy = vy + abs(vy / 3);
					}
					else
					{
						vy = 0;
					}
					ny = -ny;
					if (id != 6)
						vy = -vy;
				}
			}
			if (state == FIRE_STATE_ALIVE && id != 6)
			{
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<Koopas*>(e->obj))
					{
						e->obj->SetState(KOOPAS_STATE_DIE);
						e->obj->y += 12;
						SetState(KOOPAS_STATE_DIE);
						isFiring = false;
						isFire = 0;
						Reset();

					}
					else if (dynamic_cast<CGoomba*>(e->obj))
					{
						e->obj->y += 12;
						e->obj->vx += (float)0.05 * nx;
						isFiring = false;
						isFire = 0;
						Reset();
					}
					else if (dynamic_cast<ColorBrick*>(e->obj) || dynamic_cast<Coin*>(e->obj))
					{
						x++;
					}
					else if (dynamic_cast<BreakBrick*>(e->obj))
					{
						this->y = 250;
					}
					else if (dynamic_cast<CMario*>(e->obj))
					{
						//CMario* mario = dynamic_cast<CMario*>(e->obj);
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
	this->firedTime = 0;
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->getLevel() == MARIO_LEVEL_FIRE)
	{
		this->x = mario->x;
	}
	else
	{
		this->x = this->start_x;
	}
	
	this->y = 500;
	this->ax = 0;
	this->ay = 0;
	this->dx = 0;
	this->dy = 0;
	this->nx = 0;
	this->ny = 0;

	//isFiring = false;
}