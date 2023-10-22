#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_Transition.h"
#include "../GameObject/OBJ_HalfFade.h"
#include "../InternCodeAdachi/OBJ_ComboDisplay.h"
#include "../InternCodeAdachi/OBJ_DisplayScore.h"
#include "../InternCode.Kizuki/OBJ_AzarashiRemain.h"
#include "../GameObject/OBJ_GameOver.h"

class OBJ_Penguin;

class Scene_Game :
    public Scene
{
public:
    // ゲームオーバー用ステート
    enum class OverState
    {
        Game, WaitInput,ToGame,ToTitle
    };

private:
    OverState mState = OverState::Game;

    OBJ_Transition* p_mTransition{};

    // プレイヤー
    OBJ_Penguin* p_mPlayer{};

    // カウントダウン用オブジェクト
    GameObject* p_mObjNum{};
    GameObject* p_mObjGo{};
    // スプライト
    Com_CustomSprite* p_mSpriteNum{};
    Com_CustomSprite* p_mSpriteGo{};

    // スコア
    OBJ_DisplayScore* ScoreObj{};
    // コンボ
    OBJ_ComboDisplay* ComboObj{};
    // アザラシの数
    OBJ_AzarashiRemain* ARemainNum{};
    // アザラシの表示
    GameObject* ARemain{};

    //BGM
    Com_Audio* p_mBGM{};

    // SE
    Com_Audio* p_mSECount{};
    Com_Audio* p_mSEGo{};
    Com_Audio* p_mSEOver{};
    Com_Audio* p_mSECursor{};
    Com_Audio* p_mSEDecide{};
    Com_Audio* p_mSEClear{};

    float fWaitTime = 5.0f;
    float fWaitCnt = 0.0f;
    bool bChangeNum = false;

    bool bisUP = true;
    // ゲームオーバー用
    OBJ_GameOver* p_mOvobj{};
    OBJ_HalfFade* p_mHalfFade{};
    GameObject* ice1{};
    GameObject* ice2{};
    GameObject* p_mOnemore{};
    Com_Scaling* p_mOneScale{};
    GameObject* p_mReturn{};
    Com_Scaling* p_mRetScale{};
    GameObject* p_mBanner{};
    GameObject* p_mAllow{};


public:

    void Init()override;
    void Start()override;
    void Update()override;
    void Uninit()override;
};

