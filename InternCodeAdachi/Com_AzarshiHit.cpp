#include "Com_AzarshiHit.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;


void Com_AzarshiHit::Update()
{
	p_mObject->Translate(mMoveVal * Time->GetDeltaTime());
}

void Com_AzarshiHit::OnCollisionStay(GameObject* _obj)
{
	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();

		if (col->mColliderTag == ColliderKind::ColTag_Azarashi)
		{
			Vector3 vec = Math::GetVector(p_mObject->p_mTransform->mPosition, _obj->p_mTransform->mPosition);

			vec.y = 0;
			mMoveVal = -vec;
		}
	}
}

void Com_AzarshiHit::OnCollisionExit(GameObject* _obj)
{
	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();

		if (col->mColliderTag == ColliderKind::ColTag_Azarashi)
		{
			mMoveVal = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
}
