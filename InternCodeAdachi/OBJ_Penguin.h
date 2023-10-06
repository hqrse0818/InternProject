#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_Jump.h"
#include "Com_AngleCamera.h"
#include "Com_Gravity.h"

// ペンギンのプレファブ

class OBJ_Penguin :
    public GameObject
{
private:
    // モデル描画コンポーネント
    Com_AssimpAnimation* p_mModel = nullptr;
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
public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

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

