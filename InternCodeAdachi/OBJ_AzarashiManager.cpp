#include "OBJ_AzarashiManager.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../System/HighGetRand.h"
#include "../Scene/Scene.h"
#include "OBJ_Ice.h"
#include "OBJ_IceManager.h"
#include "GameManager.h"
#include "../InternCode.Kizuki/OBJ_AzarashiAttackEffect.h"
#include "../InternCode.Kizuki/OBJ_AzarashiDeadEffect.h"
#include "../System/CustomMath.h"

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

	vector<string> spn = SeparateString(sMaxSpawnNum, ',');

	// 出現最大数を格納
	iMaxSpawn = stoi(spn[0]);

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
		// 1回スポーンでの最小数
		iSpawnMin = stoi(as[15]);
		// 1回スポーンでの最大数
		iSpawnMax = stoi(as[16]);

		// スコアの設定
		OBJ_Azarashi::SetGettingScore(stoi(as[17]), stoi(as[18]), stoi(as[19]));

		// 距離の関係
		OBJ_Azarashi::SetScoreDistance(stof(as[20]), stof(as[21]));

		fLeaderSpawnedTime = stof(as[22]);
	}
	gt.clear();
	sr.clear();
	as.clear();

	iSpawnedNum = 0;
}

void OBJ_AzarashiManager::CreateLeader()
{
	Time->CountStart();
	// ターゲット位置設定
	std::vector<OBJ_Ice*> vec = GetScene()->GetGameObjects<OBJ_Ice>(2);
	if (vec.size() == 0)
		return;
	float f = Time->CountStop();
	DEBUG_LOG("リーダー : " << f);

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

	mInit = init;

	mLeaderPos = target;

	p_mCurrentLeader = LAzarashi;

	// 氷は左下から右上に向かって生成される

	// 行が端の場合
	if (vec[r]->myLine == 0 || vec[r]->myLine == OBJ_Ice::s_iMaxNumIndex)
	{
		if (vec[r]->myLine == 0)
		{
			iLine = 1;
		}
		else
		{
			iLine = 2;
		}
	}
	// 列が端の場合
	if (vec[r]->myRow == 0 || vec[r]->myRow == OBJ_Ice::s_iMaxNumIndex)
	{
		if (vec[r]->myRow == 0)
		{
			iRow = 1;
		}
		else
		{
			iRow = 2;
		}
	}
	GetScene()->AddGameObject(LAzarashi);
	LAzarashi->Init();
	// スタート位置とターゲット位置の設定
	LAzarashi->SetTargetPosition(init.x, init.y, init.z, target.x, fIceY, target.z, fCenterY);
	LAzarashi->Start();
	LAzarashi->Update();
	LAzarashi->GetSpawnAudio()->Play();

	iSpawnedNum++;
	if (iSpawnedNum >= iMaxSpawn)
	{
		mState = SpawnState::End;
	}
	else
	{
		mState = SpawnState::WaitTeshita;
	}

	
}
void OBJ_AzarashiManager::Update()
{
	GameObject::Update();
	if (GameManager::GetGameState() == GameState::Game)
	{
		// ゲームタイムを進める
		fGameCnt += Time->GetDeltaTime();
		// 現在のゲームタイムが次のスポーン切り替えのタイム以上ならインデックスを進める
		if (iCurrentIndex < vec_SpawnRateGameTimer.size() - 1)
		{
			if (static_cast<int>(fGameCnt) > vec_SpawnRateGameTimer[iCurrentIndex + 1])
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
				mState = SpawnState::SpawnLeader;
			}
			break;
		case SpawnState::SpawnLeader:
			// リーダー作成
			CreateLeader();
			mState = SpawnState::WaitTeshita;
			break;
		case SpawnState::WaitTeshita:
			fLeaderCnt += Time->GetDeltaTime();
			if (fLeaderCnt > fLeaderSpawnedTime)
			{
				fLeaderCnt = 0.0f;
				mState = SpawnState::SpawnTeshita;
			}
			break;
		case SpawnState::SpawnTeshita:
			// 手下作成
			CreateTeshita();
			break;
		case SpawnState::Calc:

			break;
		case SpawnState::End:
			break;
		default:
			break;
		}
	}
}

