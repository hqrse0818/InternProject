#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_Jump.h"
#include "Com_AngleCamera.h"
#include "Com_PenguinGravity.h"
#include "Com_Foot.h"
#include "Com_Model.h"
#include "Com_Shadow.h"
#include "../Component/Com_BoxCollider.h"
#include "../Component/Com_Audio.h"
#include "../InternCode.Kizuki/OBJ_HipEffect.h"

// �y���M���̃v���t�@�u
#define PenguinStatuNum (23)

// �y���M���̃X�e�[�g
enum class PenguinState
{
    // ����(���͉�)
    Walk, 
    //
    BeforeJump,
    // �W�����v(���͉�)
    Jump, 
    // �q�b�v�h���b�v�O�̗��߂̎���(���͕s��)
    BeforeHipDrop, 
    // �q�b�v�h���b�v��(���͕s��)
    HipDrop, 
    //
    AfterHipDrop,
    // ��e���(���͕s��)
    Damage, 
    // �q�b�v�h���b�v�ŃA�U���V�ɏՓ�
    HipDropOnAzarashi,
    // �ҋ@���[�V����
    Idle,

    // ���S
    Death,
};

class OBJ_Penguin :
    public GameObject
{
private:
    // ���f���`��R���|�[�l���g
    Com_Model* p_mModel = nullptr;
    // �V�F�[�_�[�R���|�[�l���g
    Com_Shader* p_mShader = nullptr;
    // �ړ��R���|�[�l���g
    Com_CharacterMove* p_mMoveCom = nullptr;
    // �W�����v�R���|�[�l���g
    Com_Jump* p_mJumpCom = nullptr;
    // �^�[�Q�b�g�ɂ���Ă�J�����R���|�[�l���g
    Com_AngleCamera* p_mCameraCom = nullptr;
    // �d�̓R���|�[�l���g
    Com_PenguinGravity* p_mGravityCom = nullptr;
    // �����R���|�[�l���g
    Com_Foot* p_mFootCom = nullptr;
    // �e
    Com_Shadow* p_mShadowCom = nullptr;
    // �R���C�_�[
    Com_BoxCollider* p_mColliderCom = nullptr;
    // �q�b�v�C���p�N�g�G�t�F�N�g
    OBJ_HipEffect* p_mHipEf = nullptr;

    // SE�Đ��p
    Com_Audio* p_mSEJump = nullptr;
    Com_Audio* p_mSEWalk = nullptr;
    Com_Audio* p_mSELand = nullptr;
    Com_Audio* p_mSEAttacLand = nullptr;
    Com_Audio* p_mSEMiss = nullptr;
    Com_Audio* p_mSEDeath = nullptr;

    // �󒆂ł̈ړ�����(�X�e�B�b�N���͂łǂꂾ���̊�����K�p���邩)
    float fAirMoveSpeed = 1.0f;

    // �J�����̃X�s�[�h
    float fCamSpeed = 1.0f;
    // �}�E�X�p�J�����X�s�[�h
    float fMouseCameraSpeed = 0.2f;

    // �q�b�v�C���p�N�g�͈̔�
    float fImpactRange = 8.0f;

    // �q�b�v�h���b�v�Ɉڍs����܂ł̃f�B���C
    float fImpactDelay = 0.2f;
    float fImpactCnt = 0.0f;

    // �A�U���V�Փˎ��̂��߂�
    float fDamagedPower = 6.0f;

    // �Փˌ�̃u���[�L�W��
    float fBlake = 0.5f;

    // ��~���e����
    float fDamagePermission = 0.05f;

    // �q�b�v�C���p�N�g�̊g�呬�x
    float fImpactScalingSpeed = 0.5f;

    // �������̏�ւ̃x�N�g��
    float fDirectVector = 0.0f;

    // ������̕��V��Ԃ̌p������
    float fFloatTime = 0.0f;
    float fFloatCnt = 0.0f;

    // ��e��̖��G����
    float fArmorTime = 0.2f;
    float fArmorCnt = 0.0f;

    float fIdleTime = 0.0f;
    float fIdelCnt = 0.0f;

    // ���sSE�̊Ԋu
    float fWalkSEDuration = 0.2f;
    float fWalkSECnt = 0.0f;

    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    PenguinState mState = PenguinState::Walk;

    DirectX::SimpleMath::Vector2 mMoveVelocity = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

private:
    void CreateFromCSV(const char* _FileName);

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);
    OBJ_Penguin(const char* _name, const char* _FileName);

    void Start()override;
    void Update();
    void OnCollisionEnter(GameObject* _obj)override;
    void OnCollisionStay(GameObject* _obj)override;

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

    void SetCameraCom(Com_AngleCamera* _com)
    {
        p_mCameraCom = _com;
    }

    void SetHipEffect(OBJ_HipEffect* _obj)
    {
        p_mHipEf = _obj;
    }
};

