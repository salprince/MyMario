#include "Include.h"
//#pragma warning(disable:28159 26495) 

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
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (int i = 1; i < tokens.size(); i++)
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

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

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
				player->SetLevel(2);
				DebugOut(L"[INFO] Player object created!\n");
				}			
			break;
		}
		
	case OBJECT_TYPE_GOOMBA: 
	{
		obj = new CGoomba();
		float l = (float)atof(tokens[4].c_str());
		obj->length = l;
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS:
	{
		float l = (float)atof(tokens[4].c_str());
		float nx0 = (float)atof(tokens[5].c_str());
		obj = new Koopas();
		obj->length = l;
		obj->nx = nx0;
		break;
	}
	case OBJECT_TYPE_BACKROUND:
	{
		int typeAnimation= (int)atof(tokens[3].c_str());
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
		if (tokens.size() == 5)
		{
			int temp = (int)atof(tokens[4].c_str());
			dynamic_cast<Coin*>(obj)->id = temp;
		}
		break;
	}
	case OBJECT_TYPE_MICSBRICK: 
	{
		obj = new MicsBrick();
		if (tokens.size() == 5)
		{
			int temp = (int)atof(tokens[4].c_str());
			dynamic_cast<MicsBrick*>(obj)->id = temp;
		}
		break;
	}		 
	case OBJECT_TYPE_LEVELMUSHROOM: obj = new LevelMushroom(); break;
	case OBJECT_TYPE_FIRE: 
	{		
		
		obj = new Fire(); 
		int l = (int)atof(tokens[4].c_str());
		dynamic_cast<Fire*>(obj)->id = l;
		/*if (l > dynamic_cast<Fire*>(obj)->maxFire)
			dynamic_cast<Fire*>(obj)->maxFire = l;*/
		//DebugOut(L"maxFireaaaaaa %d \n", l);
		break;
	}
	case OBJECT_TYPE_HUB:
	{
		obj = new MyHUB();
		break;
	}
	case OBJECT_TYPE_CHIMNEY_PORTAL: obj = new ChimneyPortal(); break;
	//case OBJECT_TYPE_GREEN_FLOWER: obj = new GreenFlower(); break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[4].c_str());
		float b = (float)atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

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

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		/*if (dynamic_cast<MyHUB*>(objects[i]))
			objects[i]->Update(dt);
		else */
			objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	CGame::GetInstance()->SetCamPos(15, 0);
	if (cx < 15)
	{
		CGame::GetInstance()->SetCamPos(15, 0);
	}
		
	else if (cy < -160)
	{
		for(int i=0; i <160; i++)
			CGame::GetInstance()->SetCamPos(round(cx), (float)-i);
	}	
	else if(cy>200)
		CGame::GetInstance()->SetCamPos(round(cx), 150);
	else 
		CGame::GetInstance()->SetCamPos(round(cx), 0);
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
	{
		if (mario->getLevel() == MARIO_LEVEL_TAIL)
		{
			if (abs(mario->vx) >= MARIO_MAX_WALKING_SPEED || mario->state == MARIO_STATE_FLY)
			{
				if (!mario->isJumping())
				{
					mario->setFlying(true);
					//if(mario->GetState()!= MARIO_STATE_FLY)
						mario->SetState(MARIO_STATE_FLY);
					//mario->timeFlying = GetTickCount();
				}
			}
			if (!mario->isJumping() && !mario->isFlying())
			{
				mario->setJumping(true);
				mario->SetState(MARIO_STATE_JUMP);
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
		//mario->SetState(MARIO_STATE_JUMP);
		break;
	}
	case DIK_Z:
	{
		if (mario->getLevel() == MARIO_LEVEL_TAIL)
		{			
			if (!mario->getIsSpin())
			{
				mario->setIsSpin(true);
				mario->spining = GetTickCount64();
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
				mario->timeShooting = GetTickCount64();
				if(mario->FireID<10)
					mario->FireID++;
				else 
					mario->FireID=1;
				//DebugOut(L"aaaaaa\n");
			}
			//DebugOut(L"Get is Fire AFTER = %d \n", mario->getIsFire());
			
		}
		break;
	}
	case DIK_F:
	{
		mario->SetLevel(MARIO_LEVEL_FIRE);
		mario->SetPosition(mario->x, mario->y - 20);
		break;
	}
	case DIK_A:
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
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_Z))
		{
			if (mario->getLevel() == MARIO_LEVEL_FIRE)
			{
				if (!mario->getIsFire())
					mario->setIsFire(true);
			}
		}
		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
		
	else if (game->IsKeyDown(DIK_LEFT))
		mario->SetState(MARIO_STATE_WALKING_LEFT);
	else
		mario->SetState(MARIO_STATE_IDLE);
	
}