#pragma once
#include "../Component/Component.h"

// �d�̓R���|�[�l���g
// ���̃R���|�[�l���g����n�ʂɂ��Ă��邩�̔��f�͍s��Ȃ�

class Com_Gravity :
    public Component
{
private:
    float fGravity = 7.0f;
    float fGravCoef = 2;
    float fFallCnt = 0.0f;
    bool bOnGround = false;

    float falseCnt = 0.0f;
    bool bSetToFalse = false;
public:
    void Update()override;
  
    void SetGround(bool _val)
    {
        bOnGround = _val;
    }
    void SetToFalse(bool _val)
    {
        bSetToFalse = _val;
    }
    bool GetGround()
    {
        return bOnGround;
    }
};

