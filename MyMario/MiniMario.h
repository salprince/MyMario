#pragma once
#include "backRound.h"
#include <map> 
class MiniMario: public backRound
{
private:
	//change miniX into real x 
	//vd : miniX=0 -> real X=70 ...
	void getMiniX(int );
	void getMiniY(int);
public:
	void Update();
	int miniX = 0;
	int miniY = 1;
	bool canMove(int, int);
	//we have 17 point that mario can move to 
	//for 1 point we will have 2 coordinate x and y 
	// change point into x&y by func getMIniX get MiniY
	//point 0 mean mario is at point(2;3)
	int point = 0;
};


