#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_Jump.h"
#include "Com_AngleCamera.h"
#include "Com_PenguinGravity.h"
#include "Com_Foot.h"
#include "Com_Model.h"
#include "Com_Shadow.h"
#include "../Component/Com_BoxCollider.h"
#include "../Component/Com_Audio.h"
#include "../InternCode.Kizuki/OBJ_HipEffect.h"

// ペンギンのプレファブ
#define PenguinStatuNum (23)

// ペンギンのステート
enum class PenguinState
{
    // 歩く(入力可)
    Walk, 
    //
    BeforeJump,
    // ジャンプ(入力可)
    Jump, 
    // ヒップドロップ前の溜めの時間(入力不可)
    BeforeHipDrop, 
    // ヒップドロップ中(入力不可)
    HipDrop, 
    //
    AfterHipDrop,
    // 被弾状態(入力不可)
    Damage, 
    // ヒップドロップでアザラシに衝突
    HipDropOnAzarashi,
    // 待機モーション
    Idle,

    // 死亡
    Death,
};

class OBJ_Penguin :
    public GameObject
{
private:
    // モデル描画コンポーネント
    Com_Model* p_mModel = nullptr;
    // シェーダーコンポーネント
    Com_Shader* p_mShader = nullptr;
    // 移動コンポーネント
    Com_CharacterMove* p_mMoveCom = nullptr;
    // ジャンプコンポーネント
    Com_Jump* p_mJumpCom = nullptr;
    // ターゲットにされてるカメラコンポーネント
    Com_AngleCamera* p_mCameraCom = nullptr;
    // 重力コンポーネント
    Com_PenguinGravity* p_mGravityCom = nullptr;
    // 足元コンポーネント
    Com_Foot* p_mFootCom = nullptr;
    // 影
    Com_Shadow* p_mShadowCom = nullptr;
    // コライダー
    Com_BoxCollider* p_mColliderCom = nullptr;
    // ヒップインパクトエフェクト
    OBJ_HipEffect* p_mHipEf = nullptr;

    // SE再生用
    Com_Audio* p_mSEJump = nullptr;
    Com_Audio* p_mSEWalk = nullptr;
    Com_Audio* p_mSELand = nullptr;
    Com_Audio* p_mSEAttacLand = nullptr;
    Com_Audio* p_mSEMiss = nullptr;
    Com_Audio* p_mSEDeath = nullptr;

    // 空中での移動制御(スティック入力でどれだけの割合を適用するか)
    float fAirMoveSpeed = 1.0f;

    // カメラのスピード
    float fCamSpeed = 1.0f;
    // マウス用カメラスピード
    float fMouseCameraSpeed = 0.2f;

    // ヒップインパクトの範囲
    float fImpactRange = 8.0f;

    // ヒップドロップに移行するまでのディレイ
    float fImpactDelay = 0.2f;
    float fImpactCnt = 0.0f;

    // アザラシ衝突時のよろめき
    float fDamagedPower = 6.0f;

    // 衝突後のブレーキ係数
    float fBlake = 0.5f;

    // 停止許容距離
    float fDamagePermission = 0.05f;

    // ヒップインパクトの拡大速度
    float fImpactScalingSpeed = 0.5f;

    // 直撃時の上へのベクトル
    float fDirectVector = 0.0f;

    // 直撃後の浮遊状態の継続時間
    float fFloatTime = 0.0f;
    float fFloatCnt = 0.0f;

    // 被弾後の無敵時間
    float fArmorTime = 0.2f;
    float fArmorCnt = 0.0f;

    float fIdleTime = 0.0f;
    float fIdelCnt = 0.0f;

    // 歩行SEの間隔
    float fWalkSEDuration = 0.2f;
    float fWalkSECnt = 0.0f;

    DirectX::SimpleMath::Vector3 mDamageVelocity = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

    PenguinState mState = PenguinState::Walk;

    DirectX::SimpleMath::Vector2 mMoveVelocity = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

private:
    void CreateFromCSV(const char* _FileName);

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);
    OBJ_Penguin(const char* _name, const char* _FileName);

    void Start()override;
    void Update();
    void OnCollisionEnter(GameObject* _obj)override;
    void OnCollisionStay(GameObject* _obj)override;

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

    void SetCameraCom(Com_AngleCamera* _com)
    {
        p_mCameraCom = _com;
    }

    void SetHipEffect(OBJ_HipEffect* _obj)
    {
        p_mHipEf = _obj;
    }
};

