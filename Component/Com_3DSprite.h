#pragma once
#include "Component.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "../Format.h"
#include "../DirectX/ShaderResourceView.h"

// 3Dのスプライト

class Com_3DSprite :
    public Component
{
protected:
    ID3D11Buffer*               p_mVertexBuffer{};
    ShaderResourceView*   p_mSRV{};
    MATERIAL                    p_mMaterial{};

public:

    Com_3DSprite();
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    virtual void SetTexture(const char* _name);
    virtual void SetMaterial(MATERIAL mat);
};

