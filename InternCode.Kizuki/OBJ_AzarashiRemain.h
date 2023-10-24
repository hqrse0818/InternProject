#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Number.h"
#include "../InternCodeAdachi/OBJ_AzarashiManager.h"

#define LoadRow (1)

//アザラシの残機
class OBJ_AzarashiRemain :public OBJ_Number
{
private:
	GameObject* pIce{};
	GameObject* pCount{};
	GameObject* pRemain{};
	OBJ_Number* Nums[3]{};
	int iRemainNum = 0;
	bool bIceCalc = false;
	int iIceScore = 0;

	DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3(100.0f, 100.0f, 0.0f);
	DirectX::SimpleMath::Vector3 position_Hund = DirectX::SimpleMath::Vector3(100.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 position_Ten = DirectX::SimpleMath::Vector3(200.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 position_One = DirectX::SimpleMath::Vector3(300.0f, 0.0f, 0.0f);

	void CreateFromCSV(const char* _FileName);

public:
	OBJ_AzarashiRemain();
	OBJ_AzarashiRemain(const char* _name);
	OBJ_AzarashiRemain(const char* _ARemain, const char* _FileName);

	void Start();
	void Update();

	int GetIceScore()
	{
		return iIceScore;
	}

	void SetDisplay(bool _val)
	{
		pIce->SetActive(_val);
		pCount->SetActive(_val);
		pRemain->SetActive(_val);
		Nums[0]->SetActive(_val);
		Nums[1]->SetActive(_val);
		Nums[2]->SetActive(_val);
	}
};