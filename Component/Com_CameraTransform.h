#pragma once
#include "Component.h"
#include "Com_Camera.h"
#include "../GameObject/GameObject.h"
#include "../System/Input.h"

class Com_CameraTransform :
	public Com_Camera
{
protected:
	//カメラの移動速度
	float moveSpeed = 0.1f;

	//上下左右の移動を取得
	float moveX = 0.0f;
	float moveY = 0.0f;

public:
	void Update() override
	{
		if (Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_WHILE_DOWN)
		{
			p_mObject->p_mTransform->Translate(0.0f, 0.0f, moveSpeed);
		}

		if (Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_WHILE_DOWN)
		{
			p_mObject->p_mTransform->Translate(0.0f, 0.0f, -moveSpeed);
		}

		if (Input::GetKeyState(KEYCODE_A) == KEYSTATE::KEY_WHILE_DOWN)
		{
			p_mObject->p_mTransform->Translate(-moveSpeed, 0.0f, 0.0f);
		}

		if (Input::GetKeyState(KEYCODE_D) == KEYSTATE::KEY_WHILE_DOWN)
		{
			p_mObject->p_mTransform->Translate(moveSpeed, 0.0f, 0.0f);
		}

		//// カメラの位置を移動
		//DirectX::SimpleMath::Vector3 cameraPosition = p_mObject->p_mTransform->mPosition;
		//cameraPosition += mUp * moveY;
		//cameraPosition += mViewMatrix.Right() * moveX;  // 右方向ベクトルを使用

		// 新しいカメラの位置を設定
		/*p_mObject->p_mTransform->mPosition = cameraPosition;*/

		// ビュー行列を更新するために基本クラスの Update() メソッドを呼び出す
		Com_Camera::Update();
	}
};