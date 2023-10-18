#pragma once
#include "GameObject.h"
#include "../DirectX/ShaderResourceView.h"

// エミッターオブジェクト
class OBJ_Emitter :
    public GameObject
{
public:
    enum Kind
    {
        Particle,
    };

public:
    Kind mKind = Kind::Particle;
    int iCreateNum;
    
public:
    OBJ_Emitter();
    OBJ_Emitter(std::string _name);
    void Init();
    void Update();
    void TexCreate(const char* _name);

protected:
    ShaderResourceView* p_mTexture;
    bool bCreate = false;

protected:
    void Create();
};

