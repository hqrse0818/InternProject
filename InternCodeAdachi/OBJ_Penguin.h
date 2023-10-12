#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_Jump.h"
#include "Com_AngleCamera.h"
#include "Com_Gravity.h"
#include "Com_Foot.h"
#include "Com_Model.h"
// ペンギンのプレファブ

// ステートマシン
enum class PenguinState
{
    // 歩行状態
    Walk, 
    // ジャンプ中
    Jump, 
    // ヒップドロップの遅延
    HipDropDelay, 
    // ヒップドロップ中
    HipDrop, 
    // 被弾状態
    Damage,
    // 停止状態
    Idle
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
    Com_Gravity* p_mGravityCom = nullptr;
    // 足元コンポーネント
    Com_Foot* p_mFootCom = nullptr;

    // 空中での移動制御(スティック入力でどれだけの割合を適用するか)
    float fAirMoveSpeed = 1.0f;

    // カメラのスピード
    float fCamSpeed = 1.0f;

private:
    void CreateFromCSV(const char* _FileName);

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);
    OBJ_Penguin(const char* _name, const char* _FileName);

    void Start()override;
    void Update();

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

    void SetCameraCom(Com_AngleCamera* _com)
    {
        p_mCameraCom = _com;
    }

};

