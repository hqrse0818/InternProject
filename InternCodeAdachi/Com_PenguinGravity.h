#pragma once
#include "../Component/Component.h"
class Com_PenguinGravity :
    public Component
{
private:
    // �d��
    float fGravity = 9.0f;
    // �W��
    float fGravCoef = 5.0f;

    // �d�͂�L��
    bool bUseGrav = true;
    // �ڒn
    bool bOnGround = false;

    // ����̒n�ʂ̍���
    float fHeight = 0;

    // �d�͂̃J�E���g
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

