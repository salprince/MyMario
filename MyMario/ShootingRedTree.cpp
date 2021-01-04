#pragma once
#include "ShootingRedTree.h"
#include "Include.h"
ShootingRedTree::ShootingRedTree()
{
	treeFire = new Fire();
	treeFire->x = -15;
	treeFire->y = -15;

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
	if (this->treeFire->isFiring == false)
	{
		if (dMarioTree <= 50 && dMarioTree >= 0)
			this->FireActive(this->nx);
	}
	//else this->FireReset();
	if (dMarioTree <= 80 && dMarioTree >= 0)
		this->y--;
	else if (dMarioTree < 0 && dMarioTree >= -80)
		this->y++;
	

}

void ShootingRedTree::Render()
{
	int ani = FLOWER_ANI_UP_LEFT;
	animation_set->at(ani)->Render(x, y);
}

void ShootingRedTree::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_UP:
		break;

	}
}
