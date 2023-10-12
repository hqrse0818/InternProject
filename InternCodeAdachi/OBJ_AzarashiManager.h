#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Azarashi.h"

#include <vector>

#define GameTimeRow (1)
#define SpawnRateRow (3)
#define SpawnNumRow (5)
#define AzarashiStateRow (7)
#define StateSetNum (11)

enum class SpawnState {
    Wait, Spawn,End
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

    int iMaxSpawn = 0;
    int iSpawnedNum = 0;
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

    SpawnState mState = SpawnState::Wait;



public:
    OBJ_AzarashiManager();
    OBJ_AzarashiManager(const char* _name);
    OBJ_AzarashiManager(const char* _name, const char* _FileName);

    void Create();

    void Update();
};

