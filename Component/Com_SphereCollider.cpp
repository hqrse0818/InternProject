#include "Com_SphereCollider.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "Com_RenderCollisionLine_Sphere.h"

using namespace std;

Com_SphereCollider::Com_SphereCollider()
{

}

void Com_SphereCollider::Init()
{
#if defined(DEBUG) || defined(_DEBUG)
	// 表示用コンポーネントを追加
	Com_RenderCollisionLine_Sphere* CollisionLine = new Com_RenderCollisionLine_Sphere;
	p_mObject->AddComponent(CollisionLine);
#endif // 
	mSphere.Center = p_mObject->p_mTransform->mPosition + mCenter;
	mSphere.Radius = fRadius;
}

void Com_SphereCollider::Update()
{
	if (p_mObject->mCollisionvector.size() > 0)
	{
		bHit = true;
	}
	else
	{
		bHit = false;
	}
	mSphere.Center = p_mObject->p_mTransform->mPosition + mCenter;
	mSphere.Radius = fRadius;
}

void Com_SphereCollider::OnCollisionEnter(GameObject* _obj)
{
	cout << "Enter" << p_mObject->sObjectName << endl;
}

void Com_SphereCollider::OnCollisionStay(GameObject* _obj)
{
	cout << "Stay" << p_mObject->sObjectName << endl;
}

void Com_SphereCollider::OnCollisionExit(GameObject* _obj)
{
	cout << "Exit" << p_mObject->sObjectName << endl;
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
