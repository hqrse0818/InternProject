#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_TestJump.h"

// �y���M���̃v���t�@�u

class OBJ_Penguin :
    public GameObject
{
private:
    // ���f���`��R���|�[�l���g
    Com_AssimpAnimation* p_mModel = nullptr;
    // �V�F�[�_�[�R���|�[�l���g
    Com_Shader* p_mShader = nullptr;
    // �ړ��R���|�[�l���g
    Com_CharacterMove* p_mMoveCom = nullptr;
    // �W�����v�R���|�[�l���g
    Com_TestJump* p_mJumpCom = nullptr;
public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

};

