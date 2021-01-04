#include "MicsBrick.h"
void MicsBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
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
}

void MicsBrick::SetState(int state)
{
	CGameObject::SetState(state);
}
void MicsBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//x += dx;
	//y += dy;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (state != MICSBRICK_ANI_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)	{
		
	}
	else
	{
		

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"shell %d\n", isShell);
}