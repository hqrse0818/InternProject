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

public:
    OBJ_BackPenguinRed();
    OBJ_BackPenguinRed(const char* _name);

    void PlayAnimaion(const char* _name);
};

