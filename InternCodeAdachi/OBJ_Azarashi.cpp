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
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Azarashi;
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
	p_mFootCom->SetFootHeight(2.0f);
	AddComponent(p_mFootCom);
}

OBJ_Azarashi::OBJ_Azarashi(const char* _name)
	: OBJ_Azarashi()
{
	sObjectName = _name;
}

OBJ_Azarashi::OBJ_Azarashi(const char* _name, int _ModelKind)
{
	sObjectName = _name;

	// シェーダー
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);

	// モデル
	// アザラシマネージャーで値を渡して設定する
	p_mModelCom = new Com_Model();
	switch (_ModelKind)
	{
	case 1:
		p_mModelCom->SetModelData(AZARASHI);
		break;
	case 2:
		p_mModelCom->SetModelData(AZARASHIWAKAME);
		break;
	default :
		break;
	}
	AddComponent(p_mModelCom);

	// コライダー
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Azarashi;
	p_mColliderCom->bMovable = true;
	p_mColliderCom->bEnable = false;
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
	AddComponent(p_mFootCom);
}


void OBJ_Azarashi::Init()
{
	GameObject::Init();

	// テスト
	mState = AzrashiState::SpawnToCenter;
	
}

void OBJ_Azarashi::Update()
{
	// コンポーネントの更新
	GameObject::Update();

	switch (mState)
	{
	case AzrashiState::SpawnToCenter:
	{
		// 中心地点に向かって移動
		p_mModelCom->PlayAnimation("Jump");
		// 移動方向を取得
		Vector3 Direction = Math::GetVector(p_mTransform->mPosition, mTargetSpawnCenterPoint);
		Direction = Math::Normalize(Direction);
		float Distance = Math::GetDoubleDistance(p_mTransform->mPosition, mTargetSpawnCenterPoint);
		Vector3 Velocity = Direction * Time->GetDeltaTime() * fToSpawnSpeed;
		float Length = Math::GetDoubleLength(Velocity);
		if (Distance <= Length)
		{
			p_mTransform->mPosition = mTargetSpawnCenterPoint;
			// スポーン後の攻撃待ちに移行
			mState = AzrashiState::SpawnToTarget;
			p_mModelCom->SetPlayAnimation(false);
			break;
		}
		// 移動量が超えない場合移動させる
		p_mTransform->Translate(Velocity);
	}
		break;
	case AzrashiState::SpawnToTarget:
	{
		// 目標地点に向かって移動
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
			mState = AzrashiState::AfterSpawnWait;
			p_mGravityCom->bEnable = true;
			p_mColliderCom->bEnable = true;
			p_mGravityCom->SetGround(false);
			break;
		}
		// 移動量が超えない場合移動させる
		p_mTransform->Translate(Velocity);
	}
		break;
	case AzrashiState::AfterSpawnWait:
		fCnt += Time->GetDeltaTime();
		if (fCnt > fAfterSpawnAttackWait)
		{
			fCnt = 0;
			bAttacked = false;
			p_mModelCom->PlayAnimation("Attack");
			p_mModelCom->SetCurrentKeyFrame(0);
			mState = AzrashiState::Attack;
		}
		break;
	case AzrashiState::Attack:
		// アニメーションの最後のフレームかチェックする
		if (p_mModelCom->GetIsRotLastKey())
		{
			mState = AzrashiState::AttackWait;
			p_mModelCom->SetPlayAnimation(false);
			if (!p_mGravityCom->bEnable)
			{
				mState = AzrashiState::Dive;
				p_mModelCom->PlayAnimation("Dive");
				p_mModelCom->SetCurrentKeyFrame(0);
			}
		}
		break;
	case AzrashiState::AttackWait:
		fCnt += Time->GetDeltaTime();
		if (fCnt > fAttackDuration)
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
		// ダメージVelocityの長さを取得
		float length = Math::GetLength(mDamageVelocity);

		cout << length << endl;
		// 一定以下なら止まって攻撃待ちに移行
		if (length < fDamagePermission)
		{
			mState = AzrashiState::AttackWait;
			p_mModelCom->SetPlayAnimation(false);
			break;
		}

		// ブレーキを掛ける
		mDamageVelocity *= fBlakeVelocity;

		p_mTransform->Translate(mDamageVelocity);
	}
	break;
	case AzrashiState::Dive:
		if (p_mModelCom->GetIsRotLastKey())
		{
			p_mModelCom->SetPlayAnimation(false);
			mState = AzrashiState::DiveTo;
		}
		break;
	case AzrashiState::DiveTo:
		Translate(0.0f, -2.0f, 0.0f);
		break;
	case AzrashiState::Death:
		p_mModelCom->SetPlayAnimation(false);
		bDestroy = true;
		break;
	}
}

