#include "ModelPool.h"

ModelPool* ModelPool::p_mInstance = nullptr;
std::unordered_map<std::string, ModelData*> ModelPool::p_mModelmap{};

// 同時に書き込みを抑制するためクリティカルセクションを使用する
CRITICAL_SECTION myCrySec;

ModelPool* ModelPool::GetInsatance()
{
	if (!p_mInstance)
	{
		p_mInstance = new ModelPool();
		// クリティカルセクション生成
		InitializeCriticalSection(&myCrySec);
	}
	return p_mInstance;
}

MODEL_DATA* ModelPool::GetModelData(const char* _ModelName)
{
	if (p_mModelmap.count(_ModelName) > 0)
	{
		return p_mModelmap[_ModelName]->GetModelData();
	}

	return nullptr;
}

void ModelPool::Uninit()
{
	for (auto data : p_mModelmap)
	{
		data.second->Uninit();
		delete data.second;
	}
	p_mModelmap.clear();

	// クリティカルセクション開放
	DeleteCriticalSection(&myCrySec);

	delete p_mInstance;
}

void ModelPool::Push(const char* _Name, ModelData* _Data)
{
	EnterCriticalSection(&myCrySec);
	if (p_mModelmap.count(_Name) > 0)
	{
		LeaveCriticalSection(&myCrySec);
		return;
	}
	p_mModelmap[_Name] = _Data;
	LeaveCriticalSection(&myCrySec);
}
