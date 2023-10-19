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
    // �ړ��̗L��
	bool bMovable = false;
    // �j��\
    bool bCanDestroy = false;
    // ����������s��Ȃ�
    bool bIsTrigger = false;
    // �o���
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
