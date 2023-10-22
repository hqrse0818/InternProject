#pragma once
#include "GameObject.h"
#include "../Component/Com_Sprite.h"

// フェードシーン遷移用オブジェクト
class OBJ_Transition :
    public GameObject
{
public:
    enum class FadeState
    {
        InEnd,
        In,
        Out,
        OutEnd
    };

protected:
    DirectX::SimpleMath::Color mColor = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
    FadeState mState = FadeState::InEnd;
    float fFadeTime = 0.0f;
    Com_Sprite* p_mSprite{};

public:

    OBJ_Transition();
    OBJ_Transition(const char* _name);
    void Update()override;

    FadeState GetState()
    {
        return mState;
    }

    void SetState(FadeState _state)
    {
        mState = _state;
    }

    void FadeIn(float _time)
    {
        mColor.w = 1.0f;
        fFadeTime = _time;
        mState = FadeState::In;
    }

    void FadeOut(float _time)
    {
        mColor.w = 0.0f;
        fFadeTime = _time;
        mState = FadeState::Out;
    }

    void SetColor(DirectX::SimpleMath::Vector3 _Col)
    {
        mColor.x = _Col.x;
        mColor.y = _Col.y;
        mColor.z = _Col.z;
    }
    void SetColor(DirectX::SimpleMath::Color _Col)
    {
        mColor = _Col;
    }

    void SetTexture(const char* _name);
};

