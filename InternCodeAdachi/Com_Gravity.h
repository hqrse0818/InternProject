#pragma once
#include "../Component/Component.h"

// �d�̓R���|�[�l���g
// ���̃R���|�[�l���g����n�ʂɂ��Ă��邩�̔��f�͍s��Ȃ�

class Com_Gravity :
    public Component
{
private:
    float fGravity = 5.0f;
    int fGravCoef = 2;
    float fFallCnt = 0.0f;
    bool bOnGround = false;

    bool bGroundAtthisFrame = false;

    float falseCnt = 0.0f;
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
};

