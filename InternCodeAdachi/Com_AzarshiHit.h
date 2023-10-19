#pragma once
#include "../Component/Component.h"
#include "../Utility.h"

// アザラシ同士の衝突
class Com_AzarshiHit :
    public Component
{
private:
    // 離れる速度
    float fSpeed = 10.0f;
    DirectX::SimpleMath::Vector3 mMoveVal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

public:
    void Update();

    void OnCollisionStay(GameObject* _obj);

    void OnCollisionExit(GameObject* _obj);
};

