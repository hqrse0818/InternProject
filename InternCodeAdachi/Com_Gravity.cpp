#include "Com_Gravity.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_Gravity::Update()
{
	if (bOnGround)
	{
		fFallCnt = 0.0f;
		return;
	}

	float Velocity = -fGravity * fFallCnt;
	fFallCnt += 0.1f;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(0.0f, Velocity, 0.0f);

}