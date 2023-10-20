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

    // �����X�P�[��
    DirectX::SimpleMath::Vector2 mMyInitScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    // �ő�X�P�[��
    DirectX::SimpleMath::Vector2 mMyMaxScale = DirectX::SimpleMath::Vector2(140.0f, 140.0f);
    // ���������X�P�[��
    DirectX::SimpleMath::Vector2 mNumInitScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
    // �����ő�X�P�[��
    DirectX::SimpleMath::Vector2 mNumMaxScale = DirectX::SimpleMath::Vector2(140.0f,140.0f);
    // �X�P�[�����O�̑��x
    float fScaleSpeed = 20.0f;
    // �����̃��C���ƂȂ�ꏊ
    DirectX::SimpleMath::Vector2 mMainPos = DirectX::SimpleMath::Vector2(800.0f, 500.0f);
    // �����̊Ԋu
    float fNumDuration = 10.0f;
    float fScaleDuration = 40.0f;

    // ���݂̒n�k�̃X�P�[��
    DirectX::SimpleMath::Vector2 mCurrentMyScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

    // ���݂̐����̃X�P�[��
    DirectX::SimpleMath::Vector2 mCurrentNumScale = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

    // ���グ�̔���
    bool bUpNum = false;

    // ��]����
    float fRotTime = 1.0f;
    float fRotCnt = 0.0f;

    // ��]�̑��x
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

