#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "PlayScence.h"
#include <map>
#include "Cell.h"
using namespace std;
class MyGrid
{
public :
	int gridX = -1;
	int gridY = -1;
	int maxX = -1;
	int maxY = -1;
	int gridWidth = 32;
	string resultpath = "RESULT.txt";
	string cellpath = "CELL.txt";
	string cellpath1 = "CELL.txt";
	void LoadFile(string path0);
	void _ParseSection_NOT_OBJECT(string line);
	void _ParseSection_OBJECTS(string line);
	void getMaxXY(int maxScreenX, int maxScreenY);
	void loadCell();
	void writeCellFinal();
	int moveBrick_GridX = -1, brickBlock = -1;
	int objectCount = 0;
	vector < Cell* > cell;
};

