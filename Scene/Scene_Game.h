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
    // �Q�[���I�[�o�[�p�X�e�[�g
    enum class OverState
    {
        Game, WaitInput,ToGame,ToTitle
    };

private:
    OverState mState = OverState::Game;

    OBJ_Transition* p_mTransition{};

    // �v���C���[
    OBJ_Penguin* p_mPlayer{};

    // �J�E���g�_�E���p�I�u�W�F�N�g
    GameObject* p_mObjNum{};
    GameObject* p_mObjGo{};
    // �X�v���C�g
    Com_CustomSprite* p_mSpriteNum{};
    Com_CustomSprite* p_mSpriteGo{};

    // �X�R�A
    OBJ_DisplayScore* ScoreObj{};
    // �R���{
    OBJ_ComboDisplay* ComboObj{};
    // �A�U���V�̐�
    OBJ_AzarashiRemain* ARemainNum{};
    // �A�U���V�̕\��
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
    // �Q�[���I�[�o�[�p
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

