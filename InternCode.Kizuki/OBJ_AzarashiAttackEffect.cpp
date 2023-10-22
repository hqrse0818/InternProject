#include "OBJ_AzarashiAttackEffect.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Particle.h"
#include "../Scene/Scene.h"
#include "../System/HighGetRand.h"

OBJ_AzarashiAttackEffect::OBJ_AzarashiAttackEffect()
{
	mKind = Particle;
	iCreateNum = 2;

	p_mTexture = new ShaderResourceView;
	p_mTexture->Create("asset/texture/azarashi_kougeki.png");
}

OBJ_AzarashiAttackEffect::OBJ_AzarashiAttackEffect(std::string _name)
	:OBJ_AzarashiAttackEffect()
{
	sObjectName = _name;
}

void OBJ_AzarashiAttackEffect::Init()
{
	GameObject::Init();
}

void OBJ_AzarashiAttackEffect::Update()
{
	GameObject::Init();
}

void OBJ_AzarashiAttackEffect::Uninit()
{
	GameObject::Uninit();
	p_mTexture->Uninit();
	delete p_mTexture;
}

void OBJ_AzarashiAttackEffect::TexCreate(const char* _name)
{
	p_mTexture->Create(_name);
}

void OBJ_AzarashiAttackEffect::Create()
{
	for (int i = 0; i < iCreateNum; i++)
	{
		OBJ_Particle* Particle = new OBJ_Particle("no");
		//Particle->p_mTransform->mPosition = Target->p_mTransform->mPosition;
		Particle->Init();
		Particle->SetTexture(p_mTexture->GetSRV());
		Particle->p_mTransform->mPosition = this->p_mTransform->mPosition;

		//�Ε����ːݒ�
		Particle->p_mTousyaBuf->SetGravity(0.1f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //����
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //���ˊp

		Vector3 angle; //�p�x
		angle.x = HighRand::fGetRand(-70, -30, 3);
		angle.y = 0;
		angle.z = HighRand::fGetRand(-70, -30, 3);

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //�͈�
		speed.x = HighRand::fGetRand(-6, 6, 2);
		speed.y = HighRand::fGetRand(-100, -1, 3) * 0.0001f;
		speed.z = HighRand::fGetRand(-6, 6, 2);

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(HighRand::fGetRand(2, 5, 3) * 0.1f);

		s_p_mScene->AddGameObject(Particle);
	}
}
