#include "RedArrowBeginScene.h"
#include "Include.h"
void RedArrowBeginScene::Update()
{
	if (beginTime == 0)
		beginTime = (float)GetTickCount64();
	Time = GetTickCount64() - beginTime;
	if(Time>7000)
		this->x = 145;	
	if (this->level == 0)
		this->y = 195;
	else 
		this->y = 215;
}