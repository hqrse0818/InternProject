#include "Com_Jump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"
#include "../Component/Com_BoxCollider.h"
#include "../InternCode.Kizuki/OBJ_Inpact.h"
#include "../Scene/Scene.h"
#include <iostream>

using namespace DirectX::SimpleMath;
using namespace std;

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
	fDropCnt += Time->GetDeltaTime();
	Vector3 fDropVelocity = Vector3(0.0f, 0.0f, 0.0f);
	fDropVelocity.y = fDropSpeed * fDropCnt + fDropInitialSpeed;
	fDropVelocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(fDropVelocity);
}

void Com_Jump::Update()
{
	//�W�����v�t���O��true
	if (bJump)
	{
		Jump(); //�W�����v�֐�
	}
	if (bDrop)
	{
		HipDrop();
	}
}

void Com_Jump::OnCollisionEnter(GameObject* _obj)
{
	//�R���C�_�[�̃^�C�v���擾
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		//�{�b�N�X�Ȃ�{�b�N�X�R���C�_�[���擾
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();

		//�h���b�v�t���O��true
		if (bDrop)
		{
			//�Ռ��I�u�W�F�N�g���Ăяo��
			OBJ_Inpact* Inpact = new OBJ_Inpact("Inpact");

			Inpact->p_mTransform->mPosition = p_mObject->p_mTransform->mPosition;

			GameObject::GetScene()->AddGameObject(Inpact);

			//��������͈͂ƈЗ͂�ݒ�
			Inpact->GetColliderCom()->fRadius = fJumpHeight; //�͈�
			Inpact->SetInpactPower(fJumpPower); //�З͂̐ݒ�
			cout << fJumpHeight << endl;

			Inpact->Init();
		}
	}
}

void Com_Jump::SetJumpHeight()
{
	fJumpHeight = p_mObject->p_mTransform->mPosition.y;
}
