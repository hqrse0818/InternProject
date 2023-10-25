#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Sprite.h"
#include "../Component/Com_Audio.h"

class OBJ_Warning :
    public GameObject
{
public:
    enum class WarningState
    {
        No, Start, Warning, End
    };

private:
    GameObject* pBack{};
    Com_Sprite* pBackSp{};
    GameObject* pFont{};
    Com_Sprite* pFontSp{};
    GameObject* pMark{};
    Com_Sprite* pMarkSp{};
    DirectX::SimpleMath::Color mColor = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.5f);
    DirectX::SimpleMath::Color mBackColor = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.5f);
    DirectX::SimpleMath::Vector3 InitBack = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
    DirectX::SimpleMath::Vector3 InitFont = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
    DirectX::SimpleMath::Vector3 InitMark = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

    WarningState mState = WarningState::No;

    float fAlphaSpeed = 1.0f;
    bool bRet = false;

    float fScaleSpeed = 25.0f;
    float fScaleMinus = -25.0f;

    Com_Audio* p_SEWarning{};

public:
    OBJ_Warning();
    OBJ_Warning(const char* _name);
    OBJ_Warning(const char* _name, const char* _FileName);

    void Update()override;

    void StartFade()
    {
        mState = WarningState::Start;
        p_SEWarning->Play();
    }
    void EndFade()
    {
        mState = WarningState::End;
    }
};

