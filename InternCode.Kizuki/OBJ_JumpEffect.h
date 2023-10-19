#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../Component/Com_DiagonalProjection.h"
#include "../Component/Com_Billboard.h"
#include "../DirectX/ShaderResourceView.h"

class OBJ_JumpEffect :public GameObject
{
private:
    Com_DiagonalProjection* p_mTousyaBuf{};
    Com_Billboard* p_mBil{};
    float fLifetime;

public:
    OBJ_JumpEffect();
    OBJ_JumpEffect(const char* _name);
    void Init();
    void Update();
    void SetTexture(ID3D11ShaderResourceView* _pSRV)
    {
        p_mBil->SetSRV(_pSRV);
    }
};