#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Azarashi.h"

#include <vector>
#define RateNumRow (1)
#define GameTimeRow (3)
#define SpawnRateRow (5)
#define SpawnNumRow (7)
#define AzarashiStateRow (9)
#define StateSetNum (24)

enum class SpawnState {
    Wait, SpawnLeader,WaitTeshita,SpawnTeshita,End,Calc
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

    static int s_iMaxSpawn;
    static int s_iSpawnedNum;
    static int s_iRemain;

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
    // 1��̃X�|�[���ł̍ŏ�������
    int iSpawnMin = 2;
    // 1��̃X�|�[���ł̍ő唭����
    int iSpawnMax = 4;
    // �l���X�R�A�ŏ�
    int iScoreMin = 100;
    // �l���X�R�A����
    int iScoreCenter = 300;
    // �l���X�R�A�ő�
    int iScoreMax = 500;

    // ���[�_�[���o�����Ă��牽�b��ɃX�|�[�����邩
    float fLeaderSpawnedTime = 0.2f;
    float fLeaderCnt = 0;

    int iRandTestNum = 0;

    DirectX::SimpleMath::Vector3 mLeaderPos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    OBJ_Azarashi* p_mCurrentLeader = nullptr;

    DirectX::SimpleMath::Vector3 mInit = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    SpawnState mState = SpawnState::Wait;

    GameObject* p_mTarget = nullptr;

    int iRow = 0;
    int iLine = 0;

public:
    OBJ_AzarashiManager();
    OBJ_AzarashiManager(const char* _name);
    OBJ_AzarashiManager(const char* _name, const char* _FileName);

    void CreateLeader();
    void CreateTeshita();
    void Start();
    void Update();


    static int GetMaxSpawn()
    {
        return s_iMaxSpawn;
    }

    static int GetSpawnedNum()
    {
        return s_iSpawnedNum;
    }

    void SetTarget(GameObject* _tar)
    {
        p_mTarget = _tar;
    }

    static void CalcRemain()
    {
        s_iRemain--;
    }

    static int GetRemain()
    {
        return s_iRemain;
    }
};

