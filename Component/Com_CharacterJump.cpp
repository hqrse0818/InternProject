#include "Com_CharacterJump.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

Com_CharacterJump::Com_CharacterJump()
{
}

void Com_CharacterJump::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN)
	{
		Jump();
	}
}

void Com_CharacterJump::Jump()
{
    while (jumpTimer < jumpDuration)
    {
        // �L�����N�^�[��������Ɉړ�
        p_mObject->p_mTransform->Translate(0.0f, jumpSpeed * Time->GetDeltaTime(), 0.0f);

        // �W�����v�^�C�}�[���X�V
        jumpTimer += Time->GetDeltaTime();

        // �n�ʂ̔���

        // �t���[�����X�V
        Update();
    }
}
