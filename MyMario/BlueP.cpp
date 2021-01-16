#include "BlueP.h"
#include "Include.h"
void BlueP::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
	if (!isCheck)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void BlueP::Render()
{
	int ani = BLUE_P_ANI_ALIVE;
	if (state == BLUE_P_STATE_ALIVE) {
		ani = BLUE_P_ANI_ALIVE;
	}
	else if (state == BLUE_P_STATE_DIE)
	{
		ani = BLUE_P_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void BlueP::SetState(int state)
{
	CGameObject::SetState(state);
}
void BlueP::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	//DebugOut(L"coindID %d  id %d coinid= %d\n", ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID(), id, idCoin);
	//DebugOut(L" %f  %f \n", this->x, this->y);
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID() == id)
	{
		
		if (isCheck == false)
		{
			width = 1;
			height = 1;
			//this->vy = (float)-0.0075;
			y -= 16;
			isCheck = true;
			this->time = (float)GetTickCount64();
		}
	}
}
