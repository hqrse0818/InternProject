#pragma once
#include "Component.h"
#include <SimpleMath.h>


class Com_Transform :
    public Component
{
private:
	// �I�u�W�F�N�g�̑O�����x�N�g���␳
	DirectX::SimpleMath::Vector3 mForwardTuneValue = DirectX::SimpleMath::Vector3(0.0f,0.0f,0.0f);

public:
	// parameters
	// �|�W�V����
	DirectX::SimpleMath::Vector3 mPosition = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	// ��]
	DirectX::SimpleMath::Vector3 mRotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	// �X�P�[��
	DirectX::SimpleMath::Vector3 mScale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
	// �A���O��
	DirectX::SimpleMath::Vector3 mEulerAngle = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	// �O�����x�N�g��
	DirectX::SimpleMath::Vector3 mForward = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	// �������x�N�g��
	DirectX::SimpleMath::Vector3 mLeft = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

public:
	// functions
	void Translate(DirectX::SimpleMath::Vector3 _val)
	{
		mPosition += _val;
	};
	void Translate(float _x, float _y, float _z)
	{
		mPosition.x += _x;
		mPosition.y += _y;
		mPosition.z += _z;
	};

	void Rotate(DirectX::SimpleMath::Vector3 _val)
	{
		mRotation += _val;
	};
	void Rotate(float _x, float _y, float _z)
	{
		mRotation.x += _x;
		mRotation.y += _y;
		mRotation.z += _z;
	};
	void Scaling(DirectX::SimpleMath::Vector3 _val)
	{
		mScale += _val;
	};
	void Scaling(float _x, float _y, float _z)
	{
		mScale.x += _x;
		mScale.y += _y;
		mScale.z += _z;
	};
	void SetTune(DirectX::SimpleMath::Vector3 _val)
	{
		mForwardTuneValue = _val;
	};
	void SetTune(float _x, float _y, float _z)
	{
		mForwardTuneValue.x = _x;
		mForwardTuneValue.y = _y;
		mForwardTuneValue.z = _z;
	};
	void SetPosition(float _x, float _y, float _z)
	{
		mPosition.x = _x;
		mPosition.y = _y;
		mPosition.z = _z;
	};
	void SetScale(float _x, float _y, float _z)
	{
		mScale.x = _x;
		mScale.y = _y;
		mScale.z = _z;
	};
	void SetRotation(float _x, float _y, float _z)
	{
		mRotation.x = _x;
		mRotation.y = _y;
		mRotation.z = _z;
	};
	void SetAngle(DirectX::SimpleMath::Vector3 _val);
	void SetAngle(float _x, float _y, float _z);
	void SetForward(DirectX::SimpleMath::Vector3 _val);
	DirectX::SimpleMath::Vector3 GetTune()
	{
		return mForwardTuneValue;
	};

	void Update()override;
	void PreDraw()override;
};

