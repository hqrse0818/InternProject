#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../InternCodeAdachi/Com_Gravity.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"
#include "Com_Foot.h"
#include "../GameObject/OBJ_Shadow.h"

// �A�U���V

enum class AzrashiState
{
    // �X�|�[���J�n�ʒu�ƃX�|�[���ꏊ���w�肵�Đ���
    SpawnToCenter, 
    // �X��܂ŗ���
    SpawnToTarget,
    // �X�|�[���ꏊ�ɓ��B��U���܂ő҂�(3�b)
    AfterSpawnWait, 
    // �U��(���[�V�����I����ҋ@�ɓ���)
    Attack,
    // �U����̑҂�����
    AttackWait,
    // ��e���(�ړ�,�ړ��I���Ŕ�e��ԏI��->�U���҂�)
    // ��e��Ԓ��ɊC�ɐG���->Death�Ɉڍs
    Damage, 
    // ��э���
    Dive,
    // ��э��݃A�j���[�V�����I���㏈��
    DiveTo,
    // ���S(�A�j���[�V�����Đ���)
    Death
};

class OBJ_Azarashi :
    public GameObject
{
private:
    // �X��̃A�U���V�̐�
    static int s_iOnIceNum;

    // �X�|�[���O��ԂŌŒ�
    AzrashiState mState = AzrashiState::SpawnToCenter;
    // ��e���̈ړ���
    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �X�|�[���ړI�ʒu
    DirectX::SimpleMath::Vector3 mTargetSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �X�|�[�����Ԓn�_
    DirectX::SimpleMath::Vector3 mTargetSpawnCenterPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    // �U���܂ł̃J�E���^�[
    float fCnt = 0.0f;
    float fAttackDuration = 0.0f;
    float fAfterSpawnAttackWait = 0.0f;

    unsigned int iScore = 0;

    // �X�|�[���n�_�܂ł̈ړ����x
    float fToSpawnSpeed = 20.0f;

    // ����U���������ǂ���
    bool bAttacked = false;

    // �ӂ���ьW��
    float fVelocity = 0.2f;

    // �u���[�L�W��
    float fBlakeVelocity = 0.9f;

    // ��e���ړ����������̒l�ȉ��Ȃ�~�߂�
    float fDamagePermission = 0.05f;

    // ��e���̌��̈ړ��x(���̒l���狗�������������̂��ӂ��Ƃт̋����ɂȂ�)
    float fVelocityDistance = 0.0f;

    // �R���|�[�l���g
    Com_SphereCollider* p_mColliderCom = nullptr;
    Com_Gravity* p_mGravityCom = nullptr;
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;
    Com_Foot* p_mFootCom = nullptr;

    OBJ_Shadow* p_mShadowObj = nullptr;

    OBJ_Azarashi* p_mLeader = nullptr;
public:
    bool bLeader = false;

public:
    OBJ_Azarashi();
    OBJ_Azarashi(const char* _name);
    OBJ_Azarashi(const char* _name, int _ModelKind);
    void Init()override;
    void Start()override;
    void Update()override;

    // �X�|�[���ʒu�̐ݒ�
    void SetTargetPosition(float _inx, float _iny, float _inz, float _tarx, float _tary, float _tarz, float _heightY);

    // �O������X�e�[�g�̐ݒ�
    void SetAzarashiState(AzrashiState _state)
    {
        mState = _state;
    }

    void OnCollisionEnter(GameObject* _obj);
    void OnCollisionStay(GameObject* _obj);

    Com_Foot* GetFootCom() { return p_mFootCom; };
    Com_SphereCollider* GetColliderCom() { return p_mColliderCom; };
    Com_Model* GetModelCom() { return p_mModelCom; };

    void SetAzrashiStatus(float _SpawnAfter, float _Duration, float _MoveSpeed, float _DamageVelocity, float _Blake, float _Permis, float _VelocityDis)
    {
        fAfterSpawnAttackWait = _SpawnAfter;
        fAttackDuration = _Duration;
        fToSpawnSpeed = _MoveSpeed;
        fVelocity = _DamageVelocity;
        fBlakeVelocity = _Blake;
        fDamagePermission = _Permis;
        fVelocityDistance = _VelocityDis;
    }

    // �X��̃A�U���V�̐��̎擾
    static int GetOnIceNum()
    {
        return s_iOnIceNum;
    }

    void SetLeader(OBJ_Azarashi* _obj);
};

