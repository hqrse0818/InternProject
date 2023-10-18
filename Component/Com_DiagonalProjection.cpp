#include "Com_DiagonalProjection.h"
#include "../System/Time.h"
#include "../../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_DiagonalProjection::Update()
{
	if (!bGravityReturn)
	{
		// 投射角から行列を生成
		Matrix mat = Matrix::CreateFromYawPitchRoll(ThrowAngle.y, ThrowAngle.x, ThrowAngle.z);

		// 速度を求める
		Vector3 speedVec = Vector3::Transform(InitSpeed, mat);

		// 位置の変化量を求める
		Vector3 Trans = speedVec;
		Trans.x = Trans.x * Cnt;
		Trans.z = Trans.z * Cnt;
		Trans.y = Cnt * speedVec.y - ((Gravity * Cnt * Cnt) / 2);

		// 現在の速度を保存
		speedVec.y = speedVec.y - (Gravity * Cnt);
		CurrentSpeed = speedVec;

		// カウントを進める
		Cnt += Time->GetDeltaTime();

		p_mObject->p_mTransform->Translate(Trans);
	}
	else
	{
		// 投射角から行列を生成
		Matrix mat = Matrix::CreateFromYawPitchRoll(ThrowAngle.y, ThrowAngle.x, ThrowAngle.z);

		// 速度を求める
		Vector3 speedVec = Vector3::Transform(InitSpeed, mat);

		// 位置の変化量を求める
		Vector3 Trans = speedVec;
		Trans.x = Trans.x * Cnt;
		Trans.z = Trans.z * Cnt;
		Trans.y = Cnt * speedVec.y + ((Gravity * Cnt * Cnt) / 2);

		// 現在の速度を保存
		speedVec.y = speedVec.y + (Gravity * Cnt);
		CurrentSpeed = speedVec;

		// カウントを進める
		Cnt += Time->GetDeltaTime();

		p_mObject->p_mTransform->Translate(Trans);
	}
}
