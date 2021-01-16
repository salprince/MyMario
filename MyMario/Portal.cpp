#include "Portal.h"
#include "Game.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = (int)(r - l + 1);
	height = (int)(b - t + 1);
}
void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->time != 0)
	{
		if ((GetTickCount64() - time) > 2000)
			CGame::GetInstance()->SwitchScene(GetSceneId());
	}
}
void CPortal::Render()
{
	int ani = PORTAL_ANI_ALIVE;
	if (time != 0)
		ani = PORTAL_ANI_DIE;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();

}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}