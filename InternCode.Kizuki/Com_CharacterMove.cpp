#include "Com_CharacterMove.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Camera.h"
#include "../System/CustomMath.h"

using namespace DirectX::SimpleMath;

Com_CharacterMove::Com_CharacterMove()
{
}

void Com_CharacterMove::MoveZ(float _value)
{
	// �J�����̃r���[�s����擾
	Matrix View = p_mCameraCom->GetViewMatrix();
	Vector3 forward;
	forward.x = View._31;
	forward.y = View._32;
	forward.z = View._33;

	static int fra = 0;
	fra++;
	if (fra > 100)
	{
		fra = 0;
	}

	// ���͂���ړ��ʂ𐶐�
	Vector3 Velocity = forward * fMoveSpeed * Time->GetDeltaTime() * _value;
	Velocity.y = 0;

	p_mObject->p_mTransform->Translate(Velocity);
}

void Com_CharacterMove::MoveX(float _value)
{
	// �J�����̃r���[�s����擾
	Matrix View = p_mCameraCom->GetViewMatrix();
	// �E�����x�N�g�����쐬
	Matrix Rot = Matrix::CreateRotationY(Euler_To_Radian(90.0f));

	View = View * Rot;

	Vector3 right;
	right.x = View._31;
	right.y = View._32;
	right.z = View._33;

	// ���͂���ړ��ʂ𐶐�
	Vector3 Velocity = right * fMoveSpeed * Time->GetDeltaTime() * _value;
	Velocity.y = 0;

	p_mObject->p_mTransform->Translate(Velocity);
}

//Controller�̓N���X�ō��
//GetView�s��