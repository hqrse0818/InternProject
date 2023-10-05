#include "Com_CharacterMove.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Camera.h"

using namespace DirectX::SimpleMath;

Com_CharacterMove::Com_CharacterMove()
{
}

void Com_CharacterMove::Move(DirectX::SimpleMath::Vector3 _value)
{
	// �J�����̃r���[�s����擾
	Matrix View = p_mCameraCom->GetViewMatrix();
	Vector3 forward = -View.Forward();
	// �r���[�s���0�̒l�������Ă����ꍇ
	if (abs(forward.x) <= 0.1f)
	{
		forward.x = 1;
	}
	if (abs(forward.z) <= 0.1f)
	{
		forward.z = 1;
	}
	// ���͂��ꂽ�l�Ɛ��ʃx�N�g�����v�Z
	_value = _value * forward ;
	// ���̈ړ����x���|����
	_value = _value * fMoveSpeed;
	// �ŏI�I�Ȉړ��ʂ�����o��
	_value = _value * Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(_value);
}

//Controller�̓N���X�ō��
//GetView�s��