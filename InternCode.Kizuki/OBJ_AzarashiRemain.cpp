#include "OBJ_AzarashiRemain.h"
#include "../Scene/Scene.h"
#include "../Component/Com_CustomSprite.h"
#include "../Component/Com_Shader.h"
#include "../InternCodeAdachi/OBJ_Ice.h"

OBJ_AzarashiRemain::OBJ_AzarashiRemain()
{
	
}

void OBJ_AzarashiRemain::Start()
{
	Nums[0] = new OBJ_Number();
	Nums[1] = new OBJ_Number();
	Nums[2] = new OBJ_Number();

	GetScene()->AddGameObject(Nums[0]);
	GetScene()->AddGameObject(Nums[1]);
	GetScene()->AddGameObject(Nums[2]);
	
	Nums[0]->SetPosition(100.0f, 0.0f, 0.0f);
	Nums[1]->SetPosition(200.0f, 0.0f, 0.0f);
	Nums[2]->SetPosition(300.0f, 0.0f, 0.0f);

	Nums[0]->SetScale(100.0f, 100.0f, 0.0f);
	Nums[1]->SetScale(100.0f, 100.0f, 0.0f);
	Nums[2]->SetScale(100.0f, 100.0f, 0.0f);
}

void OBJ_AzarashiRemain::Update()
{
	iRemainNum = OBJ_AzarashiManager::GetMaxSpawn() - OBJ_AzarashiManager::GetSpawnedNum(); //残りのアザラシを計算
	
	if (iRemainNum < 100) //100未満
	{
		Nums[0]->SetActive(false); //百の位を消す

		//桁を左に詰める
		Nums[1]->SetPosition(100.0f, 0.0f, 0.0f); 
		Nums[2]->SetPosition(200.0f, 0.0f, 0.0f);
	}
	else
	{
		Nums[0]->SetNum(iRemainNum / 100);
	}

	if (iRemainNum < 10)
	{
		Nums[1]->SetActive(false); //十の位を消す

		//桁を左に詰める
		Nums[2]->SetPosition(100.0f, 0.0f, 0.0f);
	}
	else
	{
		iRemainNum = abs(iRemainNum % 100);
		Nums[1]->SetNum(iRemainNum / 10);
	}

	iRemainNum = abs(iRemainNum % 10);
	Nums[2]->SetNum(iRemainNum);

	OBJ_Number::Update();

	

	//アザラシの残機が0以下
	if (iRemainNum <= 0)
	{
		//アザラシの全体数を取得
		std::vector<OBJ_Azarashi*> azarashiRemain = GetScene()->GetGameObjects<OBJ_Azarashi>();

		if (azarashiRemain.size() <= 0)
		{
			std::vector<OBJ_Ice*> iceRemain = GetScene()->GetGameObjects<OBJ_Ice>();

			//足場のスコア計算
			if (!bIceCalc)
			{
				iIceScore = iceRemain.size() * 500;
				bIceCalc = true;
			}
		}
	}
}
