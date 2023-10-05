#pragma once
#include "../Component/Component.h"

class Com_Gravity;
class Com_TestJump;

// �L�����N�^�[�̑����p�R���|�[�l���g
// �d�ʃt���O�ƃW�����v�t���O�̕ύX���s��

class Com_Foot :
    public Component
{
private:
    // �d�̓R���|�[�l���g
    Com_Gravity* p_mGravityCom = nullptr;
    // �W�����v�R���|�[�l���g
    Com_TestJump* p_mJumpCom = nullptr;

    // �r�̍���
    float fFootHeight = 0.0f;
    // �r�̎��ۂ̈ʒu
    float fFootPos = 0.0f;
    // �O��̑��̈ʒu
    float fLastFootPos = 0.0f;
public:
    void Update()override;

    void OnCollisionEnter(GameObject* _obj);
    void OnCollisionStay(GameObject* _obj);
    void OnCollisionExit(GameObject* _obj);

    void SetGravityCom(Com_Gravity* _com)
    {
        p_mGravityCom = _com;
    }
    void SetJumpCom(Com_TestJump* _com)
    {
        p_mJumpCom = _com;
    }

    void SetFootHeight(float _val)
    {
        fFootHeight = _val;
    }
};

