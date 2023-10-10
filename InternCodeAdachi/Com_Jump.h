#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

/*
ジャンプからヒップインパクトにステート移行したときのジャンプの現在の高さを保存する
↓
床に衝突時ヒップインパクトの当たり判定を持ったオブジェクトを生成する
この時威力と範囲をジャンプの高さから取得して格納
ヒップインパクトの設定をする
ライフタイムや出現位置など
*/

class Com_Jump :
    public Component
{
private:
    float fJumpPower = 10.0f; //ジャンプ力
    float fDropSpeed = -10.0f; //落下速度
    float fDropInitialSpeed = -7.5f;// 落下の初速
    float fDropCnt = 0.0f; // 落下時間

    float fJumpHeight = 0.0f; //現在の高さ
    float FInpactRenge = 0.0f; //ヒップインパクトの範囲
    float fImpactPower = 0.0f; //ヒップインパクトの威力

    float fFallTime = 1.0f; //ヒップインパクトの加速

    bool bJump = false; //ジャンプフラグ
    bool bDrop = false; //ヒップインパクトフラグ
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

    bool GetIsJump()
    {
        return bJump;
    }

    void SetDropFlg(bool _val)
    {
        if (!_val)
        {
            fDropCnt = 0.0f;
        }
        bDrop = _val;
    }

    void SetDropPower(float _val)
    {
        fDropSpeed = _val;
    }

    void SetDropInitialSpeed(float _val)
    {
        fDropInitialSpeed = _val;
    }

    bool GetIsDrop()
    {
        return bDrop;
    }

    void SetJumpHeight();

    float GetJumpHeight()
    {
        return fJumpHeight;
    }
};

