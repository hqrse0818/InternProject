#include "OBJ_Ice.h"
#include "../System/Input.h"
#include "../System/Time.h"

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
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("Ice_PatA");

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

	//���̈ʒu��ۑ�
	originalPosition = p_mTransform->mPosition;

	GameObject::Init();
}

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
void OBJ_Ice::Update()
{
	switch (iHP)
	{
	case 1:
		bDestroy = true; //GameObject�N���X��Destroy()���g�����߂ɕK�v
		break;
	case 2:
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		Shake();
		break;
	case 3:
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 4:
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 5:
		myColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);

	GameObject::Update();

	if (Input::GetKeyState(KEYCODE_1) == KEYSTATE::KEY_DOWN)
	{
		iHP--;
		fElapsedTime = 0.0f;
	}
}

//�A�U���V�̑ҋ@���Ԃɂ����HP������悤�ɂ���
void OBJ_Ice::HpCalc()
{

}

//���ꂪ�h��鏈��
void OBJ_Ice::Shake()
{
	//�^�C�}�[���X�V
	fElapsedTime += Time->GetDeltaTime();

	//�h��鎞�Ԃ��I��������h����~
	if (fElapsedTime >= fShakeTime)
	{
		//�h�ꂪ�I�������猳�̈ʒu�ɖ߂�
		p_mTransform->mPosition = originalPosition;
		return;
	}

	// ����������_���ɗh�炷
	float fPowerX = RandomRange(-fShakePower, fShakePower);
	float fPowerY = RandomRange(-fShakePower, fShakePower);
	float fPowerZ = RandomRange(-fShakePower, fShakePower);

	// ���݂̈ʒu���擾���A�h�ꂽ�ʒu�ɐݒ�
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + fPowerX, currentPosition.y + fPowerY, currentPosition.z + fPowerZ);
}
