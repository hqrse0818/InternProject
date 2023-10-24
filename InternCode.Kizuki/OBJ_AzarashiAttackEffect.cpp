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
		Particle->p_mTransform->mPosition.x = this->p_mTransform->mPosition.x + HighRand::fGetRand(-3, 3, 2);
		Particle->p_mTransform->mPosition.y = this->p_mTransform->mPosition.y;
		Particle->p_mTransform->mPosition.z = this->p_mTransform->mPosition.z + HighRand::fGetRand(-3, 3, 2);
		Particle->p_mTransform->mScale = DirectX::SimpleMath::Vector3(4.0, 4.0, 4.0);
		Particle->GetBil()->SetUVCut(3, 1);
		Particle->GetBil()->SetCurrent(HighRand::GetRand(1, 100));

		//ŽÎ•û“ŠŽËÝ’è
		Particle->p_mTousyaBuf->SetGravity(0.0f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //‰‘¬
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //“ŠŽËŠp

		Vector3 angle; //Šp“x
		angle.x = HighRand::fGetRand(-1, 1, 2);
		angle.y = 0;
		angle.z = HighRand::fGetRand(-1, 1, 2);

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //”ÍˆÍ
		speed.x = 0;
		speed.y = HighRand::fGetRand(2, 4, 2) * 0.1;
		speed.z = 0;

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(0.4);

		s_p_mScene->AddGameObject(Particle);
	}
}
