#pragma once
#include "GameObject.h"
//#pragma warning(disable:28159) 
#define MARIO_WALKING_SPEED				0.08f
//0.1f
#define MARIO_JUMP_SPEED_Y				0.25f
#define MARIO_JUMP_DEFLECT_SPEED		0.2f
#define MARIO_GRAVITY					0.0017f
#define MARIO_STOP_ACCELERATION			0.003f
#define MARIO_ACCELERATION				/*0.00025f*/	0.00019f
#define MARIO_DIE_DEFLECT_SPEED			0.5f
#define MARIO_MAX_WALKING_SPEED			0.16f
#define MARIO_MAX_RUNNING_SPEED			0.32f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_RUN				300
#define MARIO_STATE_JUMP			400
#define MARIO_STATE_JUMP_WAVE_TAIL	450
#define MARIO_STATE_FLY				500
#define MARIO_STATE_HOLD				600
#define MARIO_STATE_SHOOTING				700
#define MARIO_STATE_DIE				1000


#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7

#define MARIO_ANI_BIG_RUNNING_RIGHT			9
#define MARIO_ANI_BIG_RUNNING_LEFT			11
#define MARIO_ANI_BIG_BRAKE_RIGHT			10
#define MARIO_ANI_BIG_BRAKE_LEFT			12
#define MARIO_ANI_BIG_JUMPING_LEFT			14
#define MARIO_ANI_BIG_JUMPING_RIGHT			13

#define MARIO_ANI_TAIL_STATIC				15
#define MARIO_ANI_TAIL_IDLE_RIGHT			17
#define MARIO_ANI_TAIL_IDLE_LEFT			16
#define MARIO_ANI_TAIL_WALKING_RIGHT		18
#define MARIO_ANI_TAIL_WALKING_LEFT			19
#define MARIO_ANI_TAIL_BRAKE_RIGHT			23
#define MARIO_ANI_TAIL_BRAKE_LEFT			22
#define MARIO_ANI_TAIL_JUMPING_LEFT			20
#define MARIO_ANI_TAIL_JUMPING_RIGHT		21
#define MARIO_ANI_TAIL_FLYING_LEFT			24
#define MARIO_ANI_TAIL_FLYING_RIGHT			25
#define MARIO_ANI_TAIL_RUNNING_LEFT			26
#define MARIO_ANI_TAIL_RUNNING_RIGHT		27

#define MARIO_ANI_SMALL_BRAKE_LEFT			29
#define MARIO_ANI_SMALL_BRAKE_RIGHT			28
#define MARIO_ANI_SMALL_JUMPING_LEFT		31
#define MARIO_ANI_SMALL_JUMPING_RIGHT		30

#define MARIO_ANI_TAIL_IS_JUMPING_LEFT		32
#define MARIO_ANI_TAIL_IS_JUMPING_RIGHT		33
#define MARIO_ANI_TAIL_SPIN_LEFT			34
#define MARIO_ANI_TAIL_SPIN_RIGHT			35

#define MARIO_ANI_FIRE_IDLE_LEFT			37
#define MARIO_ANI_FIRE_IDLE_RIGHT			38
#define MARIO_ANI_FIRE_WALKING_LEFT			39
#define MARIO_ANI_FIRE_WALKING_RIGHT		40
#define MARIO_ANI_FIRE_RUNNING_LEFT			41
#define MARIO_ANI_FIRE_RUNNING_RIGHT		42
#define MARIO_ANI_FIRE_BRAKE_LEFT			43
#define MARIO_ANI_FIRE_BRAKE_RIGHT			44
#define MARIO_ANI_FIRE_JUMPING_LEFT			45
#define MARIO_ANI_FIRE_JUMPING_RIGHT			46

#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_LEFT	47		
#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_RIGHT		48
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT	49		
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT	50
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT	51		
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT	52

#define MARIO_ANI_FIRE_SHOOTING_LEFT			54
#define MARIO_ANI_FIRE_SHOOTING_RIGHT			53

#define GREEN_MARIO_ANI_BIG_IDLE_LEFT			55
#define GREEN_MARIO_ANI_BIG_IDLE_RIGHT			56
#define GREEN_MARIO_ANI_BIG_WALK_LEFT			57
#define GREEN_MARIO_ANI_BIG_WALK_RIGHT			58
#define GREEN_MARIO_ANI_BIG_RUN_LEFT			59
#define GREEN_MARIO_ANI_BIG_RUN_RIGHT			60
#define GREEN_MARIO_ANI_BIG_SIT_LEFT			61
#define GREEN_MARIO_ANI_BIG_SIT_RIGHT			62
#define GREEN_MARIO_ANI_BIG_JUMP_LEFT			63
#define GREEN_MARIO_ANI_BIG_JUMP_RIGHT			64
#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_TAIL	3
#define	MARIO_LEVEL_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_COLLISION_GATE 0
#define MARIO_COLLISION_GOOMBA 1
#define MARIO_COLLISION_BRICK 2
#define MARIO_COLLISION_BACKROUND 3
#define MARIO_COLLISION_COLORBRICK 4
#define MARIO_COLLISION_COIN 5
#define MARIO_COLLISION_KOOPA 6
#define MARIO_COLLISION_MICSBRICK 7
#define MARIO_COLLISION_LEVELMUSHROOM 8
#define MARIO_COLLISION_BLUE_P 13
#define MARIO_COLLISION_BREAK_BRICK 14
#define MARIO_COLLISION_CHIMNEYPORTAL 49
#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	bool isJump = false;
	bool isFly = false;
	bool isOnSky = false;
	bool isSpin = false;
	bool isHold = false;
	bool isFire = false;
	int coinID = 0;

public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void BeginSceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void PlaySceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	float acceleration = 0;
	bool readyToHoldKoopas = false;
	void SetState(int state);
	float relativeDistanceMarioKoopa = 0;
	void SetLevel(int l) { level = l; }
	int getLevel() { return level; }
	int getUntouchable() { return untouchable; }
	int spining = 0;
	void StartSpinning() { spining= (int)GetTickCount64(); }
	void StartUntouchable() { untouchable = 1; untouchable_start = (int)GetTickCount64(); }
	bool isJumping() { return this->isJump; }
	void setJumping(bool jump) { this->isJump = jump; }
	bool isFlying() { return isFly; }
	void setFlying(bool value) { this->isFly = value; }
	void setIsOnSky(bool value) { isOnSky = value; }
	bool getIsOnSky() { return isOnSky; }
	void setIsSpin(bool value) { isSpin = value; }
	bool getIsSpin() { return this->isSpin; }
	void setIsHold(bool value) {isHold = value;}
	bool getIsHold() { return isHold; }
	void setIsFire(bool value) { isFire = value; }
	bool getIsFire() { return isFire; }
	void Reset();
	int GetCoinID() { return coinID; };
	int FireID = 1;
	//tiemshotting toset ani for mario 
	int timeShooting = 0;
	int timeFlying = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int color = 1;
	float beginTime = 0;
	float highJump = 0;
	bool isHoldJump = false;
	bool canJump = true;
	//show text point
	bool showPoint = false;
	float Tx = 0;
	float Ty = 0;
};