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

// 氷の残っている位置を取得してアザラシをスポーンさせる
class OBJ_AzarashiManager :
    public GameObject
{
private:
    // スポーンレート用カウンター
    float fSpawnCnt = 0.0f;
    // ゲームの進行時間によって出現頻度を変えるためのカウント
    float fGameCnt = 0.0f;;
    // スポーンレートのインデックス
    int iCurrentIndex = 0;
    // スポーンレートを切り替えるゲーム時間の数字列
    std::vector<unsigned int> vec_SpawnRateGameTimer;
    // ゲーム時間ごとのスポーンレート
    std::vector<float> vec_SpawnRate;

    static int s_iMaxSpawn;
    static int s_iSpawnedNum;
    static int s_iRemain;

    // コライダー中心
    DirectX::SimpleMath::Vector3 mAzarashiCenter = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // コライダー半径
    float fAzarashiRadius = 1.0f;
    // 足の高さ
    float fFootHeight = 2.0f;
    // スポーン後の待ち時間
    float fAfterWait = 3.0f;
    // 攻撃間隔
    float fAttackDuration = 2.0f;
    // スポーン位置までの移動速度
    float fMoveSpeed = 20.0f;
    // ふきとび係数
    float fVelocity = 0.3f;
    // ブレーキ係数
    float fBlake = 0.9f;
    // 被弾時許容距離
    float fLength = 0.05f;
    // 出現時のy座標
    float fSpawnY = 0.0f;
    // 中間地点の高さ
    float fCenterY = 0.0f;
    // スポーン位置のy座標
    float fIceY = 0.0f;
    // 吹き飛ばし時の基底距離
    float fDamageDistance = 0.0f;
    // 1回のスポーンでの最小発生数
    int iSpawnMin = 2;
    // 1回のスポーンでの最大発生数
    int iSpawnMax = 4;
    // 獲得スコア最小
    int iScoreMin = 100;
    // 獲得スコア中間
    int iScoreCenter = 300;
    // 獲得スコア最大
    int iScoreMax = 500;

    // リーダーが出現してから何秒後にスポーンするか
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

