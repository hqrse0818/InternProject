#pragma once
#include "../Component/Component.h"
#include "../GameObject/GameObject.h"

class Com_Camera;

class Com_CharacterMove :public Component
{
private:
	float fMoveSpeed = 5.0f;
	Com_Camera* p_mCameraCom = nullptr;

public:
	Com_CharacterMove();

	void SetMoveSpeed(float _val)
	{
		fMoveSpeed = _val;
	}

	void Move(DirectX::SimpleMath::Vector3 _value);

	void SetCameraCom(Com_Camera* _com)
	{
		p_mCameraCom = _com;
	}
};