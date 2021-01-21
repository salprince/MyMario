#include "Coin.h"
#include "Include.h"
void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void Coin::Render()
{
	int ani = COIN_ANI_ALIVE;
	if (state == COIN_STATE_DIE) {
		ani = COIN_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void Coin::SetState(int state)
{
	CGameObject::SetState(state);	
	if (state == COIN_STATE_DIE)
	{
		x = 0;
		y = 0;
	}
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//CGameObject::Update(dt);
	if (isCheck && this->state != COIN_STATE_DIE)
	{		
		if ((GetTickCount64() - this->time) < 500)
		{
			vy += COIN_GRAVITY;
			y += vy * dt;
		}
		else
		{
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->showPoint = false;
			this->SetState(COIN_STATE_DIE);
			this->y = 0;
			this->x = 0;
		}
	}
	// 1 micsbrick have a id to know which coin 
	// whenmario collis mics brick mario will return a value : id of micsbrick 
	// val isCheck : to know if the coin is check or not 
	// if coin is not check yet : bbox will be =0 , checked : bbox will 16 16 
	
	if ( mario->GetCoinID() == id  && mario->numberOfCoin== this->idCoinInBrick)
	{		
		if (isCheck == false)
		{		
			mario->showPoint = true;
			this->vy = (float)-0.15;
			y -= 16;
			isCheck = true;
			this->time = (float)GetTickCount64();	
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->point += 100;
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->coinNumber++;

		}
	}
}
