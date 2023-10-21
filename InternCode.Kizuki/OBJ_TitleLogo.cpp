#include "OBJ_TitleLogo.h"
#include "../Component/Com_Sprite.h"
#include "../Component/Com_Shader.h"
#include "../System/Time.h"
#include "../Utility.h"

OBJ_TitleLogo::OBJ_TitleLogo()
{
	Com_Sprite* p_mSprite = new Com_Sprite;
	p_mSprite->SetTexture("asset/texture/logo.png");
	p_mSprite->SetUpdate(true);
	AddComponent(p_mSprite);

	Com_Shader* p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);
}

void OBJ_TitleLogo::Update()
{
	GameObject::Update();

	if (bRotate)
	{
		if (bReturn)
		{
			Rotate(0.0f, 0.0f, Euler_To_Radian(2.0f) * Time->GetDeltaTime());
			if (p_mTransform->mRotation.z > Euler_To_Radian(2.0f))
			{
				bReturn = false;
			}
		}
		else
		{
			Rotate(0.0f, 0.0f, Euler_To_Radian(-2.0f) * Time->GetDeltaTime());
			if (p_mTransform->mRotation.z < Euler_To_Radian(-2.0f))
			{
				bReturn = true;
			}
		}
	}
}
