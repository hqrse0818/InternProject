#pragma once
#include "Com_RenderCollider.h"

class Com_RenderCollisionLine_Box :
    public Com_RenderCollider
{
private:
    // ���[�J��
    DirectX::SimpleMath::Vector3 mRenderVertex[RenderBoxVertexNum];
public:
    DirectX::SimpleMath::Vector3 mSize;
    DirectX::SimpleMath::Vector3 mCenter;
    DirectX::SimpleMath::Vector3 mScale;

    void Init()override;
    void Update()override;
    void Draw()override;
};

class Com_RenderCollisionLine_Box2D :
    public Component
{
private:
    DirectX::SimpleMath::Vector2 mRenderVertex[8];

    // ���_�o�b�t�@
    ID3D11Buffer* mVertexBuffer{};

public:
    DirectX::SimpleMath::Vector2 mSize;
    DirectX::SimpleMath::Vector2 mCenter;
    DirectX::SimpleMath::Vector2 mScale;

    void Init()override;
    void Update()override;
    void Uninit()override;
    void Draw()override;
};