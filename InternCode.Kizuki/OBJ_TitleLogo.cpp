#include "OBJ_TitleLogo.h"
#include "../Component/Com_Sprite.h"
#include "../Component/Com_Shader.h"

OBJ_TitleLogo::OBJ_TitleLogo()
{
	Com_Shader* p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);

	Com_Sprite* p_mSprite = new Com_Sprite;
	p_mSprite->SetTexture("asset/texture/logo.png");
	AddComponent(p_mSprite);
}
