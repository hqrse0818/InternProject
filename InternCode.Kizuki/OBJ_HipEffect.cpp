#include "OBJ_HipEffect.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Particle.h"
#include "../Scene/Scene.h"
#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;

OBJ_HipEffect::OBJ_HipEffect()
{
	mKind = Particle;
	iCreateNum = 20;

	p_mTexture = new ShaderResourceView;
	p_mTexture->Create("asset/texture/hip.png");
}

OBJ_HipEffect::OBJ_HipEffect(std::string _name)
	:OBJ_HipEffect()
{
	sObjectName = _name;
}

void OBJ_HipEffect::Init()
{
	GameObject::Init();
}

void OBJ_HipEffect::Update()
{
	GameObject::Update();

	if (bEffectflg)
	{
		Create();
	}
}

void OBJ_HipEffect::Uninit()
{
	GameObject::Uninit();
	p_mTexture->Uninit();
	delete p_mTexture;
}

void OBJ_HipEffect::TexCreate(const char* _name)
{
	p_mTexture->Create(_name);
}

void OBJ_HipEffect::Create()
{
	for (int i = 0; i < iCreateNum; i++)
	{
		OBJ_Particle* Particle = new OBJ_Particle("no");
		Particle->p_mTransform->mPosition.x = Target->p_mTransform->mPosition.x + HighRand::fGetRand(-6, 6, 2);
		Particle->p_mTransform->mPosition.y = Target->p_mTransform->mPosition.y + 1.0f;
		Particle->p_mTransform->mPosition.z = Target->p_mTransform->mPosition.z + HighRand::fGetRand(-6, 6, 2);
		Particle->Init();
		Particle->SetTexture(p_mTexture->GetSRV());
		Particle->p_mTransform->mScale = DirectX::SimpleMath::Vector3(2.0, 2.0, 2.0);
		Particle->GetBil()->SetUVCut(4, 1);
		Particle->GetBil()->SetCurrent(100);

		//ŽÎ•û“ŠŽËÝ’è
		Particle->p_mTousyaBuf->SetGravity(-1.0f);
		//Particle->p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 0.0f, 0.0f)); //‰‘¬
		//Particle->p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //“ŠŽËŠp

		Vector3 angle; //Šp“x
		angle.x = 0;
		angle.y = 0;
		angle.z = 0;

		Particle->p_mTousyaBuf->SetThrowAngle(angle);

		Vector3 speed; //”ÍˆÍ
		speed.x = 0;
		speed.y = HighRand::fGetRand(1, 3, 2) * 0.01;
		speed.z = 0;

		Particle->p_mTousyaBuf->SetInitSpeed(speed);

		Particle->SetLifeTime(0.3f);

		s_p_mScene->AddGameObject(Particle);
	}
}
