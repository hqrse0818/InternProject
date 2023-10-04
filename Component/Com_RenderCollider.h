#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#include "Component.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"

// コライダーラインの表示コンポーネント
class Com_RenderCollider :
    public Component
{
protected:
    // 頂点バッファ
    ID3D11Buffer* p_mVertexBuffer{};

    // ピクセルシェーダー
    ID3D11PixelShader* p_mPixelShader{};

public:
    virtual void Uninit();
    virtual void Draw();
    void SetPixelShaderNoHit();
    void SetPixelShaderHit();
};

#endif // 

