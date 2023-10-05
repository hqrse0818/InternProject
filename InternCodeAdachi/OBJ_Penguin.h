#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_AssimpAnimation.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_TestJump.h"
#include "Com_AngleCamera.h"

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
    // �^�[�Q�b�g�ɂ���Ă�J�����R���|�[�l���g
    Com_AngleCamera* p_mCameraCom = nullptr;
public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);

    void Update();

    Com_CharacterMove* GetMoveCom()
    {
        return p_mMoveCom;
    }

    void SetCameraCom(Com_AngleCamera* _com)
    {
        p_mCameraCom = _com;
    }

};

