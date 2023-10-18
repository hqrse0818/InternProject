#include "OBJ_AzarashiRemain.h"
#include "../Scene/Scene.h"
#include "../Component/Com_CustomSprite.h"
#include "../Component/Com_Shader.h"
#include "../InternCodeAdachi/OBJ_Ice.h"
#include "../InternCodeAdachi/CSVLoad.h"

#define LoadRow (1)

using namespace DirectX::SimpleMath;
using namespace std;

void OBJ_AzarashiRemain::CreateFromCSV(const char* _FileName)
{
	string Line = ReadDataFromCSV(_FileName, LoadRow);

	// 文字列を(,)で分割
	istringstream iss(Line);
	string word;
	std::vector<string> sv;
	while (getline(iss, word, ','))
	{
		sv.emplace_back(word);
	}

	Nums[0]->SetScale(stof(sv[0]), stof(sv[1]), stof(sv[2]));
	Nums[1]->SetScale(stof(sv[0]), stof(sv[1]), stof(sv[2]));
	Nums[2]->SetScale(stof(sv[0]), stof(sv[1]), stof(sv[2]));
	Nums[0]->SetPosition(stof(sv[3]), stof(sv[4]), stof(sv[5]));
	Nums[1]->SetPosition(stof(sv[6]), stof(sv[7]), stof(sv[8]));
	Nums[2]->SetPosition(stof(sv[9]), stof(sv[10]), stof(sv[11]));
}

OBJ_AzarashiRemain::OBJ_AzarashiRemain()
{
	Nums[0] = new OBJ_Number();
	Nums[1] = new OBJ_Number();
	Nums[2] = new OBJ_Number();
}

OBJ_AzarashiRemain::OBJ_AzarashiRemain(const char* _name)
	:OBJ_AzarashiRemain()
{
	sObjectName = _name;
}

OBJ_AzarashiRemain::OBJ_AzarashiRemain(const char* _ARemain, const char* _FileName)
	:OBJ_AzarashiRemain()
{
	sObjectName = _ARemain;
	CreateFromCSV(_FileName);
}

void OBJ_AzarashiRemain::Start()
{
	GetScene()->AddGameObject(Nums[0]);
	GetScene()->AddGameObject(Nums[1]);
	GetScene()->AddGameObject(Nums[2]);
	
	//Nums[0]->SetPosition(100.0f, 0.0f, 0.0f);
	//Nums[1]->SetPosition(200.0f, 0.0f, 0.0f);
	//Nums[2]->SetPosition(300.0f, 0.0f, 0.0f);

	//Nums[0]->SetScale(100.0f, 100.0f, 0.0f);
	//Nums[1]->SetScale(100.0f, 100.0f, 0.0f);
	//Nums[2]->SetScale(100.0f, 100.0f, 0.0f);
}

void OBJ_AzarashiRemain::Update()
{
	iRemainNum = OBJ_AzarashiManager::GetMaxSpawn() - OBJ_AzarashiManager::GetSpawnedNum(); //残りのアザラシを計算
	
	
	Nums[0]->SetNum(iRemainNum / 100);	
	iRemainNum = abs(iRemainNum % 100);
	Nums[1]->SetNum(iRemainNum / 10);
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
