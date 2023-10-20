#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_3DSprite.h"

class OBJ_SeaSprite :
    public GameObject
{
private:
    Com_Shader* p_mShader = nullptr;
    Com_3DSprite* p_mSprite = nullptr;

public:
    OBJ_SeaSprite();
    OBJ_SeaSprite(const char* _name);

    Com_3DSprite* GetSpriteCom()
    {
        return p_mSprite;
    }
};

