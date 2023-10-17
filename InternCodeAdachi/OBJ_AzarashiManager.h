#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Azarashi.h"

#include <vector>
#define RateNumRow (1)
#define GameTimeRow (3)
#define SpawnRateRow (5)
#define SpawnNumRow (7)
#define AzarashiStateRow (9)
#define StateSetNum (15)

enum class SpawnState {
    Wait, Spawn,End,Calc
};

// �X�̎c���Ă���ʒu���擾���ăA�U���V���X�|�[��������
class OBJ_AzarashiManager :
    public GameObject
{
private:
    // �X�|�[�����[�g�p�J�E���^�[
    float fSpawnCnt = 0.0f;
    // �Q�[���̐i�s���Ԃɂ���ďo���p�x��ς��邽�߂̃J�E���g
    float fGameCnt = 0.0f;;
    // �X�|�[�����[�g�̃C���f�b�N�X
    int iCurrentIndex = 0;
    // �X�|�[�����[�g��؂�ւ���Q�[�����Ԃ̐�����
    std::vector<unsigned int> vec_SpawnRateGameTimer;
    // �Q�[�����Ԃ��Ƃ̃X�|�[�����[�g
    std::vector<float> vec_SpawnRate;

    static int iMaxSpawn;
    static int iSpawnedNum;
    // �R���C�_�[���S
    DirectX::SimpleMath::Vector3 mAzarashiCenter = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // �R���C�_�[���a
    float fAzarashiRadius = 1.0f;
    // ���̍���
    float fFootHeight = 2.0f;
    // �X�|�[����̑҂�����
    float fAfterWait = 3.0f;
    // �U���Ԋu
    float fAttackDuration = 2.0f;
    // �X�|�[���ʒu�܂ł̈ړ����x
    float fMoveSpeed = 20.0f;
    // �ӂ��ƂьW��
    float fVelocity = 0.3f;
    // �u���[�L�W��
    float fBlake = 0.9f;
    // ��e�����e����
    float fLength = 0.05f;
    // �o������y���W
    float fSpawnY = 0.0f;
    // ���Ԓn�_�̍���
    float fCenterY = 0.0f;
    // �X�|�[���ʒu��y���W
    float fIceY = 0.0f;
    // ������΂����̊�ꋗ��
    float fDamageDistance = 0.0f;

    SpawnState mState = SpawnState::Wait;

public:
    OBJ_AzarashiManager();
    OBJ_AzarashiManager(const char* _name);
    OBJ_AzarashiManager(const char* _name, const char* _FileName);

    void Create();
    void Update();

    static int GetMaxSpawn()
    {
        return iMaxSpawn;
    }

    static int GetSpawnedNum()
    {
        return iSpawnedNum;
    }
};

