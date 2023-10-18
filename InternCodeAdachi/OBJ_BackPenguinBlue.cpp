#include "OBJ_BackPenguinBlue.h"

OBJ_BackPenguinBlue::OBJ_BackPenguinBlue()
{
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("BluePenguin");
	AddComponent(p_mModelCom);
}

OBJ_BackPenguinBlue::OBJ_BackPenguinBlue(const char* _name)
	: OBJ_BackPenguinBlue()
{
	sObjectName = _name;
}

void OBJ_BackPenguinBlue::PlayAnimation(const char* _name)
{
	p_mModelCom->PlayAnimation(_name);
}
