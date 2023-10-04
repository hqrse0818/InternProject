#include "Com_CharacterMove.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../GameObject/GameObject.h"

Com_CharacterMove::Com_CharacterMove()
{
}

void Com_CharacterMove::Update()
{
	if ((Controller_Input::GetLeftStick(0).x >= 0.5))
	{
		p_mObject->p_mTransform->Translate(5.0f * Time->GetDeltaTime(), 0.0f, 0.0f);
	}
	if ((Controller_Input::GetLeftStick(0).y >= 0.5))
	{
		p_mObject->p_mTransform->Translate(0.0f, 0.0f, 5.0f * Time->GetDeltaTime());
	}
	if ((Controller_Input::GetLeftStick(0).x <= -0.5))
	{
		p_mObject->p_mTransform->Translate(-5.0f * Time->GetDeltaTime(), 0.0f, 0.0f);
	}
	if ((Controller_Input::GetLeftStick(0).y <= -0.5))
	{
		p_mObject->p_mTransform->Translate(0.0f, 0.0f, -5.0f * Time->GetDeltaTime());
	}
}

//Controller‚ÍƒNƒ‰ƒX‚Åì‚é
//GetViews—ñ