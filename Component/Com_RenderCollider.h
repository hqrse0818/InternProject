#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#include "Component.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"

// �R���C�_�[���C���̕\���R���|�[�l���g
class Com_RenderCollider :
    public Component
{
protected:
    // ���_�o�b�t�@
    ID3D11Buffer* p_mVertexBuffer{};

    // �s�N�Z���V�F�[�_�[
    ID3D11PixelShader* p_mPixelShader{};

public:
    virtual void Uninit();
    virtual void Draw();
    void SetPixelShaderNoHit();
    void SetPixelShaderHit();
};

#endif // 

