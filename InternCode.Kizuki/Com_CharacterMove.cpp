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
	// �J�����̐��ʃx�N�g�����v�Z
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// ���K������
	Forward = Math::Normalize(Forward);

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

//Controller�̓N���X�ō��
//GetView�s��