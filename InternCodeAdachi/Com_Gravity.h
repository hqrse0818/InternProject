#pragma once
#include "../Component/Component.h"

// 重力コンポーネント
// このコンポーネントから地面についているかの判断は行わない

class Com_Gravity :
    public Component
{
private:
    // 重力
    float fGravity = 5.0f;
    // デルタタイムにかかる係数
    int fGravCoef = 2;
    // 落下開始からの経過時間
    float fFallCnt = 0.0f;
    // 接地判定
    bool bOnGround = false;
    // 今回のフレームで何らかの乗れるオブジェクトの上に乗っていれば接地判定をfalseにしない
    bool bGroundAtthisFrame = false;

public:
    void Update()override;
    bool GetGroundedAtThisFrame()
    {
        return bGroundAtthisFrame;
    }
    void SetGroundOnThisFrame(bool _val)
    {
        bGroundAtthisFrame = _val;
    }

    void SetGround(bool _val)
    {
        bOnGround = _val;
    }
    bool GetGround()
    {
        return bOnGround;
    }
    void SetGravity(float _val)
    {
        fGravity = _val;
    }

    void SetGravCoef(float _val)
    {
        fGravCoef = _val;
    }
};

