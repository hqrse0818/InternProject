#pragma once
#include "Component.h"
#include <string>

enum class ColliderKind
{
    ColTag_None, ColTag_Penguin, ColTag_Azarashi, ColTag_Ice, ColTag_Attack, ColTag_Sea,ColTag_Fall
};

class Com_Collider : public Component
{
protected:
	bool bHit = false;
public :
    // ˆÚ“®‚Ì—L–³
	bool bMovable = false;
    // ”j‰ó‰Â”\
    bool bCanDestroy = false;
    // •¨—”»’è‚ğs‚í‚È‚¢
    bool bIsTrigger = false;
    // “o‚ê‚é
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
