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

    // ���_�o�b�t�@���������Ƃق��̃A�j���[�V�����𓯎��Đ��ł��Ȃ��̂Œ��_�o�b�t�@�����̓����o�ϐ��Ɏ����Ă���
    ID3D11Buffer** pp_mVertexBuffer;
    // �V�F�[�_�[�ŃA�j���[�V�����̌v�Z���s�����߂̒萔�o�b�t�@
    ID3D11Buffer* p_mCombBuffer;
    // �X�P�[���p�萔�o�b�t�@
    ID3D11Buffer* p_mScaleBuffer;

    // �Đ����̃A�j���[�V�����̖��O
    const char* p_cPlayAnimationName;
    // ���݂̃A�j���[�V�����̃t���[��
    int iFrame1;
    int iFrame2;
    // �A�j���[�V�������邩�ǂ���
    bool bPlayAnim = false;
    // �}�e���A���̎g�p
    bool bUseMaterial = false;

    DirectX::SimpleMath::Vector4 mScale;

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

    void UpdateFrame();
};

