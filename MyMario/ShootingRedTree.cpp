#pragma once
#include "ShootingRedTree.h"
#include "Include.h"
ShootingRedTree::ShootingRedTree()
{
	this->time = (double)GetTickCount64();
	this->nx = 0;
	this->SetState(FLOWER_STATE_DOWN);
};
void ShootingRedTree::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOWER_BBOX_WIDTH;
	bottom = y + FLOWER_BBOX_HEIGHT;
}

void ShootingRedTree::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float dMarioTree = mario->x - this->x;
	int timeActive = (int)((GetTickCount64() - time));
	//DebugOut(L"time = %d %f\n", timeActive% 5 , GetTickCount64() - time);	
	if (y <= 175)
		this->SetState(FLOWER_STATE_DOWN);
	else if (y >= 230)
		this->SetState(FLOWER_STATE_UP);
	if (state == FLOWER_STATE_UP)
	{
		this->y-=0.5;
	}
			
	else if (state == FLOWER_STATE_DOWN)
		this->y+=0.5;
	//DebugOut(L"STATE = %d\n", state);
	/*if (this->treeFire->isFiring == false)
	{
		if (dMarioTree <= 50 && dMarioTree >= 0)
			this->FireActive(this->nx);
	}*/
	if (abs(dMarioTree) < 100)
	{
		if (dMarioTree < 0)
			nx = -1;
		else nx = 1;
	}

}

void ShootingRedTree::Render()
{
	int ani = FLOWER_ANI_LEFT;
	if (this->state == FLOWER_STATE_UP)
	{
		if (this->nx <= 0)
			ani = FLOWER_ANI_LEFT;
		else 
			ani = FLOWER_ANI_RIGHT;
	}
	else if (this->state == FLOWER_STATE_DOWN)
	{
		if (this->nx <= 0)
			ani = FLOWER_ANI_LEFT;
		else
			ani = FLOWER_ANI_RIGHT;
	}
	animation_set->at(ani)->Render(x, y);
}

void ShootingRedTree::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_UP:
		break;
	case FLOWER_STATE_DOWN:
		break;

	}
}
