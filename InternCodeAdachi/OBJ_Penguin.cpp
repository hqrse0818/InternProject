#include "OBJ_Penguin.h"
#include "Com_Foot.h"
#include "Com_Gravity.h"
#include "../Component/Com_SphereCollider.h"
#include "../Component/Com_BoxCollider.h"

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
	p_mModel->SetUseMaterial(false);

	AddComponent(p_mModel);

	// �y���M�����g�̃R���C�_�[
	Com_BoxCollider* p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(6.0f, 8.0f, 6.0f);
	p_mCollider->SetCenter(0.0f, 4.0f, 0.0f);
	p_mCollider->bMovable = true;

	AddComponent(p_mCollider);

	// �d�̓R���|�[�l���g
	Com_Gravity* Gravity_buf = new Com_Gravity();

	AddComponent(Gravity_buf);


	//// �y���M���̑����p�I�u�W�F�N�g
	//p_mFoot = new GameObject("PenguinFoot");
	//// �����p�R���C�_�[
	//Com_BoxCollider* p_mFootCollider = new Com_BoxCollider();
	//p_mFootCollider->SetCenter(0.0f, -0.2f, 0.0f);
	//p_mFootCollider->SetSize(3.0f, 0.2f, 3.0f);
	//p_mFootCollider->bMovable = true;

	//p_mFoot->AddComponent(p_mFootCollider);

	Com_Foot* Foot_buf = new Com_Foot();
	Foot_buf->SetGravityCom(Gravity_buf);
	Foot_buf->SetFootHeight(0.5f);
	AddComponent(Foot_buf);

	//AddChild(p_mFoot);
}

OBJ_Penguin::OBJ_Penguin(const char* _name)
	: OBJ_Penguin()
{
	sObjectName = _name;
}

void OBJ_Penguin::Update()
{
	//p_mFoot->p_mTransform->mPosition = p_mTransform->mPosition;

	GameObject::Update();
}
