#pragma once
#include "ShootingRedTree.h"
#include "Include.h"
ShootingRedTree::ShootingRedTree()
{
	treeFire = new Fire();
	treeFire->x = -15;
	treeFire->y = -15;
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
void ShootingRedTree::FireActive(int nx)
{
	this->treeFire->x = this->x;
	this->treeFire->y = this->y;
	this->treeFire->ax = (float)0.05;
	this->treeFire->ay = (float)0.05;
	this->treeFire->vx  = FIRE_SPEED;
	this->treeFire->isFromTree = true;
}
void ShootingRedTree::FireReset()
{
	this->treeFire->x = -15;
	this->treeFire->y = -15;
	this->treeFire->ax =0;
	this->treeFire->ay =0;
	this->treeFire->vx =0;
	this->treeFire->isFromTree = false;
}
void ShootingRedTree::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float dMarioTree = mario->x - this->x;
	int timeActive = (int)((GetTickCount64() - time)/1000);
	//DebugOut(L"time = %d %f\n", timeActive% 5 , GetTickCount64() - time);
	if (timeActive %2 == 0)
	{
		if (state == FLOWER_STATE_UP)
			this->SetState(FLOWER_STATE_DOWN);
		else if (state == FLOWER_STATE_DOWN)
			this->SetState(FLOWER_STATE_UP);
	}
	else
	{
		if (state == FLOWER_STATE_UP)
		{
			this->y-=0.5;
		}
			
		else if (state == FLOWER_STATE_DOWN)
			this->y+=0.5;
	}
	//DebugOut(L"STATE = %d\n", state);
	if (this->treeFire->isFiring == false)
	{
		if (dMarioTree <= 50 && dMarioTree >= 0)
			this->FireActive(this->nx);
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
