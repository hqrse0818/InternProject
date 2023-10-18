#include "Com_DiagonalProjection.h"
#include "../System/Time.h"
#include "../../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_DiagonalProjection::Update()
{
	if (!bGravityReturn)
	{
		// ���ˊp����s��𐶐�
		Matrix mat = Matrix::CreateFromYawPitchRoll(ThrowAngle.y, ThrowAngle.x, ThrowAngle.z);

		// ���x�����߂�
		Vector3 speedVec = Vector3::Transform(InitSpeed, mat);

		// �ʒu�̕ω��ʂ����߂�
		Vector3 Trans = speedVec;
		Trans.x = Trans.x * Cnt;
		Trans.z = Trans.z * Cnt;
		Trans.y = Cnt * speedVec.y - ((Gravity * Cnt * Cnt) / 2);

		// ���݂̑��x��ۑ�
		speedVec.y = speedVec.y - (Gravity * Cnt);
		CurrentSpeed = speedVec;

		// �J�E���g��i�߂�
		Cnt += Time->GetDeltaTime();

		p_mObject->p_mTransform->Translate(Trans);
	}
	else
	{
		// ���ˊp����s��𐶐�
		Matrix mat = Matrix::CreateFromYawPitchRoll(ThrowAngle.y, ThrowAngle.x, ThrowAngle.z);

		// ���x�����߂�
		Vector3 speedVec = Vector3::Transform(InitSpeed, mat);

		// �ʒu�̕ω��ʂ����߂�
		Vector3 Trans = speedVec;
		Trans.x = Trans.x * Cnt;
		Trans.z = Trans.z * Cnt;
		Trans.y = Cnt * speedVec.y + ((Gravity * Cnt * Cnt) / 2);

		// ���݂̑��x��ۑ�
		speedVec.y = speedVec.y + (Gravity * Cnt);
		CurrentSpeed = speedVec;

		// �J�E���g��i�߂�
		Cnt += Time->GetDeltaTime();

		p_mObject->p_mTransform->Translate(Trans);
	}
}
