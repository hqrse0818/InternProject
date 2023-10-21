#include "OBJ_BackPenguinRed.h"
#include "../System/Time.h"

OBJ_BackPenguinRed::OBJ_BackPenguinRed()
{
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("RedPenguin");
	p_mModelCom->SetAnimNumber(0);
	AddComponent(p_mModelCom);
}

OBJ_BackPenguinRed::OBJ_BackPenguinRed(const char* _name)
	: OBJ_BackPenguinRed()
{
	sObjectName = _name;
}

void OBJ_BackPenguinRed::PlayAnimaion(const char* _name)
{
	p_mModelCom->PlayAnimation(_name);
}

void OBJ_BackPenguinRed::Update()
{
	GameObject::Update();
	fCnt += Time->GetDeltaTime();

	if (fCnt > fDelay)
	{
		p_mModelCom->PlayAnimation("Red");
	}
}
