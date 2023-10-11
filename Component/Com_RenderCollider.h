#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#include "Component.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"
#include "../DirectX/Shader.h"

// コライダーラインの表示コンポーネント
class Com_RenderCollider :
    public Component
{
protected:
    // 頂点バッファ
    ID3D11Buffer* p_mVertexBuffer{};

    // ピクセルシェーダー
    PixelShader* p_mPS{};
    VertexShader* p_mVS{};

public:
    Com_RenderCollider();

    virtual void Uninit();
    virtual void Draw();
    void SetPixelShaderNoHit();
    void SetPixelShaderHit();
};

#endif // 

