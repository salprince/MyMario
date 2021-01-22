#include "Grid.h"

void MyGrid::LoadFile(string path0)
{
	//get max line 
	this->getMaxXY(this->maxX, this->maxY);
	//path0=path0.insert(0, "GRID_");
	LPCWSTR path = ToLPCWSTR(path0);
	ifstream f;
	f.open(path);
	resultpath = path0.insert(0, "GRID_");
	cellpath = path0.insert(0, "CELL_");
	cellpath1 = path0.insert(0, "CELL_FINAL_");
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
	this->loadCell();
	this->writeCellFinal();
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
	if (tokens.size() < 3)
		return;
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
	ofstream MyFile;
	MyFile.open(resultpath, std::ios_base::app);
	MyFile << line << endl;
	MyFile.close();


	ofstream MyCellFile;
	MyCellFile.open(cellpath, std::ios_base::app);
	MyCellFile << gridX<<"\t"<<gridY<<"\t"<<objectCount << endl;
	MyCellFile.close();
	objectCount++;
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
void MyGrid::loadCell()
{
	ifstream MyCellFile;
	MyCellFile.open(cellpath);
	char str[MAX_SCENE_LINE];
	//DebugOut(L"{READFILE CELL} %d %d\n", cell.size(), cell[0].size());
	//DebugOut(L"{READFILE CELL} %d %d\n", maxX, maxY);
	/*vector <int> temp;
	temp.push_back(0);
	cell.push_back(new Cell(0, 0, temp));*/
	while (MyCellFile.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		int objectX= atoi(tokens[0].c_str());
		int objectY = atoi(tokens[1].c_str());
		int objectNum = atoi(tokens[2].c_str());
		int flag = 0;
		for (int i = 0; i < cell.size(); i++)
		{
			if (cell[i]->x == objectX && cell[i]->y == objectY)
			{
				cell[i]->list.push_back(objectNum);
				flag = 1;
				break;
			}
		}
		if(flag==0)
		{
			vector <int> temp;
			temp.push_back(objectNum);
			cell.push_back(new Cell(objectX,objectY,temp));
			//cell[0]->list.push_back(objectNum);
		}
	}
	
	MyCellFile.close();
}
void MyGrid::writeCellFinal()
{
	ofstream MyCellFile;
	MyCellFile.open(cellpath1);
	MyCellFile << endl;
	MyCellFile.close();
	MyCellFile.open(cellpath1, std::ios_base::app);
	for (int i = 0; i < cell.size(); i++)
	{
		MyCellFile << cell[i]->x << "\t" << cell[i]->y << "\t" ;
		for (int j = 0; j < cell[i]->list.size()-1; j++)
			MyCellFile << cell[i]->list[j] << "\t";
		MyCellFile << cell[i]->list[cell[i]->list.size() - 1] << "\n";
		//MyCellFile << 1 << endl;
	}
	
	MyCellFile.close();
	objectCount++;
}