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
protected:
	float fLifeTime = 0.0f; //���݂��鎞��

public:
	OBJ_Inpact();
	void Update();
};