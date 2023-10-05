#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"

class OBJ_Penguin :
    public GameObject
{
private:
    // ���f���`��R���|�[�l���g
    Com_AssimpAnimation* p_mModel = nullptr;
    // �V�F�[�_�[�R���|�[�l���g
    Com_Shader* p_mShader = nullptr;

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

};

