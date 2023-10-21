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
        Start, Tutorial,ToGame,
    };

private:
    OBJ_Transition* p_mTransition{};
    bool bLoadScene = false;
    float fFlashCnt = 0.0f;
    Com_Audio* p_mAudio{};

    TitleState mStatus = TitleState::Start;


    GameObject* p_mStartLogo{};
    GameObject* p_mTutolialLogo{};
    GameObject* p_mAllow{};

    bool bisUP = true;
public:
    void Init() override;
    void Start()override;
    void Update() override;
    void Uninit()override;
};

