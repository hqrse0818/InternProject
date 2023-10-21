#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"

class OBJ_BackPenguinRed :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;

    float fDelay = 0.0f;
    float fCnt = 0.0f;
public:
    OBJ_BackPenguinRed();
    OBJ_BackPenguinRed(const char* _name);

    void PlayAnimaion(const char* _name);

    void Update()override;

    void SetDelay(float _val)
    {
        fDelay = _val;
    }
};

