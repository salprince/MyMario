#include "MiniMario.h"

void MiniMario::getMiniX(int i)
{
	switch (i)
	{
		case 0:miniX = 2; break;
		case 1:case 2: case 11: case 12: case 13: miniX = 4; break;
		case 3: case 8:case 9 :case 15 :case 16:  miniX = 8; break;
		case 4:case 7: miniX = 10; break;
		case 5: case 6:miniX = 12; break;
		case 10: case 14: case 17:miniX = 6; break;
	}
}
void MiniMario::getMiniY(int i)
{
	switch (i)
	{
	case 0:case 1:case 6: case 7:case 8: miniY = 3; break;
	case 2:case 3:case 4:case 5: miniY = 1; break;
	case 9:case 10: case 11: miniY = 5; break;
	case 12: case 16:case 17: miniY = 7; break;
	case 13:case 14:case 15:  miniY = 9; break;
	}
}
void MiniMario::Update()
{
	getMiniX(point);
	getMiniY(point);
	this->x = miniX * 16 + 70;
	this->y = (miniY-1) * 16 + 70;
}

