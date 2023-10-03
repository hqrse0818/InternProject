#include "Com_PointCollider.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_PointCollider::Init()
{
	mPoint = mCenter + p_mObject->p_mTransform->mPosition;
}

void Com_PointCollider::Update()
{
	mPoint = mCenter + p_mObject->p_mTransform->mPosition;
}
