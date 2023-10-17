#include "OBJ_Shadow.h"

OBJ_Shadow::OBJ_Shadow()
{
	p_mTarget = nullptr;

	p_mShaderCom = new Com_Shader;
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);
	p_mShadowCom = new Com_Shadow();
	p_mShadowCom->SetSize(4.0f, 4.0f);
	p_mShadowCom->SetPositionY(2.1f);
	AddComponent(p_mShadowCom);
	p_mTransform->mPosition.y = 1.0f;
}

OBJ_Shadow::OBJ_Shadow(const char* _name)
	:OBJ_Shadow()
{
	sObjectName = _name;
}

void OBJ_Shadow::Init()
{
	GameObject::Init();
	p_mTransform->mPosition.x = p_mTarget->p_mTransform->mPosition.x;
	p_mTransform->mPosition.z = p_mTarget->p_mTransform->mPosition.z;
}

void OBJ_Shadow::Update()
{
	if (bActive)
	{
		GameObject::Update();

		p_mTransform->mPosition.x = p_mTarget->p_mTransform->mPosition.x;
		p_mTransform->mPosition.z = p_mTarget->p_mTransform->mPosition.z;

		float distance = p_mTarget->p_mTransform->mPosition.y - p_mTransform->mPosition.y;

		// ‹——£‚ª‰“‚¢‚Ù‚ÇƒTƒCƒY‚ª¬‚³‚­‚È‚é
		float OutSize = 5.0f - (distance / 10);
		p_mShadowCom->SetSize(OutSize, OutSize);
	}
}

void OBJ_Shadow::SetTarget(GameObject* _target)
{
	p_mTarget = _target;
}