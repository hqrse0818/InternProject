#include "OBJ_Penguin.h"
#include "Com_Foot.h"
#include "Com_Gravity.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "Com_TestJump.h"

OBJ_Penguin::OBJ_Penguin()
{
	// シェーダー
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// モデル
	p_mModel = new Com_AssimpAnimation();
	p_mModel->LoadModel("asset\\model\\Penguin\\pengin_v4.fbx", 1.0f, true);
	p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// ペンギン自身のコライダー
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);

	// ジャンプコンポーネント
	Com_TestJump* Jump_buf = new Com_TestJump();
	Jump_buf->SetJumpPower(20.0f);

	AddComponent(Jump_buf);

	// 重力コンポーネント
	Com_Gravity* Gravity_buf = new Com_Gravity();
	Jump_buf->SetGravityCom(Gravity_buf);

	AddComponent(Gravity_buf);

	// 足場コンポーネント
	Com_Foot* Foot_buf = new Com_Foot();
	Foot_buf->SetGravityCom(Gravity_buf);
	Foot_buf->SetFootHeight(1.0f);
	Foot_buf->SetJumpCom(Jump_buf);
	AddComponent(Foot_buf);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

void OBJ_Penguin::Update()
{
	//p_mFoot->p_mTransform->mPosition = p_mTransform->mPosition;

	GameObject::Update();
}
