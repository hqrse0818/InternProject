#include "Com_PenguinGravity.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/Time.h"
#include "../Debug.h"

void Com_PenguinGravity::Init()
{
}

void Com_PenguinGravity::Update()
{
	if (bUseGrav)
	{
		if (p_mObject->mCollisionvector.size() < 1)
		{
			bOnGround = false;
		}

		if (bOnGround)
		{
			p_mObject->p_mTransform->mPosition.y = fHeight;
		}
		else
		{
			float Moveval = fGravity * fGravCnt;

			Moveval *= Time->GetDeltaTime();
			DEBUG_LOG(Moveval);

			p_mObject->p_mTransform->Translate(0.0f, -Moveval, 0.0f);
			fGravCnt += Time->GetDeltaTime() * fGravCoef;

			if (p_mObject->p_mTransform->mPosition.y < fHeight)
			{
				p_mObject->p_mTransform->mPosition.y = fHeight;
			}

			if (p_mObject->p_mTransform->mPosition.y == fHeight)
			{
				bOnGround = true;
			}
		}
	}
}

void Com_PenguinGravity::OnCollisionEnter(GameObject* _obj)
{
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice && bUseGrav)
		{
			bOnGround = true;
			p_mObject->p_mTransform->mPosition.y = col->Getmax().y;

			fHeight = col->Getmax().y;
		}
	}
}

void Com_PenguinGravity::OnCollisionStay(GameObject* _obj)
{
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice && bUseGrav)
		{
			bOnGround = true;
			p_mObject->p_mTransform->mPosition.y = col->Getmax().y;
		}
	}
}

void Com_PenguinGravity::SetGravity(float _val)
{
	fGravity = _val;
}

void Com_PenguinGravity::SetUseGrav(bool _val)
{
	bUseGrav = _val;
}

bool Com_PenguinGravity::GetOnGround()
{
	return bOnGround;
}

void Com_PenguinGravity::SetOnGround(bool _val)
{
	bOnGround = _val;
}

void Com_PenguinGravity::SetGravCoef(float _val)
{
	fGravCoef = _val;
}
