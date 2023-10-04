#pragma once
#include "Component.h"
#include "../Format.h"
#include <iostream>
#include <unordered_map>
class Com_ModelRenderer :
    public Component
{
protected:
    // モデルマップ
    static std::unordered_map<std::string, MODEL*> map_mModelPool;

    static void LoadModel(const char* _FileName, MODEL* _Model, float _LoadScale);
    static void LoadObj(const char* _FileName, MODEL_OBJ* _ModelObj, float _LoadScale);
    static void LoadMaterial(const char* _FileName, MODEL_MATERIAL** _MaterialName, unsigned int* MaterialNum);
    MODEL* p_mModel{};

public:
    static void PreLoad(const char* _FileName, float _LoadScale);
    // モデル全消去
    static void UnloadAll();

    void Load(const char* _FileName, float _LoadScale);
    void Load(const char* _FileName);

    virtual void Draw() override;
    static void Draw(MODEL* _model);

    static MODEL* GetModelData(const char* _FileName);

    static void ScaleModelData(MODEL* _model);
    void ScaleModelData();
};

