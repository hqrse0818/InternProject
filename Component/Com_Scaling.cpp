#include "Com_Scaling.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"


void Com_Scaling::Init()
{
	mInitScale = p_mObject->p_mTransform->mScale;
}

void Com_Scaling::Update()
{
	if (bScale)
	{
		fCnt += Time->GetDeltaTime();
		if (fCnt > fTime)
		{
			fCnt = 0.0f;
			bReturn = !bReturn;
		}

		if (!bUseZ)
		{
			if (bReturn)
			{
				float delta = Time->GetDeltaTime();
				p_mObject->Scaling(delta * fIncVal, delta * fIncVal, 0.0f);
			}
			else
			{
				float delta = Time->GetDeltaTime();
				p_mObject->Scaling(delta * fDecVal, delta * fDecVal, 0.0f);
			}
		}
		else
		{
			if (bReturn)
			{
				float delta = Time->GetDeltaTime();
				p_mObject->Scaling(delta * fIncVal, delta * fIncVal, delta * fIncVal);
			}
			else
			{
				float delta = Time->GetDeltaTime();
				p_mObject->Scaling(delta * fDecVal, delta * fDecVal, delta * fDecVal);
			}
		}
		
	}
	else
	{
		p_mObject->SetScale(mInitScale.x, mInitScale.y, mInitScale.z);
	}
}
