#include "OBJ_SeaSprite.h"

OBJ_SeaSprite::OBJ_SeaSprite()
{
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);

	p_mSprite = new Com_3DSprite();
	p_mSprite->SetTexture("asset\\texture\\sea.jpg");
	AddComponent(p_mSprite);
}

OBJ_SeaSprite::OBJ_SeaSprite(const char* _name)
	: OBJ_SeaSprite()
{
	sObjectName = _name;
}
