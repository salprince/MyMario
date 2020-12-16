#include "backRound.h"
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16
void backRound::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void backRound::GetBoundingBox(float& l, float& t, float& r, float& b)
{	
	l = t = r = b = 0;
}
void backRound::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"is Annimation %d\n", isAnimation);
	if (beginTime == 0)
		beginTime = (float)GetTickCount64();
	float t = GetTickCount64() - beginTime;
	switch (isAnimation)
	{
		case 1:
		{
			if ((t< 1000))
				y -= (float)3.7; 
			break;
		}
		case 2:
		{
			if (t>6000 && t<7000)
				y += (float)3.7;
			break;
		}
	}
	
}

