#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Sprite.h"

class OBJ_Warning :
    public GameObject
{
private:
    GameObject* pBack{};
    GameObject* pFont{};
    Com_Sprite* pFontSp{};
    GameObject* pMark{};
    Com_Sprite* pMarkSp{};
    DirectX::SimpleMath::Color mColor = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

public:
    OBJ_Warning();
    OBJ_Warning(const char* _name);
    OBJ_Warning(const char* _name, const char* _FileName);
};

