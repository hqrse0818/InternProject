#pragma once
#include "../Component/Component.h"
class Com_PenguinGravity :
    public Component
{
private:
    // 重力
    float fGravity = 9.0f;
    // 係数
    float fGravCoef = 5.0f;

    // 重力を有効
    bool bUseGrav = true;
    // 接地
    bool bOnGround = false;

    // 既定の地面の高さ
    float fHeight = 0;

    // 重力のカウント
    float fGravCnt = 0.0f;

public:
    void Init();
    void Update();
    void OnCollisionEnter(GameObject* _obj);
    void OnCollisionStay(GameObject* _obj);

    void SetGravity(float _val);
    void SetUseGrav(bool _val);
    bool GetOnGround();
    void SetOnGround(bool _val);
    void SetGravCoef(float _val);
    void SetGravCnt(float _val)
    {
        fGravCnt = _val;
    }
};

