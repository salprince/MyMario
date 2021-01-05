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
			y -= 16;
			//vy = -0.1;
			isCheck = true;
			this->time = (float)GetTickCount64();
			if (GetTickCount64() % 2 == 0)
				nx = -1;
			else
				nx = 1;
			vx = nx * MUSHROOM_VX;
		}
	}
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		if (isCheck && this->state != MUSHROOM_STATE_DIE)
		{
			if ((GetTickCount64() - this->time) < 80)
			{
				x += dx;
			}
			else if (x <= 368)
			{
				vy += MUSHROOM_GRAVITY;
				x += dx;
				y += dy;
			}
			else this->SetState(COIN_STATE_DIE);
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
		}

	}
	
}
void LevelMushroom::Render()
{
	int ani = MUSHROOM_ANI_ALIVE;
	if (state == MUSHROOM_STATE_DIE) {
		ani = MUSHROOM_ANI_ALIVE;
	}
	animation_set->at(ani)->Render(x, y);
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
