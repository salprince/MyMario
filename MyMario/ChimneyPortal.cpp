#include "ChimneyPortal.h"
#include "PlayScence.h"
ChimneyPortal::ChimneyPortal()
{
	
}

void ChimneyPortal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->portalTime != 0)
	{
		left = top=right = bottom = 0;
	}
}


void ChimneyPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
}
void ChimneyPortal::Render()
{
	//animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void ChimneyPortal::SetState(int state)
{
	CGameObject::SetState(state);
	
}