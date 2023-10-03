#include "Com_Transform.h"
#include "../Utility.h"

using namespace DirectX::SimpleMath;

void Com_Transform::SetAngle(DirectX::SimpleMath::Vector3 _val)
{
	// �I�C���[�p���玩�g�̉�]���Z�b�g
	mEulerAngle = _val;
	mRotation.x = (float)Euler_To_Radian(mEulerAngle.x);
	mRotation.y = (float)Euler_To_Radian(mEulerAngle.y);
	mRotation.z = (float)Euler_To_Radian(mEulerAngle.z);
}

void Com_Transform::SetAngle(float _x, float _y, float _z)
{
	// �I�C���[�p���玩�g�̉�]���Z�b�g
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
	// �Z�b�g���ꂽ�O�����x�N�g�������]�p�x�𓾂邽�߂̑O�����x�N�g�����擾
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
	// ���g�̉�]�p�x����O�����x�N�g���𓾂邽�߂̍s��𐶐�
	MyRotation = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mRotation.y + mForwardTuneValue.y, mRotation.x + mForwardTuneValue.x, mRotation.z + mForwardTuneValue.z);

	// �O�����x�N�g�������i�[
	mForward.x = MyRotation._31;
	mForward.y = MyRotation._32;
	mForward.z = MyRotation._33;

	mForward.Normalize();

	// ���g�̉�]�p�x���獶�����x�N�g���𓾂邽�߂̍s��𐶐�
	MyRotation = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(mRotation.y + mForwardTuneValue.y - (float)PIE / 2, mRotation.x + mForwardTuneValue.x, mRotation.z + mForwardTuneValue.z);

	// �E�����x�N�g�������i�[
	mLeft.x = MyRotation._31;
	mLeft.y = MyRotation._32;
	mLeft.z = MyRotation._33;
	mLeft.Normalize();

	// �p�x�X�V
	mEulerAngle.x = (float)Radian_To_Euler(mRotation.x);
	mEulerAngle.y = (float)Radian_To_Euler(mRotation.y);
	mEulerAngle.z = (float)Radian_To_Euler(mRotation.z);
}

void Com_Transform::PreDraw()
{
	
}
