#pragma once
//#include "PlayScence.h"
#include "main.cpp"
#include <algorithm>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <assert.h>
class Grid
{
public :
	int sceneID = 0;
	int numberX = 0;
	int numberY = 0;
	LPCWSTR sceneFilePath;
	const char* path = "../testScence.txt";
	//float width = SCREEN_WIDTH/2;
	//float height= SCREEN_HEIGHT / 2;
	Grid(int id, LPCWSTR sceneFilePath);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	virtual void Load();
};

