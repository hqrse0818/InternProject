#pragma once
#include "../Component/Component.h"

class Com_Gravity;
class Com_Jump;

class Com_Foot :
    public Component
{
private:
    // �d�̓R���|�[�l���g
    Com_Gravity* p_mGravityCom = nullptr;
    // �W�����v�R���|�[�l���g
    Com_Jump* p_mJumpCom = nullptr;

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
        p_mGravityCom = _com;
    }
    void SetJumpCom(Com_Jump* _com)
    {
        p_mJumpCom = _com;
    }

    void SetFootHeight(float _val)
    {
        fFootHeight = _val;
    }
};

