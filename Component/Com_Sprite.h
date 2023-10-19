#pragma once
#include "Component.h"
#include "../Format.h"
#include "../DirectX/ShaderResourceView.h"
#include <d3d11.h>
class Com_Sprite :
    public Component
{
protected:
    ID3D11Buffer* p_mVertexBuffer{};
    ShaderResourceView* p_mSRV{};
    DirectX::SimpleMath::Vector2 mDivision = 
        DirectX::SimpleMath::Vector2(1.0f, 1.0f);
    DirectX::SimpleMath::Vector4 mUV =
        DirectX::SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    bool bUpdate = false;

    MATERIAL mMaterial{};

public:

    Com_Sprite();

    virtual void Init();
    virtual void Uninit();
    virtual void Update();
    virtual void Draw();

    // 頂点位置変更やアニメーションの有無
    void SetUpdate(bool _val)
    {
        bUpdate = _val;
    };

    void SetDivision(float _u, float _v);
    void SetUV(DirectX::SimpleMath::Vector4 _uv);
    void SetTexture(const char* _name);
    void SetTexture(ShaderResourceView* _psrv);
    void SetMaterial(MATERIAL mat);
    void SetAmbient(DirectX::SimpleMath::Color _color);
    void SetDiffuse(DirectX::SimpleMath::Color _color);
    void SetSpecular(DirectX::SimpleMath::Color _color);
    void SetEmission(DirectX::SimpleMath::Color _color);
    virtual void Create();


    MATERIAL GetMaterial()
    {
        return mMaterial;
    }
};

