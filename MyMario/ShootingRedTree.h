#include "GameObject.h"
#include "Fire.h"
#define FLOWER_UP_SPEED 0.04f;
#define FIRE_SPEED 0.04f;

#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 15

#define FLOWER_STATE_UP 100
#define FLOWER_STATE_DOWN 200
#define FLOWER_STATE_DIE 300
#define FLOWER_STATE_ATTACK 300


#define FLOWER_ANI_LEFT 0
#define FLOWER_ANI_RIGHT 1

class ShootingRedTree : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	ShootingRedTree();
	double time = 0;
	virtual void SetState(int state);
	int treeID = -1;
};
