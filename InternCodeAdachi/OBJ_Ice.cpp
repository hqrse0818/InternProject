#include "OBJ_Ice.h"

OBJ_Ice::OBJ_Ice()
{
	// シェーダー
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	//p_mShaderCom->p_mPS->Load(PS_MODEL);
	p_mShaderCom->p_mPS->Load("shader\\PS_NoHitLine.cso");

	AddComponent(p_mShaderCom);

	// モデル
	p_mModelCom = new Com_AssimpAnimation();
	p_mModelCom->LoadModel("asset\\model\\stage_v2.fbx", 1.0f, false);

	AddComponent(p_mModelCom);

	// コライダー
	p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(7.0f, 1.0f, 7.0f);
	p_mCollider->SetCenter(0.0f, 0.5f, 0.0f);
	p_mCollider->bCanStepOn = true;

	AddComponent(p_mCollider);
}

OBJ_Ice::OBJ_Ice(const char* _name)
	: OBJ_Ice()
{
	sObjectName = _name;
}
