#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../Component/Com_DiagonalProjection.h"
#include "../Component/Com_EffectBillboard.h"
#include "../DirectX/ShaderResourceView.h"

class OBJ_Particle :
    public GameObject
{
public:
    Com_DiagonalProjection* p_mTousyaBuf{};
    Com_EffectBillboard* p_mBil{};
    Com_Shader* p_mShadeer{};
    float fLifetime;
    float fDuration = 0.5f;
    float fCount = 0.0f;
public:
    OBJ_Particle();
    OBJ_Particle(const char* _name);
    void Init();
    void Update();
    void SetTexture(ID3D11ShaderResourceView* _pSRV)
    {
        p_mBil->SetSRV(_pSRV);
    }
    Com_EffectBillboard* GetBil()
    {
        return p_mBil;
    }

    void SetLifeTime(float _val)
    {
        fLifetime = _val;
    }

    void SetAnimDuration(float _val)
    {
        fDuration = _val;
    }
};

