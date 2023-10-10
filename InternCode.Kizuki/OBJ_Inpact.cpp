#include "OBJ_Inpact.h"
#include "../System/Time.h"

OBJ_Inpact::OBJ_Inpact()
{
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 1.0f; //�͈�
	fCnt = 0.0f;

	AddComponent(p_mColliderCom);
}

OBJ_Inpact::OBJ_Inpact(const char* _name) :OBJ_Inpact()
{
	sObjectName = _name;
}

void OBJ_Inpact::Update()
{
	GameObject::Update();

	// �X�P�[���ɉ��Z����l
	fCnt += Time->GetDeltaTime() / 2;

	// ���C�t�^�C��������
	fLifeTime -= Time->GetDeltaTime();
	if (fLifeTime < 0)
	{
		bDestroy = true;
		return;
	}
	
	// �ǂ��ɂ����Ă������錴��
	// p_mColliderCom->fRadius += p_mColliderCom->fRadius + fCnt;
	// �C����(���a���J�E���g���傫�����Ă���)
	// �Ռ��g�̂悤�Ȏ���ɍL���銴�����ł���
	p_mColliderCom->fRadius += fCnt;
}
