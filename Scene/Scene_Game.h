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
    GameObject* p_mObjNum{};
    GameObject* p_mObjGo{};
    // スプライト
    Com_CustomSprite* p_mSpriteNum{};
    Com_CustomSprite* p_mSpriteGo{};

    //BGM
    Com_Audio* p_mBGM{};

    // SE
    Com_Audio* p_mSECount{};
    Com_Audio* p_mSEGo{};

    float fWaitTime = 5.0f;
    float fWaitCnt = 0.0f;
    bool bChangeNum = false;

public:

    void Init()override;
    void Start()override;
    void Update()override;
    void Uninit()override;
};

