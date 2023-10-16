#include "OBJ_Penguin.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/CustomMath.h"
#include "../System/Input.h"
#include "../Scene/Scene.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Shadow.h"

#define LoadRow (1)

using namespace DirectX::SimpleMath;
using namespace std;
void OBJ_Penguin::CreateFromCSV(const char* _FileName)
{
	string Line = ReadDataFromCSV(_FileName, LoadRow);

	// �V�F�[�_�[
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// ���f��
	p_mModel = new Com_Model();
	p_mModel->SetModelData("Penguin");

	AddComponent(p_mModel);

	// �y���M�����g�̃R���C�_�[
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->bMovable = true;
	p_mCollider->mColliderTag = ColliderKind::ColTag_Penguin;

	AddComponent(p_mCollider);

	// �ړ��R���|�[�l���g
	p_mMoveCom = new Com_CharacterMove();
	// �W�����v�ƃq�b�v�C���p�N�g�̃R���|�[�l���g
	p_mJumpCom = new Com_Jump();
	// �d�̓R���|�[�l���g
	p_mGravityCom = new Com_Gravity();
	// �����R���|�[�l���g
	p_mFootCom = new Com_Foot();
	// �e�R���|�[�l���g
	p_mShadowCom = new Com_Shadow();
	
	// �������(,)�ŕ���
	istringstream iss(Line);
	string word;
	std::vector<string> sv;
	while (getline(iss, word, ','))
	{
		sv.emplace_back(word);
	}

	if (sv.size() == PenguinStatuNum)
	{
		// �ړ����x
		p_mMoveCom->SetMoveSpeed(stof(sv[0]));
		// �󒆂ł̈ړ����x
		fAirMoveSpeed = stof(sv[1]);
		// �W�����v��
		p_mJumpCom->SetJumpPower(stof(sv[2]));
		// �q�b�v�h���b�v�̗������x
		p_mJumpCom->SetDropPower(stof(sv[3]));
		// �q�b�v�h���b�v�̏����x
		p_mJumpCom->SetDropInitialSpeed(stof(sv[4]));
		p_mJumpCom->SetGravityCom(p_mGravityCom);
		// �v���C���[�̑��̍���
		p_mFootCom->SetFootHeight(stof(sv[5]));
		p_mFootCom->SetGravityCom(p_mGravityCom);
		p_mFootCom->SetJumpCom(p_mJumpCom);
		// �J�����̃X�s�[�h
		fCamSpeed = stof(sv[6]);
		// �R���C�_�[�̒��S
		p_mCollider->SetCenter(stof(sv[7]), stof(sv[8]), stof(sv[9]));
		// �R���C�_�[�̃T�C�Y
		p_mCollider->SetSize(stof(sv[10]), stof(sv[11]), stof(sv[12]));
		// �q�b�v�C���p�N�g�͈̔�
		p_mJumpCom->SetImpactRange(stof(sv[13]));
		// ���߂��̋���
		this->fDamagedPower = stof(sv[14]);
	}
	

	// �R���|�[�l���g�̒ǉ�
	AddComponent(p_mMoveCom);
	AddComponent(p_mJumpCom);
	AddComponent(p_mGravityCom);
	AddComponent(p_mFootCom);
	AddComponent(p_mShadowCom);
	p_mShadowCom->SetSize(3.0f, 3.0f);	
}

OBJ_Penguin::OBJ_Penguin()
{
	// �V�F�[�_�[
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// ���f��
	p_mModel = new Com_Model();
	p_mModel->SetModelData("Penguin");
	p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// �y���M�����g�̃R���C�_�[
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;
	p_mCollider->mColliderTag = ColliderKind::ColTag_Penguin;

	AddComponent(p_mCollider);

	// �ړ��R���|�[�l���g
	p_mMoveCom = new Com_CharacterMove();
	p_mMoveCom->SetMoveSpeed(15.0f);

	AddComponent(p_mMoveCom);

	// �W�����v�R���|�[�l���g
	p_mJumpCom = new Com_Jump();
	p_mJumpCom->SetJumpPower(20.0f);

	AddComponent(p_mJumpCom);

	// �d�̓R���|�[�l���g
	p_mGravityCom = new Com_Gravity();
	p_mJumpCom->SetGravityCom(p_mGravityCom);

	AddComponent(p_mGravityCom);

	// �����R���|�[�l���g
	p_mFootCom = new Com_Foot();
	p_mFootCom->SetGravityCom(p_mGravityCom);
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

	p_mGravityCom->SetGround(false);

	OBJ_Shadow* myShadow = new OBJ_Shadow("PenguinShadow");
	myShadow->SetTarget(this);
	myShadow->Init();
	myShadow->Start();
	GetScene()->AddGameObject(myShadow);
}

