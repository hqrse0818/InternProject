#include "OBJ_BackGround.h"

OBJ_BackGround::OBJ_BackGround()
{
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("BackGround");
	AddComponent(p_mModelCom);
}

OBJ_BackGround::OBJ_BackGround(const char* _name)
	: OBJ_BackGround()
{
	sObjectName = _name;
}
