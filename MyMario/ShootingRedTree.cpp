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
	//DebugOut(L"%d\n", this->treeID);
	CGameObject::Update(dt, coObjects);
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float dMarioTree = mario->x - this->x;
	int timeActive = (int)((GetTickCount64() - time));
	//DebugOut(L"time = %d %f\n", timeActive% 5 , GetTickCount64() - time);	
	if (this->state == FLOWER_STATE_DIE)
	{
		x = 0; 
		y = 0;
		mario->treeNx = 0;
		mario->treeX = 0;
		mario->treeY = 0;
		mario->treeFireID = -1;

		return;
	}
	int y0=0, y1=0;
	if (x == 1815)
	{
		y0 = 187;
		y1=219;
	}
	else if (x==376)
	{
		y0= 175;
		y1= 219;
	}
	else if (x == 1880)
	{
		y0 = 175;
		y1 = 219;
	}
	if (y <= y0 )
		this->SetState(FLOWER_STATE_DOWN);
	else if (y >= y1)
		this->SetState(FLOWER_STATE_UP);
	if (state == FLOWER_STATE_UP)
	{
		this->y -= (float)0.3;
	}
	else if (state == FLOWER_STATE_DOWN)
		this->y += (float)0.3;
	
	
	if (abs(dMarioTree) < 200)
	{
		
		
		//DebugOut(L"%d	%f	%f\n", mario->treeFireID, mario->treeX, mario->treeY);
		if (dMarioTree < 0)
			nx = -1;
		else nx = 1;
		mario->treeNx = this->nx;
		if (x != 1815)
		{
			mario->treeFireID = this->treeID;
			mario->treeX = this->x + nx*10;
			mario->treeY = 170;
			
		}
	}

}

void ShootingRedTree::Render()
{
	int ani = FLOWER_ANI_LEFT;
	if (this->state == FLOWER_STATE_UP)
	{
		if (x == 1815)
			ani = FLOWER_ANI_EATER;
		else	if (this->nx <= 0)
			ani = FLOWER_ANI_LEFT;
		else
			ani = FLOWER_ANI_RIGHT;
	}
	else if (this->state == FLOWER_STATE_DOWN)
	{
		if (x == 1815)
			ani = FLOWER_ANI_EATER;
		else if (this->nx <= 0)
			ani = FLOWER_ANI_LEFT;
		else
			ani = FLOWER_ANI_RIGHT;
	}
	else if (this->state == FLOWER_STATE_DIE)
		ani = FLOWER_ANI_DIE;
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
