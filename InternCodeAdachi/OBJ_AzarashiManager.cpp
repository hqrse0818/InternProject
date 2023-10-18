#include "OBJ_AzarashiManager.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../System/HighGetRand.h"
#include "../Scene/Scene.h"
#include "OBJ_Ice.h"

using namespace DirectX::SimpleMath;
using namespace std;

int OBJ_AzarashiManager::iMaxSpawn = 0;
int OBJ_AzarashiManager::iSpawnedNum = 0;

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
	string sSpawnRateNum = ReadDataFromCSV(_FileName, RateNumRow);
	string sGameTime = ReadDataFromCSV(_FileName, GameTimeRow);
	string sSpawnRate = ReadDataFromCSV(_FileName, SpawnRateRow);
	string sMaxSpawnNum = ReadDataFromCSV(_FileName, SpawnNumRow);
	string sAzarashiState = ReadDataFromCSV(_FileName, AzarashiStateRow);

	// 出現最大数を格納
	iMaxSpawn = stoi(sMaxSpawnNum);

	// 文字列を(,)で分割
	istringstream num(sSpawnRateNum);
	string wo;
	vector<string>nu;
	while (getline(num,wo , ','))
	{
		nu.emplace_back(wo);
	}
	unsigned int SpawnRateNumnum = stoi(nu[0]);
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
	for (unsigned int i = 0; i < SpawnRateNumnum; i++)
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
		// スポーン時のy座標
		fSpawnY = stof(as[11]);
		// 中間地点のy座標
		fCenterY = stof(as[12]);
		// 氷上での高さ
		fIceY = stof(as[13]);
		// 吹き飛ばしの基底距離
		fDamageDistance = stof(as[14]);

	}
	gt.clear();
	sr.clear();
	as.clear();
}

void OBJ_AzarashiManager::Create()
{
	// ターゲット位置設定
	std::vector<OBJ_Ice*> vec = GetScene()->GetGameObjects<OBJ_Ice>();
	if (vec.size() == 0)
		return;

	// リーダーを作成
	OBJ_Azarashi* LAzarashi = new OBJ_Azarashi("Leader", 2);
	// アザラシのステータス設定
	LAzarashi->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
	LAzarashi->GetColliderCom()->fRadius = fAzarashiRadius;
	LAzarashi->GetFootCom()->SetFootHeight(fFootHeight);
	LAzarashi->SetAzrashiStatus(fAfterWait, fAttackDuration, fMoveSpeed, fVelocity, fBlake, fLength, fDamageDistance);
	LAzarashi->bLeader = true;
	// スポーンエリアを大まかに指定
	int Rand = HighRand::GetRand(1, 4);
	Vector3 init;
	init.y = fSpawnY;
	// 初期スポーン地点設定
	switch (Rand)
	{
	case 1:
	{
		// x上のスポーン位置
		init.x = HighRand::fGetRand(-45, 45, 3);
		// z上のスポーン位置
		init.z = HighRand::fGetRand(36, 45, 3);
	}
	break;
	case 2:
	{
		// x上のスポーン位置
		init.x = HighRand::fGetRand(36, 45, 3);
		// z上のスポーン位置
		init.z = HighRand::fGetRand(-45, 45, 3);
	}
	break;
	case 3:
	{
		// x上のスポーン位置
		init.x = HighRand::fGetRand(-45, 45, 3);
		// z上のスポーン位置
		init.z = HighRand::fGetRand(-45, -36, 3);
	}
	break;
	case 4:
	{
		// x上のスポーン位置
		init.x = HighRand::fGetRand(-45, -36, 3);
		// z上のスポーン位置
		init.z = HighRand::fGetRand(-45, 45, 3);
	}
	break;
	}
	// リーダーのポジションを決定
	Vector3 target;
	int r = HighRand::GetRand(0, vec.size() - 1);
	target = vec[r]->p_mTransform->mPosition;

	int row = 0;
	int line = 0;
	// 氷は左下から右上に向かって生成される

	// 行が端の場合
	if (vec[r]->myLine == 0 || vec[r]->myLine == OBJ_Ice::s_iMaxNumIndex)
	{
		if (vec[r]->myLine == 0)
		{
			line = 1;
		}
		else
		{
			line = 2;
		}
	}
	// 列が端の場合
	if (vec[r]->myRow == 0 || vec[r]->myRow == OBJ_Ice::s_iMaxNumIndex)
	{
		if (vec[r]->myRow == 0)
		{
			row = 1;
		}
		else
		{
			row = 2;
		}
	}
	GetScene()->AddGameObject(LAzarashi);
	LAzarashi->Init();
	// スタート位置とターゲット位置の設定
	LAzarashi->SetTargetPosition(init.x, init.y, init.z, target.x, fIceY, target.z, fCenterY);
	LAzarashi->Start();
	LAzarashi->Update();

	int spawnnum = HighRand::GetRand(2, 4);

	for (int i = 0; i < spawnnum; i++)
	{
		OBJ_Azarashi* azarashis = new OBJ_Azarashi("Teshita",1);
		azarashis->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
		azarashis->GetColliderCom()->fRadius = fAzarashiRadius;
		azarashis->GetFootCom()->SetFootHeight(fFootHeight);
		azarashis->SetAzrashiStatus(fAfterWait, fAttackDuration, fMoveSpeed, fVelocity, fBlake, fLength, fDamageDistance);
		// リーダーと同じ位置を目標地点にする
		Vector3 TeshitaTarget = target;
		// 下
		if (line == 1)
		{
			TeshitaTarget.z += HighRand::fGetRand(10.0f, 20.0f, 3);
		}
		// 上
		else if (line == 2)
		{
			TeshitaTarget.z -= HighRand::fGetRand(10.0f, 20.0f, 3);
		}
		else
		{
			TeshitaTarget.z += HighRand::fGetRand(-7.0f, 7.0f, 3);
		}
		// 左
		if (row == 1)
		{
			TeshitaTarget.x += HighRand::fGetRand(10.0f, 20.0f, 3);
		}
		// 右
		else if (row == 2)
		{
			TeshitaTarget.x -= HighRand::fGetRand(10.0f, 20.0f, 3);
		}
		else
		{
			TeshitaTarget.x += HighRand::fGetRand(-7.0f, 7.0f, 3);
		}

		GetScene()->AddGameObject(azarashis);
		azarashis->Init();
		azarashis->SetTargetPosition(init.x, init.y, init.z, TeshitaTarget.x, fIceY, TeshitaTarget.z, fCenterY);
		azarashis->SetLeader(LAzarashi);
		azarashis->Start();
		azarashis->Update();
	}
	

	iSpawnedNum++;
	if (iSpawnedNum >= iMaxSpawn)
	{
		mState = SpawnState::End;
	}
	else
	{
		mState = SpawnState::Wait;
	}

	
}
void OBJ_AzarashiManager::Update()
{
	GameObject::Update();
	// ゲームタイムを進める
	fGameCnt += Time->GetDeltaTime();
	// 現在のゲームタイムが次のスポーン切り替えのタイム以上ならインデックスを進める
	if (iCurrentIndex < vec_SpawnRateGameTimer.size() - 1)
	{
		if(static_cast<int>(fGameCnt) > vec_SpawnRateGameTimer[iCurrentIndex + 1])
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
	case SpawnState::Calc:

		break;
	case SpawnState::End:
		break;
	default:
		break;
	}
}