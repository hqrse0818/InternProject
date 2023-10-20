#include "OBJ_Penguin.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/CustomMath.h"
#include "../System/Input.h"
#include "../Scene/Scene.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Shadow.h"
#include "OBJ_Azarashi.h"
#include "GameManager.h"

using namespace DirectX::SimpleMath;
using namespace std;
void OBJ_Penguin::CreateFromCSV(const char* _FileName)
{
	string Line = ReadDataFromCSV(_FileName, 1);

	// シェーダー
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// モデル
	p_mModel = new Com_Model();
	p_mModel->SetModelData("Penguin");

	AddComponent(p_mModel);

	// ペンギン自身のコライダー
	p_mColliderCom = new Com_BoxCollider();
	p_mColliderCom->bMovable = true;
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Penguin;

	AddComponent(p_mColliderCom);

	// 移動コンポーネント
	p_mMoveCom = new Com_CharacterMove();
	// ジャンプとヒップインパクトのコンポーネント
	p_mJumpCom = new Com_Jump();
	// 重力コンポーネント
	p_mGravityCom = new Com_PenguinGravity();
	// 足元コンポーネント
	p_mFootCom = new Com_Foot();
	
	// 文字列を(,)で分割
	std::vector<string> sv = SeparateString(Line,',');
	

	// vectorコンテナのサイズと設定する数を比較
	if (sv.size() == PenguinStatuNum)
	{
		// 移動速度
		p_mMoveCom->SetMoveSpeed(stof(sv[0]));
		// 空中での移動速度
		fAirMoveSpeed = stof(sv[1]);
		// ジャンプ力
		p_mJumpCom->SetJumpPower(stof(sv[2]));
		// ヒップドロップの落下速度
		p_mJumpCom->SetDropPower(stof(sv[3]));
		// ヒップドロップの初速度
		p_mJumpCom->SetDropInitialSpeed(stof(sv[4]));
		//p_mJumpCom->SetGravityCom(p_mGravityCom);
		// プレイヤーの足の高さ
		p_mFootCom->SetFootHeight(stof(sv[5]));
		//p_mFootCom->SetGravityCom(p_mGravityCom);
		p_mFootCom->SetJumpCom(p_mJumpCom);
		// カメラのスピード
		fCamSpeed = stof(sv[6]);
		// コライダーの中心
		p_mColliderCom->SetCenter(stof(sv[7]), stof(sv[8]), stof(sv[9]));
		// コライダーのサイズ
		p_mColliderCom->SetSize(stof(sv[10]), stof(sv[11]), stof(sv[12]));
		// ヒップインパクトの範囲
		p_mJumpCom->SetImpactRange(stof(sv[13]));
		// よろめきの強さ
		this->fDamagedPower = stof(sv[14]);
		// スケール
		float scale = stof(sv[15]);
		SetScale(scale, scale, scale);

		p_mJumpCom->SetImpactSpeed(stof(sv[16]));

		p_mGravityCom->SetGravity(stof(sv[17]));

		p_mGravityCom->SetGravCoef(stof(sv[18]));

		fDirectVector = stof(sv[19]);

		fFloatTime = stof(sv[20]);

		fMouseCameraSpeed = stof(sv[21]);

		fArmorTime = stof(sv[22]);
	}
	p_mSEAttacLand = new Com_Audio();
	p_mSEAttacLand->Load("asset\\audio\\SE\\SE プレイヤー\\攻撃 着地.wav");
	AddComponent(p_mSEAttacLand);
	p_mSEDeath = new Com_Audio();
	p_mSEDeath->Load("asset\\audio\\SE\\SE プレイヤー\\死亡.wav");
	AddComponent(p_mSEDeath);
	p_mSEJump = new Com_Audio();
	p_mSEJump->Load("asset\\audio\\SE\\SE プレイヤー\\ジャンプ.wav");
	AddComponent(p_mSEJump);
	p_mSELand = new Com_Audio();
	p_mSELand->Load("asset\\audio\\SE\\SE プレイヤー\\着地.wav");
	AddComponent(p_mSELand);
	p_mSEMiss = new Com_Audio();
	p_mSEMiss->Load("asset\\audio\\SE\\SE プレイヤー\\攻撃 失敗.wav");
	AddComponent(p_mSEMiss);
	p_mSEWalk = new Com_Audio();
	p_mSEWalk->Load("asset\\audio\\SE\\SE プレイヤー\\足音.wav");
	AddComponent(p_mSEWalk);
	

	// コンポーネントの追加
	AddComponent(p_mMoveCom);
	AddComponent(p_mJumpCom);
	AddComponent(p_mGravityCom);
	AddComponent(p_mFootCom);
}

