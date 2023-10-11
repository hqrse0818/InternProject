#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_BoxCollider.h"

class OBJ_Sea :
    public GameObject
{
private:
    Com_BoxCollider* p_mColliderCom = nullptr;

public:
    OBJ_Sea();
    OBJ_Sea(const char* _name);
};