void OBJ_Azarashi::SetTargetPosition(float _inx, float _iny, float _inz, float _tarx, float _tary, float _tarz, float _heightY)
{
	// 始めに自身の位置を設定
	SetPosition(_inx, _iny, _inz);

	mTargetSpawnPoint.x = _tarx;
	mTargetSpawnPoint.y = _tary;
	mTargetSpawnPoint.z = _tarz;

	// 中間地点を割り出す
	mTargetSpawnCenterPoint.x = p_mTransform->mPosition.x + mTargetSpawnPoint.x / 2;
	mTargetSpawnCenterPoint.z = p_mTransform->mPosition.z + mTargetSpawnPoint.z / 2;
	mTargetSpawnCenterPoint.y = _heightY;
}

void OBJ_Azarashi::OnCollisionEnter(GameObject* _obj)
{
	GameObject::OnCollisionEnter(_obj);


	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (mState == AzrashiState::SpawnToTarget)
		{
			if (col->mColliderTag == ColliderKind::ColTag_Ice)
			{
				mState = AzrashiState::AfterSpawnWait;
			}
		}
		if (col->mColliderTag == ColliderKind::ColTag_Sea)
		{
			// 死亡処理
			mState = AzrashiState::Death;
		}
	}
	

	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Attack)
		{
			// 以下の状態の時はreturn 
			if (mState == AzrashiState::SpawnToTarget ||
				mState == AzrashiState::SpawnToCenter ||
				mState == AzrashiState::Death ||
				mState == AzrashiState::Damage ||
				mState == AzrashiState::Dive)
				return;

			// 吹き飛ばされる量の計算
			// 衝突オブジェクトとの方向を取得する
			Vector3 Direction = Math::GetVector(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
			// 向きを逆にする
			Direction = -Direction;
			Direction = Math::Normalize(Direction);
			// 衝突オブジェクトとの距離を取得
			float dis = Math::GetDistance(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
			float vec = fVelocityDistance - dis;
			if (vec > 0.0f)
			{
				Direction *= (vec * fVelocity);

				mDamageVelocity.x = Direction.x;
				mDamageVelocity.z = Direction.z;
				mDamageVelocity.y = 0.0f;

				// 攻撃までのカウントリセット
				fCnt = 0;
				// ダメージ状態に移行
				mState = AzrashiState::Damage;
				p_mModelCom->PlayAnimation("Damage");
				p_mModelCom->SetCurrentKeyFrame(0);
			}
		}
	}
}

void OBJ_Azarashi::OnCollisionStay(GameObject* _obj)
{
	GameObject::OnCollisionStay(_obj);

	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice && mState == AzrashiState::Attack)
		{
			if (!bAttacked)
			{
				// 足場の耐久力を1減らす
				OBJ_Ice* ice = static_cast<OBJ_Ice*>(_obj);
				ice->HpCalc();
				if (ice->GetHP() <= 1)
				{
					// 重力の更新を停止
					p_mGravityCom->bEnable = false;
					p_mFootCom->bEnable = false;
					p_mColliderCom->bEnable = true;
					mState = AzrashiState::Dive;
					p_mModelCom->PlayAnimation("Dive");
					p_mModelCom->SetCurrentKeyFrame(0);
				}
				bAttacked = true;
			}
		}
		if (col->mColliderTag == ColliderKind::ColTag_Sea)
		{
			if (mState == AzrashiState::SpawnToCenter ||
				mState == AzrashiState::SpawnToTarget)
			{
				return;
			}
				// 死亡処理
				mState = AzrashiState::Death;
		}
	}
}
