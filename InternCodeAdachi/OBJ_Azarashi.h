#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../InternCodeAdachi/Com_Gravity.h"

// �A�U���V

enum class AzrashiState
{
    // �X�|�[���O�̏��
    BeforeSpawnWait, 
    // �X�|�[���J�n�ʒu�ƃX�|�[���ꏊ���w�肵�Đ���
    Spawn, 
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

    // �R���|�[�l���g

public:
    void Init()override;
    void Update()override;
};

