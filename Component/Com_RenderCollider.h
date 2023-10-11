#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#include "Component.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"
#include "../DirectX/Shader.h"

// �R���C�_�[���C���̕\���R���|�[�l���g
class Com_RenderCollider :
    public Component
{
protected:
    // ���_�o�b�t�@
    ID3D11Buffer* p_mVertexBuffer{};

    // �s�N�Z���V�F�[�_�[
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

