#include "Grid.h"
#include <iostream>
#include "PlayScence.h"

void MyGrid::LoadFile(string path0)
{
	LPCWSTR path = ToLPCWSTR(path0);
	ifstream f;
	f.open(path);
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
	//tokens.insert(tokens.begin(), "99999");
	if(tokens.size() >=3)
		line.insert(0, "99999\t");
	ofstream MyFile;
	MyFile.open(resultpath, std::ios_base::app);
	MyFile << line << endl;
	MyFile.close();
}
void MyGrid::getMaxXY()
{

}