#include "OBJ_AzarashiRemain.h"

OBJ_AzarashiRemain::OBJ_AzarashiRemain()
{
	Com_Sprite* p_mSprite = new Com_Sprite();
	p_mSprite->SetTexture("asset/texture/zanki.png");
	AddComponent(p_mSprite);
}

void OBJ_AzarashiRemain::Update()
{
}
