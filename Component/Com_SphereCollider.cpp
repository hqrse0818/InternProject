#include "Com_SphereCollider.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"

using namespace std;

Com_SphereCollider::Com_SphereCollider()
{
}

void Com_SphereCollider::Init()
{
	mSphere.Center = p_mObject->p_mTransform->mPosition + mCenter;
	mSphere.Radius = fRadius * p_mObject->p_mTransform->mScale.x;
}

void Com_SphereCollider::Update()
{
	mSphere.Center = p_mObject->p_mTransform->mPosition + mCenter;
	mSphere.Radius = fRadius * p_mObject->p_mTransform->mScale.x;
}

void Com_SphereCollider::OnCollisionEnter(GameObject* _obj)
{
	cout << "Hit" << p_mObject->sObjectName << endl;
}

Com_CircleCollider::Com_CircleCollider()
{
}

void Com_CircleCollider::Init()
{
	mCircle.Center.x = p_mObject->p_mTransform->mPosition.x + Center.x;
	mCircle.Center.y = p_mObject->p_mTransform->mPosition.y + Center.y;
	mCircle.Radius = Radius;
}

void Com_CircleCollider::Update()
{
	mCircle.Center.x = p_mObject->p_mTransform->mPosition.x + Center.x;
	mCircle.Center.y = p_mObject->p_mTransform->mPosition.y + Center.y;
	mCircle.Radius = Radius;
}
