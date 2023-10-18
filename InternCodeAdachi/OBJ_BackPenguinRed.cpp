#include "OBJ_BackPenguinRed.h"

OBJ_BackPenguinRed::OBJ_BackPenguinRed()
{
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("RedPenguin");
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
