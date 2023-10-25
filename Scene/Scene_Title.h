#pragma once
#include "Scene.h"
#include "../ComponentHeader.h"
#include "../GameObject/OBJ_Transition.h"

class Scene_Title :
    public Scene
{
private:
    enum class TitleState
    {
        WaitFade, WaitInput, Tutorial,ToGame,
    };

    enum class TutorialPage
    {
        None, Page1, Page2, Page3
    };

private:
    OBJ_Transition* p_mTransition{};
    bool bLoadScene = false;
    float fFlashCnt = 0.0f;
    

    TitleState mState = TitleState::WaitFade;
    TutorialPage mPage = TutorialPage::None;


    GameObject* p_mStartLogo{};
    Com_Scaling* p_mStartScale{};
    GameObject* p_mTutolialLogo{};
    Com_Scaling* p_mTutoScale{};
    GameObject* p_mAllow{};
    GameObject* p_mBanner{};
    GameObject* p_mExp1{};
    GameObject* p_mExp2{};

    GameObject* pBackFont{};
    GameObject* pBackButton{};

    Com_Audio* p_mAudio{};
    Com_Audio* p_mSECursor{};
    Com_Audio* p_mSEDecide{};

    bool bisUP = true;
    bool bisLeft = true;
public:
    void Init() override;
    void Start()override;
    void Update() override;
    void Uninit()override;
};

