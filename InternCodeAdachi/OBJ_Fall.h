#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_BoxCollider.h"
class OBJ_Fall :
    public GameObject
{
private:
    Com_BoxCollider* p_mColliderCom = nullptr;

public:
    OBJ_Fall();
    OBJ_Fall(const char* _name);

    Com_BoxCollider* GetColliderCom()
    {
        return p_mColliderCom;
    }
};

