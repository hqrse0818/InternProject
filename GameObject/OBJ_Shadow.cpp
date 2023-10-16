#include "OBJ_Shadow.h"

OBJ_Shadow::OBJ_Shadow()
{
	p_mTarget = nullptr;

	p_mShaderCom = new Com_Shader;
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	p_mShaderCom->p_mPS->Load(PS_MODEL);
	AddComponent(p_mShaderCom);
	p_mShadowCom = new Com_Shadow();
	p_mShadowCom->SetSize(4.0f, 4.0f);
	AddComponent(p_mShadowCom);
	p_mColliderCom = new Com_BoxCollider();
	p_mColliderCom->SetCenter(0.0f, 0.0f, 0.0f);
	p_mColliderCom->SetSize(1.0f, 1.0f, 1.0f);
	p_mColliderCom->bMovable = true;
	AddComponent(p_mColliderCom);
	p_mTransform->mPosition.y = 1.0f;
}

OBJ_Shadow::OBJ_Shadow(const char* _name)
	:OBJ_Shadow()
{
	sObjectName = _name;
}

void OBJ_Shadow::Update()
{
	GameObject::Update();

	p_mTransform->mPosition.x = p_mTarget->p_mTransform->mPosition.x;
	p_mTransform->mPosition.z = p_mTarget->p_mTransform->mPosition.z;
}

void OBJ_Shadow::OnCollisionStay(GameObject* _obj)
{
	GameObject::OnCollisionStay(_obj);

	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice)
		{
			p_mTransform->mPosition.y = col->Getmax().y + p_mTransform->mScale.y / 2;
		}
	}
}

void OBJ_Shadow::SetTarget(GameObject* _target)
{
	p_mTarget = _target;
}