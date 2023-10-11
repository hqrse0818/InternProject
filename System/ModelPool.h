#pragma once
#include "ModelData.h"

#include <unordered_map>
#include <string>

// モデルデータ格納用クラス
// このデータにModelDataクラスで作成したモデルを格納しCom_Modelで使用する

class ModelPool
{
private:
	static ModelPool* p_mInstance;
	static std::unordered_map<std::string, ModelData*> p_mModelmap;
	ModelPool() {};

public:
	static ModelPool* GetInsatance();

	static MODEL_DATA* GetModelData(const char* _ModelName);

	static void Uninit();

	static void Push(const char* _Name, ModelData* _Data);
};

