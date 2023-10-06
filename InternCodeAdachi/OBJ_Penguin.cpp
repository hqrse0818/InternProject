#include "OBJ_Penguin.h"
#include "Com_Foot.h"
#include "Com_Gravity.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"
#include "../System/Input.h"
#include "../Scene/Scene.h"
#include "Com_Jump.h"

using namespace DirectX::SimpleMath;

OBJ_Penguin::OBJ_Penguin()
{
	// �V�F�[�_�[
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_MODEL);
	p_mShader->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShader);

	// ���f��
	p_mModel = new Com_AssimpAnimation();
	p_mModel->LoadModel("asset\\model\\Penguin\\pengin_v4.fbx", 1.0f, true);
	//p_mModel->LoadModel("asset\\model\\Penguin\\pengin_rig_v1.fbx", 1.0f, true);
	//p_mModel->LoadAnimation("asset\\model\\Penguin\\pengin_anime_v1.fbx", "hand");
	//p_mModel->PlayAnimation("hand");
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
	Com_Foot* Foot_buf = new Com_Foot();
	Foot_buf->SetGravityCom(p_mGravityCom);
	Foot_buf->SetFootHeight(2.0f);
	Foot_buf->SetJumpCom(p_mJumpCom);
	AddComponent(Foot_buf);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

void OBJ_Penguin::Update()
{
	// �q�b�v�C���p�N�g
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && p_mJumpCom->GetIsJump())
	{
		if (!p_mJumpCom->GetIsDrop())
		{
			p_mJumpCom->SetJumpFlg(false);
			p_mJumpCom->SetDropFlg(true);
		}
	}
	// �W�����v
	if (Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN && p_mGravityCom->GetGround())
	{
		p_mJumpCom->SetJumpFlg(true);
	}

	// �n��ɂ���Ƃ��̓X�e�B�b�N�̒l�����̂܂ܔ��f
	if (p_mGravityCom->GetGround())
	{
		p_mMoveCom->MoveX(Controller_Input::GetLeftStick(0).x);
		p_mMoveCom->MoveZ(Controller_Input::GetLeftStick(0).y);
	}
	else
	{
		p_mMoveCom->MoveX(Controller_Input::GetLeftStick(0).x/ 5);
		p_mMoveCom->MoveZ(Controller_Input::GetLeftStick(0).y / 5);
	}
	
	// �A���O������
	// ���̊p�x
	p_mCameraCom->SetAngle(p_mCameraCom->GetAngle() + Controller_Input::GetRightStick(0).x);
	// ����
	p_mCameraCom->SetHeight(p_mCameraCom->GetHeight() + Controller_Input::GetRightStick(0).y);


	// �A�j���[�V�����̍X�V
	p_mModel->UpdateFrame();

	GameObject::Update();

}
