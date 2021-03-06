#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "HUB.h"
#include "Koopas.h"
#include "Cell.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_BACKROUND	4
#define OBJECT_TYPE_COLORBRICK	5
#define OBJECT_TYPE_COIN	6
#define OBJECT_TYPE_MICSBRICK	7
#define OBJECT_TYPE_LEVELMUSHROOM	8
#define OBJECT_TYPE_GREEN_FLOWER	9
#define OBJECT_TYPE_FIRE			10
#define OBJECT_TYPE_HUB			11
#define OBJECT_TYPE_SHOOTING_RED_TREE		12
#define OBJECT_TYPE_BLUE_P		13
#define OBJECT_TYPE_BREAK_BRICK		14
#define OBJECT_TYPE_MOVE_BRICK		15
#define OBJECT_TYPE_BB_ANI		16
#define OBJECT_TYPE_CHIMNEY_PORTAL	49
#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

#define SCENE1_MAX_HEIGHT 2810
#define SCENE1_MIN_HEIGHT 15
class CPlayScene : public CScene
{
protected:
	CMario* player=nullptr;
	MyHUB* hub = nullptr;
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	vector < Cell* > cell;

public:
	CPlayScene(int id, LPCWSTR filePath, LPCWSTR filePathCell);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void LoadCell();
	CMario* GetPlayer() { return player; };
	MyHUB* GetHUB() { return hub; };
	float time = 0;
	long point = 0;
	int live = 4;
	int pointLevel = 0;
	int coinNumber = 0;
	vector <int> pointList = { 100,200,400,800,1000,2000,4000,8000 };
	bool isShowEndText = false;
	float switchSceneTime = 0;
	float cx = 0;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

