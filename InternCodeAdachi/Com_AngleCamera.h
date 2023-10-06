#pragma once
#include "../Component/Com_Camera.h"
class Com_AngleCamera :
    public Com_Camera
{
private:
    float fCurrentAngle = 0.0f;
    float fDistance = 10.0f;
    float fHeight = 5.0f;

public:
    float GetAngle()
    {
        return fCurrentAngle;
    }
    void SetAngle(float _val)
    {
        fCurrentAngle = _val;
    }
    void SetDistance(float _val)
    {
        fDistance = _val;
    }

    float GetHeight()
    {
        return fHeight;
    }

    void SetHeight(float _val)
    {
        fHeight = _val;
        if (fHeight > 45)
        {
            fHeight = 45;
        }
        else if (fHeight < 5)
        {
            fHeight = 5;
        }
    }

    void Update();
};

