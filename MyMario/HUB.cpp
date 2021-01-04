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
	/*float cx, cy;
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
		y = round(cy-5);
	}	
	else if (cy > game->GetScreenHeight() / 2)
	{
		x = round(cx);
		cy += game->GetScreenHeight() /2;
		y = round(cy-5);
	}
	else
	{
		x = round(cx);
		cy += game->GetScreenHeight()/2+40;
		y = round(cy-5);
	}
	//DebugOut(L"cx cy %f %f\n", cx, cy);*/
	
}

void MyHUB::Render()
{
	animation_set->at(HUB_ANI_BLACK_BACKROUND)->Render(x - 15, y);
	animation_set->at(HUB_ANI_NORMAL)->Render(x, y);
	//render 3 frame card 
	animation_set->at(HUB_ANI_FRAME_CARD)->Render(x+164, y);
	animation_set->at(HUB_ANI_FRAME_CARD)->Render(x + 164 +24, y);
	animation_set->at(HUB_ANI_FRAME_CARD)->Render(x + 164 +48, y);
	//render M letter
	animation_set->at(HUB_ANI_M_LETTER)->Render(x+5, y+16);
	//nextto M letter
	animation_set->at(HUB_ANI_NUMBER_0)->Render(x + 38, y + 16);
	//render level 1 
	animation_set->at(HUB_ANI_NUMBER_1)->Render(x +39, y +8);
	//render black arrow 
	for(int i=0 ; i <6; i++)
		animation_set->at(HUB_ANI_BLACK_ARROW)->Render(x + 54+8*i, y + 8);
	animation_set->at(HUB_ANI_BLACK_P)->Render(x + 104, y + 8);
	
	
}

void MyHUB::SetState(int state)
{
	CGameObject::SetState(state);

}

