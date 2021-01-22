#include "Goomba.h"
#include "Utils.h"
#include "Mario.h"
#include "BeginScene.h"
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
	CMario* player = ((BeginScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float time = GetTickCount64() - player->beginTime;
	if ((time < this->appearTime * 1000))
		vy = 0;
	else
		vy += GRAVITY * dt;
	
	if (state == GOOMBA_STATE_WALKING)
	{
		//vy = 0.15f;	
		if (startx == 0)
			startx = x;
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
		//if ((GetTickCount64() - jumpTime) < 10000 && jumpTime !=0)
		{
			if (this->level == 2 && wing)
			{
				if (!isJump)
				{
					vy += -JUMP_SPEECH * 2;
					isJump = true;
				}
			}
		}
		/*else
			jumpTime = GetTickCount64();*/
		DebugOut(L"%f\n", (GetTickCount64() - jumpTime)/1000);
		CalcPotentialCollisions(coObjects, coEvents);
		this->setStartDying((int)GetTickCount64());
		this->setEndDying((int)GetTickCount64());
	}
		
	else if(state == GOOMBA_STATE_DIE)
	{				
		if ((getEndDying() - getStartDying()) < 200)
		{
			this->setEndDying((int)GetTickCount64() + 50);
		}
		else
			this->setIsDie(true);
			
	}
	if (getIsDie())
		SetState(GOOMBA_STATE_CLEAR);
		
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (ny == 0 && nx != 0)
			{
				nx = -nx;
				vx = -vx;
			}
			if (isJump)
				isJump = false;
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING_LEFT;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	else if (state == GOOMBA_STATE_CLEAR)
		ani = GOOMBA_ANI_CLEAR;
	else
	{
		if(level== GOOMBA_LEVEL_WING && wing)
			ani = GOOMBA_ANI_WING;
		else ani = GOOMBA_ANI_WALKING_RIGHT;
	}
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
