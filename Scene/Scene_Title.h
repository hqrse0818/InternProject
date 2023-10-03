#pragma once
#include "Scene.h"
#include "../ComponentHeader.h"
#include "../GameObject/OBJ_Transition.h"

class Scene_Title :
    public Scene
{
private:
    OBJ_Transition* p_mTransition{};
    bool bLoadScene = false;
    float fFlashCnt = 0.0f;
    Com_Audio* p_mAudio{};
public:
    void Init() override;
    void Start()override;
    void Update() override;
    void Uninit()override;
};

