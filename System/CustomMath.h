#pragma once
#include "../Utility.h"

namespace Math
{
	using namespace DirectX::SimpleMath;
	
	// ルートを取得
	float GetRoot(float _num);
	// 内積
	float GetDot(DirectX::SimpleMath::Vector3 _valueA, DirectX::SimpleMath::Vector3 _valueB);
	// 外積
	DirectX::SimpleMath::Vector3 GetCross(DirectX::SimpleMath::Vector3 _valuA, DirectX::SimpleMath::Vector3 _valueB);
	// 距離取得(Vector3)
	float GetDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// 距離取得(Vector2)
	float GetDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End);
	// 2乗距離取得
	float GetDoubleDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// 2乗距離取得
	float GetDoubleDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End);
	// ベクトルの長さ取得
	float GetLength(DirectX::SimpleMath::Vector3 _val);
	// ベクトルの長さの2上を取得
	float GetDoubleLength(DirectX::SimpleMath::Vector3 _val);
	// 正規化
	DirectX::SimpleMath::Vector3 Normalize(DirectX::SimpleMath::Vector3 _val);
	// ベクトルの方向から回転を求める
	DirectX::SimpleMath::Matrix CalcMatrixFromVector(DirectX::SimpleMath::Vector3 _CurrentForward, DirectX::SimpleMath::Vector3 _TargetForward);
	// 自身の回転から目標の正面ベクトルの方向に回転させるための値を取得する関数
	DirectX::SimpleMath::Vector3 RotatoVectorTowardsTarget(DirectX::SimpleMath::Vector3 _myRotation, DirectX::SimpleMath::Vector3 _targetForward);
	// y軸を中心に自身の回転から目標の正面ベクトルの方向に回転させるための値を取得する関数
	DirectX::SimpleMath::Vector3 RotatoVectorTowardsTargetY(DirectX::SimpleMath::Vector3 _myRotation, DirectX::SimpleMath::Vector3 _targetForward);
	// 2点間のベクトル取得
	DirectX::SimpleMath::Vector3 GetVector(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End);
	// 指定の乗数を取得
	float GetPower(float _val, int _num);
	// 絶対値
	float Abs(float _val);
	// _minから_maxの値に収める
	float Clamp(float _val, float _min, float _max);
}