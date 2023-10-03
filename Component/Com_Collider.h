#pragma once
#include "Component.h"

class Com_Collider : public Component
{
protected:
	bool bHit = false;
public :
    // 移動の有無
	bool bMovable = false;
    // 破壊可能
    bool bCanDestroy = false;
    // 物理判定を行わない
    bool bIsTrigger = false;
    // 登れる
    bool bCanStepOn = false;

    bool GetHit()
    {
        return bHit;
    }
    bool SetHit(bool _b)
    {
        bHit = _b;
    }
};
