#include "Com_CharacterMove.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Camera.h"
#include "../System/CustomMath.h"
#include <iostream>

using namespace DirectX::SimpleMath;
using namespace std;

Com_CharacterMove::Com_CharacterMove()
{
}

void Com_CharacterMove::MoveZ(float _value)
{
	// �J�����̐��ʃx�N�g�����v�Z
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// ���K������
	Forward = Math::Normalize(Forward);

	// �J�����̌����Ɠ��͒l����I�u�W�F�N�g�̌������Z�o

	Forward *= _value * fMoveSpeed * Time->GetDeltaTime();
	Forward.y = 0.0f;
	p_mObject->p_mTransform->Translate(Forward);
}

void Com_CharacterMove::MoveX(float _value)
{
	// �J�����̐��ʃx�N�g�����v�Z
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	Forward = Math::Normalize(Forward);

	// �E�����x�N�g���𔲂��o��
	Vector3 Right = Math::GetCross(Vector3::Up, Forward);

	// ���͂���ړ��ʂ𐶐�
	Right *= _value * fMoveSpeed * Time->GetDeltaTime();
	Right.y = 0.0f;

	p_mObject->p_mTransform->Translate(Right);
}

void Com_CharacterMove::Move(float _x, float _z)
{
	// �ړ��O�̏���ۑ�
	Vector3 CurrentPos = p_mObject->p_mTransform->mPosition;

	// �J�����̐��ʃx�N�g�����v�Z
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// ���K������
	Forward = Math::Normalize(Forward);
	// �E�����x�N�g���𔲂��o��
	Vector3 Right = Math::GetCross(Vector3::Up, Forward);

	Forward *= _z * fMoveSpeed * Time->GetDeltaTime();
	Forward.y = 0.0f;
	// ���͂���ړ��ʂ𐶐�
	Right *= _x * fMoveSpeed * Time->GetDeltaTime();
	Right.y = 0.0f;

	// ��������&������������
	Vector3 Velocity = Forward + Right;
	p_mObject->p_mTransform->Translate(Velocity);

	// �����������������߂�
	Vector3 CurrentForward = p_mObject->p_mTransform->mForward;
	Vector3 MyPos = p_mObject->p_mTransform->mPosition * 2;
	// ������������
	Vector3 TargetVector = MyPos - CurrentPos;
	// ���K�����ē��ς����߂�
	TargetVector = Math::Normalize(TargetVector);
	CurrentForward = Math::Normalize(CurrentForward);
	float dot = Math::GetDot(TargetVector, CurrentForward);
	float angle = acos(dot);

}

//Controller�̓N���X�ō��
//GetView�s��