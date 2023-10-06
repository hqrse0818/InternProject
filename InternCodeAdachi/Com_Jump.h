#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

class Com_Jump :
    public Component
{
private:
    float fJumpPower = 10.0f; //�W�����v��
    float fDropPower = -20.0f; //�������x
    float fInpactPower = 5.0f;
    float fInpactRange = 5.0f;

    float fFallTime = 1.0f; //�q�b�v�h���b�v�̉���

    bool bJump = false; //�W�����v�t���O
    bool bDrop = false; //�q�b�v�h���b�v�t���O
    Com_Gravity* p_mGravityCom = nullptr;

public:
    void Jump();
    void HipDrop();
    void Update();

    void OnCollisionEnter(GameObject* _obj);

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

    void SetDropFlg(bool _val)
    {
        bDrop = _val;
    }

    bool GetJumpFlg()
    {
        return bJump;
    }

    bool GetDropFlg()
    {
        return bDrop;
    }
};

