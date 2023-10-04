#pragma once
#include "../GameObject/GameObject.h"
#include"../Component/Com_SphereCollider.h"

class OBJ_Penguin :
    public GameObject
{
private:
    // �����p�R���C�_�[
    GameObject* p_mFoot = nullptr;
    // �R���C�_�[�R���|�[�l���g
    Com_SphereCollider* p_mCollider = nullptr;

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

};

