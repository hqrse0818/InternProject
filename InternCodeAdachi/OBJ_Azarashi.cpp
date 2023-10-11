#include "OBJ_Azarashi.h"
#include "../ModelName.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"
#include "../Component/Com_BoxCollider.h"
#include <iostream>

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_Azarashi::OBJ_Azarashi()
{
	// シェーダー
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	// モデル
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData(AZARASHI);
	AddComponent(p_mModelCom);

	// コライダー(暫定csvで読めるようにする)
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 2.0f;
	p_mColliderCom->bMovable = true;
	p_mColliderCom->SetCenter(0.0f, 2.0f, 0.0f);
	AddComponent(p_mColliderCom);

	// 重力
	p_mGravityCom = new Com_Gravity();
	p_mGravityCom->SetGround(true);
	// スポーン完了まで重力を無効化する
	p_mGravityCom->bEnable = false;
	AddComponent(p_mGravityCom);

	// 足元コンポーネント
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
	// スポーン待ち
	//mState = AzrashiState::BeforeSpawnWait;

	// テスト
	mState = AzrashiState::Spawn;
	
}

void OBJ_Azarashi::Update()
{
	// コンポーネントの更新
	GameObject::Update();

	switch (mState)
	{
	case AzrashiState::BeforeSpawnWait:
		break;
	case AzrashiState::Spawn:
	{
		p_mModelCom->PlayAnimation("Jump");
		p_mModelCom->UpdateFrame(1);
		// 移動方向を取得
		Vector3 Direction = Math::GetVector(p_mTransform->mPosition, mTargetSpawnPoint);
		Direction = Math::Normalize(Direction);
		float Distance = Math::GetDoubleDistance(p_mTransform->mPosition, mTargetSpawnPoint);
		Vector3 Velocity = Direction * Time->GetDeltaTime() * fToSpawnSpeed;
		float Length = Math::GetDoubleLength(Velocity);
		if (Distance <= Length)
		{
			p_mTransform->mPosition = mTargetSpawnPoint;
			// スポーン後の攻撃待ちに移行
			mState = AzrashiState::Fall;
			p_mGravityCom->bEnable = true;
			p_mGravityCom->SetGround(false);
			break;
		}
		// 移動量が超えない場合移動させる
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
		// アニメーションの最後のフレームかチェックする
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
			mState = AzrashiState::Attack;
		}
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

void OBJ_Azarashi::OnCollisionEnter(GameObject* _obj)
{
	GameObject::OnCollisionEnter(_obj);

	if (mState == AzrashiState::Fall)
	{
		if (_obj->mColType == Collider::ColliderForm::Box)
		{
			Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
			if (col->bCanStepOn)
			{
				mState = AzrashiState::AfterSpawnWait;
			}
		}
	}
}
