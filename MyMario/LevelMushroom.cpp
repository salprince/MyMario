#include "LevelMushroom.h"

void LevelMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
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
