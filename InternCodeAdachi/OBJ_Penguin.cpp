#include "OBJ_Penguin.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/Input.h"
#include "../Scene/Scene.h"
#include "CSVLoad.h"

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
	//p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// �y���M�����g�̃R���C�_�[
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);

	// �ړ��R���|�[�l���g
	p_mMoveCom = new Com_CharacterMove();
	// �W�����v�ƃq�b�v�C���p�N�g�̃R���|�[�l���g
	p_mJumpCom = new Com_Jump();
	// �d�̓R���|�[�l���g
	p_mGravityCom = new Com_Gravity();
	// �����R���|�[�l���g
	p_mFootCom = new Com_Foot();
	
	// �������(,)�ŕ���
	istringstream iss(Line);
	string word;
	std::vector<string> sv;
	while (getline(iss, word, ','))
	{
		sv.emplace_back(word);
	}

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
	
	// �R���|�[�l���g�̒ǉ�
	AddComponent(p_mMoveCom);
	AddComponent(p_mJumpCom);
	AddComponent(p_mGravityCom);
	AddComponent(p_mFootCom);

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
}

void OBJ_Penguin::Update()
{
	GameObject::Update();

	p_mModel->PlayAnimation("Walk");

	// �q�b�v�C���p�N�g
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && p_mJumpCom->GetIsJump() ||
		Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_DOWN && p_mJumpCom->GetIsJump())
	{
		p_mJumpCom->SetJumpHeight();

		if (!p_mJumpCom->GetIsDrop())
		{
			p_mJumpCom->SetJumpFlg(false);
			p_mJumpCom->SetDropFlg(true);
		}
	}
	// �W�����v
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetGround() ||
		Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetGround())
	{
		p_mJumpCom->SetJumpFlg(true);
	}

	// �n��ɂ���Ƃ��̓X�e�B�b�N�̒l�����̂܂ܔ��f
	if (p_mGravityCom->GetGround())
	{
		if (Controller_Input::GetIsGamePadConnect(0))
		{
			p_mMoveCom->MoveX(Controller_Input::GetLeftStick(0).x);
			p_mMoveCom->MoveZ(Controller_Input::GetLeftStick(0).y);
		}
		else
		{
			if (Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveZ(1.0f);
			}
			if (Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveZ(-1.0f);
			}
			if (Input::GetKeyState(KEYCODE_D) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveX(1.0f);
			}
			if (Input::GetKeyState(KEYCODE_A) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveX(-1.0f);
			}
		}
	}
	else
	{
		if (Controller_Input::GetIsGamePadConnect(0))
		{
			p_mMoveCom->MoveX(Controller_Input::GetLeftStick(0).x * fAirMoveSpeed);
			p_mMoveCom->MoveZ(Controller_Input::GetLeftStick(0).y * fAirMoveSpeed);
		}
		else
		{
			if (Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveZ(fAirMoveSpeed);
			}
			if (Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveZ(-fAirMoveSpeed);
			}
			if (Input::GetKeyState(KEYCODE_D) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveX(fAirMoveSpeed);
			}
			if (Input::GetKeyState(KEYCODE_A) == KEYSTATE::KEY_WHILE_DOWN)
			{
				p_mMoveCom->MoveX(-fAirMoveSpeed);
			}
		}
	}
	
	// �A���O������
	// ���̊p�x
	p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Controller_Input::GetRightStick(0).x * fCamSpeed));
	p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + (Input::GetCursorMove().x * fCamSpeed));
	// ����
	p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() - Controller_Input::GetRightStick(0).y);
	p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() + Input::GetCursorMove().y);


	// �A�j���[�V�����̍X�V
	p_mModel->UpdateFrame(1);
}
