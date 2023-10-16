#pragma once
#include "GameObject.h"
#include "../InternCodeAdachi/Com_Shadow.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_BoxCollider.h"

class OBJ_Shadow :
    public GameObject
{
private:
    GameObject* p_mTarget;
    Com_Shader* p_mShaderCom;
    Com_Shadow* p_mShadowCom;
    Com_BoxCollider* p_mColliderCom;
    
public:
    OBJ_Shadow();
    OBJ_Shadow(const char* _name);

    void Update();
    void OnCollisionStay(GameObject* _obj);

    void SetTarget(GameObject* _target);

};

