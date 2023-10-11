#pragma once

// ���f���f�[�^�ǂݍ��݃N���X
// Assimp���g�p

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib, "assimp-vc142-mtd.lib")
#else
#pragma comment(lib, "assimp-vc142-mt.lib")
#endif // DEBUG

#include <unordered_map>
#include <vector>

#include "../DirectX/renderer.h"

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#include "assimp/Importer.hpp"

struct DEFORM_VERTEX
{
    aiVector3D Position;
    aiVector3D Normal;
    int BoneNum;
    std::string BoneName[4];
    int BoneIndex[4];
    float BoneWeight[4];
};

struct BONE
{
    aiMatrix4x4 Matrix;
    aiMatrix4x4 AnimationMatrix;
    aiMatrix4x4 AniamtionMatrix1;
    aiMatrix4x4 AnimationMatrix2;
    aiMatrix4x4 OffsetMatrix;
    int mIndex;
};

struct BoneCompMatrix
{
    DirectX::SimpleMath::Matrix BoneCombMtx[400];   // �{�[���R���r�l�[�V�����s��
};

struct MODEL_DATA
{
    // Assimp�ǂݍ��ݗp
    const aiScene* p_mAiScene = nullptr;
    // �A�j���[�V�������X�g
    std::unordered_map<std::string, const aiScene*>map_mAnimation;
    // ���_�o�b�t�@
    ID3D11Buffer** pp_mVertexBuffer;
    // �C���f�b�N�X�o�b�t�@
    ID3D11Buffer** pp_mIndexBuffer;
    std::unordered_map<std::string, ID3D11ShaderResourceView*> map_mTexture;
    // �}�e���A���f�[�^
    std::vector<MATERIAL> vec_material;
    // �ό`��̒��_�f�[�^
    std::vector < DEFORM_VERTEX > * vec_mDeformVertex;
    // �{�[���f�[�^
    std::unordered_map<std::string, BONE> map_mBone;
};

class ModelData
{
private:
    MODEL_DATA* mModelData{};
    ID3D11ShaderResourceView* LoadDiffuseTexture(std::string _FileName, std::string _ModelFileName);
private:
    // �{�[�����ċA�I�ɍ쐬
    void CreateBone(aiNode* _node);

public:
    ModelData();

    // ���f���̓ǂݍ���
    void LoadModel(const char* _FileName, bool _bLoadMaterial);
    // �A�j���[�V�����̓ǂݍ���
    void LoadAnimation(const char* _FileName, const char* _AnimName);
    // ���f���f�[�^�����f���f�[�^�v�[���ɓo�^
    void Push(const char* _ModelName);
    // �J��
    void Uninit();
    MODEL_DATA* GetModelData()
    {
        return mModelData;
    }
};

