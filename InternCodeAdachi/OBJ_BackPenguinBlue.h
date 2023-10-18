#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"

class OBJ_BackPenguinBlue :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;

public:
    OBJ_BackPenguinBlue();
    OBJ_BackPenguinBlue(const char* _name);

    void PlayAnimation(const char* _name);
};

