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
		width = 0;
		height = 0;
	}
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//1 micsbrick have a id to know which coin 
	// whenmario collis mics brick mario will return a value : id of micsbrick 
	// val isCheck : to know if the coin is check or not 
	// if coin is not check yet : bbox will be =0 , checked : bbox will 16 16 
	if ( ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID() == id)
	{
		if (isCheck == false)
		{
			width = 16;
			height = 10;
			y -= 16;
			isCheck = true;
		}
	}
}
