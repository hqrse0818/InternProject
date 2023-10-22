#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_Transition.h"

class Scene_Clear :
    public Scene
{
public:
    enum class ClearState
    {
        // �e�X�R�A�҂�
        WaitState, 
        // �g�[�^���X�R�A�҂�
        WaitTotal, 
        // ���͑҂�
        WaitInput, 
        // �^�C�g����
        ToTitle, 
        // �Q�[����
        ToGame,
    };

private:
    // �g�[�^���X�R�A
    int iTotalScore = 0;
    // �ő�R���{��
    int iMaxCombo = 0;
    // �c�����X�̐�
    int iRemainIceNum = 0;
    // ���j�A�U���V��
    int iBreakAzarashiNum = 0;

    OBJ_Transition* p_mTransition{};

    Com_Audio* p_mSEClear{};
    Com_Audio* p_mSEDrum{};
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

    ClearState mState = ClearState::WaitState;
public:

    void Init();
    void Start();
    void Update();
    void Uninit();
};

