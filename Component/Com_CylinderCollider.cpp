#include "Com_CylinderCollider.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"

Com_CylinderCollider::Com_CylinderCollider()
{
}

void Com_CylinderCollider::Init()
{
	
}

void Com_CylinderCollider::Update()
{
	// シリンダーの下面を更新
	mCylinder.Bottom = p_mObject->p_mTransform->mPosition;
	mCylinder.Bottom.y = p_mObject->p_mTransform->mPosition.y -  p_mObject->p_mTransform->mScale.y / 2 * fBottomLength;

	// シリンダーの上面を更新
	mCylinder.Top = p_mObject->p_mTransform->mPosition;
	mCylinder.Top.y = p_mObject->p_mTransform->mPosition.y + p_mObject->p_mTransform->mScale.y / 2 * fTopLength;
}
