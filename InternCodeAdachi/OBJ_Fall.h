#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
class OBJ_Fall :
    public GameObject
{
private:
    Com_SphereCollider* p_mColliderCom = nullptr;

public:
    OBJ_Fall();
    OBJ_Fall(const char* _name);
};

