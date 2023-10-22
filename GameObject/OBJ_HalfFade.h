#pragma once
#include "OBJ_Transition.h"
class OBJ_HalfFade :
    public OBJ_Transition
{
private:
    float fAlpha = 0.5f;

public:
    OBJ_HalfFade();
    OBJ_HalfFade(const char* _name);

    void Update();
    void SetAlpha(float _val)
    {
        fAlpha = _val;
    }
};