OBJ_Penguin::OBJ_Penguin()
{
	// シェーダー
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// モデル
	p_mModel = new Com_Model();
	p_mModel->SetModelData("Penguin");
	p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// ペンギン自身のコライダー
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;
	p_mCollider->mColliderTag = ColliderKind::ColTag_Penguin;

	AddComponent(p_mCollider);

	// 移動コンポーネント
	p_mMoveCom = new Com_CharacterMove();
	p_mMoveCom->SetMoveSpeed(15.0f);

	AddComponent(p_mMoveCom);

	// ジャンプコンポーネント
	p_mJumpCom = new Com_Jump();
	p_mJumpCom->SetJumpPower(20.0f);

	AddComponent(p_mJumpCom);

	// 重力コンポーネント
	p_mGravityCom = new Com_PenguinGravity();
	//p_mJumpCom->SetGravityCom(p_mGravityCom);

	AddComponent(p_mGravityCom);

	// 足元コンポーネント
	p_mFootCom = new Com_Foot();
	//p_mFootCom->SetGravityCom(p_mGravityCom);
	p_mFootCom->SetFootHeight(2.0f);
	p_mFootCom->SetJumpCom(p_mJumpCom);
	AddComponent(p_mFootCom);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

OBJ_Penguin::OBJ_Penguin(const char* _name, const char* _FileName)
{
	sObjectName = _name;

	CreateFromCSV(_FileName);
}

void OBJ_Penguin::Start()
{
	GameObject::Start();
	mState = PenguinState::Walk;

	p_mGravityCom->SetOnGround(false);

	OBJ_Shadow* myShadow = new OBJ_Shadow("PenguinShadow");
	myShadow->SetTarget(this);
	myShadow->Init();
	myShadow->Start();
	GetScene()->AddGameObject(myShadow);
}

void OBJ_Penguin::Update()
{
	//if(GameManager::)
	GameObject::Update();

	// 入力取得
	if (Controller_Input::GetIsGamePadConnect(0))
	{
		mMoveVelocity.x = Controller_Input::GetLeftStick(0).x;
		mMoveVelocity.y = Controller_Input::GetLeftStick(0).y;
	}
	else
	{
		if (Input::GetKeyState(KEYCODE_A) == KEYSTATE::KEY_WHILE_DOWN)mMoveVelocity.x = -1;
		if (Input::GetKeyState(KEYCODE_D) == KEYSTATE::KEY_WHILE_DOWN)mMoveVelocity.x = 1;
		if (Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_WHILE_DOWN)mMoveVelocity.y = 1;
		if (Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_WHILE_DOWN)mMoveVelocity.y = -1;
	}

	if (mMoveVelocity.x == 0 && mMoveVelocity.y == 0)
	{
		if (mState == PenguinState::Walk)
		{
			fIdelCnt += Time->GetDeltaTime();
			if (fIdelCnt > fIdleTime)
			{
				fIdelCnt = 0.0f;
				p_mModel->SetPlayAnimation(false);
				mState = PenguinState::Idle;
				p_mModel->PlayAnimation("Idle");
			}
		}
	}
	else
	{
		if (mState == PenguinState::Idle)
		{
			mState = PenguinState::Walk;
		}
	}

	switch (mState)
	{
		// 歩き状態
	case PenguinState::Walk:
		fWalkSECnt += Time->GetDeltaTime();
		if (fWalkSECnt > fWalkSEDuration)
		{
			p_mSEWalk->Play();
			fWalkSECnt = 0.0f;
		}

		p_mModel->PlayAnimation("Walk");
		p_mMoveCom->Move(mMoveVelocity.x, mMoveVelocity.y);
		// ジャンプ
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetOnGround() ||
			Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetOnGround())
		{
			p_mJumpCom->SetJumpFlg(true);
			p_mModel->PlayAnimation("ToJump");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeJump;
			//
			p_mGravityCom->bEnable = false;
			p_mGravityCom->SetOnGround(false);
			//
			p_mSEJump->Play();
		}
		break;
	case PenguinState::BeforeJump:
		p_mFootCom->bEnable = false;
		p_mMoveCom->Move(mMoveVelocity.x * fAirMoveSpeed, mMoveVelocity.y *fAirMoveSpeed);

		// ヒップインパクトに派生できるように
		if (Controller_Input::GetRightTriggerSimple(0) == KEYSTATE::KEY_WHILE_DOWN ||
			Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_WHILE_DOWN)
		{
			// ヒップインパクトの予約
			p_mModel->PlayAnimation("HipDrop");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeHipDrop;
			p_mGravityCom->bEnable = false;
		}

		if (p_mModel->GetIsRotLastKey())
		{
			p_mJumpCom->SetJumpFlg(false);
			p_mModel->PlayAnimation("Jump");
			p_mModel->SetCurrentKeyFrame(0);
			//
			p_mGravityCom->bEnable = true;
			//
			mState = PenguinState::Jump;
		}
		break;
	case PenguinState::Jump:
		p_mMoveCom->Move(mMoveVelocity.x * fAirMoveSpeed, mMoveVelocity.y * fAirMoveSpeed);
		// ヒップインパクト
		if (Controller_Input::GetRightTriggerSimple(0) == KEYSTATE::KEY_WHILE_DOWN ||
			Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_WHILE_DOWN)
		{
			// ヒップインパクトの予約
			p_mModel->PlayAnimation("HipDrop");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeHipDrop;
			p_mGravityCom->bEnable = false;
		}
		break;
	case PenguinState::BeforeHipDrop:
		// アニメーションの最後のキーまで待機
		if (p_mModel->GetIsRotLastKey())
		{
			p_mJumpCom->SetDropFlg(true);
			p_mJumpCom->SetJumpFlg(false);
			p_mModel->SetPlayAnimation(false);
			p_mGravityCom->bEnable = true;
			mState = PenguinState::HipDrop;
		}
		break;
	case PenguinState::HipDrop:
		if (p_mGravityCom->GetOnGround())
		{
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::AfterHipDrop;
			p_mSEAttacLand->Play();
			//p_mModel->SetModelData("AttackPenguin");
			p_mModel->PlayAnimation("AfterHipDrop");
			p_mHipEf->Create();
		}
		break;
	case PenguinState::AfterHipDrop:
		if (p_mModel->GetIsRotLastKey())
		{
			p_mJumpCom->SetDropFlg(false);
			p_mModel->SetCurrentKeyFrame(0);
			p_mModel->PlayAnimation("Walk");
			mState = PenguinState::Walk;
			p_mHipEf->Create();
		}
		break;
	case PenguinState::Damage:
	{
		//p_mGravityCom->bEnable = false;
		//p_mColliderCom->bEnable = false;
		//fArmorCnt += Time->GetDeltaTime();

		//// 許容距離よりも短ければ待機状態に移行
		//if (fArmorCnt > fArmorTime)
		//{
		//	mState = PenguinState::Walk;
		//	p_mGravityCom->bEnable = true;
		//	p_mColliderCom->bEnable = true;
		//	p_mModel->SetCurrentKeyFrame(0);
		//	fArmorCnt = 0.0f;
		//	break;
		//}

		// ダメージVelocityの長さを取得
		float length = Math::GetLength(mDamageVelocity);

		// 一定以下なら止まって攻撃待ちに移行
		if (length < fDamagePermission)
		{
			mState = PenguinState::Walk;
			p_mModel->SetPlayAnimation(false);
			break;
		}

		// ブレーキを掛ける
		mDamageVelocity *= fBlake;

		p_mTransform->Translate(mDamageVelocity);

		/*Vector3 Velocity = mDamageVelocity * Time->GetDeltaTime();
		mDamageVelocity *= fBlake;

		p_mTransform->Translate(Velocity);*/
	}
		break;
	case PenguinState::HipDropOnAzarashi:
	{
		fFloatCnt += Time->GetDeltaTime();
		p_mGravityCom->bEnable = false;

		// ヒップインパクトに派生できるように
		if (Controller_Input::GetRightTriggerSimple(0) == KEYSTATE::KEY_WHILE_DOWN  && fFloatCnt > fFloatTime / 2||
			Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_WHILE_DOWN && fFloatCnt > fFloatTime /2)
		{
			fFloatCnt = 0.0f;
			// ヒップインパクトの予約
			p_mModel->PlayAnimation("HipDrop");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeHipDrop;
			p_mGravityCom->bEnable = false;
		}

		if (fFloatCnt > fFloatTime)
		{
			fFloatCnt = 0.0f;
			mState = PenguinState::Walk;
			p_mGravityCom->bEnable = true;
			p_mColliderCom->bEnable = true;
			//p_mModel->SetModelData("Penguin");
			p_mModel->SetCurrentKeyFrame(0);
			
			/*p_mJumpCom->SetJumpFlg(true);
			p_mModel->PlayAnimation("Jump");
			p_mModel->SetCurrentKeyFrame(0);
			p_mGravityCom->bEnable = true;
			mState = PenguinState::Jump;*/

			/*p_mJumpCom->SetJumpFlg(true);
			p_mModel->PlayAnimation("JumpTo");
			p_mModel->SetCurrentKeyFrame(0);
			p_mGravityCom->bEnable = false;
			mState = PenguinState::BeforeJump;*/

			break;
		}

		Vector3 Velocity = mDamageVelocity * Time->GetDeltaTime();

		p_mTransform->Translate(Velocity);
		p_mMoveCom->Move(mMoveVelocity.x * fAirMoveSpeed, mMoveVelocity.y * fAirMoveSpeed);
	}
		break;

	case PenguinState::Idle:
		// ジャンプ
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetOnGround() ||
			Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetOnGround())
		{
			p_mJumpCom->SetJumpFlg(true);
			p_mModel->PlayAnimation("ToJump");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeJump;
			//
			p_mGravityCom->bEnable = false;
			p_mGravityCom->SetOnGround(false);
			//
			p_mSEJump->Play();
		}
		break;
	case PenguinState::FallMotion:
		p_mGravityCom->bEnable = false;
		break;
	case PenguinState::Fall:
		break;
	case PenguinState::Death:
		// ゲームマネージャーを変更
		break;
	}
	// アングル調整
	// 横の角度
	p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Controller_Input::GetRightStick(0).x * fCamSpeed));
	// 高さ
	p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() - Controller_Input::GetRightStick(0).y);

	if (Input::GetIsCenter())
	{
		p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Input::GetCursorMove().x * fMouseCameraSpeed));
		p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() + Input::GetCursorMove().y);
	}

	// Velocityリセット
	mMoveVelocity.x = 0;
	mMoveVelocity.y = 0;
}

