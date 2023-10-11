#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../InternCodeAdachi/Com_Gravity.h"

// アザラシ

enum class AzrashiState
{
    // スポーン前の状態
    BeforeSpawnWait, 
    // スポーン開始位置とスポーン場所を指定して生成
    Spawn, 
    // スポーン場所に到達後攻撃まで待つ(3秒)
    AfterSpawnWait, 
    // 攻撃(モーション終了後待機に入る)
    Attack,
    // 攻撃後の待ち時間
    AttackWait,
    // 被弾状態(移動,移動終了で被弾状態終了->攻撃待ち)
    // 被弾状態中に海に触れる->Deathに移行
    Damage, 
    // 死亡(アニメーション再生後)
    Death
};

class OBJ_Azarashi :
    public GameObject
{
private:
    // スポーン前状態で固定
    AzrashiState mState = AzrashiState::BeforeSpawnWait;
    // 被弾時の移動量
    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // スポーン開始地点(最終的にマネージャー側でスポーン開始地点を指定する)
    DirectX::SimpleMath::Vector3 mInitialSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // スポーン目的位置(氷上のどこかにスポーンさせる(目的地に着いたら攻撃待ちに移行))
    DirectX::SimpleMath::Vector3 mTargetSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // 攻撃までのカウンター
    float fCnt = 0.0f;

    // コンポーネント

public:
    void Init()override;
    void Update()override;
};

