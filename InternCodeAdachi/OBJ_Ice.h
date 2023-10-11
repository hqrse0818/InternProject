#pragma once
#include "../GameObject/GameObject.h"
#include "../InternCodeAdachi/Com_Model.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_BoxCollider.h"

class OBJ_Ice :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;
    Com_BoxCollider* p_mCollider = nullptr;
    DirectX::SimpleMath::Color myColor = DirectX::SimpleMath::Color{1.0f, 1.0f, 1.0f, 1.0f};
    int iHP = 5;
public:
    OBJ_Ice();
    OBJ_Ice(const char* _name);

    void Init();
    void Update();

    void HpCalc(); //‘«ê‚ÌHPŒvZ
    void Shake(); //‘«ê‚Ì—h‚ê

    //ƒ‰ƒ“ƒ_ƒ€ŒvZ
    float RandomRange(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

};

