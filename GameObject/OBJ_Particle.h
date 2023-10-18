#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../Component/Com_DiagonalProjection.h"
#include "../Component/Com_Billboard.h"
#include "../DirectX/ShaderResourceView.h"

class OBJ_Particle :
    public GameObject
{
public:
    Com_DiagonalProjection* p_mTousyaBuf{};
    Com_Billboard* p_mBil{};
    float fLifetime;
public:
    OBJ_Particle();
    OBJ_Particle(const char* _name);
    void Init();
    void Update();
    void SetTexture(ID3D11ShaderResourceView* _pSRV)
    {
        p_mBil->SetSRV(_pSRV);
    }
};

