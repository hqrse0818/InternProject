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

    bool bUpdate = false;

    MATERIAL mMaterial{};

    int iSeparateX = 1;
    int iSeparateY = 1;

    float fCurrentx = 0;
    float fCurrenty = 0;
    float fCurrentz = 1;
    float fCurrentw = 1;

    int iCurrent = 1;

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

    void SetSeparateNum(int _u, int _v);
    void SetCurrent(int _val);

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

