#pragma once
#include "../GameObject/GameObject.h"
#include"../Component/Com_SphereCollider.h"

class OBJ_Penguin :
    public GameObject
{
private:
    // 足元用コライダー
    GameObject* p_mFoot = nullptr;
    // コライダーコンポーネント
    Com_SphereCollider* p_mCollider = nullptr;

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

};

