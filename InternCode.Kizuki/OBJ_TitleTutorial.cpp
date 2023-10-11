#include "OBJ_TitleTutorial.h"

OBJ_TitleTutorial::OBJ_TitleTutorial()
{
	Com_Sprite* p_mPrite = new Com_Sprite();
	//Sprite_buf->SetTexture("asset/texture/.png");
	AddComponent(p_mSprite);
}

void OBJ_TitleTutorial::Init()
{
}
