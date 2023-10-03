#pragma once
#include "Component.h"

class Com_Collider : public Component
{
protected:
	bool bHit = false;
public :
    // �ړ��̗L��
	bool bMovable = false;
    // �j��\
    bool bCanDestroy = false;
    // ����������s��Ȃ�
    bool bIsTrigger = false;
    // �o���
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
