#pragma once
#include "GameObject.h"
#define HUB_WIDTH 0
#define HUB_HEIGHT 0
#define HUB_STATE_NORMAL 100

#define HUB_ANI_NORMAL 0
#define HUB_ANI_M_LETTER 1
#define HUB_ANI_WHITE_P 2
#define HUB_ANI_BLACK_P 3
#define HUB_ANI_WHITE_ARROW 4
#define HUB_ANI_BLACK_ARROW 5
#define HUB_ANI_FRAME_CARD 6
#define HUB_ANI__FRAME_CARD_MUSHROOM 7
#define HUB_ANI_FRAME_CARD_TREE 8
#define HUB_ANI_FRAME_CARD_STAR 9
#define HUB_ANI_POINT_100 10
#define HUB_ANI_POINT_200	11
#define HUB_ANI_POINT_400	12	
#define HUB_ANI_POINT_800	13
#define HUB_ANI_POINT_1000	14
#define HUB_ANI_POINT_2000	15
#define HUB_ANI_POINT_4000	16
#define HUB_ANI_POINT_8000	17
#define HUB_ANI_POINT_1UP	18
#define HUB_ANI_NUMBER_0	19
#define HUB_ANI_NUMBER_1	20
#define HUB_ANI_NUMBER_2	21
#define HUB_ANI_NUMBER_3	22
#define HUB_ANI_NUMBER_4	23
#define HUB_ANI_NUMBER_5	24
#define HUB_ANI_NUMBER_6	25
#define HUB_ANI_NUMBER_7	26
#define HUB_ANI_NUMBER_8	27
#define HUB_ANI_NUMBER_9	28
#define HUB_ANI_TEXT_A		29
#define HUB_ANI_TEXT_B		30		
#define HUB_ANI_TEXT_C		31
#define HUB_ANI_TEXT_D		32
#define HUB_ANI_TEXT_E		33
#define HUB_ANI_TEXT_F		34
#define HUB_ANI_TEXT_G		35		
#define HUB_ANI_TEXT_H		36
#define HUB_ANI_TEXT_I		37
#define HUB_ANI_TEXT_J		38
#define HUB_ANI_TEXT_K		39
#define HUB_ANI_TEXT_L		40
#define HUB_ANI_TEXT_M		41
#define HUB_ANI_TEXT_N		42
#define HUB_ANI_TEXT_O		43
#define HUB_ANI_TEXT_P		44
#define HUB_ANI_TEXT_Q		45
#define HUB_ANI_TEXT_R		46
#define HUB_ANI_TEXT_S		47
#define HUB_ANI_TEXT_T		48
#define HUB_ANI_TEXT_U		49
#define HUB_ANI_TEXT_V		50
#define HUB_ANI_TEXT_W		51
#define HUB_ANI_TEXT_X		52
#define HUB_ANI_TEXT_Y		53
#define HUB_ANI_TEXT_Z		54
#define HUB_ANI_BLACK_BACKROUND 55

#define SCENCE1_TIME		365
class MyHUB : public CGameObject
{
public:
	MyHUB(): CGameObject(){	}
	virtual void Render() ;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void renderText(string s, int x, int y);
	float time = 0;
	string timeText="";
	string pointText = "000000";
};
