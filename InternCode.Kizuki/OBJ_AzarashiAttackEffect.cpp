#include "OBJ_AzarashiAttackEffect.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Particle.h"
#include "../Scene/Scene.h"
#include "../System/HighGetRand.h"

OBJ_AzarashiAttackEffect::OBJ_AzarashiAttackEffect()
{
	mKind = Particle;
	iCreateNum = 3;

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
		Particle->p_mTransform->mScale = DirectX::SimpleMath::Vector3(3.0, 3.0, 3.0);

		//ŽÎ•û“ŠŽËÝ’è
		Particle->p_mTousyaBuf->SetGravity(-2.0f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //‰‘¬
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //“ŠŽËŠp

		Vector3 angle; //Šp“x
		angle.x = 0;
		angle.y = 0;
		angle.z = 0;

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //”ÍˆÍ
		speed.x = HighRand::fGetRand(-1, 1, 2);
		speed.y = HighRand::fGetRand(2, 4, 2) * 0.1;
		speed.z = HighRand::fGetRand(-1, 1, 2);

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(HighRand::fGetRand(2, 5, 3) * 0.1f);

		s_p_mScene->AddGameObject(Particle);
	}
}
