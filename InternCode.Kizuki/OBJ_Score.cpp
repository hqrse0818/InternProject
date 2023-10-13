#include "OBJ_Score.h"
#include "../Component/Com_Sprite.h"

OBJ_Score::OBJ_Score()
{
	Com_Sprite* p_mSprite = new Com_Sprite;
	p_mSprite->SetTexture("asset/texture/score.png");
	AddComponent(p_mSprite);
}

void OBJ_Score::Init()
{

}

void OBJ_Score::Update()
{

}

//curenty=(ƒƒ“ƒo•Ï”+4*v•ªŠ„”)