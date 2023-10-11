#pragma once
#include "ModelData.h"

#include <unordered_map>
#include <string>

// ���f���f�[�^�i�[�p�N���X
// ���̃f�[�^��ModelData�N���X�ō쐬�������f�����i�[��Com_Model�Ŏg�p����

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

