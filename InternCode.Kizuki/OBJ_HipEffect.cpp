#include "OBJ_HipEffect.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../Scene/Scene.h"
#include "../GameObject/OBJ_Particle.h"

OBJ_HipEffect::OBJ_HipEffect()
{
	mKind = Particle;
	iCreateNum = 10;

	p_mTexture = new ShaderResourceView;
	p_mTexture->Create("asset/texture/start.png");
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

	if (Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_DOWN)
	{
		Create();
	}

	if (bCreate)
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
		Particle->p_mTransform->mPosition = p_mTransform->mPosition;
		Particle->Init();
		Particle->SetTexture(p_mTexture->GetSRV());
		s_p_mScene->AddGameObject(Particle);
	}
}
