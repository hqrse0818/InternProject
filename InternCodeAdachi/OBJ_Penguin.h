#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_TestJump.h"

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
    Com_TestJump* p_mJumpCom = nullptr;
public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

};

