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

    bool bFollowTargetY = false;
    
public:
    OBJ_Shadow();
    OBJ_Shadow(const char* _name);

    void Init();
    void Update();

    void SetTarget(GameObject* _target);
    void SetFollowTargetY(bool _val)
    {
        bFollowTargetY = _val;
    }

};

