#include "Scene_Test2.h"
#include "../ComponentHeader.h"
#include "../System/Input.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;

void Scene_Test2::Init()
{
	bCheckCol = true; //当たり判定をアクティブ化

	Player = new OBJ_PlayerCharacter("Test");

	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_MODEL);
	Shader_buf->p_mPS->Load(PS_MODEL);
	Player->AddComponent(Shader_buf);

	Com_AssimpAnimation* Model_buf = new Com_AssimpAnimation();
	Model_buf->LoadModel("asset\\model\\pengin_v3.fbx", 0.5f, false);
	Model_buf->LoadAnimation("asset\\model\\pengin_v3.fbx", "anim");
	Player->AddComponent(Model_buf);

	Com_BoxCollider* Col_buf = new Com_BoxCollider();
	Col_buf->mSize = Vector3(1.0f, 1.0f, 1.0f);
	Player->AddComponent(Col_buf);

	// レイヤーの指定なしでキーオブジェクトとして追加
	AddKeyObject(Player);

	//ステージ
	Com_BoxCollider* bo_col = new Com_BoxCollider();
	bo_col->SetSize(6.0f, 1.0f, 6.0f); //大きさ設定
	bo_col->SetCenter(0.0f, 0.5f, 0.0f); //中心点設定
	bo_col->bMovable = true; //動くコライダーとして設定

	// テスト用ボックスコライダーオブジェクト
	GameObject* testObj = new GameObject("col");
	Col_buf = new Com_BoxCollider();
	testObj->AddComponent(Col_buf);
	testObj->p_mTransform->SetPosition(0.0f, 0.0f, 0.5f);

	AddGameObject(testObj);

	GameObject* Camera = new GameObject("Camera");
	Com_Camera* Camera_buf = new Com_Camera();
	Camera_buf->SetTarget(Player);
	Camera_buf->SetUseTarget(true);
	Camera->p_mTransform->SetPosition(0.0f, 3.0f, -5.0f);
	Camera->AddComponent(Camera_buf);

	// レイヤーを指定してオブジェクトを追加
	AddGameObject(Camera, 0);
}

void Scene_Test2::Update()
{
	Com_AssimpAnimation* anim = GetKeyObject("Test")->GetComponent<Com_AssimpAnimation>();

	anim->UpdateFrame();

	/*if (Math::Abs(Controller_Input::GetLeftStick(0).x) > 0.5f || Math::Abs(Controller_Input::GetLeftStick(0).y) > 0.5f)
	{
		anim->PlayAnimation("Run");
	}
	else
	{
		anim->PlayAnimation("Idle");
	}*/

	if (Controller_Input::GetButton(0, GAMEPAD_SHOULDER_L) == KEYSTATE::KEY_WHILE_DOWN)
	{
		Player->p_mTransform->Rotate(0.0f, -0.5f * Time->GetDeltaTime(), 0.0f);
	}
	if (Controller_Input::GetButton(0, GAMEPAD_SHOULDER_R) == KEYSTATE::KEY_WHILE_DOWN)
	{
		Player->p_mTransform->Rotate(0.0f, 0.5f * Time->GetDeltaTime(), 0.0f);
	}

	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_WHILE_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN)
	{
		anim->PlayAnimation("anim");
	}
}