void OBJ_Penguin::Update()
{
	GameObject::Update();

	// ���͎擾
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

	switch (mState)
	{
		// �������
	case PenguinState::Walk:
		p_mModel->PlayAnimation("Walk");
		p_mMoveCom->Move(mMoveVelocity.x, mMoveVelocity.y);
		// �W�����v
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetGround() ||
			Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetGround())
		{
			p_mJumpCom->SetJumpFlg(true);
			p_mModel->PlayAnimation("ToJump");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeJump;
		}
		break;
	case PenguinState::BeforeJump:
		p_mFootCom->bEnable = false;
		p_mMoveCom->Move(mMoveVelocity.x * fAirMoveSpeed, mMoveVelocity.y *fAirMoveSpeed);
		if (p_mModel->GetIsRotLastKey())
		{
			p_mJumpCom->SetJumpFlg(false);
			p_mModel->PlayAnimation("Jump");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::Jump;
		}
		break;
	case PenguinState::Jump:
		p_mFootCom->bEnable = true;
		p_mMoveCom->Move(mMoveVelocity.x * fAirMoveSpeed, mMoveVelocity.y * fAirMoveSpeed);
		// �q�b�v�C���p�N�g
		if (Controller_Input::GetRightTriggerSimple(0) == KEYSTATE::KEY_WHILE_DOWN ||
			Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_WHILE_DOWN)
		{
			// �q�b�v�C���p�N�g�̗\��
			p_mModel->PlayAnimation("HipDrop");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::BeforeHipDrop;
			p_mGravityCom->bEnable = false;
		}
		break;
	case PenguinState::BeforeHipDrop:
		// �A�j���[�V�����̍Ō�̃L�[�܂őҋ@
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
		if (p_mGravityCom->GetGround())
		{
			p_mModel->PlayAnimation("AfterHipDrop");
			p_mModel->SetCurrentKeyFrame(0);
			mState = PenguinState::AfterHipDrop;
		}
		break;
	case PenguinState::AfterHipDrop:
		if (p_mModel->GetIsRotLastKey())
		{
			p_mModel->SetCurrentKeyFrame(0);
			p_mModel->PlayAnimation("Walk");
			mState = PenguinState::Walk;
		}
		break;
	case PenguinState::Damage:
	{
		// �_���[�WVelocity�̒������擾
		float length = Math::GetLength(mDamageVelocity);

		cout << length << endl;
		// ���e���������Z����Αҋ@��ԂɈڍs
		if (length < fDamagePermission)
		{
			mState = PenguinState::Walk;
			p_mModel->SetCurrentKeyFrame(0);
			break;
		}

		// �u���[�L���|����
		mDamageVelocity *= fBlake;

		p_mTransform->Translate(mDamageVelocity);
	}
		break;
	case PenguinState::HipDropOnAzarashi:
		break;
	}
	// �A���O������
	// ���̊p�x
	p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Controller_Input::GetRightStick(0).x * fCamSpeed));
	// ����
	p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() - Controller_Input::GetRightStick(0).y);

	if (Input::GetIsCenter())
	{
		p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Input::GetCursorMove().x * fMouseCameraSpeed));
		p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() + Input::GetCursorMove().y);
	}

	// Velocity���Z�b�g
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
				mState = PenguinState::Walk;
			}

			p_mShadowCom->SetShadowHeight(p_mTransform->mPosition.y);
		}
	}
	if (_obj->mColType == Collider::ColliderForm::Sphere)
	{
		Com_SphereCollider* col = _obj->GetComponent<Com_SphereCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Azarashi)
		{
			if (mState != PenguinState::BeforeHipDrop &&
				mState != PenguinState::HipDrop)
			{
				Vector3 Direction = Math::GetVector(p_mTransform->mPosition, _obj->p_mTransform->mPosition);
				Direction = Math::Normalize(-Direction);
				// �_���[�W��̂��߂����v�Z
				mDamageVelocity = fDamagedPower * Direction;
				mDamageVelocity.y = 0;

				mState = PenguinState::Damage;
				p_mJumpCom->SetJumpFlg(false);
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
}
