#include "Com_Transform.h"
#include "../Utility.h"

using namespace DirectX::SimpleMath;

void Com_Transform::SetAngle(DirectX::SimpleMath::Vector3 _val)
{
	// オイラー角から自身の回転をセット
	mEulerAngle = _val;
	mRotation.x = (float)Euler_To_Radian(mEulerAngle.x);
	mRotation.y = (float)Euler_To_Radian(mEulerAngle.y);
	mRotation.z = (float)Euler_To_Radian(mEulerAngle.z);
}

void Com_Transform::SetAngle(float _x, float _y, float _z)
{
	// オイラー角から自身の回転をセット
	mEulerAngle.x = _x;
	mEulerAngle.y = _y;
	mEulerAngle.z = _z;

	mRotation.x = (float)Euler_To_Radian(mEulerAngle.x);
	mRotation.y = (float)Euler_To_Radian(mEulerAngle.y);
	mRotation.z = (float)Euler_To_Radian(mEulerAngle.z);
}

void Com_Transform::SetForward(DirectX::SimpleMath::Vector3 _val)
{
	mForward = _val;
	// セットされた前向きベクトルから回転角度を得るための前向きベクトルを取得
	DirectX::SimpleMath::Matrix myrotation;
	myrotation = DirectX::XMMatrixLookAtLH(mPosition, _val, DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));

	Quaternion rotation;
	Vector3 scale;
	Vector3 pos;
	myrotation.Decompose(scale, rotation, pos);

	mRotation.x = rotation.x;
	mRotation.y = rotation.y;
	mRotation.z = rotation.z;

}

void Com_Transform::Update()
{
	DirectX::SimpleMath::Matrix MyRotation;
	// 自身の回転角度から前向きベクトルを得るための行列を生成
	MyRotation = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mRotation.y + mForwardTuneValue.y, mRotation.x + mForwardTuneValue.x, mRotation.z + mForwardTuneValue.z);

	// 前向きベクトル情報を格納
	mForward.x = MyRotation._31;
	mForward.y = MyRotation._32;
	mForward.z = MyRotation._33;

	mForward.Normalize();

	// 自身の回転角度から左向きベクトルを得るための行列を生成
	MyRotation = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mRotation.y + mForwardTuneValue.y - (float)PIE / 2, mRotation.x + mForwardTuneValue.x, mRotation.z + mForwardTuneValue.z);

	// 右向きベクトル情報を格納
	mLeft.x = MyRotation._31;
	mLeft.y = MyRotation._32;
	mLeft.z = MyRotation._33;
	mLeft.Normalize();

	// 角度更新
	mEulerAngle.x = (float)Radian_To_Euler(mRotation.x);
	mEulerAngle.y = (float)Radian_To_Euler(mRotation.y);
	mEulerAngle.z = (float)Radian_To_Euler(mRotation.z);
}

void Com_Transform::PreDraw()
{
	
}
