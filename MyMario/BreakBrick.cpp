#include "BreakBrick.h"
#include "Include.h"
void BreakBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
	if (state == BREAK_BRICK_STATE_DIE)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void BreakBrick::Render()
{
	int ani = BREAK_BRICK_ANI_ALIVE;
	if (state == BREAK_BRICK_STATE_COIN) {
		ani = BREAK_BRICK_ANI_COIN;
	}
	else if (state == BREAK_BRICK_STATE_DIE) {
		ani = BREAK_BRICK_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void BreakBrick::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == BREAK_BRICK_STATE_DIE)
	{
		width = 0;
		height = 0;
	}
	if (state == BREAK_BRICK_STATE_COIN)
	{
		width = 5;
		height = 5;
	}
}
void BreakBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	
	// 1 micsbrick have a id to know which coin 
	// whenmario collis mics brick mario will return a value : id of micsbrick 
	// val isCheck : to know if the coin is check or not 
	// if coin is not check yet : bbox will be =0 , checked : bbox will 16 16 
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID() == id)
	{
		if (isCheck == false)
		{
			this->SetState(BREAK_BRICK_STATE_COIN);
			isCheck =true;
		}
	}
}
