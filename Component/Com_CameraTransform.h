#pragma once
#include "Component.h"
#include "Com_Camera.h"
#include "../GameObject/GameObject.h"
#include "../System/Input.h"

class Com_CameraTransform :
	public Com_Camera
{
protected:
	//�J�����̈ړ����x
	float moveSpeed = 0.1f;

	//�㉺���E�̈ړ����擾
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

		//// �J�����̈ʒu���ړ�
		//DirectX::SimpleMath::Vector3 cameraPosition = p_mObject->p_mTransform->mPosition;
		//cameraPosition += mUp * moveY;
		//cameraPosition += mViewMatrix.Right() * moveX;  // �E�����x�N�g�����g�p

		// �V�����J�����̈ʒu��ݒ�
		/*p_mObject->p_mTransform->mPosition = cameraPosition;*/

		// �r���[�s����X�V���邽�߂Ɋ�{�N���X�� Update() ���\�b�h���Ăяo��
		Com_Camera::Update();
	}
};