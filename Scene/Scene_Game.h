#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_Transition.h"

class OBJ_Penguin;

class Scene_Game :
    public Scene
{
private:
    OBJ_Transition* p_mTransition{};

    // �v���C���[
    OBJ_Penguin* p_mPlayer{};

    // �J�E���g�_�E���p�I�u�W�F�N�g
    GameObject* p_mObjNum{};
    GameObject* p_mObjGo{};
    // �X�v���C�g
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

