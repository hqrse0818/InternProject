#pragma once
#include "Scene.h"

class OBJ_Penguin;

class Scene_Game :
    public Scene
{
private:
    // プレイヤー
    OBJ_Penguin* p_mPlayer{};

    // カウントダウン用オブジェクト
    GameObject* objNum1{};
    GameObject* objGo{};
    // スプライト
    Com_CustomSprite* p_mSpriteCountNum{};
    Com_CustomSprite* p_mSpriteGo{};

    //BGM
    Com_Audio* p_mAudio{};

    // SE

    float fWaitTime = 4.0f;
    float fWaitCnt = 0.0f;

public:

    void Init();
    void Start();
    void Update();

};

