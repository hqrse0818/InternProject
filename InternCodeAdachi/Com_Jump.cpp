#include "Com_Jump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"
#include "../Component/Com_BoxCollider.h"
#include "../InternCode.Kizuki/OBJ_Inpact.h"
#include "../Scene/Scene.h"

using namespace DirectX::SimpleMath;

//�W�����v����
void Com_Jump::Jump()
{
	fFallTime = 1.0f;

	Vector3 Velocity = Vector3(0.0f, 0.0f, 0.0f);
	Velocity.y = fJumpPower;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(Velocity);
}

//���n����
void Com_Jump::HipDrop()
{
	//�����̑���
	Vector3 fDropVelocity = Vector3(0.0f, 0.0f, 0.0f);
	//�������Ԃ�������
	fDropVelocity.y = fDropPower * fFallTime;
	//�������Ԃ����Z
	fFallTime += 1.0f;
	fDropVelocity.y *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(fDropVelocity);
}

void Com_Jump::Update()
{
	//�W�����v�t���O��true
	if (bJump)
	{
		Jump(); //�W�����v�֐�

		//�󒆂�B���������Ƃ�
		if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bDrop == false)
		{
			bDrop = true; //�h���b�v��true
			bJump = false; //�W�����v���t�H���X
		}
	}

	//�n���B���������Ƃ�
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && bJump == false)
	{
		//�������Ԃ����Z�b�g
		fFallTime = 1.0f;

		bJump = true; //�W�����v�t���O��true
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
