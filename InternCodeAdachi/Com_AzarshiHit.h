#pragma once
#include "../Component/Component.h"
#include "../Utility.h"

// �A�U���V���m�̏Փ�
class Com_AzarshiHit :
    public Component
{
private:
    // ����鑬�x
    float fSpeed = 10.0f;
    DirectX::SimpleMath::Vector3 mMoveVal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

public:
    void Update();

    void OnCollisionStay(GameObject* _obj);

    void OnCollisionExit(GameObject* _obj);
};

