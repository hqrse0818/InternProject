#include "OBJ_Azarashi.h"
#include "../ModelName.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"
#include "../Component/Com_BoxCollider.h"
#include "OBJ_Ice.h"
#include "../GameObject/OBJ_Shadow.h"
#include "../Scene/Scene.h"
#include <iostream>
#include "OBJ_Score.h"

using namespace DirectX::SimpleMath;
using namespace std;

int OBJ_Azarashi::s_iOnIceNum = 0;
int OBJ_Azarashi::s_iScoreMin = 0;
int OBJ_Azarashi::s_iScoreCenter= 0;
int OBJ_Azarashi::s_iScoreMax = 0;
float OBJ_Azarashi::fScoreDisCen = 0.0f;
float OBJ_Azarashi::fScoreDisMax = 0.0f;

OBJ_AzarashiAttackEffect* OBJ_Azarashi::p_mAttackEf = nullptr;
OBJ_AzarashiDeadEffect* OBJ_Azarashi::p_mDeadEf = nullptr;

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
		p_mModelCom->SetModelData(AZARASHI);
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
	p_mFootCom->bEnable = false;
	AddComponent(p_mFootCom);

	// アザラシヒットコンポーネント
	p_mHitCom = new Com_AzarshiHit();
	AddComponent(p_mHitCom);
}


void OBJ_Azarashi::Init()
{
	GameObject::Init();

	// テスト
	mState = AzrashiState::SpawnToCenter;
	
}

void OBJ_Azarashi::Start()
{
	OBJ_Shadow* myShadow = new OBJ_Shadow("Azarahis");
	myShadow->SetTarget(this);
	myShadow->Init();
	myShadow->Start();
	GetScene()->AddGameObject(myShadow);
	p_mShadowObj = myShadow;
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
			SetRotation(0.0f, 0.0f, 0.0f);
			p_mShadowObj->SetActive(true);
			break;
		}
		// 移動量が超えない場合移動させる
		p_mTransform->Translate(Velocity);

		Vector3 v = Math::Normalize(Velocity);
		float angley = atan2f(v.x, v.z);
		float anglex = atan2f(v.y, v.z);
		float anglez = atan2f(v.x, v.z);
		SetRotation(-anglex, -angley, -anglez);
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
			p_mFootCom->bEnable = true;
			p_mGravityCom->SetGround(false);
			p_mShadowObj->SetFollowTargetY(true);
			s_iOnIceNum++;
			break;
		}
		// 移動量が超えない場合移動させる
		p_mTransform->Translate(Velocity);
		if (Velocity.x == 0 && Velocity.y == 0 && Velocity.z == 0)
		{
			return;
		}
		Vector3 v = Math::Normalize(Velocity);
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
			p_mAttackEf->p_mTransform->mPosition = this->p_mTransform->mPosition;
			p_mAttackEf->Create();
		}
		break;
	case AzrashiState::Damage:
	{
		// ダメージVelocityの長さを取得
		float length = Math::GetLength(mDamageVelocity);

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
		iScore = 0;
		if (p_mModelCom->GetIsRotLastKey())
		{
			p_mModelCom->SetPlayAnimation(false);
			p_mColliderCom->bEnable = true;
			mState = AzrashiState::DiveTo;
		}
		break;
	case AzrashiState::DiveTo:
		Translate(0.0f, -2.0f, 0.0f);
		break;
	case  AzrashiState::Dive2:
		if (p_mModelCom->GetIsRotLastKey())
		{
			p_mModelCom->SetPlayAnimation(false);
			p_mColliderCom->bEnable = true;
			mState = AzrashiState::DiveTo2;
		}
		break;
	case AzrashiState::DiveTo2:
		Translate(0.0f, -2.0f, 0.0f);
		break;
	case AzrashiState::Death:
		s_iOnIceNum--;
		OBJ_Score::CalcScore(iScore);
		p_mShadowObj->bDestroy = true;
		p_mShadowObj->SetActive(false);
		p_mModelCom->SetPlayAnimation(false);
		p_mColliderCom->bEnable = false;
		bDestroy = true;
		break;
	case AzrashiState::Death2:
		s_iOnIceNum--;
		OBJ_Score::AddNoComboScore(50);
		p_mShadowObj->bDestroy = true;
		p_mShadowObj->SetActive(false);
		p_mModelCom->SetPlayAnimation(false);
		p_mColliderCom->bEnable = false;
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
			p_mDeadEf->p_mTransform->mPosition = this->p_mTransform->mPosition;
			p_mDeadEf->Create();
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
				mState == AzrashiState::Dive||
				mState == AzrashiState::DiveTo ||
				mState == AzrashiState::Dive2 ||
				mState == AzrashiState::DiveTo2 ||
				mState == AzrashiState::Death2)
				return;

			// 吹き飛ばされる量の計算
			// 衝突オブジェクトとの方向を取得する
			Vector3 Direction = Math::GetVector(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
			// 向きを逆にする
			Direction = -Direction;
			Direction = Math::Normalize(Direction);
			// 衝突オブジェクトとの距離を取得
			float dis = Math::GetDistance(p_mTransform->mPosition, _obj->p_mTransform->mPosition);

			DEBUG_LOG(dis);

			// 距離によってスコア加算予定値を変更する(距離は仮)
			if (dis < fScoreDisMax)
			{
				iScore = s_iScoreMax;
			}
			else if (dis < fScoreDisCen)
			{
				iScore = s_iScoreCenter;
			}
			else
			{
				iScore = s_iScoreMin;
			}

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
					p_mColliderCom->bEnable = false;
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
			if (mState == AzrashiState::DiveTo2 || mState == AzrashiState::Dive2)
			{
				mState = AzrashiState::Death2;
			}
			else
			{
				// 死亡処理
				mState = AzrashiState::Death;
			}
				
		}
		if (col->mColliderTag == ColliderKind::ColTag_Fall)
		{
			if (mState != AzrashiState::Damage &&
				mState != AzrashiState::Dive &&
				mState != AzrashiState::DiveTo &&
				mState != AzrashiState::Death &&
				mState != AzrashiState::Dive2 &&
				mState != AzrashiState::DiveTo2)
			{
				mState = AzrashiState::Dive2;
				if (iScore == 0)
				{
					iScore = 50;
				}
				// 重力の更新を停止
				p_mGravityCom->bEnable = false;
				p_mFootCom->bEnable = false;
				p_mColliderCom->bEnable = false;
				p_mModelCom->PlayAnimation("Dive");
				p_mModelCom->SetCurrentKeyFrame(0);
			}
		}
	}
}

void OBJ_Azarashi::SetLeader(OBJ_Azarashi* _obj)
{
	p_mLeader = _obj;
}
