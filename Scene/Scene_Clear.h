#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_Transition.h"
#include "../InternCode.Kizuki/OBJ_Number.h"

class Scene_Clear :
    public Scene
{
public:
    enum class ClearState
    {
        // 各スコア待ち
        WaitState, 
        // トータルスコア待ち
        WaitTotal, 
        // 入力待ち
        WaitInput, 
        // タイトルへ
        ToTitle, 
        // ゲームへ
        ToGame,
    };

private:
    // トータルスコア
    int iTotalScore = 0;
    // 最大コンボ数
    int iMaxCombo = 0;
    // 残った氷の数
    int iRemainIceNum = 0;
    // 撃破アザラシ数
    int iBreakAzarashiNum = 0;

    int currentcom = 0;
    int currentice = 0;
    int currentbre = 0;
    int currentsco = 0;

    OBJ_Number* p_mComs[3];
    OBJ_Number* p_mIces[2];
    OBJ_Number* p_mBreaks[3];
    OBJ_Number* p_mScores[6];
    int scoresnum = 0;

    OBJ_Transition* p_mTransition{};

    Com_Audio* p_mSEClear{};
    Com_Audio* p_mSEDrum{};
    float fDrumDuration = 3.5f;
    float fDrumCnt = 0.0f;
    Com_Audio* p_mSEResult{};
    Com_Audio* p_mSECursor{};
    Com_Audio* p_mSEDecide{};

    GameObject* p_mOnemore{};
    Com_Scaling* p_mOneScale{};
    GameObject* p_mReturn{};
    Com_Scaling* p_mRetScale{};
    GameObject* p_mBanner{};
    GameObject* p_mAllow{};

    bool bisUP = false;

    bool bSEEnd = false;
    ClearState mState = ClearState::WaitState;
public:

    void Init();
    void Start();
    void Update();
    void Uninit();
};

