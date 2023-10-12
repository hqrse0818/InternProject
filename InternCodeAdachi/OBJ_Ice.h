#pragma once
#include "../GameObject/GameObject.h"
#include "../InternCodeAdachi/Com_Model.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_BoxCollider.h"
#include "../Component/Com_Audio.h"

using namespace DirectX::SimpleMath;

class OBJ_Ice :
    public GameObject
{
private:
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;
    Com_BoxCollider* p_mCollider = nullptr;
    Com_Audio* p_mAudio{};
    DirectX::SimpleMath::Color myColor = DirectX::SimpleMath::Color{1.0f, 1.0f, 1.0f, 1.0f};
    int iHP = 5; //�����HP

    float fShakeTime = 0.5f; //�h��鎞��
    float fElapsedTime = 0.0f; //�o�ߎ���
    float fShakePower = 0.1f; // �h��͈̔�

    Vector3 originalPosition; // �I�u�W�F�N�g�̌��̈ʒu���i�[����ϐ�

public:
    OBJ_Ice();
    OBJ_Ice(const char* _name);

    void Init();
    void Update();

    void HpCalc(); //�����HP�v�Z
    int GetHP()
    {
        return iHP;
    }
    void Shake(); //����̗h��

    //�����_���v�Z
    float RandomRange(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

};

