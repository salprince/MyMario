#include "MovableBrick.h"
#include "Include.h"
void MovableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}

void MovableBrick::Render()
{
	int ani = MOVE_BRICK_ANI_ALIVE;
	if (state == MOVE_BRICK_STATE_DIE) {
		ani = MOVE_BRICK_ANI_DIE;
	}
	animation_set->at(ani)->Render(x, y);
}

void MovableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MOVE_BRICK_STATE_DIE)
	{
		x = 0;
		y = 0;
	}

}
void MovableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int l = 20;
	if (x <= 100)
		x++;
	else if (x >= 200)
		x--;
}