#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"

class OBJ_Penguin :
    public GameObject
{
private:
    // モデル描画コンポーネント
    Com_AssimpAnimation* p_mModel = nullptr;
    // シェーダーコンポーネント
    Com_Shader* p_mShader = nullptr;

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

};