void OBJ_Penguin::OnCollisionEnter(GameObject* _obj)
{
	GameObject::OnCollisionEnter(_obj);
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();

		if (col->mColliderTag == ColliderKind::ColTag_Ice)
		{
			if (mState != PenguinState::HipDrop && mState != PenguinState::AfterHipDrop && mState != PenguinState::BeforeHipDrop &&
				mState != PenguinState::BeforeJump && mState != PenguinState::Damage)
			{
				if (mState == PenguinState::Jump)
				{
					p_mSELand->Play();
				}
				mState = PenguinState::Walk;
			}
		}
	}
	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Azarashi)
		{
			if (mState != PenguinState::BeforeHipDrop &&
				mState != PenguinState::HipDrop && mState != PenguinState::HipDropOnAzarashi && mState != PenguinState::Damage)
			{
				Vector3 Direction = Math::GetVector(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
				Direction = Math::Normalize(-Direction);
				// ダメージ後のよろめきを計算
				mDamageVelocity = fDamagedPower * Direction;
				//mDamageVelocity.y = fDamagedPower;
				mDamageVelocity.y = 0.0f;
				mState = PenguinState::Damage;
				p_mJumpCom->SetJumpFlg(false);
				p_mJumpCom->SetDropFlg(false);
				p_mGravityCom->SetOnGround(false);
				p_mGravityCom->bEnable = true;
			}
			else if (mState == PenguinState::HipDrop)
			{
				// アザラシの上に乗った状態へ
				mState = PenguinState::HipDropOnAzarashi;
				p_mColliderCom->bEnable = false;
				// 読み込みで変える
				mDamageVelocity.y = fDirectVector;
				mDamageVelocity.x = 0;
				mDamageVelocity.z = 0;
				
				p_mJumpCom->SetDropFlg(false);
				p_mJumpCom->SetJumpFlg(false);
				p_mGravityCom->SetOnGround(false);
				p_mSEMiss->Play();
			}
		}
	}
}

void OBJ_Penguin::OnCollisionStay(GameObject* _obj)
{
	GameObject::OnCollisionStay(_obj);
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice)
		{
			
		}
	}
	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();

		if (col->mColliderTag == ColliderKind::ColTag_Azarashi)
		{
			if (mState == PenguinState::HipDrop)
			{
				// アザラシの上に乗った状態へ
				mState = PenguinState::HipDropOnAzarashi;
				p_mColliderCom->bEnable = false;
				// 読み込みで変える
				mDamageVelocity.y = fDirectVector;
				mDamageVelocity.x = 0;
				mDamageVelocity.z = 0;

				p_mJumpCom->SetDropFlg(false);
				p_mJumpCom->SetJumpFlg(false);
				p_mGravityCom->SetOnGround(false);
				p_mSEMiss->Play();
			}
		}
		if (col->mColliderTag == ColliderKind::ColTag_Fall)
		{
			// 落下させる
		}
	}
}
