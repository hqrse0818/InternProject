#pragma once
#include "../Component/Com_Camera.h"
class Com_AngleCamera :
    public Com_Camera
{
private:
    float fCurrentAngle = 0.0f;
    float fDistance = 10.0f;
    float fHeight = 5.0f;
    bool bFollow = true;

    float fCamUpSpeed = 15.0f;
    float fMaxHeight =50.0f;
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
        if (bFollow)
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
    }

    void SetCamUpSpeed(float _val)
    {
        fCamUpSpeed = _val;
    }

    void SetMaxHeight(float _val)
    {
        fMaxHeight = _val;
    }

    void SetFollow(bool _val)
    {
        bFollow = _val;
    }

    void Update();
};

