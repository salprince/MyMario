#include "Include.h"
#include "BlueP.h"
#include "BreakBrick.h"
#include "ShootingRedTree.h"
#include "MovableBrick.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/
void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < (int)tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < (int)tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 5) return; // skip invalid lines - an object set must have at least id, x, y
	int gridx= atoi(tokens[0].c_str());
	int gridy = atoi(tokens[1].c_str());
	int object_type = atoi(tokens[2].c_str());
	float x = (float)atof(tokens[3].c_str());
	float y = (float)atof(tokens[4].c_str());

	int ani_set_id = atoi(tokens[5].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
		case OBJECT_TYPE_MARIO:
		{			
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				return;
			}
			else
			{
				obj = new CMario(x, y);
				player = (CMario*)obj;
				player->SetLevel(MARIO_LEVEL_SMALL);
				DebugOut(L"[INFO] Player object created!\n");
				}			
			break;
		}
		
	case OBJECT_TYPE_GOOMBA: 
	{
		obj = new CGoomba();
		float l = (float)atof(tokens[6].c_str());
		obj->length = l;
		if (tokens.size() == 8)
		{
			int temp = (int)atof(tokens[7].c_str());
			dynamic_cast<CGoomba*>(obj)->level = temp;
		}
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS:
	{
		float l = (float)atof(tokens[6].c_str());
		float nx0 = (float)atof(tokens[7].c_str());
		obj = new Koopas();
		obj->length = l;
		obj->nx = (int)nx0;
		if (tokens.size() >= 9)
		{
			int temp = (int)atof(tokens[8].c_str());
			dynamic_cast<Koopas*>(obj)->typeKoopas = temp;
			
		}
		if (tokens.size() == 10)
		{
			int temp = (int)atof(tokens[9].c_str());
			dynamic_cast<Koopas*>(obj)->level = temp;
		}
		break;
	}
	
	case OBJECT_TYPE_BACKROUND:
	{
		int typeAnimation= (int)atof(tokens[5].c_str());
		obj = new backRound();
		if (CGame::GetInstance()->GetCurrentScene()->typeScene !=0)
		{
			//int animation1 = atof(tokens[4].c_str());
			//dynamic_cast<backRound*>(obj)->isAnimation = animation1;
		}			
		break;
	}
	case OBJECT_TYPE_COLORBRICK: obj = new ColorBrick(); break;
	case OBJECT_TYPE_COIN: 
	{
		obj = new Coin();
		if (tokens.size() >= 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<Coin*>(obj)->id = temp;
		}
		if (tokens.size() >= 8)
		{
			int temp1 = (int)atof(tokens[7].c_str());
			dynamic_cast<Coin*>(obj)->idCoinInBrick = temp1;
		}
		break;
	}
	case OBJECT_TYPE_MICSBRICK: 
	{
		obj = new MicsBrick();
		if (tokens.size() >= 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<MicsBrick*>(obj)->oldY = y;
			dynamic_cast<MicsBrick*>(obj)->id = temp;
		}
		if (tokens.size() >= 8)
		{
			int temp = (int)atoi(tokens[7].c_str());
			dynamic_cast<MicsBrick*>(obj)->numberOfCoin = temp;
		}
		break;
	}		 
	case OBJECT_TYPE_LEVELMUSHROOM:
	{
		obj = new LevelMushroom();
		if (tokens.size() == 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<LevelMushroom*>(obj)->id = temp;
			dynamic_cast<LevelMushroom*>(obj)->start_x = x;
			dynamic_cast<LevelMushroom*>(obj)->start_y = y;
		}
		break;
	}
	case OBJECT_TYPE_FIRE: 
	{		
		
		obj = new Fire(); 
		int l = (int)atof(tokens[6].c_str());
		dynamic_cast<Fire*>(obj)->id = l;
		dynamic_cast<Fire*>(obj)->start_x = obj->x;
		dynamic_cast<Fire*>(obj)->start_y = obj->y;
		break;
	}
	case OBJECT_TYPE_HUB:
	{
		
		obj = new MyHUB();
		this->hub = (MyHUB*)(obj);
		break;
	}
	case OBJECT_TYPE_SHOOTING_RED_TREE:
	{
		obj = new ShootingRedTree(); break;
		dynamic_cast<ShootingRedTree*>(obj)->start_y = y;
		if (tokens.size() >= 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<ShootingRedTree*>(obj)->treeID = temp;
		}
		
	}
	case OBJECT_TYPE_BLUE_P:
	{
		obj = new BlueP();
		if (tokens.size() >= 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<BlueP*>(obj)->id = temp;
		}
		if (tokens.size() == 8)
		{
			int temp = (int)atof(tokens[7].c_str());
			dynamic_cast<BlueP*>(obj)->idCoin = temp;
		}
		break;
	}
	case OBJECT_TYPE_BREAK_BRICK:
	{
		obj = new BreakBrick();
		if (tokens.size() == 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<BreakBrick*>(obj)->id = temp;
		}
		break;
	}
	case OBJECT_TYPE_MOVE_BRICK:
	{
		obj = new MovableBrick();
		if (tokens.size() >= 7)
		{
			int temp = (int)atof(tokens[6].c_str());
			dynamic_cast<MovableBrick*>(obj)->id = temp;
			int temp1 = (int)atof(tokens[7].c_str());
			dynamic_cast<MovableBrick*>(obj)->relativePosition= temp1;
			int temp2 = (int)atof(tokens[8].c_str());
			dynamic_cast<MovableBrick*>(obj)->x0= (float)temp2;
			int temp3 = (int)atof(tokens[9].c_str());
			dynamic_cast<MovableBrick*>(obj)->x1= (float)temp3;
		}
		break;
	}
	case OBJECT_TYPE_CHIMNEY_PORTAL: obj = new ChimneyPortal(); break;
	//case OBJECT_TYPE_GREEN_FLOWER: obj = new GreenFlower(); break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[6].c_str());
		float b = (float)atof(tokens[7].c_str());
		int scene_id = atoi(tokens[8].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	obj->gridX = gridx;
	obj->gridY = gridy;
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	CGame* game = CGame::GetInstance();
	vector<LPGAMEOBJECT> coObjects;
	int idScene = (int)(CPlayScene*)CGame::GetInstance()->GetCurrentSceneID();
	int lengthX = 0, lengthY = 0;
	if ((int)game->GetScreenWidth() % 32 == 0)
		lengthX = game->GetScreenWidth() / 32;
	else lengthX = game->GetScreenWidth() / 32 + 1;
	if (idScene == 4) 
		lengthX = 8;
	if ((int)game->GetScreenHeight() % 32 == 0)
		lengthY = game->GetScreenHeight() / 32;
	else lengthY = game->GetScreenHeight() / 32 + 1;
	for (size_t i = 1; i < objects.size(); i++)
	{
		if((abs(objects[i]->gridX - player->gridX)) < lengthX && (abs(objects[i]->gridY - player->gridY) < lengthY))
			coObjects.push_back(objects[i]);
		else if (dynamic_cast<MyHUB*>(objects[i]))
		{
			coObjects.push_back(objects[i]);
		}
		else if (dynamic_cast<Fire*>(objects[i]))
		{
			coObjects.push_back(objects[i]);
		}
		else if (dynamic_cast<CPortal*>(objects[i]))
		{
			coObjects.push_back(objects[i]);
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		if ((abs(objects[i]->gridX - player->gridX)) < lengthX && (abs(objects[i]->gridY - player->gridY)<lengthY))
			objects[i]->Update(dt, &coObjects);
		else if (dynamic_cast<MyHUB*>(objects[i]))
		{
			//DebugOut(L"HUBBB push back \n");
			objects[i]->Update(dt, &coObjects);
		}

		else if (dynamic_cast<Fire*>(objects[i]))
		{
			//DebugOut(L"HUBBB push back \n");
			objects[i]->Update(dt, &coObjects);
		}
		else if (dynamic_cast<CPortal*>(objects[i]))
		{
			//DebugOut(L"HUBBB push back \n");
			objects[i]->Update(dt, &coObjects);
		}
			
	}
	//this->GetHUB()->Render();
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	// Update camera to follow mario
	float cy=0;
	if (idScene == 3)
	{
		player->GetPosition(cx, cy);
		cy -= game->GetScreenHeight() / 2;
		cx -= game->GetScreenWidth() / 2;
	}
	else if(cx<1640)
		cx+=0.5;
	else if (cx > 2182)
		cx = 2182;
	else
	{
		player->GetPosition(cx, cy);
		cx -= game->GetScreenWidth() / 2;
	}
	
	
	//DebugOut(L"%f %d\n", cx, idScene);
	if (((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->state != MARIO_STATE_DIE )
	{
		//if(((CPlayScene*)CGame::GetInstance()->GetCurrentScene() )
		//DebugOut(L"%d\n ", (CPlayScene*)CGame::GetInstance()->GetCurrentSceneID());
		if (idScene == 3)
		{
			CGame::GetInstance()->SetCamPos(15, 0);
			if (cx < 15)
			{
				CGame::GetInstance()->SetCamPos(15, 0);
			}

			else if (cy < -140)
			{
				for (int i = 0; i < 140; i++)
					CGame::GetInstance()->SetCamPos(round(cx), (float)-i);
			}
			else if (cy < -160)
			{
				CGame::GetInstance()->SetCamPos(round(cx), round(cy));
			}
			else if (cy > 150 && cx > 1900 && switchSceneTime == 0)
			{
				CGame::GetInstance()->SetCamPos((float)round(2145), (float)300);
			}

			else if (cx > 2444)
			{
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetHUB()->isMove = false;
				CGame::GetInstance()->SetCamPos(2445, 0);
			}
			else
			{
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetHUB()->isMove = true;
				CGame::GetInstance()->SetCamPos(round(cx), 0);
			}
		}
		else /*if (idScene == 4)*/
		{
			if (cx > 2182)
				CGame::GetInstance()->SetCamPos((float)2182, 0);
			else	CGame::GetInstance()->SetCamPos(round(cx), 0);
		}
	}
	
		
}

void CPlayScene::Render()
{
	if (time == 0)
		time = (float)GetTickCount64();
	for (int i = 0; i < (int)objects.size(); i++)
	{
		//if(!dynamic_cast<MyHUB*>(objects[i]))
			objects[i]->Render();
	}	
	//this->GetHUB()->Render();
	if (isShowEndText)
	{
		this->GetHUB()->renderText("OF COURSE CLEAR", 2650, 100);
		this->GetHUB()->renderText("U GOT A CARD", 2650, 120);
		this->GetHUB()->renderCard(HUB_ANI_FRAME_CARD_STAR, 2750, 110);
		//this->GetPlayer()->SetState(MARIO_STATE_WALKING_RIGHT);
		//this->GetPlayer()->x+=3;
		
	}
	if(this->GetPlayer()->showPoint)
		this->GetHUB()->renderText("100", (int)this->GetPlayer()->Tx, (int)this->GetPlayer()->Ty);
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < (int)objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	 	case DIK_S:
		{
			//DebugOut(L"UP\n");
			if (!mario->jumpToken)
				mario->jumpToken = true;
			break;
		}
		case DIK_A:
		{
			//DebugOut(L"UP\n");
			if (mario->isMoveFast)
				mario->isMoveFast =false;
			break;
		}
	}
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
	{
		//DebugOut(L"DOWN\n");
		if (mario->getLevel() == MARIO_LEVEL_TAIL)
		{
			if (abs(mario->vx) >= MARIO_MAX_WALKING_SPEED || mario->state == MARIO_STATE_FLY)
			{
				if (!mario->isJumping())
				{
					mario->setFlying(true);
					mario->SetState(MARIO_STATE_FLY);
				}
			}
			if (!mario->isJumping() && !mario->isFlying())
			{
				mario->setJumping(true);
				mario->SetState(MARIO_STATE_JUMP);
				//mario->vy = -MARIO_JUMP_SPEED_Y;
			}
			else if (mario->isJumping())
			{
				mario->setIsOnSky(true);
				mario->vy = (float)0.00001;
			}
			else
			{

				mario->vy = (float)-0.2;
				//mario->SetState(MARIO_STATE_JUMP_WAVE_TAIL);
			}
		}		
		else if (!mario->isJumping())
		{
			mario->setJumping(true);
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	}
	case DIK_A:case DIK_Z:
	{
		if (mario->getLevel() == MARIO_LEVEL_TAIL)
		{			
			if (!mario->getIsSpin())
			{
				mario->setIsSpin(true);
				mario->spining =(int) GetTickCount64();
			}			
		}
		else if (mario->getLevel() == MARIO_LEVEL_BIG)
		{
			mario->readyToHoldKoopas = false;
			if(!mario->readyToHoldKoopas)
				mario->readyToHoldKoopas = true;
			if (mario->getIsHold())
				mario->setIsHold(false);
		}
		else if (mario->getLevel() == MARIO_LEVEL_FIRE)
		{
			if (!mario->getIsFire())
			{
				mario->setIsFire(true);

				mario->timeShooting =(int) GetTickCount64();
				if(mario->FireID<2)
					mario->FireID++;
				else 
					mario->FireID=1;
				
			}
			
		}
		break;
	}
	case DIK_F:
	{
		mario->SetLevel(MARIO_LEVEL_FIRE);
		mario->SetPosition(mario->x, mario->y - 20);
		break;
	}
	case DIK_R:
		mario->Reset();
		break;
	case DIK_B:
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetPosition(mario->x, mario->y -20);
		break;
	case DIK_T:
		mario->SetLevel(MARIO_LEVEL_TAIL);
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetPosition(mario->x, mario->y -20);
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_A))
		mario->isMoveFast = true;
	if (game->IsKeyDown(DIK_RIGHT))
	{		
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
		
	else if (game->IsKeyDown(DIK_LEFT))
	{
		 mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
	if (game->IsKeyDown(DIK_S))
	{		
		if (mario->getLevel() == MARIO_LEVEL_TAIL)
		{
			/*if (mario->state == MARIO_STATE_FLY || mario->isFlying())
			{
				/*if (!mario->isJumping())
				{
					mario->setFlying(true);
					mario->SetState(MARIO_STATE_FLY);
				}
			}
			else if (mario->jumpToken)
			{
				float y = mario->y;
				float y0 = mario->oldY;
				if (!mario->isJumping())
				{
					if (y > y0 - MARIO_MIN_JUMP)
					{
						mario->setJumping(true);
						mario->SetState(MARIO_STATE_JUMP);
						//mario->setIsOnSky(true);
						//mario->jumpToken = false;
					}
				}
				else
				{
					if (y0 - y < MARIO_MAX_JUMP && !mario->isJumpHigh)
					{
						if (mario->vy > -0.05)
						{
							mario->vy = -0.07;
						}

					}
					else
					{
						mario->isJumpHigh = true;
						mario->jumpToken = false;
						if (y < y0)
						{
							mario->y++;
							mario->vy = 0;
						}
						else
							mario->y = y0;

					}
				}
			}*/
		}
		else
		{
			if (mario->jumpToken)
			{
				float y = mario->y;
				float y0 = mario->oldY;

				if (!mario->isJumping())
				{
					if (y > y0 - MARIO_MIN_JUMP)
					{
						mario->setJumping(true);
						mario->SetState(MARIO_STATE_JUMP);
					}
				}
				else
				{
					if (y0 - y < MARIO_MAX_JUMP && !mario->isJumpHigh)
					{
						if (mario->vy > -0.05)
						{
							mario->vy = (float)-0.07;
						}

					}
					else
					{
						mario->isJumpHigh = true;
						mario->jumpToken = false;
						if (y < y0)
						{
							mario->y++;
							mario->vy = 0;
						}
						else
							mario->y = y0;

					}
				}
			}

		}
		
		
	}
}