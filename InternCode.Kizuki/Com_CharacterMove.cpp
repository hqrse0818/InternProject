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
	// カメラの正面ベクトルを計算
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// 正規化する
	Forward = Math::Normalize(Forward);

	Forward *= _value * fMoveSpeed * Time->GetDeltaTime();
	Forward.y = 0.0f;
	p_mObject->p_mTransform->Translate(Forward);
}

void Com_CharacterMove::MoveX(float _value)
{
	// カメラの正面ベクトルを計算
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	Forward = Math::Normalize(Forward);

	// 右向きベクトルを抜き出す
	Vector3 Right = Math::GetCross(Vector3::Up, Forward);

	// 入力から移動量を生成
	Right *= _value * fMoveSpeed * Time->GetDeltaTime();
	Right.y = 0.0f;

	p_mObject->p_mTransform->Translate(Right);
}

//Controllerはクラスで作る
//GetView行列