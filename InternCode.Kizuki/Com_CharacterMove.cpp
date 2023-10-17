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
	// カメラの正面ベクトルを計算
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// 正規化する
	Forward = Math::Normalize(Forward);

	// カメラの向きと入力値からオブジェクトの向きを算出

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

void Com_CharacterMove::Move(float _x, float _z)
{
	// 移動前の情報を保存
	Vector3 CurrentPos = p_mObject->p_mTransform->mPosition;

	// カメラの正面ベクトルを計算
	Vector3 Target = p_mCameraCom->GetTargetPosition();
	Vector3 CamPos = p_mCameraCom->p_mObject->p_mTransform->mPosition;
	Vector3 Forward = Math::GetVector(CamPos, Target);
	// 正規化する
	Forward = Math::Normalize(Forward);
	// 右向きベクトルを抜き出す
	Vector3 Right = Math::GetCross(Vector3::Up, Forward);

	Forward *= _z * fMoveSpeed * Time->GetDeltaTime();
	Forward.y = 0.0f;
	// 入力から移動量を生成
	Right *= _x * fMoveSpeed * Time->GetDeltaTime();
	Right.y = 0.0f;

	// 動く方向&向きたい方向
	Vector3 Velocity = Forward + Right;
	p_mObject->p_mTransform->Translate(Velocity);

	// 向きたい方向を求める
	Vector3 CurrentForward = p_mObject->p_mTransform->mForward;
	Vector3 MyPos = p_mObject->p_mTransform->mPosition * 2;
	// 向きたい方向
	Vector3 TargetVector = MyPos - CurrentPos;
	// 正規化して内積を求める
	TargetVector = Math::Normalize(TargetVector);
	CurrentForward = Math::Normalize(CurrentForward);
	float dot = Math::GetDot(TargetVector, CurrentForward);
	float angle = acos(dot);

}

//Controllerはクラスで作る
//GetView行列