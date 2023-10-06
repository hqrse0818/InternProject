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
    int iHP = 5; //‘«ê‚ÌHP
    float fShakeTime = 0.0f;
public:
    OBJ_Ice();
    OBJ_Ice(const char* _name);

    void Init();
    void Update();
    void HpCalc(); //HPŒvZˆ—
    void Shake(); //—h‚ê‚éˆ—

    float RandomRange(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }
};

