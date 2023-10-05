#include "OBJ_Penguin.h"
#include "Com_Foot.h"
#include "Com_Gravity.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

OBJ_Penguin::OBJ_Penguin()
{
	// シェーダー
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// モデル
	p_mModel = new Com_AssimpAnimation();
	p_mModel->LoadModel("asset\\model\\Penguin\\pengin_rig_v1.fbx", 1.0f, true);
	p_mModel->LoadAnimation("asset\\model\\Penguin\\pengin_anime_v1.fbx", "hand");
	p_mModel->PlayAnimation("hand");
	p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// ペンギン自身のコライダー
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);

	// 移動コンポーネント
	p_mMoveCom = new Com_CharacterMove();
	p_mMoveCom->SetMoveSpeed(15.0f);

	AddComponent(p_mMoveCom);

	// ジャンプコンポーネント
	p_mJumpCom = new Com_TestJump();
	p_mJumpCom->SetJumpPower(12.0f);

	AddComponent(p_mJumpCom);

	// 重力コンポーネント
	Com_Gravity* Gravity_buf = new Com_Gravity();
	p_mJumpCom->SetGravityCom(Gravity_buf);

	AddComponent(Gravity_buf);

	// 足場コンポーネント
	Com_Foot* Foot_buf = new Com_Foot();
	Foot_buf->SetGravityCom(Gravity_buf);
	Foot_buf->SetFootHeight(1.5f);
	Foot_buf->SetJumpCom(p_mJumpCom);
	AddComponent(Foot_buf);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

void OBJ_Penguin::Update()
{
	// ジャンプ
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && p_mJumpCom->GetIsJump() == false)
	{
		p_mJumpCom->SetJumpFlg(true);
	}
	// 移動
	p_mMoveCom->Move(Vector3(Controller_Input::GetLeftStick(0).x, 0.0f, Controller_Input::GetLeftStick(0).y));
	// アニメーションの更新
	p_mModel->UpdateFrame();

	GameObject::Update();
}
