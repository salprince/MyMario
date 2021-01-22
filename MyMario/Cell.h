#pragma once
#include "GameObject.h"
#include "Utils.h"
using namespace std;
class Cell
{
public :
	int x;
	int y;
	vector <int> list;
	vector <int> GetVector() { return list; }
	Cell(){}
	Cell(int x, int y ,vector<int> v)
	{
		this->x = x;
		this -> y = y;
		this->list = v;
	}
};

