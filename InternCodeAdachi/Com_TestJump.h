#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

// テスト用ジャンプコンポーネント

class Com_TestJump :
    public Component
{
private:
    // ジャンプ慮k
    float fJumpPower = 10.0f;
    // ジャンプフラグfalse = 飛んでない
    bool bJump = false;
    // 重力コンポーネント
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

