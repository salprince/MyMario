#include "backRound.h"
void backRound::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void backRound::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = 0 ;
	b = 0;
}