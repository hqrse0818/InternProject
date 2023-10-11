#include "OBJ_Azarashi.h"
#include "../ModelName.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"
#include <iostream>

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_Azarashi::OBJ_Azarashi()
{
	// �V�F�[�_�[
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	// ���f��
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData(AZARASHI);
	AddComponent(p_mModelCom);

	// �R���C�_�[(�b��csv�œǂ߂�悤�ɂ���)
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 2.0f;
	p_mColliderCom->SetCenter(0.0f, 2.0f, 0.0f);
	AddComponent(p_mColliderCom);

	// �d��
	p_mGravityCom = new Com_Gravity();
	p_mGravityCom->SetGround(true);
	// �X�|�[�������܂ŏd�͂𖳌�������
	p_mGravityCom->bEnable = false;
	AddComponent(p_mGravityCom);
}

OBJ_Azarashi::OBJ_Azarashi(const char* _name)
	: OBJ_Azarashi()
{
	sObjectName = _name;
}


void OBJ_Azarashi::Init()
{
	GameObject::Init();
	// �X�|�[���҂�
	//mState = AzrashiState::BeforeSpawnWait;

	// �e�X�g
	mState = AzrashiState::Spawn;
	
}

void OBJ_Azarashi::Update()
{
	// �R���|�[�l���g�̍X�V
	GameObject::Update();

	switch (mState)
	{
	case AzrashiState::BeforeSpawnWait:
		break;
	case AzrashiState::Spawn:
	{
		p_mModelCom->PlayAnimation("Jump");
		p_mModelCom->UpdateFrame();
		// �ړ��������擾
		Vector3 Direction = Math::GetVector(p_mTransform->mPosition, mTargetSpawnPoint);
		Direction = Math::Normalize(Direction);
		float Distance = Math::GetDistance(p_mTransform->mPosition, mTargetSpawnPoint);
		Vector3 Velocity = Direction * Time->GetDeltaTime() * fToSpawnSpeed;
		float Length = Math::GetLength(Velocity);
		if (Distance <= Length)
		{
			p_mTransform->mPosition = mTargetSpawnPoint;
			// �X�|�[����̍U���҂��Ɉڍs
			mState = AzrashiState::Fall;
			break;
		}
		// �ړ��ʂ������Ȃ��ꍇ�ړ�������
		p_mTransform->Translate(Velocity);
	}
		break;
	case AzrashiState::Fall:
		p_mGravityCom->bEnable = true;
		p_mGravityCom->SetGround(false);
		break;
	case AzrashiState::AfterSpawnWait:
		break;
	case AzrashiState::Attack:
		break;
	case AzrashiState::AttackWait:
		break;
	case AzrashiState::Damage:
		break;
	case AzrashiState::Death:
		break;
	}
}

void OBJ_Azarashi::SetTargetPosition(float _x, float _y, float _z)
{
	mTargetSpawnPoint.x = _x;
	mTargetSpawnPoint.y = _y;
	mTargetSpawnPoint.z = _z;
}
