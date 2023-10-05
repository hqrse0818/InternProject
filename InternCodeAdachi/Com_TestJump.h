#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

class Com_TestJump :
    public Component
{
private:
    float fJumpPower = 10.0f;

    bool bJump = false;
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
};

