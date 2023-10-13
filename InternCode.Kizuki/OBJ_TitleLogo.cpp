#include "OBJ_TitleLogo.h"
#include "../Component/Com_Sprite.h"

OBJ_TitleLogo::OBJ_TitleLogo()
{
	Com_Sprite* p_mSprite = new Com_Sprite;
	p_mSprite->SetTexture("asset/texture/logo");
	AddComponent(p_mSprite);
}
