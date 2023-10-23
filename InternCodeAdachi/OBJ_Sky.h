#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"

class OBJ_Sky :
    public GameObject
{
private:
    Com_Shader* p_mShader{};
    Com_Model* p_mModel{};

    float fRotSpeed = 2.0f;
public:
    OBJ_Sky();
    OBJ_Sky(const char* _name);

    void Update();

    void SetRotSpeed(float _val)
    {
        fRotSpeed = _val;
    }
};

