#pragma once

// モデルデータ読み込みクラス
// Assimpを使用

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
    DirectX::SimpleMath::Matrix BoneCombMtx[400];   // ボーンコンビネーション行列
};

struct MODEL_DATA
{
    // Assimp読み込み用
    const aiScene* p_mAiScene = nullptr;
    // アニメーションリスト
    std::unordered_map<std::string, const aiScene*>map_mAnimation;
    // 頂点バッファ
    ID3D11Buffer** pp_mVertexBuffer;
    // インデックスバッファ
    ID3D11Buffer** pp_mIndexBuffer;
    std::unordered_map<std::string, ID3D11ShaderResourceView*> map_mTexture;
    // マテリアルデータ
    std::vector<MATERIAL> vec_material;
    // 変形後の頂点データ
    std::vector < DEFORM_VERTEX > * vec_mDeformVertex;
    // ボーンデータ
    std::unordered_map<std::string, BONE> map_mBone;
};

class ModelData
{
private:
    MODEL_DATA* mModelData{};
    ID3D11ShaderResourceView* LoadDiffuseTexture(std::string _FileName, std::string _ModelFileName);
private:
    // ボーンを再帰的に作成
    void CreateBone(aiNode* _node);

public:
    ModelData();

    // モデルの読み込み
    void LoadModel(const char* _FileName, bool _bLoadMaterial);
    // アニメーションの読み込み
    void LoadAnimation(const char* _FileName, const char* _AnimName);
    // モデルデータをモデルデータプールに登録
    void Push(const char* _ModelName);
    // 開放
    void Uninit();
    MODEL_DATA* GetModelData()
    {
        return mModelData;
    }
};

