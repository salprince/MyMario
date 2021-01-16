#include "LevelMushroom.h"
#include "Include.h"
void LevelMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;

}
void LevelMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID() == id)
	{
		if (isCheck == false)
		{
			width = 16;
			height = 16;
			y -=5;
			isCheck = true;
		}
		if (id == 10)
			this->SetState(MUSHROOM_STATE_1UP);
		if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getLevel() < MARIO_LEVEL_BIG || id==10)
		{
			if ((start_y - y) < 16 && isCheck && !isRun)
			{
				y--;
			}
			else isRun = true;
		}
		else
		{
			if ((start_y - y) <= 30 && isCheck && !isRun)
			{
				y--;
			}
			else
			{
				isRun = true;
				isFly = true;
			}

		}
	}
	
	//set mushroom state leaf
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getLevel() >= MARIO_LEVEL_BIG)
	{
		if (isCheck && this->state != MUSHROOM_STATE_DIE)
		{
			if (isFly)
			{
				nx = -1;
				if ((start_y - y) > -50)
				{
					if ((start_y - y) > -30 )
						nx = 1;
					x += nx*0.2;
					y++;
				}
				else
				{
					this->SetState(MUSHROOM_STATE_DIE);
					this->y = 0;
					this->x = 0;
				}
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		if (isCheck && this->state != MUSHROOM_STATE_DIE )
		{
			if (isRun )
			{
				if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getLevel() < MARIO_LEVEL_BIG || id == 10)
				{
					if (x > 1480)
						nx = -1;
					else this->nx = 1;
					if ((start_x - x) > -18)
						x++;
					else
					{
						if ((x - start_x) < 93)
						{
							vx = nx * MUSHROOM_VX/2;
							vy += MUSHROOM_GRAVITY;
							x += dx;
							y += dy;
						}
						else this->SetState(MUSHROOM_STATE_DIE);
					}
				}
				
			}
			
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		CalcPotentialCollisions(coObjects, coEvents);
		x += min_tx * dx + nx * 0.4f;
		if (ny != 0) vy = 0;
		
		
	}
	
}
void LevelMushroom::Render()
{
	int ani = MUSHROOM_ANI_ALIVE_1;
	if(state ==MUSHROOM_STATE_1UP)
		ani = MUSHROOM_ANI_1UP;
	else if(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getLevel()>=MARIO_LEVEL_BIG)
		ani = MUSHROOM_ANI_ALIVE_2;
	if (state == MUSHROOM_STATE_DIE) {
		ani = MUSHROOM_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void LevelMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MUSHROOM_STATE_DIE)
	{
		this->x = -500;
		this->y = -500;
		width = 0;
		height = 0;
	}
}
