#include "Com_Camera.h"
#include "../DirectX/renderer.h"
#include "../GameObject/GameObject.h"
#include "../main.h"

using namespace DirectX::SimpleMath;


void Com_Camera::SetTarget(GameObject* _targetpos)
{
	p_mTarget = _targetpos;
	SetUseTarget(true);
}

void Com_Camera::Init()
{
	//p_mObject->p_mTransform->mPosition.z = -10.0f;
}

void Com_Camera::Update()
{
	if (p_mTarget != nullptr)
	{
		mTargetPosition = p_mTarget->p_mTransform->mPosition;
		mTargetPosition *= mTargetCorrect;
	}
	// �r���[�ϊ��s��쐬
	mViewMatrix = DirectX::XMMatrixLookAtLH(p_mObject->p_mTransform->mPosition, mTargetPosition, mUp);
}

void Com_Camera::Draw()
{
	// �r���[�s����Z�b�g
	Renderer::SetViewMatrix(&mViewMatrix);

	// ��ʂ̔䗦�̐ݒ�
	float aspect = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);

	// �v���W�F�N�V�����s��̐���
	Matrix projectionMatrix;

	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fFov), aspect, fNear, fFar);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
