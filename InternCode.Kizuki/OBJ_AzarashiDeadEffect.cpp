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
	iCreateNum = 1;

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
		Particle->p_mTransform->mPosition.x = this->p_mTransform->mPosition.x + 2.0f;
		Particle->p_mTransform->mPosition.y = this->p_mTransform->mPosition.y + 15.0f;
		Particle->p_mTransform->mPosition.z = this->p_mTransform->mPosition.z + 2.0f;
		Particle->p_mTransform->mScale = DirectX::SimpleMath::Vector3(4.0, 4.0, 4.0);
		Particle->GetBil()->SetUVCut(2, 1);
		Particle->GetBil()->SetCurrent(HighRand::GetRand(1, 100));

		//ŽÎ•û“ŠŽËÝ’è
		Particle->p_mTousyaBuf->SetGravity(0.0f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //‰‘¬
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //“ŠŽËŠp

		Vector3 angle; //Šp“x
		angle.x = 0;
		angle.y = 0;
		angle.z = 0;

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //”ÍˆÍ
		speed.x = 0;
		speed.y = 0;
		speed.z = 0;

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(HighRand::fGetRand(7, 10, 3) * 0.1f);

		s_p_mScene->AddGameObject(Particle);
	}
}
