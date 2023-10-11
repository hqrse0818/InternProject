#include "OBJ_Azarashi.h"
#include "../ModelName.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"
#include "../Component/Com_BoxCollider.h"
#include "OBJ_Ice.h"
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
	p_mColliderCom->bMovable = true;
	p_mColliderCom->SetCenter(0.0f, 2.0f, 0.0f);
	AddComponent(p_mColliderCom);

	// �d��
	p_mGravityCom = new Com_Gravity();
	p_mGravityCom->SetGround(true);
	// �X�|�[�������܂ŏd�͂𖳌�������
	p_mGravityCom->bEnable = false;
	AddComponent(p_mGravityCom);

	// �����R���|�[�l���g
	p_mFootCom = new Com_Foot();
	p_mFootCom->SetGravityCom(p_mGravityCom);
	p_mFootCom->SetFootHeight(1.5f);
	AddComponent(p_mFootCom);
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
		p_mModelCom->UpdateFrame(1);
		// �ړ��������擾
		Vector3 Direction = Math::GetVector(p_mTransform->mPosition, mTargetSpawnPoint);
		Direction = Math::Normalize(Direction);
		float Distance = Math::GetDoubleDistance(p_mTransform->mPosition, mTargetSpawnPoint);
		Vector3 Velocity = Direction * Time->GetDeltaTime() * fToSpawnSpeed;
		float Length = Math::GetDoubleLength(Velocity);
		if (Distance <= Length)
		{
			p_mTransform->mPosition = mTargetSpawnPoint;
			// �X�|�[����̍U���҂��Ɉڍs
			mState = AzrashiState::Fall;
			p_mGravityCom->bEnable = true;
			p_mGravityCom->SetGround(false);
			break;
		}
		// �ړ��ʂ������Ȃ��ꍇ�ړ�������
		p_mTransform->Translate(Velocity);
	}
		break;
	case AzrashiState::Fall:
		break;
	case AzrashiState::AfterSpawnWait:
		fCnt += Time->GetDeltaTime();
		if (fCnt > 3)
		{
			fCnt = 0;
			bAttacked = false;
			p_mModelCom->PlayAnimation("Attack");
			p_mModelCom->SetCurrentKeyFrame(0);
			mState = AzrashiState::Attack;
		}
		break;
	case AzrashiState::Attack:
		p_mModelCom->UpdateFrame(1);
		// �A�j���[�V�����̍Ō�̃t���[�����`�F�b�N����
		if (p_mModelCom->GetIsRotLastKey())
		{
			mState = AzrashiState::AttackWait;
		}
		break;
	case AzrashiState::AttackWait:
		fCnt += Time->GetDeltaTime();
		if (fCnt > 2)
		{
			fCnt = 0;
			bAttacked = false;
			p_mModelCom->PlayAnimation("Attack");
			p_mModelCom->SetCurrentKeyFrame(0);
			mState = AzrashiState::Attack;
		}
		break;
	case AzrashiState::Damage:
	{
		// �_���[�WVelocity�̒������擾
		float length = Math::GetLength(mDamageVelocity);

	}
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

void OBJ_Azarashi::OnCollisionEnter(GameObject* _obj)
{
	GameObject::OnCollisionEnter(_obj);

	if (mState == AzrashiState::Fall)
	{
		if (_obj->mColType == Collider::ColliderForm::Box)
		{
			Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
			if (col->ColliderTag == "Ice")
			{
				mState = AzrashiState::AfterSpawnWait;
			}
		}
	}

	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();
		if (col->ColliderTag == "Impact")
		{
			// �ȉ��̏�Ԃ̎���return 
			if (mState == AzrashiState::Fall ||
				mState == AzrashiState::Spawn ||
				mState == AzrashiState::BeforeSpawnWait ||
				mState == AzrashiState::Death)
				return;

			// ������΂����ʂ̌v�Z
			// �Փ˃I�u�W�F�N�g�Ƃ̕������擾����
			Vector3 Direction = Math::GetVector(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
			// �������t�ɂ���
			Direction = -Direction;
			Direction = Math::Normalize(Direction);
			// �Փ˃I�u�W�F�N�g�Ƃ̋������擾
			float dis = Math::GetDistance(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
			Direction *= dis;

			mDamageVelocity.x = Direction.x;
			mDamageVelocity.z = Direction.z;
			mDamageVelocity.y = 0.0f;

			// �_���[�W��ԂɈڍs
			mState = AzrashiState::Damage;
		}
	}
}

void OBJ_Azarashi::OnCollisionStay(GameObject* _obj)
{
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->ColliderTag == "Ice" && mState == AzrashiState::Attack)
		{
			if (!bAttacked)
			{
				// ����̑ϋv�͂�1���炷
				static_cast<OBJ_Ice*>(_obj)->HpCalc();
				bAttacked = true;
			}
		}
	}
}
