#include "OBJ_Sea.h"

OBJ_Sea::OBJ_Sea()
{
	// �R���C�_�[
	p_mColliderCom = new Com_BoxCollider();
	p_mColliderCom->ColliderTag = "Sea";
	AddComponent(p_mColliderCom);


}

OBJ_Sea::OBJ_Sea(const char* _name)
	: OBJ_Sea()
{
	sObjectName = _name;
}
