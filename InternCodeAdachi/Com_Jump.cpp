#include "Com_Jump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"
#include "../Component/Com_BoxCollider.h"
#include "../InternCode.Kizuki/OBJ_Inpact.h"
#include "../Scene/Scene.h"

using namespace DirectX::SimpleMath;

//ジャンプ処理
void Com_Jump::Jump()
{
	fFallTime = 1.0f;

	Vector3 Velocity = Vector3(0.0f, 0.0f, 0.0f);
	Velocity.y = fJumpPower;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(Velocity);
}

//着地処理
void Com_Jump::HipDrop()
{
	//落下の速さ
	Vector3 fDropVelocity = Vector3(0.0f, 0.0f, 0.0f);
	//落下時間をかける
	fDropVelocity.y = fDropPower * fFallTime;
	//落下時間を加算
	fFallTime += 1.0f;
	fDropVelocity.y *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(fDropVelocity);
}

void Com_Jump::Update()
{
	//ジャンプフラグがtrue
	if (bJump)
	{
		Jump(); //ジャンプ関数

		//空中でBを押したとき
		if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bDrop == false)
		{
			bDrop = true; //ドロップをtrue
			bJump = false; //ジャンプをフォルス
		}
	}

	//地上でBを押したとき
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bJump == false)
	{
		//落下時間をリセット
		fFallTime = 1.0f;

		bJump = true; //ジャンプフラグをtrue
		p_mGravityCom->SetGround(false);
	}

	if (bDrop)
	{
		HipDrop();
	}
}

void Com_Jump::OnCollisionEnter(GameObject* _obj)
{
	if (bDrop)
	{
		OBJ_Inpact* Inpact = new OBJ_Inpact("Inpact");

		Inpact->p_mTransform->mPosition = p_mObject->p_mTransform->mPosition;

		GameObject::GetScene()->AddGameObject(Inpact);
	}
}
