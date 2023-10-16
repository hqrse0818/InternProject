#pragma once
#include "../Utility.h"

namespace Math
{
	using namespace DirectX::SimpleMath;
	
	// ���[�g���擾
	float GetRoot(float _num);
	// ����
	float GetDot(DirectX::SimpleMath::Vector3 _valueA, DirectX::SimpleMath::Vector3 _valueB);
	// �O��
	DirectX::SimpleMath::Vector3 GetCross(DirectX::SimpleMath::Vector3 _valuA, DirectX::SimpleMath::Vector3 _valueB);
	// �����擾(Vector3)
	float GetDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// �����擾(Vector2)
	float GetDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End);
	// 2�拗���擾
	float GetDoubleDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// 2�拗���擾
	float GetDoubleDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End);
	// �x�N�g���̒����擾
	float GetLength(DirectX::SimpleMath::Vector3 _val);
	// �x�N�g���̒�����2����擾
	float GetDoubleLength(DirectX::SimpleMath::Vector3 _val);
	// ���K��
	DirectX::SimpleMath::Vector3 Normalize(DirectX::SimpleMath::Vector3 _val);
	// �x�N�g���̕��������]�����߂�
	DirectX::SimpleMath::Matrix CalcMatrixFromVector(DirectX::SimpleMath::Vector3 _CurrentForward, DirectX::SimpleMath::Vector3 _TargetForward);
	// 2�_�Ԃ̃x�N�g���擾
	DirectX::SimpleMath::Vector3 GetVector(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// �w��̏搔���擾
	float GetPower(float _val, int _num);
	// ��Βl
	float Abs(float _val);
	// _min����_max�̒l�Ɏ��߂�
	float Clamp(float _val, float _min, float _max);
}