#include "OBJ_Penguin.h"

OBJ_Penguin::OBJ_Penguin()
{
	// �y���M���̑����p�R���C�_�[�I�u�W�F�N�g
	p_mFoot = new GameObject("PenguinFoot");
	// �y���M�����g�̃R���C�_�[
	p_mCollider = new Com_SphereCollider();
	p_mCollider->fRadius = 4.0f;
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);

	// �����p�R���C�_�[
	p_mCollider = new Com_SphereCollider();
	p_mCollider->SetCenter(0.0f, 0.0f, 0.0f);
	p_mCollider->fRadius = 0.5f;
	p_mCollider->bMovable = true;
	p_mFoot->AddComponent(p_mCollider);

	AddChild(p_mFoot);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

void OBJ_Penguin::Update()
{
	p_mFoot->p_mTransform->mPosition = p_mTransform->mPosition;

	GameObject::Update();
}
