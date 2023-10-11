#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../InternCodeAdachi/Com_Gravity.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"
#include "Com_Foot.h"

// �A�U���V

enum class AzrashiState
{
    // �X�|�[���O�̏��
    BeforeSpawnWait, 
    // �X�|�[���J�n�ʒu�ƃX�|�[���ꏊ���w�肵�Đ���
    Spawn, 
    // �X��܂ŗ���
    Fall,
    // �X�|�[���ꏊ�ɓ��B��U���܂ő҂�(3�b)
    AfterSpawnWait, 
    // �U��(���[�V�����I����ҋ@�ɓ���)
    Attack,
    // �U����̑҂�����
    AttackWait,
    // ��e���(�ړ�,�ړ��I���Ŕ�e��ԏI��->�U���҂�)
    // ��e��Ԓ��ɊC�ɐG���->Death�Ɉڍs
    Damage, 
    // ���S(�A�j���[�V�����Đ���)
    Death
};

class OBJ_Azarashi :
    public GameObject
{
private:
    // �X�|�[���O��ԂŌŒ�
    AzrashiState mState = AzrashiState::BeforeSpawnWait;
    // ��e���̈ړ���
    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �X�|�[���J�n�n�_(�ŏI�I�Ƀ}�l�[�W���[���ŃX�|�[���J�n�n�_���w�肷��)
    DirectX::SimpleMath::Vector3 mInitialSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �X�|�[���ړI�ʒu(�X��̂ǂ����ɃX�|�[��������(�ړI�n�ɒ�������U���҂��Ɉڍs))
    DirectX::SimpleMath::Vector3 mTargetSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �U���܂ł̃J�E���^�[
    float fCnt = 0.0f;

    // �X�|�[���n�_�܂ł̈ړ����x
    float fToSpawnSpeed = 20.0f;

    // ����U���������ǂ���
    bool bAttacked = false;

    // �R���|�[�l���g
    Com_SphereCollider* p_mColliderCom = nullptr;
    Com_Gravity* p_mGravityCom = nullptr;
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;
    Com_Foot* p_mFootCom = nullptr;
public:
    OBJ_Azarashi();
    OBJ_Azarashi(const char* _name);
    void Init()override;
    void Update()override;

    // �X�|�[���ʒu�̐ݒ�
    void SetTargetPosition(float _x, float _y, float _z);

    void OnCollisionEnter(GameObject* _obj);
};

