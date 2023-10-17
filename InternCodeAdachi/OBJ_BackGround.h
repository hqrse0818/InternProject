#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"

class OBJ_BackGround :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;

public:
    OBJ_BackGround();
    OBJ_BackGround(const char* _name);
};

