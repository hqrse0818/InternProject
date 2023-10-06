#include "Com_Jump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

void Com_Jump::Jump()
{
	Vector3 Velocity = Vector3(0.0f, 0.0f, 0.0f);
	Velocity.y = fJumpPower;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(Velocity);
}

void Com_Jump::HipDrop()
{
	Vector3 fDropVelocity = Vector3(0.0f, 0.0f, 0.0f);
	fDropVelocity.y = fDropPower;
	fDropVelocity.y *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(fDropVelocity);
}

void Com_Jump::Update()
{
	//ジャンプフラグがtrue
	if (bJump)
	{
		Jump(); //ジャンプ関数

		if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bDrop == false)
		{
			bDrop = true;
			bJump = false;
		}
	}

	//Bボタンを押してジャンプフラグがfalse
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bJump == false)
	{
		bJump = true; //ジャンプフラグをtrue
		p_mGravityCom->SetGround(false);
	}

	if (bDrop)
	{
		HipDrop();
	}
}
