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
	if (state == MOVE_BRICK_STATE_FALL)
	{
	}

}
void MovableBrick::moveBlockBrick(int id, float x0,float x1)
{
	if (this->id == id)
	{
		if (x <= x0+ 16*relativePosition)
			nx = 1;
		else if (x >= x1 + 16 * relativePosition)
			nx = -1;
		if (this->nx < 0)
			x-=0.5;
		else if(this->nx >0)
			x+=0.5;
	}

}
void MovableBrick::fallBlockBrick(int id)
{
	if (this->id == id)
	{
		if (!isActive)
			isActive = true;
		x = round(x);
		y+=0.5;
		nx = 0;
	}
}
void MovableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario= ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	/*if (isActive == true)
		fallBlockBrick(id);*/
	if (mario->moveBrickID != -1)
		fallBlockBrick(mario->moveBrickID);
	else
	{
		if (isActive == true)
			fallBlockBrick(id);
		else moveBlockBrick(1, x0, x1);
	}
		
	
}