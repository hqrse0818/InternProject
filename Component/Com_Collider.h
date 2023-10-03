#pragma once
#include "Component.h"

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

    bool GetHit()
    {
        return bHit;
    }
    bool SetHit(bool _b)
    {
        bHit = _b;
    }
};
