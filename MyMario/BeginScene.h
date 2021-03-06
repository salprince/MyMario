#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Include.h"

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
#define OBJECT_TYPE_RED_ARROW		11
#define OBJECT_TYPE_CHIMNEY_PORTAL	49
#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024
class BeginScene : public CScene
{
protected:
	CMario* player=NULL;					// A play scene has to have player, right? 
	CMario* player1=NULL;
	vector<LPGAMEOBJECT> objects;
	RedArrowBeginScene* redArrow = NULL;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);



public:
	BeginScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	RedArrowBeginScene* getArrow() { return redArrow; }
	CMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class BeginScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	BeginScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};


