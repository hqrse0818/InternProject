#include "OBJ_Ice.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../InternCodeAdachi/CSVLoad.h"
#include "../ModelName.h"

#define LoadRow (1)

using namespace DirectX::SimpleMath;
using namespace std;

void OBJ_Ice::CreateFromCSV(const char* _FileName)
{
	string Line = ReadDataFromCSV(_FileName, LoadRow);

	// �������(,)�ŕ���
	istringstream iss(Line);
	string word;
	std::vector<string> sv;
	while (getline(iss, word, ','))
	{
		sv.emplace_back(word);
	}

	fShakeTime = stof(sv[0]); //�h��鎞��
	fShakePower = stof(sv[1]); // �h��͈̔�
	p_mCollider->SetCenter(stof(sv[2]), stof(sv[3]), stof(sv[4]));
	p_mCollider->SetSize(stof(sv[5]), stof(sv[6]), stof(sv[7]));
}

OBJ_Ice::OBJ_Ice()
{
	myColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	// �V�F�[�_�[
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	p_mShaderCom->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShaderCom);

	// ���f��
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData(ICE_HP5);

	AddComponent(p_mModelCom);

	// �R���C�_�[
	p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(7.0f, 2.0f, 7.0f);
	p_mCollider->SetCenter(0.0f, 1.0f, 0.0f);
	p_mCollider->bCanStepOn = true;
	p_mCollider->mColliderTag = ColliderKind::ColTag_Ice;

	AddComponent(p_mCollider);

	//��

	//�q�r
	p_mAudio_Damage = new Com_Audio();
	p_mAudio_Damage->Load("asset\\audio\\SE\\SE ���̑�\\�X �q�r.wav");
	p_mAudio_Damage->SetUseTarget(false);
	AddComponent(p_mAudio_Damage);
	//�j��
	p_mAudio_Break = new Com_Audio();
	p_mAudio_Break->Load("asset\\audio\\SE\\SE ���̑�\\�X �j��.wav");
	p_mAudio_Break->SetUseTarget(false);
	AddComponent(p_mAudio_Break);
}

OBJ_Ice::OBJ_Ice(const char* _name)
	: OBJ_Ice()
{
	sObjectName = _name;
}

OBJ_Ice::OBJ_Ice(const char* _ice, const char* _FileName)
	: OBJ_Ice()
{
	sObjectName = _ice;
	CreateFromCSV(_FileName);
}

void OBJ_Ice::Init()
{
	p_mShaderCom->p_mPS->CreateBuffer(16);

	//���̈ʒu��ۑ�
	originalPosition = p_mTransform->mPosition;

	GameObject::Init();
}

/*
	HP�̗ʂŕύX(�e�N�X�`���ɕύX�\��)
	�Z�ϋv�l��2�ȏ�̎�
	�E�Ԃ���ƈ�u�k����
	�E�e�N�X�`���؂�ւ�
	�E�Ђт�����SE���Đ�
	�E�ϋv�l��-1

	�Z�ϋv�l��1�̎�
	�E�I�u�W�F�N�g������
	�E�����SE���Đ�
	�E�����G�t�F�N�g���Đ�
*/
void OBJ_Ice::Update()
{
	GameObject::Update();

	switch (iHP)
	{
	case 1:
		p_mCollider->bEnable = false;
		fLastLifeWaitTime -= Time->GetDeltaTime();
		if (fLastLifeWaitTime < 0)
		{
			bDestroy = true; //GameObject�N���X��Destroy()���g�����߂ɕK�v
		}
		break;
	case 2:
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		Shake();
		break;
	case 3:
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 4:
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 5:
		myColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}

	

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);
}

//�A�U���V�̑ҋ@���Ԃɂ����HP������悤�ɂ���
void OBJ_Ice::HpCalc()
{
	iHP--;
	fElapsedTime = 0.0f;

	if (iHP <= 4 && iHP > 1);
	{
		p_mAudio_Damage->Play();
	}

	switch (iHP)
	{
	case 4:
		p_mModelCom->SetModelData(ICE_HP4);
		break;
	case 3:
		p_mModelCom->SetModelData(ICE_HP3);
		break;
	case 2:
		p_mModelCom->SetModelData(ICE_HP2);
		break;
	case 1:
		p_mAudio_Break->Play();
		p_mModelCom->SetModelData(ICE_HP1);
		break;
	}
}

//���ꂪ�h��鏈��
void OBJ_Ice::Shake()
{
	//�^�C�}�[���X�V
	fElapsedTime += Time->GetDeltaTime();

	//�h��鎞�Ԃ��I��������h����~
	if (fElapsedTime >= fShakeTime)
	{
		//�h�ꂪ�I�������猳�̈ʒu�ɖ߂�
		p_mTransform->mPosition = originalPosition;
		return;
	}

	// ����������_���ɗh�炷
	float fPowerX = RandomRange(-fShakePower, fShakePower);
	float fPowerY = RandomRange(-fShakePower, fShakePower);
	float fPowerZ = RandomRange(-fShakePower, fShakePower);

	// ���݂̈ʒu���擾���A�h�ꂽ�ʒu�ɐݒ�
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + fPowerX, currentPosition.y + fPowerY, currentPosition.z + fPowerZ);
}
