#pragma once
#include "../Component/Component.h"

class Com_Gravity;
class Com_TestJump;

// キャラクターの足元用コンポーネント
// 重量フラグとジャンプフラグの変更も行う

class Com_Foot :
    public Component
{
private:
    // 重力コンポーネント
    Com_Gravity* p_mGravityCom = nullptr;
    // ジャンプコンポーネント
    Com_TestJump* p_mJumpCom = nullptr;

    // 脚の高さ
    float fFootHeight = 0.0f;
    // 脚の実際の位置
    float fFootPos = 0.0f;
    // 前回の足の位置
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

