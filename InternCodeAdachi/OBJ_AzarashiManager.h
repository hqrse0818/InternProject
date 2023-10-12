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

    int iMaxSpawn = 0;
    int iSpawnedNum = 0;
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

    SpawnState mState = SpawnState::Wait;



public:
    OBJ_AzarashiManager();
    OBJ_AzarashiManager(const char* _name);
    OBJ_AzarashiManager(const char* _name, const char* _FileName);

    void Create();

    void Update();
};

