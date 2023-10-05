#include "OBJ_Inpact.h"
#include "../System/Time.h"

OBJ_Inpact::OBJ_Inpact()
{
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 1.0f; //”ÍˆÍ

	AddComponent(p_mColliderCom);
}

OBJ_Inpact::OBJ_Inpact(const char* _name) :OBJ_Inpact()
{
	sObjectName = _name;
}

void OBJ_Inpact::Update()
{
	fCnt += Time->GetDeltaTime();
	if (fCnt > fLifeTime)
	{
		bDestroy = true;
		return;
	}

	p_mColliderCom->fRadius += p_mColliderCom->fRadius + fCnt;
}
