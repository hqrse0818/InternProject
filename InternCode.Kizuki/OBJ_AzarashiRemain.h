#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Number.h"
#include "../InternCodeAdachi/OBJ_AzarashiManager.h"

//アザラシの残機
class OBJ_AzarashiRemain :public OBJ_Number
{
private:
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
};