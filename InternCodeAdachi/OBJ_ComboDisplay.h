#pragma once
#include "../GameObject/GameObject.h"
#include "../InternCode.Kizuki/OBJ_Number.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_CustomSprite.h"

class OBJ_ComboDisplay :
    public GameObject
{
private:
    Com_Shader* p_mShader;
    Com_CustomSprite* p_mSprite;
    OBJ_Number* Nums[3];
    ShaderResourceView* p_mSRV{};

    int iLastCombo = 0;
    int iCurrentCombo = 0;

    float fComboResetTime = 0.0f;

    float fComboCnt = 0.0f;

    float fEuler = 0.0f;

    // 初期スケール
    DirectX::SimpleMath::Vector2 mMyInitScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    // 最大スケール
    DirectX::SimpleMath::Vector2 mMyMaxScale = DirectX::SimpleMath::Vector2(140.0f, 140.0f);
    // 数字初期スケール
    DirectX::SimpleMath::Vector2 mNumInitScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    // 数字最大スケール
    DirectX::SimpleMath::Vector2 mNumMaxScale = DirectX::SimpleMath::Vector2(140.0f,140.0f);
    // スケーリングの速度
    float fScaleSpeed = 20.0f;
    // 数字のメインとなる場所
    DirectX::SimpleMath::Vector2 mMainPos = DirectX::SimpleMath::Vector2(800.0f, 500.0f);
    // 数字の間隔
    float fNumDuration = 10.0f;
    float fScaleDuration = 40.0f;

    // 現在の地震のスケール
    DirectX::SimpleMath::Vector2 mCurrentMyScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

    // 現在の数字のスケール
    DirectX::SimpleMath::Vector2 mCurrentNumScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

    // 桁上げの発生
    bool bUpNum = false;

    // 回転時間
    float fRotTime = 1.0f;
    float fRotCnt = 0.0f;

    // 回転の速度
    float fRotSpeed = 20.0f;

public:
    OBJ_ComboDisplay();
    OBJ_ComboDisplay(const char* _name);
    OBJ_ComboDisplay(const char* _name, const char* _FileName);

    void Init();
    void Start();
    void Update();
    void Uninit();
};

