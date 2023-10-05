#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

// �e�X�g�p�W�����v�R���|�[�l���g

class Com_TestJump :
    public Component
{
private:
    // �W�����v��k
    float fJumpPower = 10.0f;
    // �W�����v�t���Ofalse = ���łȂ�
    bool bJump = false;
    // �d�̓R���|�[�l���g
    Com_Gravity* p_mGravityCom = nullptr;

public:
    void Jump();
    void Update();

    void SetGravityCom(Com_Gravity* _com)
    {
        p_mGravityCom = _com;
    }
    void SetJumpPower(float _val)
    {
        fJumpPower = _val;
    }

    void SetJumpFlg(bool _val)
    {
        bJump = _val;
    }

    bool GetIsJump()
    {
        return bJump;
    }
};

