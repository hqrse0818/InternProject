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

    // 頂点バッファが同じだとほかのアニメーションを同時再生できないので頂点バッファだけはメンバ変数に持っておく
    ID3D11Buffer** pp_mVertexBuffer;
    // シェーダーでアニメーションの計算を行うための定数バッファ
    ID3D11Buffer* p_mCombBuffer;
    // スケール用定数バッファ
    ID3D11Buffer* p_mScaleBuffer;

    // 再生中のアニメーションの名前
    const char* p_cPlayAnimationName;
    // 現在のアニメーションのフレーム
    int iFrame1;
    int iFrame2;
    // アニメーションするかどうか
    bool bPlayAnim = false;
    // マテリアルの使用
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

