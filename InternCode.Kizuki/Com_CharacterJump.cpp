#include "Com_CharacterJump.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

Com_CharacterJump::Com_CharacterJump()
{
	jumpFlg = false; //�W�����v�t���O��������
}

void Com_CharacterJump::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN)
	{
		Jump();
		HipDrop();
	}

	if (p_mObject->p_mTransform->mPosition.y >= 0.0f)
	{
		//�d��
		m_Velocity.y -= 0.015f;

		//��R
		m_Velocity.y -= m_Velocity.y * 0.01f;
	}

	//�ړ�
	p_mObject->p_mTransform->Translate(m_Velocity);

	//�n�ʂɒ��n�����烊�Z�b�g
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

void Com_CharacterJump::HipDrop()
{
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN
		&& m_Velocity.y <=0.55)
	{
		m_Velocity.y = 0.0f;
	}
}

//�q�b�v�h���b�v�͉������^�C�~���O�ŗ������悤�ɂ���i�A�łł������Ƃ���j