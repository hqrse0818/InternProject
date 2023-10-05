#pragma once
#include "../Component/Component.h"
#include "../GameObject/GameObject.h"

class Com_CharacterJump :public Component
{
protected:
	bool jumpFlg = false; //ジャンプフラグ
	bool hipDropFlg = false; //ヒップドロップフラグ
	DirectX::SimpleMath::Vector3 m_Velocity{}; //速度
	float gravity = 4.0f; //重力
	float fallTime = 0.0; //落下時間
	float jumpPow = 0.6; //ジャンプ力

public:
	Com_CharacterJump();
	void Update();
	void Jump(); //ジャンプ関数
	void HipDrop(); //ヒップドロップ関数
};

//ジャンプの高さなどは別で定義
//プランナーがcsvで操作しやすいように