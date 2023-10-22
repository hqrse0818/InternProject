#pragma once
#include "GameObject.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_Sprite.h"

class OBJ_GameOver :
    public GameObject
{
public:
    enum class GameOverObjState
    {
        None,Start,Move1, Wait1, Move2, Wait2, Move3, Finish,
    };

private:
    Com_Shader* p_mShader{};
    Com_Sprite* p_mSprite{};

    GameOverObjState mState = GameOverObjState::Start;

    DirectX::SimpleMath::Vector2 mStopPosA = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    DirectX::SimpleMath::Vector2 mStopPosB = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    DirectX::SimpleMath::Vector2 mFinalPos = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    float fDuration = 0.5f;
    float fWaitTime = 0.3f;
    float fCnt = 0.0f;

    DirectX::SimpleMath::Vector2 mMoveVal = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

    bool bStart = false;
    bool bWait = false;
    bool bEnd = false;

public:

    OBJ_GameOver();
    OBJ_GameOver(const char* _name);

    void SetStopPosA(float _x, float _y)
    {
        mStopPosA.x = _x;
        mStopPosA.y = _y;
    }
    void SetStopPosB(float _x, float _y)
    {
        mStopPosB.x = _x;
        mStopPosB.y = _y;
    }
    void SetFinalPos(float _x, float _y)
    {
        mFinalPos.x = _x;
        mFinalPos.y = _y;
    }

    void SetDuration(float _val)
    {
        fDuration = _val;
    }

    void SetWaitTime(float _val)
    {
        fWaitTime = _val;
    }

    void FallStart()
    {
        bStart = true;
        mState = GameOverObjState::Move1;
    }

    void Init();
    void Update();

    GameOverObjState GetState()
    {
        return mState;
    }
};

