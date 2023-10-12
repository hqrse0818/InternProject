#pragma once
#include "Component.h"
#include <string>

enum class ColliderKind
{
    ColTag_None, ColTag_Penguin, ColTag_Azarashi, ColTag_Ice, ColTag_Attack, ColTag_Sea,
};

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

    ColliderKind mColliderTag = ColliderKind::ColTag_None;

    bool GetHit()
    {
        return bHit;
    }
    bool SetHit(bool _b)
    {
        bHit = _b;
    }
};
