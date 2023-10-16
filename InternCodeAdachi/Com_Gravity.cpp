#include "Com_Gravity.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_Gravity::Update()
{
	if (p_mObject->sObjectName == "Test")
	{
		std::cout << "bSetFlase : " << bSetToFalse << std::endl;
		std::cout << "bOnGround : " << bOnGround << std::endl;
	}

	if (bSetToFalse)
	{
		falseCnt += Time->GetDeltaTime();
		if (falseCnt > 0.1f)
		{
			falseCnt = 0.0f;
			bOnGround = false;
			bSetToFalse = false;
		}
	}
	else
	{
		falseCnt = 0.0f;
	}

	if (bOnGround)
	{
		fFallCnt = 0.0f;
	}
	else
	{
		// d—ÍŒvŽZ
		float Velocity = -fGravity * fFallCnt;
		Velocity *= Time->GetDeltaTime();

		p_mObject->p_mTransform->Translate(0.0f, Velocity, 0.0f);
		fFallCnt += Time->GetDeltaTime() * fGravCoef;
	}
}