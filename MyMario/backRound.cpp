#include "backRound.h"
#include "Utils.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
void backRound::Render()
{
	animation_set->at(0)->Render(x, y);
	if(isColorBackround==2 && Time >6000)
		animation_set->at(1)->Render(x, y);
	//RenderBoundingBox();
}

void backRound::GetBoundingBox(float& l, float& t, float& r, float& b)
{	
	l = t = r = b = 0;
}
void backRound::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (beginTime == 0)
		beginTime = (float)GetTickCount64();
	Time = GetTickCount64() - beginTime;
	switch (isAnimation)
	{
		//case 1 is brick _ flying from bottom to top
		case BACKROUND_TYPE_GO_UP:
		{
			if ((Time < 1000))
				y -= (float)3.7; 
			break;
		}
		//case 2 is object which fly from top to bottom
		case BACKROUND_TYPE_GO_DOWN:
		{
			if (Time > 6000 && Time < 7035)
			{
				y += (float)3.7;
			}

			y = round(y);
			break;
		}
		case BACKROUND_TYPE_CAN_HIDE:
		{
			if (Time < 6000)
				this->y = -150;
			else this->y = start_y;
			break;
		}
	}
	x = round(x);
	
}

