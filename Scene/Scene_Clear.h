#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_Transition.h"
#include "../InternCode.Kizuki/OBJ_Number.h"
#include "../InternCodeAdachi/OBJ_ResultPenguin.h"

class Scene_Clear :
    public Scene
{
public:
    enum class ClearState
    {
        // 氷ボーナス
        WaitIce, 
        // 最大コンボ待ち
        WaitCombo,
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
    int iIceScore = 0;
    // 撃破アザラシ数
    int iBreakAzarashiNum = 0;

    int currentcom = 0;
    int currentice = 0;
    int currentbre = 0;
    int currentsco = 0;

    //トータル 毎フレーム加算する値
    int isc = 0;

    // 氷
    int iic = 0;
    // コンボ
    int ico = 0;

    OBJ_Number* p_mComs[3];
    OBJ_Number* p_mICes[5];
    OBJ_Number* p_mScores[6];
    int scoresnum = 0;

    OBJ_Transition* p_mTransition{};

    
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

    bool bisUP = true;

    bool bSEEnd = false;

    bool bThisOne = true;

    int cnt = 0;
    ClearState mState = ClearState::WaitIce;

    OBJ_ResultPenguin* p_mPenguin{};
public:

    void Init();
    void Start();
    void Update();
    void Uninit();
};

