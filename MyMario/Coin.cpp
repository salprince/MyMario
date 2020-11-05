#include "Coin.h"

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
