#include "Com_CharacterJump.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

Com_CharacterJump::Com_CharacterJump()
{
	jumpFlg = false; //ジャンプフラグを初期化
}

void Com_CharacterJump::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN)
	{
		Jump();
	}

	if (p_mObject->p_mTransform->mPosition.y >= 0.0f)
	{
		//重力
		m_Velocity.y -= 0.015f;

		//抵抗
		m_Velocity.y -= m_Velocity.y * 0.01f;
	}

	//移動
	p_mObject->p_mTransform->Translate(m_Velocity);

	//地面に着地したらリセット
	if (p_mObject->p_mTransform->mPosition.y <= 0.0f)
	{
		m_Velocity.y = 0.0f;
	}
}

void Com_CharacterJump::Jump()
{
	if (m_Velocity.y == 0.0f)
	{
		jumpFlg = true;
	}

	if (jumpFlg == true)
	{
		m_Velocity.y = 0.55f;
		jumpFlg = false;
	}
}
