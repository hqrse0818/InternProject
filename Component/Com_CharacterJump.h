#pragma once
#include "Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //�W�����v���Ă��邩�ǂ���

	// �W�����v�̍����⑬�x��ݒ�
	float jumpHeight = 2.0f; // �W�����v�̍���
	float jumpSpeed = 1.0f;  // �W�����v�̏㏸���x

	// �W�����v�𐧌�
	float jumpDuration = jumpHeight / jumpSpeed;
	float jumpTimer = 0.0f;

public:
	Com_CharacterJump();
	void Update();
	void Jump();
};