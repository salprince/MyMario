#pragma once
#include "MiniMario.h"
#include "Include.h"

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MINI_MARIO	1000
#define OBJECT_TYPE_BACKROUND	4
#define MAX_SCENE_LINE 1024
class MiniMapScene : public CScene
{

protected:
	vector<LPGAMEOBJECT> objects;
	MiniMario* miniMario = NULL;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	MiniMapScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	MiniMario* getMiniMario() { return miniMario; }
};

class MinimapSceneScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	MinimapSceneScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};


