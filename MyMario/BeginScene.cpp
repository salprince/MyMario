#include "BeginScene.h"
#include "Include.h"
using namespace std;

BeginScene::BeginScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new BeginScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/
void BeginScene::_ParseSection_TEXTURES(string line)
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

void BeginScene::_ParseSection_SPRITES(string line)
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

void BeginScene::_ParseSection_ANIMATIONS(string line)
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

void BeginScene::_ParseSection_ANIMATION_SETS(string line)
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

void BeginScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		int colorType = atof(tokens[4].c_str());
		//type =1 red ; type =2 : green 
		//DebugOut(L"[ERROR] MARIO object was created before! %d\n",typeScence );
		if (player != NULL && colorType == 1)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		else if (colorType == 2)
		{
			obj = new CMario(x, y);
			player1 = (CMario*)obj;
			player1->SetLevel(2);
			player1->nx = -1;
			player1->color = 2;
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
		float l = atof(tokens[4].c_str());
		obj->length = l;
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS:
	{
		float l = atof(tokens[4].c_str());
		float nx0 = atof(tokens[5].c_str());
		obj = new Koopas();
		obj->length = l;
		obj->nx = nx0;
		break;
	}
	case OBJECT_TYPE_BACKROUND:
	{
		int typeAnimation = atof(tokens[3].c_str());
		obj = new backRound();
		if (typeAnimation == 9004)
		{
			int animation1 = atof(tokens[4].c_str());
			dynamic_cast<backRound*>(obj)->isAnimation = animation1;
		}
		break;
	}
	case OBJECT_TYPE_COLORBRICK: obj = new ColorBrick(); break;
	case OBJECT_TYPE_COIN: obj = new Coin(); break;
	case OBJECT_TYPE_MICSBRICK: obj = new MicsBrick(); break;
	case OBJECT_TYPE_LEVELMUSHROOM: obj = new LevelMushroom(); break;
	case OBJECT_TYPE_FIRE:
	{

		obj = new Fire();
		int l = atof(tokens[4].c_str());
		dynamic_cast<Fire*>(obj)->id = l;
		/*if (l > dynamic_cast<Fire*>(obj)->maxFire)
			dynamic_cast<Fire*>(obj)->maxFire = l;*/
			//DebugOut(L"maxFireaaaaaa %d \n", l);
		break;
	}
	case OBJECT_TYPE_CHIMNEY_PORTAL: obj = new ChimneyPortal(); break;
		//case OBJECT_TYPE_GREEN_FLOWER: obj = new GreenFlower(); break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
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

void BeginScene::Load()
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

void BeginScene::Update(DWORD dt)
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
	if (player == NULL) return;
	float cx, cy;
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	CGame::GetInstance()->SetCamPos(15, 00);
	if (cx < 15)
		CGame::GetInstance()->SetCamPos(15, 00);
	else if (cy < -160)
	{
		for (int i = 0; i < 160; i++)
			CGame::GetInstance()->SetCamPos(round(cx), -i);
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

void BeginScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void BeginScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();
	player = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void BeginScenceKeyHandler::OnKeyDown(int KeyCode)
{
	
}

void BeginScenceKeyHandler::KeyState(BYTE* states)
{	

}