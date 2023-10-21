#include "OBJ_Fall.h"

OBJ_Fall::OBJ_Fall()
{
	p_mColliderCom = new Com_BoxCollider();
	// 衝突時落下用オブジェクト
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Fall;
	p_mColliderCom->SetSize(1.5f, 3.0f, 1.5f);
	p_mColliderCom->SetCenter(0.0f, 0.0f, 0.0f);
	AddComponent(p_mColliderCom);
}

OBJ_Fall::OBJ_Fall(const char* _name)
	: OBJ_Fall()
{
	sObjectName = _name;
}
