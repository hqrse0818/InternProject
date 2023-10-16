#include "OBJ_AzarashiManager.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../System/HighGetRand.h"
#include "../Scene/Scene.h"
#include "OBJ_Ice.h"

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

	// �o���ő吔���i�[
	iMaxSpawn = stoi(sMaxSpawnNum);

	// �������(,)�ŕ���
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
	for (unsigned int i = 0; i < gt.size(); i++)
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
	// �A�U���V�̃X�e�[�^�X�ݒ�
	azarashi->GetColliderCom()->SetCenter(mAzarashiCenter.x, mAzarashiCenter.y, mAzarashiCenter.z);
	azarashi->GetColliderCom()->fRadius = fAzarashiRadius;
	azarashi->GetFootCom()->SetFootHeight(fFootHeight);
	azarashi->SetAzrashiStatus(fAfterWait, fAttackDuration, fMoveSpeed, fVelocity, fBlake, fLength,fDamageDistance);

	azarashi->Init();
	azarashi->Start();
	

	// �X�|�[���G���A���܂��Ɏw��
	Rand = HighRand::GetRand(1, 4);
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
	case 3 : 
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
	// �^�[�Q�b�g�ʒu�ݒ�
	std::vector<OBJ_Ice*> vec = GetScene()->GetGameObjects<OBJ_Ice>();
	if (vec.size() == 0)
		return;
	int r = HighRand::GetRand(0, vec.size() - 1);

	Vector3 target = vec[r]->p_mTransform->mPosition;

	// �X�^�[�g�ʒu�ƃ^�[�Q�b�g�ʒu�̐ݒ�
	azarashi->SetTargetPosition(init.x, init.y, init.z,target.x, fIceY, target.z, fCenterY);

	GetScene()->AddGameObject(azarashi);
	azarashi->Update();

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
	// �Q�[���^�C����i�߂�
	fGameCnt += Time->GetDeltaTime();
	// ���݂̃Q�[���^�C�������̃X�|�[���؂�ւ��̃^�C���ȏ�Ȃ�C���f�b�N�X��i�߂�
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
	case SpawnState::End:
		break;
	default:
		break;
	}
}