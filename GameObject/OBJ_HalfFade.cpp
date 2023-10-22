#include "OBJ_HalfFade.h"
#include "../System/Time.h"

OBJ_HalfFade::OBJ_HalfFade()
{
	// •‚ÉÝ’è
	mColor.x = 0.0f;
	mColor.y = 0.0f;
	mColor.z = 0.0f;
}

OBJ_HalfFade::OBJ_HalfFade(const char* _name)
	: OBJ_HalfFade()
{
	sObjectName = _name;
}

void OBJ_HalfFade::Update()
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
		if (mColor.w >= fAlpha)
		{
			mState = FadeState::OutEnd;
		}
		break;
	case OBJ_Transition::FadeState::OutEnd:
		mColor.w = fAlpha;
		break;
	default:
		break;
	}

	MATERIAL mat{};
	mat.Diffuse = mColor;
	p_mSprite->SetMaterial(mat);

	GameObject::Update();
}
