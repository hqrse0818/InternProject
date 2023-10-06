#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

class Com_Jump :
    public Component
{
private:
    float fJumpPower = 10.0f; //�W�����v��
    float fDropPower = -8.0f; //�������x

    bool bJump = false; //�W�����v�t���O
    bool bDrop = false; //�q�b�v�h���b�v�t���O
    Com_Gravity* p_mGravityCom = nullptr;

public:
    void Jump();
    void HipDrop();
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

    void SetDropFlg(bool _val)
    {
        bDrop = _val;
    }
};

