#pragma once
#include "../Component/Component.h"

// �d�̓R���|�[�l���g
// ���̃R���|�[�l���g����n�ʂɂ��Ă��邩�̔��f�͍s��Ȃ�

class Com_Gravity :
    public Component
{
private:
    float fGravity = 3.0f;
    float fFallCnt = 0.0f;
    bool bOnGround = false;
public:
    void Update()override;
  
    void SetGround(bool _val)
    {
        bOnGround = _val;
    }
    bool GetGround()
    {
        return bOnGround;
    }
};

