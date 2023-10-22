#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"
#include "../InternCodeAdachi/Com_Gravity.h"
#include "../Component/Com_Shader.h"
#include "Com_Model.h"
#include "Com_Foot.h"
#include "../Component/Com_Audio.h"
#include "../GameObject/OBJ_Shadow.h"
#include "Com_AzarshiHit.h"
#include "../InternCode.Kizuki/OBJ_AzarashiAttackEffect.h"
#include "../InternCode.Kizuki/OBJ_AzarashiDeadEffect.h"

// アザラシ

enum class AzrashiState
{
    // スポーン開始位置とスポーン場所を指定して生成
    SpawnToCenter, 
    // 氷上まで落下
    SpawnToTarget,
    // スポーン場所に到達後攻撃まで待つ(3秒)
    AfterSpawnWait, 
    // 攻撃(モーション終了後待機に入る)
    Attack,
    // 攻撃後の待ち時間
    AttackWait,
    // 被弾状態(移動,移動終了で被弾状態終了->攻撃待ち)
    // 被弾状態中に海に触れる->Deathに移行
    Damage, 
    // 飛び込み
    Dive,
    // 飛び込みアニメーション終了後処理
    DiveTo,
    // 死亡(アニメーション再生後)
    Death,
    // 落ちるようオブジェクト衝突時
    Dive2,
    // 飛び込みアニメーション終了後
    DiveTo2,
    // Dive2終了後処理
    Death2
};

class OBJ_Azarashi :
    public GameObject
{
private:
    // 氷上のアザラシの数
    static int s_iOnIceNum;

    // スコア一覧
    static int s_iScoreMin;
    static int s_iScoreCenter;
    static int s_iScoreMax;

    // スコアと距離の関係
     // 最大スコアを得るための基準距離
    static float fScoreDisMax;
    // 次のスコアの基準距離
    static float fScoreDisCen;

    // スポーン前状態で固定
    AzrashiState mState = AzrashiState::SpawnToCenter;
    // 被弾時の移動量
    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // スポーン目的位置
    DirectX::SimpleMath::Vector3 mTargetSpawnPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // スポーン中間地点
    DirectX::SimpleMath::Vector3 mTargetSpawnCenterPoint = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    // 攻撃までのカウンター
    float fCnt = 0.0f;
    float fAttackDuration = 0.0f;
    float fAfterSpawnAttackWait = 0.0f;

    unsigned int iScore = 0;

    // スポーン地点までの移動速度
    float fToSpawnSpeed = 20.0f;

    // 今回攻撃したかどうか
    bool bAttacked = false;

    // ふっ飛び係数
    float fVelocity = 0.2f;

    // ブレーキ係数
    float fBlakeVelocity = 0.9f;

    // 被弾中移動距離がこの値以下なら止める
    float fDamagePermission = 0.05f;

    // 被弾時の元の移動度(この値から距離を引いたものがふきとびの強さになる)
    float fVelocityDistance = 0.0f;

    // コンポーネント
    Com_SphereCollider* p_mColliderCom = nullptr;
    Com_Gravity* p_mGravityCom = nullptr;
    Com_Shader* p_mShaderCom = nullptr;
    Com_Model* p_mModelCom = nullptr;
    Com_Foot* p_mFootCom = nullptr;
    Com_AzarshiHit* p_mHitCom = nullptr;
    Com_Audio* p_mSESpawn = nullptr;
    Com_Audio* p_mSEHitBig = nullptr;
    Com_Audio* p_mSEHitMid = nullptr;
    Com_Audio* p_mSEHitSma = nullptr;
    Com_Audio* p_mSELand = nullptr;
    Com_Audio* p_mSEDeath = nullptr;

    float fDeadTime = 1.0f;
    float fDeadCnt = 0.0f;

    OBJ_Shadow* p_mShadowObj = nullptr;

    OBJ_Azarashi* p_mLeader = nullptr;

    static OBJ_AzarashiAttackEffect* p_mAttackEf;
    static OBJ_AzarashiDeadEffect* p_mDeadEf;

public:
    bool bLeader = false;

public:
    OBJ_Azarashi();
    OBJ_Azarashi(const char* _name);
    OBJ_Azarashi(const char* _name, int _ModelKind);
    void Init()override;
    void Start()override;
    void Update()override;

    // スポーン位置の設定
    void SetTargetPosition(float _inx, float _iny, float _inz, float _tarx, float _tary, float _tarz, float _heightY);

    // 外部からステートの設定
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

    // 氷上のアザラシの数の取得
    static int GetOnIceNum()
    {
        return s_iOnIceNum;
    }

    void SetLeader(OBJ_Azarashi* _obj);

    static void SetGettingScore(int _min, int _cen, int _max)
    {
        s_iScoreMin = _min;
        s_iScoreCenter = _cen;
        s_iScoreMax = _max;
    }

    static void SetScoreDistance(float _high, float _cen)
    {
        fScoreDisMax = _high;
        fScoreDisCen = _cen;
    }

    static void SetAttackEfect(OBJ_AzarashiAttackEffect* _obj)
    {
        p_mAttackEf = _obj;
    }

    static void SetDeadEffect(OBJ_AzarashiDeadEffect* _obj)
    {
        p_mDeadEf = _obj;
    }

    Com_Audio* GetSpawnAudio()
    {
        return p_mSESpawn;
    }
};

