#pragma once
#include "../Component/Component.h"
#include "Com_Gravity.h"

/*
�W�����v����q�b�v�C���p�N�g�ɃX�e�[�g�ڍs�����Ƃ��̃W�����v�̌��݂̍�����ۑ�����
��
���ɏՓˎ��q�b�v�C���p�N�g�̓����蔻����������I�u�W�F�N�g�𐶐�����
���̎��З͂Ɣ͈͂��W�����v�̍�������擾���Ċi�[
�q�b�v�C���p�N�g�̐ݒ������
���C�t�^�C����o���ʒu�Ȃ�
*/

class Com_Jump :
    public Component
{
private:
    float fJumpPower = 10.0f; //�W�����v��
    float fDropSpeed = -10.0f; //�������x
    float fDropInitialSpeed = -7.5f;// �����̏���
    float fDropCnt = 0.0f; // ��������

    float fJumpHeight = 0.0f; //���݂̍���
    float FInpactRenge = 0.0f; //�q�b�v�C���p�N�g�͈̔�
    float fImpactPower = 0.0f; //�q�b�v�C���p�N�g�̈З�

    float fFallTime = 1.0f; //�q�b�v�C���p�N�g�̉���

    bool bJump = false; //�W�����v�t���O
    bool bDrop = false; //�q�b�v�C���p�N�g�t���O
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

