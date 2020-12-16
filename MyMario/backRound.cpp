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
	if (isAnimation == 1)
	{
		if(beginTime==0)
			beginTime = (float)GetTickCount64();
		if ((GetTickCount64() - beginTime < 1000))
		{
			y -= (float)3.7;
		}

	}
}

