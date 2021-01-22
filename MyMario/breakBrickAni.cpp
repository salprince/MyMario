#include "breakBrickAni.h"
//id form 1 ->5 : mario 
//id form 10->6 : for shooting red tree
void breakBrickAni::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
	this->marioHandle = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
}

void breakBrickAni::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (marioHandle->isSawBreakBrick)
	{		
		CGameObject::Update(dt, coObjects);
		vy += 0.005f;
		nx = 1;
		if (id == 1 || id == 4)
			nx = -1;
		if (id == 1 || id == 2)
			ny = -1;
		vx = nx * BBANI_FLYING_SPEED;
		vy += ny * BBANI_GRAVITY;
		x += dx;
		y += dy;
	}
	else
	{
		this->Reset();
		setPositionAfterMario(marioHandle->x, marioHandle->y, marioHandle->nx);
	}
	
}
void breakBrickAni::Render()
{
	int ani = BBANI_ANI_ALIVE;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void breakBrickAni::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BBANI_STATE_ALIVE:
		break;
	}
}
void breakBrickAni::Reset()
{
	this->SetState(BBANI_STATE_ALIVE);
	this->SetSpeed(0.0, 0.0);
	this->y = 500;
	this->ax = 0;
	this->ay = 0;
	this->dx = 0;
	this->dy = 0;
	this->nx = 0;
	this->ny = 0;
}