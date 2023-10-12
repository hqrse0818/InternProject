#include "OBJ_Sea.h"

OBJ_Sea::OBJ_Sea()
{
	// コライダー
	p_mColliderCom = new Com_BoxCollider();
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Sea;

	p_mColliderCom->SetSize(200.0f, 20.0f, 200.0f);
	p_mColliderCom->SetCenter(0.0f, 10.0f, 0.0f);

	AddComponent(p_mColliderCom);
}

OBJ_Sea::OBJ_Sea(const char* _name)
	: OBJ_Sea()
{
	sObjectName = _name;
}
