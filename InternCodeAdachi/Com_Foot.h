#pragma once
#include "../Component/Component.h"

class Com_Gravity;

class Com_Foot :
    public Component
{
private:
    // �ʒu�����̃^�[�Q�b�g
    Com_Gravity* p_mGravityTarget = nullptr;
    // �r�̍���
    float fFootHeight = 0.0f;
    // �r�̎��ۂ̈ʒu
    float fFootPos = 0.0f;
public:
    void Update()override;

    void OnCollisionEnter(GameObject* _obj);
    void OnCollisionStay(GameObject* _obj);
    void OnCollisionExit(GameObject* _obj);

    void SetGravityCom(Com_Gravity* _com)
    {
        p_mGravityTarget = _com;
    }

    void SetFootHeight(float _val)
    {
        fFootHeight = _val;
    }
};