void OBJ_AzarashiManager::CreateTeshita()
{
	Time->CountStart();
	std::vector<OBJ_Ice*> vec = GetScene()->GetGameObjects<OBJ_Ice>(2);
	if (vec.size() == 0)
		return;

	int spawnnum = HighRand::GetRand(iSpawnMin, iSpawnMax);
	if (iMaxSpawn - iSpawnedNum < spawnnum)
	{
		spawnnum = iMaxSpawn - iSpawnedNum;
	}

	//// スポーンエリアを大まかに指定
	//int Rand = HighRand::GetRand(1, 4);
	//Vector3 init;
	//init.y = fSpawnY;
	//// 初期スポーン地点設定
	//switch (Rand)
	//{
	//case 1:
	//{
	//	// x上のスポーン位置
	//	init.x = HighRand::fGetRand(-45, 45, 3);
	//	// z上のスポーン位置
	//	init.z = HighRand::fGetRand(36, 45, 3);
	//}
	//break;
	//case 2:
	//{
	//	// x上のスポーン位置
	//	init.x = HighRand::fGetRand(36, 45, 3);
	//	// z上のスポーン位置
	//	init.z = HighRand::fGetRand(-45, 45, 3);
	//}
	//break;
	//case 3:
	//{
	//	// x上のスポーン位置
	//	init.x = HighRand::fGetRand(-45, 45, 3);
	//	// z上のスポーン位置
	//	init.z = HighRand::fGetRand(-45, -36, 3);
	//}
	//break;
	//case 4:
	//{
	//	// x上のスポーン位置
	//	init.x = HighRand::fGetRand(-45, -36, 3);
	//	// z上のスポーン位置
	//	init.z = HighRand::fGetRand(-45, 45, 3);
	//}
	//break;
	//}

	for (int i = 0; i < spawnnum; i++)
	{
		int r = HighRand::GetRand(0, vec.size() - 1);
		Vector3 target = vec[r]->p_mTransform->mPosition;

		// プレイヤーの方向に少しだけ寄せる
		Vector3 Direction = Math::GetVector(target, p_mTarget->p_mTransform->mPosition);
		Direction = Math::Normalize(Direction);
		int t = HighRand::fGetRand(5, 14, 3);
		Direction *= t;
		target.x += Direction.x;
		target.z += Direction.z;




		OBJ_Azarashi* azarashis = new OBJ_Azarashi("Teshita", 1);
		azarashis->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
		azarashis->GetColliderCom()->fRadius = fAzarashiRadius;
		azarashis->GetFootCom()->SetFootHeight(fFootHeight);
		azarashis->SetAzrashiStatus(fAfterWait, fAttackDuration, fMoveSpeed, fVelocity, fBlake, fLength, fDamageDistance);

		// リーダーと同じ位置を目標地点にする
		Vector3 TeshitaTarget = mLeaderPos;

		//// ランダムでオフセット設定

		//// 下
		//if (iLine== 1)
		//{
		//	TeshitaTarget.x += HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//// 上
		//else if (iLine == 2)
		//{
		//	TeshitaTarget.x -= HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//else
		//{
		//	TeshitaTarget.x += HighRand::fGetRand(-10.0f, 10.0f, 3);
		//}
		//// 左
		//if (iRow == 1)
		//{
		//	TeshitaTarget.z += HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//// 右
		//else if (iRow == 2)
		//{
		//	TeshitaTarget.z -= HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//else
		//{
		//	TeshitaTarget.z += HighRand::fGetRand(-10.0f, 10.0f, 3);
		//}

		GetScene()->AddGameObject(azarashis);
		azarashis->Init();
		// リーダーの近く
		//azarashis->SetTargetPosition(mInit.x, mInit.y, mInit.z, TeshitaTarget.x, fIceY, TeshitaTarget.z, fCenterY);
		// どこかの氷の上
		azarashis->SetTargetPosition(mInit.x, mInit.y, mInit.z, target.x, fIceY, target.z, fCenterY);
		//azarashis->SetTargetPosition(init.x, init.y, init.z, TeshitaTarget.x, fIceY, TeshitaTarget.z, fCenterY);
		azarashis->Start();
		azarashis->Update();
		azarashis->GetSpawnAudio()->Play();
	}

	iSpawnedNum += spawnnum;

	if (iSpawnedNum >= iMaxSpawn)
	{
		mState = SpawnState::End;
	}
	else
	{
		mState = SpawnState::Wait;
	}

	float f = Time->CountStop();
	DEBUG_LOG("手下 : " << f);
}

void OBJ_AzarashiManager::Start()
{
	//エフェクトを作成
	OBJ_AzarashiAttackEffect* p_mAttackEf = new OBJ_AzarashiAttackEffect("AttackEffect");
	GetScene()->AddGameObject(p_mAttackEf);

	OBJ_AzarashiDeadEffect* p_mDeadEf = new OBJ_AzarashiDeadEffect("DeadEffect");
	GetScene()->AddGameObject(p_mDeadEf);

	OBJ_Azarashi::SetAttackEfect(p_mAttackEf);
	OBJ_Azarashi::SetDeadEffect(p_mDeadEf);
}
