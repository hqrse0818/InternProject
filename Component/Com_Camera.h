#pragma once
#include "Component.h"
#include "../Utility.h"


class Com_Camera :
    public Component
{
protected:
    // ターゲット
    GameObject* p_mTarget{};
    // 
    DirectX::SimpleMath::Vector3 mUp = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
    // ビュー変換行列
    DirectX::SimpleMath::Matrix mViewMatrix{};

    // 最終的な注視点
    DirectX::SimpleMath::Vector3 mTargetPosition = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
    // 注視点の調整
    DirectX::SimpleMath::Vector3 mTargetCorrect = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

    // オブジェクトをターゲットにする
    bool bUseTargetObject = true;
    float fFov = 45.0f;
    float fNear = 1.0f;
    float fFar = 1000.0f;



public:
    void SetTarget(GameObject* _targetpos);
    void SetTargetPosition(DirectX::SimpleMath::Vector3 _pos)
    {
        mTargetPosition = _pos;
    }
    void SetUseTarget(bool _val)
    {
        bUseTargetObject = _val;
    }
    void SetCorrect(DirectX::SimpleMath::Vector3 _val)
    {
        mTargetCorrect = _val;
    }

    void SetUp(DirectX::SimpleMath::Vector3 _Up)
    {
        mUp = _Up;
    }
    void SetFov(float _fov)
    {
        fFov = _fov;
    }
    void SetNear(float _near)
    {
        fNear = _near;
    }
    void SetFar(float _far)
    {
        fFar = _far;
    }

    const DirectX::SimpleMath::Matrix GetViewMatrix()
    {
        return mViewMatrix;
    }

    void Init();
    virtual void Update();
    virtual void Draw();
};

