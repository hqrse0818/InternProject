#include "OBJ_Transition.h"
#include "../ComponentHeader.h"
#include "../System/TextureCreate.h"
#include "../main.h"
#include "../Format.h"
#include "../System/Time.h"
#include "../TextureFilePath.h"

using namespace DirectX::SimpleMath;

OBJ_Transition::OBJ_Transition()
{
	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load("shader\\unlitTextureVS.cso");
	Shader_buf->p_mPS->Load("shader\\unlitTexturePS.cso");
	AddComponent(Shader_buf);

	p_mSprite = new Com_Sprite();
	p_mSprite->SetTexture(Tex_WhiteBase);
	MATERIAL mat{};
	mat.Diffuse = mColor;
	p_mSprite->SetMaterial(mat);
	AddComponent(p_mSprite);

	p_mTransform->SetScale(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);
	p_mTransform->mPosition.x = SCREEN_WIDTH / 2;
	p_mTransform->mPosition.y = SCREEN_HEIGHT / 2;
}

OBJ_Transition::OBJ_Transition(const char* _name)
	: OBJ_Transition()
{
	sObjectName = _name;
}

void OBJ_Transition::Update()
{
	switch (mState)
	{
	case OBJ_Transition::FadeState::InEnd:
		mColor.w = 0.0f;
		break;
	case OBJ_Transition::FadeState::In:
		mColor.w -= Time->GetDeltaTime() / fFadeTime;
		if (mColor.w <= 0.0f)
		{
			mState = FadeState::InEnd;
		}
		break;
	case OBJ_Transition::FadeState::Out:
		mColor.w += Time->GetDeltaTime() / fFadeTime;
		if (mColor.w >= 1.0f)
		{
			mState = FadeState::OutEnd;
		}
		break;
	case OBJ_Transition::FadeState::OutEnd:
		mColor.w = 1.0f;
		break;
	default:
		break;
	}

	MATERIAL mat{};
	mat.Diffuse = mColor;
	p_mSprite->SetMaterial(mat);

	GameObject::Update();
}

void OBJ_Transition::SetTexture(const char* _name)
{
	p_mSprite->SetTexture(_name);
}
