#pragma once
#include "../Component/Component.h"
#include "../../Utility.h"

// �Ε�����
// �e���΂����艽���𓊂����肷��̂Ɏg����

class Com_DiagonalProjection :
    public Component
{
private:
    DirectX::SimpleMath::Vector3 InitSpeed;
    DirectX::SimpleMath::Vector3 CurrentSpeed;
    DirectX::SimpleMath::Vector3 ThrowAngle = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    bool bGravityReturn = false;
    float Cnt;
    float fGravity = 4.0f;
public:
    void SetInitSpeed(DirectX::SimpleMath::Vector3 _val)
    {
        InitSpeed = _val;
    }
    void SetCnt(float _val)
    {
        Cnt = 0;
    }
    void SetThrowAngle(DirectX::SimpleMath::Vector3 _val)
    {
        ThrowAngle = _val;
    }
    DirectX::SimpleMath::Vector3 GetInitSpeed()
    {
        return InitSpeed;
    }
    float GetCount()
    {
        return Cnt;
    }
    DirectX::SimpleMath::Vector3 GetAngle()
    {
        return ThrowAngle;
    }
    void SetReturn(bool _val)
    {
        bGravityReturn = _val;
    }
    bool GetReturn()
    {
        return bGravityReturn;
    }
    DirectX::SimpleMath::Vector3 GetCurrentSpeed()
    {
        return CurrentSpeed;
    }
    void SetGravity(float _val)
    {
        fGravity = _val;
    }

    void Update()override;
};

