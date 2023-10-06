#include "OBJ_Ice.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

OBJ_Ice::OBJ_Ice()
{
	myColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	// �V�F�[�_�[
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	//p_mShaderCom->p_mPS->Load(PS_MODEL);
	p_mShaderCom->p_mPS->Load("shader\\PS_IceState.cso");

	AddComponent(p_mShaderCom);

	// ���f��
	p_mModelCom = new Com_AssimpAnimation();
	p_mModelCom->LoadModel("asset\\model\\stage_v2.fbx", 1.0f, false);

	AddComponent(p_mModelCom);

	// �R���C�_�[
	p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(7.0f, 1.0f, 7.0f);
	p_mCollider->SetCenter(0.0f, 0.5f, 0.0f);
	p_mCollider->bCanStepOn = true;

	AddComponent(p_mCollider);
}

OBJ_Ice::OBJ_Ice(const char* _name)
	: OBJ_Ice()
{
	sObjectName = _name;
}

void OBJ_Ice::Init()
{
	p_mShaderCom->p_mPS->CreateBuffer(16);
}

void OBJ_Ice::Update()
{
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

	switch (iHP) 
	{
	case 1:
		bDestroy = true; //GameObject�N���X��Destroy()���g�����߂ɕK�v
		break;
	case 2:
		Shake();
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		Shake();
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		Shake();
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 5:
		myColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);

	GameObject Update();

	//�v�Z����
	HpCalc();

	//�e�X�g�i�{�^����������HP������j
	if (Input::GetKeyState(KEYCODE_1) == KEYSTATE::KEY_DOWN)
	{
		iHP--;
	}
}

//�A�U���V�̑ҋ@���Ԃɂ����HP������悤�ɂ���
void OBJ_Ice::HpCalc()
{

}

//���ꂪ�h��鏈��
void OBJ_Ice::Shake()
{
	// ����������_���ɗh�炷
	float shakeAmount = 0.1f; // �h��͈̔�
	float offsetX = RandomRange(-shakeAmount, shakeAmount);
	float offsetY = RandomRange(-shakeAmount, shakeAmount);
	float offsetZ = RandomRange(-shakeAmount, shakeAmount);

	// ���݂̈ʒu���擾���A�h�ꂽ�ʒu�ɐݒ肵�܂�
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + offsetX, currentPosition.y + offsetY, currentPosition.z + offsetZ);
}