#pragma once
#include "backRound.h"
#include <map> 
class MiniMario: public backRound
{
private:
	//change miniX into real x 
	//vd : miniX=0 -> real X=70 ...
	int getRealX(int );
	int getRealY(int);
	

public:
	void Update();
	void InitMap(map<int, int>);
	//this is the position in vector 
	map <int, int> mapXY;
	int miniX = 0;
	int miniY = 1;
	bool canMove(int, int);
	vector<int> vtX = { 2,4,8,10,12 };
	vector<int> vtY = { 1,3,5,7,9};
};

