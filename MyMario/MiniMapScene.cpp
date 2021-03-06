#include "MiniMapScene.h"

MiniMapScene::MiniMapScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new MinimapSceneScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/
void MiniMapScene::_ParseSection_TEXTURES(string line)
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

void MiniMapScene::_ParseSection_SPRITES(string line)
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

void MiniMapScene::_ParseSection_ANIMATIONS(string line)
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

void MiniMapScene::_ParseSection_ANIMATION_SETS(string line)
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

void MiniMapScene::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_MINI_MARIO:
	{
		obj = new MiniMario();
		miniMario = (MiniMario*)obj;
		break;
	}
	
	case OBJECT_TYPE_BACKROUND:
	{
		int typeAnimation = (int)atof(tokens[3].c_str());
		obj = new backRound();
		if (typeAnimation == 9004 || typeAnimation == 29001)
		{
			int animation1 = (int)atof(tokens[4].c_str());
			dynamic_cast<backRound*>(obj)->isAnimation = animation1;
		}
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

void MiniMapScene::Load()
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

void MiniMapScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	float cx=0, cy=0;
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	CGame::GetInstance()->SetCamPos(15, 00);
	if (cx < 15)
		CGame::GetInstance()->SetCamPos(15, 00);
	else if (cy < -160)
	{
		for (int i = 0; i < 160; i++)
			CGame::GetInstance()->SetCamPos(round(cx), (float)-i);
	}
	else if (cy > 200)
		CGame::GetInstance()->SetCamPos(round(cx), 150);
	else
		CGame::GetInstance()->SetCamPos(round(cx), 00);
	if (CGame::GetInstance()->GetCurrentScene()->typeScene == 0)
		CGame::GetInstance()->SetCamPos(15, 00);
	//CGame::GetInstance()->SetCamPos(2300, 250);
	//DebugOut(L"tick count %d\n", GetTickCount64());
}

void MiniMapScene::Render()
{
	for (int i = 0; i < (int)objects.size(); i++)
		objects[i]->Render();
}

void MiniMapScene::Unload()
{
	for (int i = 0; i < (int)objects.size(); i++)
		delete objects[i];
	objects.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void MinimapSceneScenceKeyHandler::OnKeyDown(int KeyCode)
{
	MiniMario* mario = ((MiniMapScene*)scence)->getMiniMario();
	switch (KeyCode)
	{
		//when mario go to 1 POINT : decision WHERE MARIO can GO and WHERE NOT
		case DIK_LEFT:
		{
			switch (mario->point)
			{
				//explain : at point 1 : mario can go left and it go to point 0
				//at point 7 : mario can go left and it go to point 8
			case 1:case 3:case 4:case 5: case 14:  mario->point--; break;
			case 7: case 6: case 9:case 10:case 16: mario->point++; break;
			case 15:mario->point-=2; break;
			}
			//update : CHANGE the POSITION of mini mario DEPEND on its POINT
			mario->Update();
			break;
		}
		case DIK_RIGHT:
		{
			switch (mario->point)
			{
			case 0:case 2:case 3:case 4:case 14:  mario->point++; break;
			case 7:case 8:case 10:case 11:case 17:mario->point--; break;
			case 13:mario->point+=2; break;
			}
			mario->Update();
			break;
		}

		case DIK_UP:
		{
			switch (mario->point)
			{
			case 1:case 15: mario->point++; break;
			case 6:case 9:case 12:mario->point--; break;
			case 8: mario->point-=5; break;
			case 13:mario->point-=2; break;
			}
			mario->Update();
			break;
		}
		case DIK_DOWN:
		{
			switch (mario->point)
			{
			case 5:case 8:case 12: mario->point++; break;
			case 15:case 16:case 2:mario->point--; break;
			case 3: mario->point += 5; break;
			case 11: mario->point += 2; break;
			}
			mario->Update();
		
			break;
		}
		case DIK_W:
		{
			if (mario->point == 7)
				idNewScene = 4;
			else if (mario->point == 2)
				idNewScene = 3;
			else idNewScene = 2;
			CGame::GetInstance()->SwitchScene(this->idNewScene);
		}
	}
}
