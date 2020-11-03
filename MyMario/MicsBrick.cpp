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
	if (state == MICSBRICK_ANI_ALIVE) {
		ani = MICSBRICK_ANI_ALIVE;
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
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"shell %d\n", isShell);
}