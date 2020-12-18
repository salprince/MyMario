#include "MiniMario.h"
void MiniMario::InitMap(map <int, int> m)
{
	mapXY[1] = 0;
	mapXY[4] = 3;
	mapXY[4] = 1;
	mapXY[8] = 1;
	mapXY[10] = 1;
	mapXY[12] = 1;
	mapXY[12] = 3;
	mapXY[10] = 3;
	mapXY[8] = 3;
	mapXY[8] = 5;
	mapXY[6] = 5;
	mapXY[4] = 5;
	mapXY[4] = 7;
	mapXY[4] = 9;
	mapXY[6] = 9;
	mapXY[8] = 9;
	mapXY[8] = 7;
	mapXY[6] = 7;
}
int MiniMario::getRealX(int x)
{
	int result = 0;
	switch (x)
	{
		case 2: result = 102; break;
		case 4:result = 134; break;
		case 8:result = 198; break;
		case 10: result = 230; break;
		case 12: result = 262; break;
	}
	return result;
}
int MiniMario::getRealY(int y)
{
	int result = 0;
	switch (y)
	{
	case 1:result = 70; break;
	case 3:result = 102; break;
	case 5: result = 134; break;
	case 7: result = 166; break;
	case 9: result = 198; break;
	}
	return result;
}
bool MiniMario::canMove(int x, int y)
{
	return true;	
}
void MiniMario::Update()
{
	
	this->x = getRealX(vtX[miniX]);
	this->y = getRealY(vtY[miniY]);
	DebugOut(L"x= %f y= %f\n", x, y);
	DebugOut(L"minix= %d miniy= %d\n", vtX[miniX], vtY[miniY]);
}

