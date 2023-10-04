#pragma once
#include "../Component/Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //ジャンプしているかどうか
	DirectX::SimpleMath::Vector3 m_Velocity{};
	float gravity = 4.0f; //重力
	float fallTime = 0.0; //落下時間
	float jumpPow = 10.0f; //ジャンプ力

public:
	Com_CharacterJump();
	void Update();
	void Jump();
};

//ジャンプの高さなどは別で定義
//プランナーがcsvで操作しやすいように