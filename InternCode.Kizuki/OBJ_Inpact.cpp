#include "OBJ_Inpact.h"

OBJ_Inpact::OBJ_Inpact()
{
	//衝撃のコライダー
	Com_SphereCollider* p_mCollider = new Com_SphereCollider;
	p_mCollider->SetCenter(0.0f, 0.0f, 0.0f);
	p_mCollider->fRadius = 2.0f;
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);
}

void OBJ_Inpact::Update()
{
}
