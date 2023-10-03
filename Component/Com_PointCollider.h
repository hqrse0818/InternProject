#pragma once
#include "Com_Collider.h"
#include "../Format.h"
// ポイントコライダー
class Com_PointCollider :
    public Com_Collider
{
protected:
    POINT3D mPoint;

public:
    DirectX::SimpleMath::Vector3 mCenter = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);

public:
    void Init();
    void Update();
    void SetCenter(float _x, float _y, float _z)
    {
        mCenter.x = _x;
        mCenter.y = _y;
        mCenter.z = _z;
    }
    const POINT3D GetPoint()
    {
        return mPoint;
    }
};

