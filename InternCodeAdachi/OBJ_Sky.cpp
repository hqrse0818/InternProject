#include "OBJ_Sky.h"
#include "../System/Time.h"
#include "../Utility.h"

OBJ_Sky::OBJ_Sky()
{
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShader);

	p_mModel = new Com_Model();
	p_mModel->SetModelData("Sky");
	AddComponent(p_mModel);
}

OBJ_Sky::OBJ_Sky(const char* _name)
	: OBJ_Sky()
{
	sObjectName = _name;
}

void OBJ_Sky::Update()
{
	GameObject::Update();

	Rotate(0.0f, Euler_To_Radian(fRotSpeed) * Time->GetDeltaTime(), 0.0f);
}
