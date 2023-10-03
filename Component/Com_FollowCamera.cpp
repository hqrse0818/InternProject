#include "Com_FollowCamera.h"
#include "../DirectX/renderer.h"
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../main.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

void Com_FollowCamera::Update()
{
	
}

void Com_FollowCamera::PreDraw()
{
	if (p_mTarget != nullptr)
	{
		// �������x�N�g�������
		Vector3 BackVector;
		BackVector.x = p_mTarget->p_mTransform->mForward.x * -1;
		BackVector.y = p_mTarget->p_mTransform->mForward.y;
		BackVector.z = p_mTarget->p_mTransform->mForward.z * -1;

		// �|�W�V�������v�Z
		Vector3 tmpPos{};
		Vector3 tarpos = p_mTarget->p_mTransform->mPosition;
		tmpPos.x = tarpos.x + BackVector.x * mMultiDistance.x;
		tmpPos.y = tarpos.y + BackVector.y * mMultiDistance.y + fTargetHeight;
		tmpPos.z = tarpos.z + BackVector.z * mMultiDistance.z;

		// �|�W�V�����̓K��
		p_mObject->p_mTransform->mPosition = tmpPos;

		// �����_�̕␳
		mTargetPosition = p_mTarget->p_mTransform->mPosition + p_mTarget->p_mTransform->mForward * mTargetCorrect;

		// �ςȓz
		//TargetPosition = Target->transform->Position * TargetCorrect;
		
		//if (Target->GetComponent<Com_PlayerMovement>()->GetJumpFlg())
		//{
		//	tmpPos.y -= AddDistance.y;
		//	// �|�W�V�����̓K��
		//	mObject->transform->Position = tmpPos;
		//}

		if (Input::GetKeyState(KEYCODE_UP) == KEYSTATE::KEY_WHILE_DOWN)
		{
			fTargetHeight += 0.1f;
			if (fTargetHeight > fMaxHeight)
			{
				fTargetHeight = fMaxHeight;
			}
		}
		if (Input::GetKeyState(KEYCODE_DOWN) == KEYSTATE::KEY_WHILE_DOWN)
		{
			fTargetHeight -= 0.1f;
			if (fTargetHeight < fMinimumHeight)
			{
				fTargetHeight = fMinimumHeight;
			}
		}
	}
	else
	{
		mTargetPosition = p_mObject->p_mTransform->mPosition + (p_mObject->p_mTransform->mForward * mTargetCorrect);
	}
}