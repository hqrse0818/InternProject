#include "OBJ_AzarashiDeadEffect.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Particle.h"
#include "../Scene/Scene.h"
#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;

OBJ_AzarashiDeadEffect::OBJ_AzarashiDeadEffect()
{
	mKind = Particle;
	iCreateNum = 2;

	p_mTexture = new ShaderResourceView;
	p_mTexture->Create("asset/texture/azarashi_sibou.png");
}

OBJ_AzarashiDeadEffect::OBJ_AzarashiDeadEffect(std::string _name)
	:OBJ_AzarashiDeadEffect()
{
	sObjectName = _name;
}

void OBJ_AzarashiDeadEffect::Init()
{
	GameObject::Init();
}

void OBJ_AzarashiDeadEffect::Update()
{
	GameObject::Update();

	if (bEffectflg)
	{
		Create();
	}
}

void OBJ_AzarashiDeadEffect::Uninit()
{
	GameObject::Uninit();
	p_mTexture->Uninit();
	delete p_mTexture;
}

void OBJ_AzarashiDeadEffect::TexCreate(const char* _name)
{
	p_mTexture->Create(_name);
}

void OBJ_AzarashiDeadEffect::Create()
{
	for (int i = 0; i < iCreateNum; i++)
	{
		OBJ_Particle* Particle = new OBJ_Particle("no");
		//Particle->p_mTransform->mPosition = Target->p_mTransform->mPosition;
		Particle->Init();
		Particle->SetTexture(p_mTexture->GetSRV());
		Particle->p_mTransform->mPosition = this->p_mTransform->mPosition;
		Particle->p_mTransform->mScale = DirectX::SimpleMath::Vector3(9.0, 9.0, 9.0);
		Particle->GetBil()->SetUVCut(2, 1);
		Particle->GetBil()->SetCurrent(HighRand::GetRand(1, 100));

		//�Ε����ːݒ�
		Particle->p_mTousyaBuf->SetGravity(-0.5f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //����
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //���ˊp

		Vector3 angle; //�p�x
		angle.x = 0;
		angle.y = HighRand::fGetRand(0, 90, 3);
		angle.z = 0;

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //�͈�
		speed.x = HighRand::fGetRand(-1, 1, 2);
		speed.y = HighRand::fGetRand(1, 3, 3) * 0.1;
		speed.z = HighRand::fGetRand(-1, 1, 2);

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(HighRand::fGetRand(10, 12, 3) * 0.1f);

		s_p_mScene->AddGameObject(Particle);
	}
}
