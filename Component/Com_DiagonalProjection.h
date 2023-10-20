#pragma once
#include "../Component/Component.h"
#include "../../Utility.h"

// ŽÎ•û“ŠŽË
// ’e‚ð”ò‚Î‚µ‚½‚è‰½‚©‚ð“Š‚°‚½‚è‚·‚é‚Ì‚ÉŽg‚¦‚é

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

