#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_BoxCollider.h"

class OBJ_Ice :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_AssimpAnimation* p_mModelCom = nullptr;
    Com_BoxCollider* p_mCollider = nullptr;
    DirectX::SimpleMath::Color myColor;
    int iHP = 5; //足場のHP
public:
    OBJ_Ice();
    OBJ_Ice(const char* _name);

    void Init();
    void Update();
    void HpCalc(); //HP計算処理
};

