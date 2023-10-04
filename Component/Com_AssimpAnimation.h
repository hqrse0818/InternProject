#pragma once
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment (lib, "assimp-vc142-mtd.lib")
#else
#pragma comment(lib, "assimp-vc142-mt.lib")
#endif // DEBUG




#include "Component.h"
#include "../DirectX/renderer.h"

#include <unordered_map>

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
    float BoneWeight[4];
};

struct BONE
{
    aiMatrix4x4 Matrix;
    aiMatrix4x4 AnimationMatrix;
    aiMatrix4x4 AniamtionMatrix1;
    aiMatrix4x4 AnimationMatrix2;
    aiMatrix4x4 OffsetMatrix;
};

struct aiSubset
{
    unsigned int	IndexNum = 0;					// インデックス数
    unsigned int	VertexNum = 0;					// 頂点数
    unsigned int	IndexBase = 0;					// 開始インデックス
    unsigned int	VertexBase = 0;					// 頂点ベース
    unsigned int	MaterialIdx = 0;				// マテリアルインデックス
};

class Com_AssimpAnimation :
    public Component
{
private:
    const aiScene* p_mAiScene = nullptr;
    std::unordered_map<std::string, const aiScene*>map_mAnimation;

    ID3D11Buffer** pp_mVertexBuffer;
    ID3D11Buffer** pp_mIndexBuffer;

    std::unordered_map<std::string, ID3D11ShaderResourceView*> map_mTexture;
    // マテリアルデータ
    std::vector<MATERIAL> vec_material;
    // サブセットデータ
    std::vector<aiSubset> vec_subsets;

    // 変形後の頂点データ
    std::vector<DEFORM_VERTEX>* vec_mDeformVertex;
    // ボーンデータ
    std::unordered_map<std::string, BONE> map_mBone;

    const char* p_cPlayAnimationName;

    int iFrame1;
    int iFrame2;

    bool bUseMaterial = false;

    bool bPlayAnim = false;

private:
    void CreateBone(aiNode* _Node);
    void UpdateBoneMatrix(aiNode* _Node, aiMatrix4x4 _Matrix);

    void TransWorldToLocal(aiNode* _node, aiMatrix4x4& parentTransform);
    ID3D11ShaderResourceView* LoadDiffuseTexture(std::string filename, std::string m_filename);

public:
    void LoadModel(const char* _FileName, float _LoadScale, bool _bLosdMaterial);
    void LoadAnimation(const char* _FileName, const char* _Name);
    void Uninit();
    void Update();
    void Draw();
    void UpdateFrame();
    // アニメーションカウントのリセット
    void ResetAnimationFrame();
    // 引数で再生するアニメーションを指定
    void PlayAnimation(const char* _AnimName);
    // アニメーションを停止する
    void StopAnimation();
    // 全てのテクスチャを一律に書き換える
    void SetTexture(const char* _FileName);
};

