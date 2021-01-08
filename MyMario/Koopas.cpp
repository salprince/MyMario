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
	//if (this->typeKoopas == 1)
		//this->SetState(KOOPAS_STATE_WING);
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;	
}
void Koopas::BeginSceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CMario* player = ((BeginScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float time = GetTickCount64() - player->beginTime;
	if ((time > this->appearTime*1000) && this->y==500 )
		this->y = 0;
	else 
		this->y = 500;

}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CMario* player = ((BeginScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float time = GetTickCount64() - player->beginTime;
	if (((BeginScene*)CGame::GetInstance()->GetCurrentScene())->typeScene == SCENE_TYPE_BEGIN)
	{
		if ((time < this->appearTime * 1000))
		{
			vy = 0;
			vx = 0;
			this->SetState(KOOPAS_STATE_WALKING);
			this->nx = 1;
		}

		else
		{
			vy += GRAVITY * dt;
			vx = nx * KOOPAS_WALKING_SPEED;
			if (this->appearTime == 15)
				vx = 0.05;
		}
	}
	
	if (state != KOOPAS_STATE_DIE)
	{
		if (state == KOOPAS_STATE_HOLD)
		{
			this->marioHandle= ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (!marioHandle->getIsHold())
			{
				this->setIsHold(false);
				this->SetState(KOOPAS_STATE_SHELL_RUNNING);
				this->nx = marioHandle->nx;
				this->vx = nx * KOOPAS_RUNNING_SPEED;				
				this->vy = (float)-0.2;
				this->marioHandle = NULL;
			}
			else
				setPositionWhileHolding(marioHandle->x, marioHandle->y, marioHandle->vx, marioHandle->nx);
		}
		else
		{
			if (state != KOOPAS_STATE_SHELL_RUNNING)
				this->gravity = (float)0.0001;
			else	gravity = (float)0.0008;
			vy += gravity * dt;
			if (startx == 0)
				startx = x;
			if (vx < 0 && x < 15 )
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
		
	}	
	//make koopa waling after some seconds
	if (isShell == true && state != KOOPAS_STATE_HOLD)
	{
		if (getIsHold())
		{
			SetState(KOOPAS_STATE_HOLD);
		}
		else
		{
			if (getShellIn() == 0)
			{
				setShellIn((int)GetTickCount64());
				setShellOut((int)GetTickCount64());
			}

			else
			{
				if (getShellOut() - getShellIn() < 3000)
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

	if (getIsHold() && this->GetState() == KOOPAS_STATE_SHELL)
		state = KOOPAS_STATE_HOLD;
	/*else 
		state = KOOPAS_STATE_SHELL;*/
	
	if (coEvents.size() == 0)
	{		
		if (!isJump && this->typeKoopas==1)
		{
			vy += -JUMP_SPEECH;
			isJump = true;
		}			
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
		}
		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
			if (dynamic_cast<ColorBrick*>(e->obj))
			{
				if (isJump)
					isJump = false;
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
				//e->obj->vx += (float)(0.05*ny);
				SetState(KOOPAS_STATE_DIE);
				vx = (float)(-0.05 * ny);
			}
			if (dynamic_cast<CGoomba*>(e->obj))
			{
				//e->obj->SetState(GOOMBA_STATE_CLEAR);
				e->obj->y += 12;
				e->obj->vx += (float)(0.05 * ny);
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Koopas::Render()
{
	int ani = GREEN_KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE ) {
		ani = GREEN_KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_HOLD)
		ani = GREEN_KOOPAS_ANI_HOLD;
	else if (state == KOOPAS_STATE_SHELL|| state == KOOPAS_STATE_SHELL_RUNNING )
		ani = GREEN_KOOPAS_ANI_SHELL;
	else if (this->typeKoopas==1)
	{
		if (vx > 0) ani = GREEN_KOOPAS_ANI_WING_RIGHT;
		else if (vx < 0) ani = GREEN_KOOPAS_ANI_WING_LEFT;
	}
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
		vy = (float)0.1;
		height = 14;
		width=16;
		break;
	case KOOPAS_STATE_WALKING:
		if(((BeginScene*)CGame::GetInstance()->GetCurrentScene())->typeScene != SCENE_TYPE_BEGIN)
			vx = KOOPAS_WALKING_SPEED;
		width = 16;
		height = 26;
		break;
	case KOOPAS_STATE_SHELL:
		vy = 0;
		vx = 0;
		height = 14;
		width = 16;
		break;
	case KOOPAS_STATE_WING:
		break;
	case KOOPAS_STATE_HOLD:
		vy = 0;
		vx = 0;
		height = 14;
		width = 16;
		DebugOut(L" Koopa is HOLD\n");
		break;
	case KOOPAS_STATE_SHELL_RUNNING:
		height = 14;
		width = 16;
		break;

	}

}