#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"

//Inpact�̃I�u�W�F�N�g������ăX�t�B�A�R���C�_�[������
//�����o�ϐ���lifetime�ƃX�t�B�A�R���C�_�[����������
//update����lifetime�����炷�悤�ɂ���
//�X�t�B�A�R���C�_�[new
//���[�o�u���ɂ���
//fradius�Ŕ��a����������
//SetCenter�ݒ�
//radius

class OBJ_Inpact :public GameObject
{
private:
	//�R���C�_�[�R���|�[�l���g
	Com_SphereCollider* p_mColliderCom = nullptr;
	float fLifeTime = 1.0f; //���݂��鎞��
	float fScaleSpeed = 0.0f;	// �g�呬�x

public:
	OBJ_Inpact();
	OBJ_Inpact(const char* _name);

	float SetLifeTime(float _val)
	{
		fLifeTime = _val;
	}

	void Update();

	Com_SphereCollider* GetColliderCom() 
	{
		return p_mColliderCom;
	}

	void SetScaleSpeed(float _val)
	{
		fScaleSpeed = _val;
	}
};