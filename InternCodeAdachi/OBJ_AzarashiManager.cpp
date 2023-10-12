#include "OBJ_AzarashiManager.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_AzarashiManager::OBJ_AzarashiManager()
{
}

OBJ_AzarashiManager::OBJ_AzarashiManager(const char* _name)
{
	sObjectName = _name;
}

OBJ_AzarashiManager::OBJ_AzarashiManager(const char* _name, const char* _FileName)
{
	sObjectName = _name;
	
	string sGameTime = ReadDataFromCSV(_FileName, GameTimeRow);
	string sSpawnRate = ReadDataFromCSV(_FileName, SpawnRateRow);
	string sMaxSpawnNum = ReadDataFromCSV(_FileName, SpawnNumRow);
	string sAzarashiState = ReadDataFromCSV(_FileName, AzarashiStateRow);

	// 出現最大数を格納
	iMaxSpawn = stoi(sMaxSpawnNum);

	// 文字列を(,)で分割
	istringstream iss(sGameTime);
	string word;
	// ゲームタイム
	std::vector<string> gt;
	// スポーンレート
	std::vector<string> sr;
	// アザラシのステータス
	std::vector<string> as;
	while (getline(iss, word, ','))
	{
		gt.emplace_back(word);
	}
	iss = istringstream(sSpawnRate);
	while (getline(iss, word, ','))
	{
		sr.emplace_back(word);
	}
	iss = istringstream(sAzarashiState);
	while (getline(iss, word, ','))
	{
		as.emplace_back(word);
	}
	// サイズが一緒じゃなかったらエラー
	assert(sr.size() == gt.size());

	// スポーンレートとスポーンレート変更時間を格納
	for (unsigned int i = 0; i < gt.size(); i++)
	{
		vec_SpawnRateGameTimer.emplace_back(stoi(gt[i]));
		vec_SpawnRate.emplace_back(stof(sr[i]));
	}
	if (as.size() == StateSetNum)
	{
		// コライダーの中心の読み込み
		mAzarashiCenter.x = stof(as[0]);
		mAzarashiCenter.y = stof(as[1]);
		mAzarashiCenter.z = stof(as[2]);
		// コライダーの半径
		fAzarashiRadius = stof(as[3]);

		// 足の高さ
		fFootHeight = stof(as[4]);
		// スポーン後の待ち時間
		fAfterWait = stof(as[5]);
		// 攻撃間隔
		fAttackDuration = stof(as[6]);
		// 移動速度
		fMoveSpeed = stof(as[7]);
		// ふきとび係数
		fVelocity = stof(as[8]);
		// ブレーキ係数
		fBlake = stof(as[9]);
		// 被弾時の停止許容距離
		fLength = stof(as[10]);
	}
	



	gt.clear();
	sr.clear();
	as.clear();
}

void OBJ_AzarashiManager::Create()
{
	int Rand = HighRand::GetRand(0, 100);
	if (Rand > 50)
	{
		Rand = 1;
	}
	else
	{
		Rand = 2;
	}

	OBJ_Azarashi* azarashi = new OBJ_Azarashi("Created", Rand);
	azarashi->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
	azarashi->GetColliderCom()->fRadius = fAzarashiRadius;
	azarashi->GetFootCom()->SetFootHeight(fFootHeight);

}

void OBJ_AzarashiManager::Update()
{
	GameObject::Update();
	// ゲームタイムを進める
	fGameCnt += Time->GetDeltaTime();
	// 現在のゲームタイムが次のスポーン切り替えのタイム以上ならインデックスを進める
	if (iCurrentIndex < vec_SpawnRateGameTimer.size())
	{
		if(static_cast<int>(fGameCnt) > vec_SpawnRate[iCurrentIndex + 1])
		{
			iCurrentIndex++;
		}
	}
	

	switch (mState)
	{
	case SpawnState::Wait:
		fSpawnCnt += Time->GetDeltaTime();
		if (fSpawnCnt > vec_SpawnRate[iCurrentIndex])
		{
			fSpawnCnt = 0.0f;
			mState = SpawnState::Spawn;
		}
		break;
	case SpawnState::Spawn:
		Create();
		break;
	case SpawnState::End:
		break;
	default:
		break;
	}
}