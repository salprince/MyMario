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
	CGameObject::Update(dt);
	//1 micsbrick have a id to know which coin 
	// whenmario collis mics brick mario will return a value : id of micsbrick 
	// val isCheck : to know if the coin is check or not 
	// if coin is not check yet : bbox will be =0 , checked : bbox will 16 16 
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetCoinID() == id)
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
