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

	// �o���ő吔���i�[
	iMaxSpawn = stoi(spn[0]);

	// �������(,)�ŕ���
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
	// �Q�[���^�C��
	std::vector<string> gt;
	// �X�|�[�����[�g
	std::vector<string> sr;
	// �A�U���V�̃X�e�[�^�X
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
	// �T�C�Y���ꏏ����Ȃ�������G���[
	assert(sr.size() == gt.size());

	// �X�|�[�����[�g�ƃX�|�[�����[�g�ύX���Ԃ��i�[
	for (unsigned int i = 0; i < SpawnRateNumnum; i++)
	{
		vec_SpawnRateGameTimer.emplace_back(stoi(gt[i]));
		vec_SpawnRate.emplace_back(stof(sr[i]));
	}
	if (as.size() == StateSetNum)
	{
		// �R���C�_�[�̒��S�̓ǂݍ���
		mAzarashiCenter.x = stof(as[0]);
		mAzarashiCenter.y = stof(as[1]);
		mAzarashiCenter.z = stof(as[2]);
		// �R���C�_�[�̔��a
		fAzarashiRadius = stof(as[3]);

		// ���̍���
		fFootHeight = stof(as[4]);
		// �X�|�[����̑҂�����
		fAfterWait = stof(as[5]);
		// �U���Ԋu
		fAttackDuration = stof(as[6]);
		// �ړ����x
		fMoveSpeed = stof(as[7]);
		// �ӂ��ƂьW��
		fVelocity = stof(as[8]);
		// �u���[�L�W��
		fBlake = stof(as[9]);
		// ��e���̒�~���e����
		fLength = stof(as[10]);
		// �X�|�[������y���W
		fSpawnY = stof(as[11]);
		// ���Ԓn�_��y���W
		fCenterY = stof(as[12]);
		// �X��ł̍���
		fIceY = stof(as[13]);
		// ������΂��̊�ꋗ��
		fDamageDistance = stof(as[14]);
		// 1��X�|�[���ł̍ŏ���
		iSpawnMin = stoi(as[15]);
		// 1��X�|�[���ł̍ő吔
		iSpawnMax = stoi(as[16]);

		// �X�R�A�̐ݒ�
		OBJ_Azarashi::SetGettingScore(stoi(as[17]), stoi(as[18]), stoi(as[19]));

		// �����̊֌W
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
	// �^�[�Q�b�g�ʒu�ݒ�
	std::vector<OBJ_Ice*> vec = GetScene()->GetGameObjects<OBJ_Ice>(2);
	if (vec.size() == 0)
		return;
	float f = Time->CountStop();
	DEBUG_LOG("���[�_�[ : " << f);

	// ���[�_�[���쐬
	OBJ_Azarashi* LAzarashi = new OBJ_Azarashi("Leader", 2);

	// �A�U���V�̃X�e�[�^�X�ݒ�
	LAzarashi->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
	LAzarashi->GetColliderCom()->fRadius = fAzarashiRadius;
	LAzarashi->GetFootCom()->SetFootHeight(fFootHeight);
	LAzarashi->SetAzrashiStatus(fAfterWait, fAttackDuration, fMoveSpeed, fVelocity, fBlake, fLength, fDamageDistance);
	LAzarashi->bLeader = true;
	// �X�|�[���G���A���܂��Ɏw��
	int Rand = HighRand::GetRand(1, 4);
	Vector3 init;
	init.y = fSpawnY;
	// �����X�|�[���n�_�ݒ�
	switch (Rand)
	{
	case 1:
	{
		// x��̃X�|�[���ʒu
		init.x = HighRand::fGetRand(-45, 45, 3);
		// z��̃X�|�[���ʒu
		init.z = HighRand::fGetRand(36, 45, 3);
	}
	break;
	case 2:
	{
		// x��̃X�|�[���ʒu
		init.x = HighRand::fGetRand(36, 45, 3);
		// z��̃X�|�[���ʒu
		init.z = HighRand::fGetRand(-45, 45, 3);
	}
	break;
	case 3:
	{
		// x��̃X�|�[���ʒu
		init.x = HighRand::fGetRand(-45, 45, 3);
		// z��̃X�|�[���ʒu
		init.z = HighRand::fGetRand(-45, -36, 3);
	}
	break;
	case 4:
	{
		// x��̃X�|�[���ʒu
		init.x = HighRand::fGetRand(-45, -36, 3);
		// z��̃X�|�[���ʒu
		init.z = HighRand::fGetRand(-45, 45, 3);
	}
	break;
	}
	// ���[�_�[�̃|�W�V����������
	Vector3 target;
	int r = HighRand::GetRand(0, vec.size() - 1);
	target = vec[r]->p_mTransform->mPosition;

	mInit = init;

	mLeaderPos = target;

	p_mCurrentLeader = LAzarashi;

	// �X�͍�������E��Ɍ������Đ��������

	// �s���[�̏ꍇ
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
	// �񂪒[�̏ꍇ
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
	// �X�^�[�g�ʒu�ƃ^�[�Q�b�g�ʒu�̐ݒ�
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
		// �Q�[���^�C����i�߂�
		fGameCnt += Time->GetDeltaTime();
		// ���݂̃Q�[���^�C�������̃X�|�[���؂�ւ��̃^�C���ȏ�Ȃ�C���f�b�N�X��i�߂�
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
			// ���[�_�[�쐬
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
			// �艺�쐬
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

	//// �X�|�[���G���A���܂��Ɏw��
	//int Rand = HighRand::GetRand(1, 4);
	//Vector3 init;
	//init.y = fSpawnY;
	//// �����X�|�[���n�_�ݒ�
	//switch (Rand)
	//{
	//case 1:
	//{
	//	// x��̃X�|�[���ʒu
	//	init.x = HighRand::fGetRand(-45, 45, 3);
	//	// z��̃X�|�[���ʒu
	//	init.z = HighRand::fGetRand(36, 45, 3);
	//}
	//break;
	//case 2:
	//{
	//	// x��̃X�|�[���ʒu
	//	init.x = HighRand::fGetRand(36, 45, 3);
	//	// z��̃X�|�[���ʒu
	//	init.z = HighRand::fGetRand(-45, 45, 3);
	//}
	//break;
	//case 3:
	//{
	//	// x��̃X�|�[���ʒu
	//	init.x = HighRand::fGetRand(-45, 45, 3);
	//	// z��̃X�|�[���ʒu
	//	init.z = HighRand::fGetRand(-45, -36, 3);
	//}
	//break;
	//case 4:
	//{
	//	// x��̃X�|�[���ʒu
	//	init.x = HighRand::fGetRand(-45, -36, 3);
	//	// z��̃X�|�[���ʒu
	//	init.z = HighRand::fGetRand(-45, 45, 3);
	//}
	//break;
	//}

	for (int i = 0; i < spawnnum; i++)
	{
		int r = HighRand::GetRand(0, vec.size() - 1);
		Vector3 target = vec[r]->p_mTransform->mPosition;

		// �v���C���[�̕����ɏ��������񂹂�
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

		// ���[�_�[�Ɠ����ʒu��ڕW�n�_�ɂ���
		Vector3 TeshitaTarget = mLeaderPos;

		//// �����_���ŃI�t�Z�b�g�ݒ�

		//// ��
		//if (iLine== 1)
		//{
		//	TeshitaTarget.x += HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//// ��
		//else if (iLine == 2)
		//{
		//	TeshitaTarget.x -= HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//else
		//{
		//	TeshitaTarget.x += HighRand::fGetRand(-10.0f, 10.0f, 3);
		//}
		//// ��
		//if (iRow == 1)
		//{
		//	TeshitaTarget.z += HighRand::fGetRand(7.0f, 22.0f, 3);
		//}
		//// �E
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
		// ���[�_�[�̋߂�
		//azarashis->SetTargetPosition(mInit.x, mInit.y, mInit.z, TeshitaTarget.x, fIceY, TeshitaTarget.z, fCenterY);
		// �ǂ����̕X�̏�
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
	DEBUG_LOG("�艺 : " << f);
}

void OBJ_AzarashiManager::Start()
{
	//�G�t�F�N�g���쐬
	OBJ_AzarashiAttackEffect* p_mAttackEf = new OBJ_AzarashiAttackEffect("AttackEffect");
	GetScene()->AddGameObject(p_mAttackEf);

	OBJ_AzarashiDeadEffect* p_mDeadEf = new OBJ_AzarashiDeadEffect("DeadEffect");
	GetScene()->AddGameObject(p_mDeadEf);

	OBJ_Azarashi::SetAttackEfect(p_mAttackEf);
	OBJ_Azarashi::SetDeadEffect(p_mDeadEf);
}
