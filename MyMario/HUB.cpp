#include "HUB.h"
#include "PlayScence.h"
#include "HUB.h"
#include "PlayScence.h"
void MyHUB::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = 0;
	top = 0;
	right = 0 + HUB_WIDTH;
	bottom = 0 + HUB_HEIGHT;
}

void MyHUB::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects)
{
	//update position of HUD
	if (isMove && ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetState()!= MARIO_STATE_DIE)
	{
		float cx, cy;
		CMario* player = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		player->GetPosition(cx, cy);
		CGame* game = CGame::GetInstance();
		cx -= game->GetScreenWidth() / 2;
		cy -= game->GetScreenHeight() / 2;
		if (cx < 15)
		{
			this->x = 15;
			this->y = 260;
		}
		else if (cy < -140)
		{
			this->x = round(player->x - game->GetScreenWidth() / 2);
			this->y = (float)round(-140 + game->GetScreenHeight() + -40);
		}
		else
		{
			this->x = round(player->x - game->GetScreenWidth() / 2);
			this->y = 260;
		}	

		if (player->y > 250)
		{
			this->y = 525;
			this->x = (float)2350 - game->GetScreenWidth() / 2;
		}
	}
	
	//update point and time to HUD
	this->time = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->time;
	this->timeText = std::to_string(SCENCE1_TIME - (int)(GetTickCount64() / 1000 - time / 1000));
	//process to change point of scence to string 
	//this is the way I can thinking to 
	int tempPoint= ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->point;
	pointText = "";
	for (int i = 0; i < (int)(6 - std::to_string(tempPoint).size()); i++)
		this->pointText += "0";
	this->pointText += std::to_string(tempPoint);	
	//process to show speech of mario 
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (abs(mario->vx) >= 0 && abs(mario->vx) <= 0.01)
		levelSpeech = 0;
	else if (abs(mario->vx) > 0.01 && abs(mario->vx) <= 0.06)
		levelSpeech = 1;
	else if (abs(mario->vx) >0.03  && abs(mario->vx) <= 0.06)
		levelSpeech = 2;
	else if (abs(mario->vx) > 0.06 && abs(mario->vx) <= 0.09)
		levelSpeech = 3;
	else if (abs(mario->vx) > 0.09 && abs(mario->vx) <= 0.12)
		levelSpeech = 4;
	else if (abs(mario->vx) > 0.12 && abs(mario->vx) < 0.15)
		levelSpeech = 5;
	else if (abs(mario->vx) >= 0.15 && abs(mario->vx) <= 0.36)
		levelSpeech = 6;
	if(mario->getIsOnSky() || mario->isFlying())
		levelSpeech = 0;
}
void MyHUB::renderText(string s,int x, int y)
{
	for (int i = 0; i < (int)s.size(); i++)
	{
		int acsiiCode = static_cast<int>(s[i]);
		if (acsiiCode >= 48 && acsiiCode <= 57)
			animation_set->at(acsiiCode- 29)->Render((float)(x +i*8), (float)y);
		else if (acsiiCode >= 65 && acsiiCode <= 90)
			animation_set->at(acsiiCode - 36)->Render((float)(x + i * 8), (float)y);
	}
}
void MyHUB::renderSpeech( int number,int x, int y)
{
	for (int i =0 ; i < number; i++)
		animation_set->at(HUB_ANI_WHITE_ARROW)->Render((float)x + i*8, (float)y );
}
void MyHUB::renderCard(int type, int x, int y)
{
	animation_set->at(type)->Render((float)x , (float)y);
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
	//render level 1 
	animation_set->at(HUB_ANI_NUMBER_1)->Render(x +39, y +8);
	//render black arrow 
	for(int i=0 ; i <6; i++)
		animation_set->at(HUB_ANI_BLACK_ARROW)->Render(x + 54+8*i, y + 8);
	animation_set->at(HUB_ANI_BLACK_P)->Render(x + 104, y + 8);	
	renderSpeech(levelSpeech, (int)x + 54, (int)y + 8);
	//render scence time 
	renderText(timeText, (int)x+125, (int)y+16);
	//render live of mario 
	renderText(std::to_string(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->live), (int )x + 38, (int)y + 16);
	//render number of coin - which mario have 
	renderText(std::to_string(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->coinNumber), (int)x + 133, (int)y + 8);
	renderText(pointText, (int)x + 54, (int)y + 16);
	if(((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->isShowEndText )
		animation_set->at(HUB_ANI_FRAME_CARD_STAR)->Render(x + 165, y);

}

void MyHUB::SetState(int state)
{
	CGameObject::SetState(state);

}

