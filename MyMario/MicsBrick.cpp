#include "MicsBrick.h"
#include "Include.h"
void MicsBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MICSBRICK_BBOX_WIDTH;
	b = y + MICSBRICK_BBOX_HEIGHT;
}

void MicsBrick::Render()
{
	int ani = MICSBRICK_ANI_ALIVE;
	if (state == MICSBRICK_STATE_ALIVE) {
		ani = MICSBRICK_ANI_ALIVE;
	}
	else if (state == MICSBRICK_STATE_DIE)
	{
		ani = MICSBRICK_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void MicsBrick::SetState(int state)
{
	CGameObject::SetState(state);
}
void MicsBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	int coinid = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID();
	if (isCheck && y!=oldY)
	{
		//DebugOut(L"OLD Y %f\n", oldY);
		if (y < oldY)
		{
			vy += COIN_GRAVITY;
			y += vy * dt;
		}
		else y = oldY;
	}
	else if(isCheck == false && coinid == id && coinid!=7)
	{		
		{
			this->vy = (float)-0.0075;
			y -= 16;
			isCheck = true;
			this->time = (float)GetTickCount64();
		}
	}
}