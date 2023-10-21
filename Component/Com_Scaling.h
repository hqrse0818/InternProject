#pragma once
#include "Component.h"
#include "../Utility.h"

class Com_Scaling :
    public Component
{
private:
    DirectX::SimpleMath::Vector3 mInitScale = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    float fIncVal = 1.0f;
    float fDecVal = -1.0f;

    float fTime = 1.0f;
    float fCnt = 0.0f;

    bool bUseZ = false;
    bool bReturn = false;
    bool bScale = false;

public:
    void Init();
    void Update();

    void SetSpeed(float _inc, float _dec)
    {
        fIncVal = _inc;
        fDecVal = _dec;
    }

    void SetTime(float _val)
    {
        fTime = _val;
    }
    
    void SetUseZ(bool _val)
    {
        bUseZ = _val;
    }

    void SetUpdate(bool _val)
    {
        bScale = _val;
    }
};

