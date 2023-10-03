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

    static void LoadModel(const char* _FileName, MODEL* _Model);
    static void LoadObj(const char* _FileName, MODEL_OBJ* _ModelObj);
    static void LoadMaterial(const char* _FileName, MODEL_MATERIAL** _MaterialName, unsigned int* MaterialNum);
    MODEL* p_mModel{};

public:
    static void PreLoad(const char* _FileName);
    // モデル全消去
    static void UnloadAll();

    void Load(const char* _FileName);

    virtual void Draw() override;

    static MODEL* GetModelData(const char* _FileName);
};

