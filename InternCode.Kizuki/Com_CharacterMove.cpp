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
	// カメラのビュー行列を取得
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

	// 入力から移動量を生成
	Vector3 Velocity = forward * fMoveSpeed * Time->GetDeltaTime() * _value;
	Velocity.y = 0;

	p_mObject->p_mTransform->Translate(Velocity);
}

void Com_CharacterMove::MoveX(float _value)
{
	// カメラのビュー行列を取得
	Matrix View = p_mCameraCom->GetViewMatrix();
	// 右向きベクトルを作成
	Matrix Rot = Matrix::CreateRotationY(Euler_To_Radian(90.0f));

	View = View * Rot;

	Vector3 right;
	right.x = View._31;
	right.y = View._32;
	right.z = View._33;

	// 入力から移動量を生成
	Vector3 Velocity = right * fMoveSpeed * Time->GetDeltaTime() * _value;
	Velocity.y = 0;

	p_mObject->p_mTransform->Translate(Velocity);
}

//Controllerはクラスで作る
//GetView行列