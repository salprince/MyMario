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
	/*l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y - BRICK_BBOX_WIDTH;*/
	l = t = r = b = 0;
}

