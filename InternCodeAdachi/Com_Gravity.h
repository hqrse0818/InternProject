#pragma once
#include "../Component/Component.h"

// �d�̓R���|�[�l���g
// ���̃R���|�[�l���g����n�ʂɂ��Ă��邩�̔��f�͍s��Ȃ�

class Com_Gravity :
    public Component
{
private:
    // �d��
    float fGravity = 5.0f;
    // �f���^�^�C���ɂ�����W��
    int fGravCoef = 2;
    // �����J�n����̌o�ߎ���
    float fFallCnt = 0.0f;
    // �ڒn����
    bool bOnGround = false;
    // ����̃t���[���ŉ��炩�̏���I�u�W�F�N�g�̏�ɏ���Ă���ΐڒn�����false�ɂ��Ȃ�
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

