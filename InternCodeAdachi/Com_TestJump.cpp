#include "Com_TestJump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

void Com_TestJump::Jump()
{
	Vector3 Velocity = Vector3(0.0f, 0.0f, 0.0f);
	Velocity.y = fJumpPower;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(Velocity);
}

void Com_TestJump::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN && bJump == false)
	{
		bJump = true;
		p_mGravityCom->SetGround(false);
	}

	if (bJump)
	{
		Jump();
	}
}
