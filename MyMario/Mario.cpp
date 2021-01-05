#include "Include.h"


CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}
void CMario::BeginSceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (this->beginTime == 0)
		this->beginTime =(float) GetTickCount64();
	float t = GetTickCount64() - beginTime;
	//vy += (float)(MARIO_GRAVITY * 1.25);
	
	if (t < 800)
	{
		this->x = -50;
	}
	else if (t > 800 && t < 850)
	{
		this->y = 180;
	}
	else if (t > 850 && t < 1500)
	{
		if (color == 2)
		{
			this->x = 15;
			this->SetState(MARIO_STATE_WALKING_RIGHT);
			vx = (float)MARIO_MAX_WALKING_SPEED;
		}
			
		else
		{
			this->x = 384;
			this->SetState(MARIO_STATE_WALKING_LEFT);
			vx = (float)MARIO_MAX_WALKING_SPEED;
		}
			
	}
	else if (t > 1500 && t < 3000)
	{
		switch (color)
		{
			case 1:
			{
				//red mario 
				this->SetState(MARIO_STATE_WALKING_LEFT);
				//this->x -= 1.5;
				vx =- (float)(MARIO_MAX_WALKING_SPEED/1.5);
				break;
			}
			case 2 :
			{
				//green mario 				
				this->SetState(MARIO_STATE_WALKING_RIGHT);
				vx = (float)MARIO_MAX_WALKING_SPEED/3;
				//this->x += 1.5;
				break;
			}
		}						
	}		
	else if (t > 3000 && t < 4000)
	{
		switch (color)
		{
			case 1:
			{
				break;
			}
			case 2:
			{
				//green mario 				
				this->SetState(MARIO_STATE_JUMP);
				vx = (float)(MARIO_MAX_WALKING_SPEED/1.5);
				vy -= (float)0.03;
				break;
			}
		}
	}
	else if (t > 4000 && t < 5000)
	{
		switch (color)
		{
			case 1:
			{
				break;
			}
			case 2:
			{
				//green mario 		
				if(vy <0)
					this->SetState(MARIO_STATE_JUMP);
				else 
					this->SetState(MARIO_STATE_IDLE);
				vx = (float)(MARIO_MAX_WALKING_SPEED/1.5);
				vy-= (float)(MARIO_GRAVITY * 1.25);
				vy += (float)0.03;
				break;
			}
		}
	}
	else if (t > 5000 && t < 6000)
	{
		switch (color)
		{
			case 1:
			{
				break;
			}
			case 2:
			{
				//green mario 		
				this->SetState(MARIO_STATE_WALKING_RIGHT);
				vx = (float)(MARIO_MAX_WALKING_SPEED /1.5);
				break;
			}
		}
	}
	else
	{
		vx = 0;		
		this->SetState(MARIO_STATE_IDLE);
	}

}
void CMario::PlaySceneUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MARIO_STATE_WALKING_RIGHT || state == MARIO_STATE_WALKING_LEFT)
	{
		if (vx > MARIO_MAX_WALKING_SPEED)
			vx = MARIO_MAX_WALKING_SPEED;
		else if (vx < -MARIO_MAX_WALKING_SPEED)
			vx = -MARIO_MAX_WALKING_SPEED;
		else
		{
			vx += ((int)nx) * (MARIO_ACCELERATION * dt);
		}
		if (abs(vx) >= MARIO_MAX_WALKING_SPEED - 0.05)
			this->SetState(MARIO_STATE_RUN);
	}
	else if (state == MARIO_STATE_IDLE)
	{
		if (vx > MARIO_STOP_ACCELERATION / 2)
		{
			vx = vx - abs(vx / 5);
		}
		else if (vx < -MARIO_STOP_ACCELERATION / 2)
		{
			vx = vx + abs(vx / 5);
		}
		else
		{
			vx = 0;
		}
	}

	if (getLevel() == MARIO_LEVEL_TAIL && spining != 0)
	{
		if (GetTickCount64() - spining >= 200)
			setIsSpin(false);
	}
	else if (getLevel() == MARIO_LEVEL_FIRE && timeShooting != 0)
	{
		setIsFire(false);
		if (GetTickCount64() - timeShooting >= 100)
			timeShooting = 0;
	}
	/*else if (getLevel() == MARIO_LEVEL_TAIL && timeFlying != 0)
	{
		if (GetTickCount() - timeFlying >= 200)
			setFlying(false);
	}*/
	else
	{
		spining = 0;
		timeShooting = 0;
		timeShooting = 0;

	}

	if (getIsHold())
		SetState(MARIO_STATE_HOLD);
}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	//DebugOut(L" type scence %d \n", CGame::GetInstance()->GetCurrentScene()->typeScene);
	CGameObject::Update(dt);
	if (!getIsOnSky())
		vy += MARIO_GRAVITY * dt;
	else
		vy += (float)(MARIO_GRAVITY * 1.25);
	//make mario cant move out of left border 
	if (vx < 0 && x < 15) x = 15;
	if (vx > 0 && x > 2810) x = 2810;
	if (vy < 0 && y < -120) y = -120;
	//DebugOut(L"%f %f \n",vy , y);
	if (CGame::GetInstance()->GetCurrentScene()->typeScene == 0)
	{
		BeginSceneUpdate(dt);
	}
	else
	{
		PlaySceneUpdate(dt);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

			LPCOLLISIONEVENT e = coEventsResult[i];

			//seting state of collision
			int stateCollision = -1;
			if (dynamic_cast<CGoomba*>(e->obj))
				stateCollision = MARIO_COLLISION_GOOMBA;
			else if (dynamic_cast<CPortal*>(e->obj))
				stateCollision = MARIO_COLLISION_GATE;
			else if (dynamic_cast<CBrick*>(e->obj))
				stateCollision = MARIO_COLLISION_BRICK;
			else if (dynamic_cast<backRound*>(e->obj))
				stateCollision = MARIO_COLLISION_BACKROUND;
			else if (dynamic_cast<ColorBrick*>(e->obj))
				stateCollision = MARIO_COLLISION_COLORBRICK;
			else if (dynamic_cast<CBrick*>(e->obj))
				stateCollision = MARIO_COLLISION_BRICK;
			else if (dynamic_cast<Coin*>(e->obj))
				stateCollision = MARIO_COLLISION_COIN;
			else if (dynamic_cast<Koopas*>(e->obj))
				stateCollision = MARIO_COLLISION_KOOPA;
			else if (dynamic_cast<MicsBrick*>(e->obj))
				stateCollision = MARIO_COLLISION_MICSBRICK;
			else if (dynamic_cast<ChimneyPortal*>(e->obj))
				stateCollision = MARIO_COLLISION_CHIMNEYPORTAL;
			else if (dynamic_cast<LevelMushroom*>(e->obj))
				stateCollision = MARIO_COLLISION_LEVELMUSHROOM;
			switch (stateCollision)
			{
			case MARIO_COLLISION_CHIMNEYPORTAL:
			{
				if (this->isJumping())
					this->setJumping(false);
				if (this->isFlying())
					this->setFlying(false);
				if (this->getIsOnSky())
					this->setIsOnSky(false);
				if (y < 100)
				{
					y = 300;
				}
				else if (y > 250)
				{
					y = 190;
					x -= 153;
				}
				break;
			}
			case MARIO_COLLISION_GATE:
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				break;
			}
			case MARIO_COLLISION_GOOMBA:
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level == MARIO_LEVEL_TAIL && getIsSpin())
								goomba->SetState(GOOMBA_STATE_CLEAR);
							else
							{
								if (level > MARIO_LEVEL_SMALL)
								{
									level -= 1;
									StartUntouchable();
								}
								else
									SetState(MARIO_STATE_DIE);
							}
						}
					}
				}
				break;
			}
			case MARIO_COLLISION_KOOPA:
			{
				Koopas* koopa = dynamic_cast<Koopas*>(e->obj);
				if (untouchable == 0)
				{					
					if (e->ny < 0)
					{

						if (this->isJumping())
							this->setJumping(false);
						if (this->isFlying())
							this->setFlying(false);
						if (this->getIsOnSky())
							this->setIsOnSky(false);
					}
					if (e->ny < 0)
					{
						if (koopa->GetState() != KOOPAS_STATE_DIE && koopa->GetState() != KOOPAS_STATE_SHELL)
						{
							koopa->SetState(KOOPAS_STATE_SHELL);
							if (koopa->isShell == false)
								koopa->y += 9;
							koopa->isShell = true;
						}
					}
					else if (e->nx != 0)
					{
						if (untouchable == 0)
						{

							//making kick koopas
							if (koopa->GetState() == KOOPAS_STATE_SHELL && abs(koopa->vx) == 0)
							{
								if (abs(vx) > 0.06)
								{
									if (readyToHoldKoopas)
										readyToHoldKoopas = false;
									if (nx < 0)
										koopa->vx = (float)0.15;
									else koopa->vx = (float)-0.15;
									koopa->SetState(KOOPAS_STATE_SHELL_RUNNING);
								}
								else
								{
									if (readyToHoldKoopas)
									{
										koopa->y -= 4;
										relativeDistanceMarioKoopa = abs(koopa->x - x);
										koopa->setIsHold(true);
										this->setIsHold(true);

									}
								}
							}
							else if (koopa->GetState() == KOOPAS_STATE_HOLD)
							{
								koopa->x = this->x + 16;
							}
							else if (koopa->GetState() == KOOPAS_STATE_SHELL_RUNNING || koopa->GetState() == KOOPAS_STATE_WALKING)
							{
								if (level == MARIO_LEVEL_TAIL && getIsSpin())
									koopa->SetState(KOOPAS_STATE_SHELL);
								else if (level > MARIO_LEVEL_SMALL)
								{
									level -= 1;
									StartUntouchable();
								}
								else
									SetState(MARIO_STATE_DIE);
							}

						}
					}
				}

				break;
			}
			case MARIO_COLLISION_BACKROUND:
			{
				break;
			}
			case MARIO_COLLISION_COLORBRICK:
			{
				if (e->ny < 0)
				{
					if (this->isJumping())
						this->setJumping(false);
					if (this->isFlying())
						this->setFlying(false);
					if (this->getIsOnSky())
						this->setIsOnSky(false);
				}
				break;
			}
			case MARIO_COLLISION_BRICK:
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0)
				{
					//(vx = 0);
					SetState(MARIO_STATE_IDLE);
				}
				if (e->ny != 0)
				{
					if (this->isJumping())
						this->setJumping(false);
					if (this->isFlying())
						this->setFlying(false);
					if (this->getIsOnSky())
						this->setIsOnSky(false);
				}

				break;
			}
			case MARIO_COLLISION_COIN:
			{
				Coin* coin = dynamic_cast<Coin*>(e->obj);
				coin->SetState(COIN_STATE_DIE);
				break;
			}
			case MARIO_COLLISION_MICSBRICK:
			{
				MicsBrick* micsBrick = dynamic_cast<MicsBrick*>(e->obj);
				if (e->ny != 0)
				{
					if (this->isJumping())
						this->setJumping(false);
					if (this->isFlying())
						this->setFlying(false);
					if (this->getIsOnSky())
						this->setIsOnSky(false);
				}
				if (e->ny >0)
					this->coinID = dynamic_cast<MicsBrick*>(e->obj)->id;
				dynamic_cast<MicsBrick*>(e->obj)->SetState(MICSBRICK_STATE_DIE);
				break;
			}
			case MARIO_COLLISION_LEVELMUSHROOM:
			{
				LevelMushroom* mushroom = dynamic_cast<LevelMushroom*>(e->obj);
				mushroom->SetState(MUSHROOM_STATE_DIE);				
				if (level < MARIO_LEVEL_TAIL)
					level++;
				this->y -= 20;
				break;
			}
			default:break;
			}
		}
	}
	//it means mario is in begin scene
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];	
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	{
		if (level == MARIO_LEVEL_BIG)
		{
			if (nx > 0)
			{
				if (vx < 0 && state == MARIO_STATE_WALKING_RIGHT)
				{
					ani = MARIO_ANI_BIG_BRAKE_RIGHT;
				}
				else if (vx == 0)
				{
					if (state == MARIO_STATE_HOLD)
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_IDLE_RIGHT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_IDLE_RIGHT;
						else ani = MARIO_ANI_BIG_IDLE_RIGHT;
					}
					
				}					
				else
				{
					if (state == MARIO_STATE_RUN)
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_RUN_RIGHT;
						else ani = MARIO_ANI_BIG_RUNNING_RIGHT;
					}
						
					else if (state == MARIO_STATE_HOLD)
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_WALK_RIGHT;
						else ani = MARIO_ANI_BIG_WALKING_RIGHT;
					}
				}
			}
			else {
				if (vx > 0 && state == MARIO_STATE_WALKING_LEFT)
				{
					ani = MARIO_ANI_BIG_BRAKE_LEFT;
				}
				else if (vx == 0)
				{
					if (state == MARIO_STATE_HOLD)
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_IDLE_LEFT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_IDLE_LEFT;
						else ani = MARIO_ANI_BIG_IDLE_LEFT;
					}						
				}
				else
				{
					if (state == MARIO_STATE_RUN)
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_RUN_LEFT;
						else ani = MARIO_ANI_BIG_RUNNING_LEFT;
					}						
					else if (state == MARIO_STATE_HOLD)
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_WALK_LEFT;
						else ani = MARIO_ANI_BIG_WALKING_LEFT;
					}
				}
			}
			if (isJumping()|| state == MARIO_STATE_JUMP)
			{
				if (nx > 0)
				{
					if (getIsHold())
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_JUMP_RIGHT;
						else ani = MARIO_ANI_BIG_JUMPING_RIGHT;
					}						
				}
				else
				{
					if (getIsHold())
					{
						ani = MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT;
					}						
					else
					{
						if (color == 2)
							ani = GREEN_MARIO_ANI_BIG_JUMP_LEFT;
						else ani = MARIO_ANI_BIG_JUMPING_LEFT;
					}
				}
			}

		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (nx > 0)
			{
				if (vx < 0 && state == MARIO_STATE_WALKING_RIGHT)
				{
					ani = MARIO_ANI_SMALL_BRAKE_RIGHT;
				}
				else if (vx == 0)
					ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else
				{
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				}
			}
			else {
				if (vx > 0 && state == MARIO_STATE_WALKING_LEFT)
				{
					ani = MARIO_ANI_SMALL_BRAKE_LEFT;
				}
				else if (vx == 0)
					ani = MARIO_ANI_SMALL_IDLE_LEFT;
				else
				{
					ani = MARIO_ANI_SMALL_WALKING_LEFT;
				}
			}
			if (isJumping())
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_SMALL_JUMPING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_SMALL_JUMPING_LEFT;
				}
			}
		}
		else if (level == MARIO_LEVEL_TAIL)
		{
			if (nx > 0)
			{
				if (vx < 0)
				{					
					ani = MARIO_ANI_TAIL_BRAKE_LEFT;
				}
				else if (vx == 0)
					ani = MARIO_ANI_TAIL_IDLE_RIGHT;
				else
				{
					if (state == MARIO_STATE_RUN)
						ani = MARIO_ANI_TAIL_RUNNING_RIGHT;
					else ani = MARIO_ANI_TAIL_WALKING_RIGHT;
				}
			}
			else {
				if (vx > 0)
				{
					ani = MARIO_ANI_TAIL_BRAKE_RIGHT;
				}
				else if (vx == 0)
					ani = MARIO_ANI_TAIL_IDLE_LEFT;
				else
				{
					if (state == MARIO_STATE_RUN)
						ani = MARIO_ANI_TAIL_RUNNING_LEFT;
					else ani = MARIO_ANI_TAIL_WALKING_LEFT;
				}
			}
			if (isFlying())
			{
				if (nx > 0)
				{
					ani = MARIO_ANI_TAIL_FLYING_RIGHT;
				}
				else
				{
					ani = MARIO_ANI_TAIL_FLYING_LEFT;
				}
			}
			else if (isJumping())
			{
				if (nx > 0)
				{
					if(getIsOnSky())
						ani = MARIO_ANI_TAIL_IS_JUMPING_RIGHT;
					else ani = MARIO_ANI_TAIL_JUMPING_RIGHT;
					//ani = MARIO_ANI_TAIL_IS_JUMPING_RIGHT;
				}
				else
				{
					if (getIsOnSky())
						ani = MARIO_ANI_TAIL_IS_JUMPING_LEFT;
					else
						ani = MARIO_ANI_TAIL_JUMPING_LEFT;
					//ani = MARIO_ANI_TAIL_IS_JUMPING_LEFT;
				}
			}
			else if (getIsSpin())
			{
				if (nx > 0)
					ani = MARIO_ANI_TAIL_SPIN_LEFT;
				else 
					ani = MARIO_ANI_TAIL_SPIN_RIGHT;
			}
				
			
		}
		else if (level == MARIO_LEVEL_FIRE)
		{
		if (nx > 0)
		{
			if (vx < 0 && state == MARIO_STATE_WALKING_RIGHT)
			{
				ani = MARIO_ANI_FIRE_BRAKE_RIGHT;
			}
			else if (vx == 0)
				ani = MARIO_ANI_FIRE_IDLE_RIGHT;
			else
			{
				if (state == MARIO_STATE_RUN)
					ani = MARIO_ANI_FIRE_RUNNING_RIGHT;
				else ani = MARIO_ANI_FIRE_WALKING_RIGHT;
			}
		}
		else {
			if (vx > 0 && state == MARIO_STATE_WALKING_LEFT)
			{
				ani = MARIO_ANI_FIRE_BRAKE_LEFT;
			}
			else if (vx == 0)
				ani = MARIO_ANI_FIRE_IDLE_LEFT;
			else
			{
				if (state == MARIO_STATE_RUN)
					ani = MARIO_ANI_FIRE_RUNNING_LEFT;
				else ani = MARIO_ANI_FIRE_WALKING_LEFT;
			}
		}
		if (isJumping())
		{
			if (nx > 0)
			{
				ani = MARIO_ANI_FIRE_JUMPING_RIGHT;
			}
			else
			{
				ani = MARIO_ANI_FIRE_JUMPING_LEFT;
			}
		}
		else if (timeShooting!=0)
		{
			if (nx > 0)
				ani = MARIO_ANI_FIRE_SHOOTING_LEFT;
			else
				ani = MARIO_ANI_FIRE_SHOOTING_RIGHT;
		}

		}
	}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);
	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:		
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		nx = -1;
		break;
	case MARIO_STATE_RUN:
		break;
	case MARIO_STATE_JUMP:
		if (CGame::GetInstance()->GetCurrentScene()->typeScene == 1)
			vy = -MARIO_JUMP_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_JUMP_WAVE_TAIL:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		//vy -= 0.02;
		//vy = -MARIO_JUMP_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_FLY:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		vy = -MARIO_JUMP_SPEED_Y*1.5;
		ny = -1;
		break;
	case MARIO_STATE_IDLE:
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SHOOTING:
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL || level == MARIO_LEVEL_FIRE)
	{
		if (GetState() == MARIO_STATE_HOLD)
		{
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	//start_y -= MARIO_BIG_BBOX_HEIGHT*2 ;
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
