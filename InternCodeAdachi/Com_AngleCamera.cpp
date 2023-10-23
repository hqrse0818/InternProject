#include "Com_AngleCamera.h"
#include "../GameObject/GameObject.h"
#include "../Utility.h"
#include "../System/Time.h"

void Com_AngleCamera::Update()
{
	// CurrentAngle‚©‚çŒ»Ý‚ÌˆÊ’u‚ð‹‚ß‚é
	if (bFollow)
	{
		float x = sinf((float)Euler_To_Radian(fCurrentAngle));
		float z = cosf((float)Euler_To_Radian(fCurrentAngle));
		p_mObject->p_mTransform->mPosition.x = x * fDistance;
		p_mObject->p_mTransform->mPosition.z = z * fDistance;

		p_mObject->p_mTransform->mPosition.x += p_mTarget->p_mTransform->mPosition.x;
		p_mObject->p_mTransform->mPosition.z += p_mTarget->p_mTransform->mPosition.z;
		p_mObject->p_mTransform->mPosition.y = p_mTarget->p_mTransform->mPosition.y + fHeight;
	}
	else
	{
		fHeight += fCamUpSpeed * Time->GetDeltaTime();
		if (fHeight > fMaxHeight)
		{
			fHeight = fMaxHeight;
		}

		float x = sinf((float)Euler_To_Radian(fCurrentAngle));
		float z = cosf((float)Euler_To_Radian(fCurrentAngle));
		p_mObject->p_mTransform->mPosition.x = x * fDistance;
		p_mObject->p_mTransform->mPosition.z = z * fDistance;

		p_mObject->p_mTransform->mPosition.x += p_mTarget->p_mTransform->mPosition.x;
		p_mObject->p_mTransform->mPosition.z += p_mTarget->p_mTransform->mPosition.z;
		p_mObject->p_mTransform->mPosition.y = p_mTarget->p_mTransform->mPosition.y + fHeight;
	}

	Com_Camera::Update();
}
