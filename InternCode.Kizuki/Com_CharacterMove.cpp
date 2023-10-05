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
	// カメラのビュー行列を取得
	Matrix View = p_mCameraCom->GetViewMatrix();
	Vector3 forward = -View.Forward();
	// ビュー行列に0の値が入っていた場合
	if (abs(forward.x) <= 0.1f)
	{
		forward.x = 1;
	}
	if (abs(forward.z) <= 0.1f)
	{
		forward.z = 1;
	}
	// 入力された値と正面ベクトルを計算
	_value = _value * forward ;
	// 元の移動速度を掛ける
	_value = _value * fMoveSpeed;
	// 最終的な移動量を割り出す
	_value = _value * Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(_value);
}

//Controllerはクラスで作る
//GetView行列