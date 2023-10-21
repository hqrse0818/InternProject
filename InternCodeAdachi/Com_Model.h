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

    // シェーダーでアニメーションの計算を行うための定数バッファ
    ID3D11Buffer* p_mCombBuffer{};
    // スケール用定数バッファ
    ID3D11Buffer* p_mScaleBuffer{};

    // 再生中のアニメーションの名前
    const char* p_cPlayAnimationName{};
    // 現在のアニメーションのフレーム
    int iFrame1 = 0;
    int iFrame2 = 0;
    // アニメーションするかどうか
    bool bPlayAnim = false;
    // マテリアルの使用
    bool bUseMaterial = false;
    // 現在のアニメーションのキーが最後の時trueにする
    bool bRotLastKey = false;
    bool bPosLastKey = false;

    DirectX::SimpleMath::Vector4 mScale{};

    // アニメーション再生補正値
    float fAnimSpeed = 0.001;
    float fAnimCnt = 0.0f;

    // 順再生かどうか
    bool bPlayOrder = true;

    int iAnimNumber = 0;
    bool bResetFrame = false;

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
    void SetPlayAnimation(bool _val);

    void UpdateFrame();

    void SetAnimSpeed(float _val)
    {
        fAnimSpeed = _val;
        if (_val < 0.0f)
        {
            bPlayOrder = false;
        }
        else
        {
            bPlayOrder = true;
        }
    }

    bool GetIsRotLastKey()
    {
        return bRotLastKey;
    }

    bool GetIsPosLastKey()
    {
        return bPosLastKey;
    }

    // アニメーションを特定の位置でセット
    void SetCurrentKeyFrame(int _val)
    {
        iFrame1 = _val;
    }

    void SetAnimNumber(int _num)
    {
        iAnimNumber = _num;
    }

    void SetResetKey(bool _val)
    {
        bResetFrame = _val;
    }
};

