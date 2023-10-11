#pragma once
#include "../Component/Component.h"

#include <string>

#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#include "assimp/Importer.hpp"

#include "../System/ModelData.h"

class Com_Model :
    public Component
{
private:
    MODEL_DATA* mModelData = nullptr;

    // �V�F�[�_�[�ŃA�j���[�V�����̌v�Z���s�����߂̒萔�o�b�t�@
    ID3D11Buffer* p_mCombBuffer{};
    // �X�P�[���p�萔�o�b�t�@
    ID3D11Buffer* p_mScaleBuffer{};

    // �Đ����̃A�j���[�V�����̖��O
    const char* p_cPlayAnimationName{};
    // ���݂̃A�j���[�V�����̃t���[��
    int iFrame1 = 0;
    int iFrame2 = 0;
    // �A�j���[�V�������邩�ǂ���
    bool bPlayAnim = false;
    // �}�e���A���̎g�p
    bool bUseMaterial = false;
    // ���݂̃A�j���[�V�����̃L�[���Ō�̎�true�ɂ���
    bool bRotLastKey = false;
    bool bPosLastKey = false;

    DirectX::SimpleMath::Vector4 mScale{};

private:
    void UpdateBoneMatrix(aiNode* _Node, aiMatrix4x4 _Matrix);

public:
    Com_Model();

    bool SetModelData(const char* _ModelName);

    void Update();
    void Draw();
    void Uninit();

    void SetUseMaterial(bool _b)
    {
        bUseMaterial = _b;
    }

    void SetScale(float _x, float _y, float _z)
    {
        mScale.x = _x;
        mScale.y = _y;
        mScale.z = _z;
        mScale.w = 1.0f;
    }

    void PlayAnimation(const char* _name);
    void StopAnimation();

    void UpdateFrame(int _val);

    bool GetIsRotLastKey()
    {
        return bRotLastKey;
    }

    bool GetIsPosLastKey()
    {
        return bPosLastKey;
    }

    // �A�j���[�V���������̈ʒu�ŃZ�b�g
    void SetCurrentKeyFrame(int _val)
    {
        iFrame1 = _val;
    }
};

