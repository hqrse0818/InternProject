#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

class Com_Jump :
    public Component
{
private:
    float fJumpPower = 10.0f; //ジャンプ力
    float fDropPower = -20.0f; //落下速度
    float fInpactPower = 5.0f;
    float fInpactRange = 5.0f;

    float fFallTime = 1.0f; //ヒップドロップの加速

    bool bJump = false; //ジャンプフラグ
    bool bDrop = false; //ヒップドロップフラグ
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

