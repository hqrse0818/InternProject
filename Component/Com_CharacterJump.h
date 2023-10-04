#pragma once
#include "Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //ジャンプしているかどうか

	// ジャンプの高さや速度を設定
	float jumpHeight = 2.0f; // ジャンプの高さ
	float jumpSpeed = 1.0f;  // ジャンプの上昇速度

	// ジャンプを制御
	float jumpDuration = jumpHeight / jumpSpeed;
	float jumpTimer = 0.0f;

public:
	Com_CharacterJump();
	void Update();
	void Jump();
};