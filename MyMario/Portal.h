#pragma once

#include "GameObject.h"
#define PORTAL_ANI_ALIVE	0
#define PORTAL_ANI_DIE	1

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	int width;
	int height;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	float time = 0;
	bool changeScene = false;
};