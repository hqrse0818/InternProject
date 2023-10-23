#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../Component/Com_Sprite.h"

class OBJ_ResultPenguin :
    public GameObject
{
private:
    Com_Shader* p_mShader{};
    Com_Sprite* p_mMainSprite{};

   ShaderResourceView* p_mSprites[210];

   float fRate = 0.0125f;
   float fCnt = 0.0f;

   int Current = 0;

   bool bUpdate = false;

public:
    OBJ_ResultPenguin();
    OBJ_ResultPenguin(const char* _name);

    void Update();

    void Uninit();

    void SetUpdate(bool _val)
    {
        bUpdate = _val;
    }
};

