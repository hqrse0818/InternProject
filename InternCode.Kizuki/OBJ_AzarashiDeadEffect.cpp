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
	iCreateNum = 10;

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
		Particle->p_mTransform->mPosition = Target->p_mTransform->mPosition;
		Particle->Init();
		Particle->SetTexture(p_mTexture->GetSRV());

		//ŽÎ•û“ŠŽËÝ’è
		Particle->p_mTousyaBuf->SetGravity(0.1f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //‰‘¬
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //“ŠŽËŠp

		Vector3 angle; //Šp“x
		angle.x = HighRand::fGetRand(-70, -30, 3);
		angle.y = 0;
		angle.z = HighRand::fGetRand(-70, -30, 3);

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //”ÍˆÍ
		speed.x = HighRand::fGetRand(-6, 6, 2);
		speed.y = HighRand::fGetRand(-100, -1, 3) * 0.0001f;
		speed.z = HighRand::fGetRand(-6, 6, 2);

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(HighRand::fGetRand(2, 5, 3) * 0.1f);

		s_p_mScene->AddGameObject(Particle);
	}
}
