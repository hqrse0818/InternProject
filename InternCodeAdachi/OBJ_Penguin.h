#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Shader.h"
#include "../InternCode.Kizuki/Com_CharacterMove.h"
#include "Com_Jump.h"
#include "Com_AngleCamera.h"
#include "Com_Gravity.h"
#include "Com_Foot.h"
#include "Com_Model.h"

// �y���M���̃v���t�@�u

class OBJ_Penguin :
    public GameObject
{
private:
    // ���f���`��R���|�[�l���g
    Com_Model* p_mModel = nullptr;
    // �V�F�[�_�[�R���|�[�l���g
    Com_Shader* p_mShader = nullptr;
    // �ړ��R���|�[�l���g
    Com_CharacterMove* p_mMoveCom = nullptr;
    // �W�����v�R���|�[�l���g
    Com_Jump* p_mJumpCom = nullptr;
    // �^�[�Q�b�g�ɂ���Ă�J�����R���|�[�l���g
    Com_AngleCamera* p_mCameraCom = nullptr;
    // �d�̓R���|�[�l���g
    Com_Gravity* p_mGravityCom = nullptr;
    // �����R���|�[�l���g
    Com_Foot* p_mFootCom = nullptr;

    // �󒆂ł̈ړ�����(�X�e�B�b�N���͂łǂꂾ���̊�����K�p���邩)
    float fAirMoveSpeed = 1.0f;

    // �J�����̃X�s�[�h
    float fCamSpeed = 1.0f;

private:
    void CreateFromCSV(const char* _FileName);

public:
    OBJ_Penguin();
    OBJ_Penguin(const char* _name);
    OBJ_Penguin(const char* _name, const char* _FileName);

    void Start()override;
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

