#include "Grid.h"
#include <iostream>
#include "PlayScence.h"

void MyGrid::LoadFile(string path0)
{
	LPCWSTR path = ToLPCWSTR(path0);
	ifstream f;
	f.open(path);
	resultpath = path0.insert(0, "GRID_");
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		
		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") 
		{
			ofstream MyFile;
			MyFile.open(resultpath);
			MyFile << "[TEXTURES]" << endl;
			MyFile.close();
			section = SCENE_SECTION_TEXTURES; continue; 
		}
		if (line == "[SPRITES]") 
		{
			ofstream MyFile;
			MyFile.open(resultpath, std::ios_base::app);
			MyFile << "[SPRITES]" << endl;
			MyFile.close();
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") 
		{
			ofstream MyFile;
			MyFile.open(resultpath, std::ios_base::app);
			MyFile << "[ANIMATIONS]" << endl;
			MyFile.close();
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") 
		{
			ofstream MyFile;
			MyFile.open(resultpath, std::ios_base::app);
			MyFile << "[ANIMATION_SETS]" << endl;
			MyFile.close();
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") 
		{
			ofstream MyFile;
			MyFile.open(resultpath, std::ios_base::app);
			MyFile << "[OBJECTS]" << endl;
			MyFile.close();
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES:
		case SCENE_SECTION_SPRITES: 
		case SCENE_SECTION_ANIMATIONS: 
		case SCENE_SECTION_ANIMATION_SETS:	_ParseSection_NOT_OBJECT(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
}
void MyGrid::_ParseSection_NOT_OBJECT(string line)
{
	ofstream MyFile;
	MyFile.open(resultpath, std::ios_base::app);
	MyFile << line<<endl;
	MyFile.close();
}
void MyGrid::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	int gridX = -1, gridY = -1;
	
	
	
	if (tokens.size() >= 3)
	{
		int object_type = atoi(tokens[0].c_str());
		int x = (float)atof(tokens[1].c_str());
		int  y = (float)atof(tokens[2].c_str());
		if (x% 32 == 0)
			gridX = x/ 32;
		else gridX = x / 32 + 1;
		if (y % 32 == 0)
			gridY = y/ 32;
		else gridY = y / 32 + 1;
		if (object_type == OBJECT_TYPE_MOVE_BRICK)
		{
			int brickBlockId = atoi(tokens[4].c_str());
			int brickId = atoi(tokens[5].c_str());
			if (brickId == 0)
			{
				brickBlock = brickBlockId;
				moveBrick_GridX = gridX;
			}				
			gridX = moveBrick_GridX;
		}
		string s = std::to_string(gridX) + "\t" + std::to_string(gridY) + "\t";
		line.insert(0, s);
	}		
	ofstream MyFile;
	MyFile.open(resultpath, std::ios_base::app);
	MyFile << line << endl;
	MyFile.close();
}
void MyGrid::getMaxXY(int maxScreenX, int maxScreenY)
{
	if (maxScreenX % 32 == 0)
		this->maxX = maxScreenX / 32;
	else this->maxX = maxScreenX / 32 +1;
	if (maxScreenY % 32 == 0)
		this->maxY = maxScreenY / 32;
	else this->maxY = maxScreenY / 32 + 1;
}