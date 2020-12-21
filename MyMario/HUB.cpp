#include "HUB.h"
#include "PlayScence.h"
#include "HUB.h"
#include "PlayScence.h"
void MyHUB::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HUB_WIDTH;
	bottom = y + HUB_HEIGHT;
}

void MyHUB::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	float cx, cy;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	if (cx < 15)
		x = 15;
	else if (cy > 100)
	{
		
		x = round(cx-154);
		cy += game->GetScreenHeight() / 2;
		y = round(cy);
	}	
	else if (cy > game->GetScreenHeight() / 2)
	{
		x = round(cx);
		cy += game->GetScreenHeight() /2;
		y = round(cy);
	}
	else
	{
		x = round(cx);
		cy += game->GetScreenHeight()/2+40;
		y = round(cy);
	}
	//DebugOut(L"cx cy %f %f\n", cx, cy);
	
}

void MyHUB::Render()
{
	int ani = GOOMBA_ANI_WALKING_LEFT;
	animation_set->at(ani)->Render(x, y);
}

void MyHUB::SetState(int state)
{
	CGameObject::SetState(state);

}

