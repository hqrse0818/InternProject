#include "OBJ_Emitter.h"
#include "../ComponentHeader.h"
#include "../System/Time.h"
//#include "../BaseObject.h"
#include "../Scene/Scene.h"
#include "OBJ_Particle.h"

OBJ_Emitter::OBJ_Emitter()
{
	mKind = Particle;
	iCreateNum = 10;
	Com_BoxCollider* Collider_buf = new Com_BoxCollider();
	Collider_buf->SetSize(2.0f, 2.0f, 2.0f);
	AddComponent(Collider_buf);

	p_mTexture = new ShaderResourceView;
}

OBJ_Emitter::OBJ_Emitter(std::string _name)
:OBJ_Emitter()
{
	sObjectName = _name;
}

void OBJ_Emitter::Init()
{
	GameObject::Init();
}

void OBJ_Emitter::Update()
{
	GameObject::Update();

	if (Input::GetKeyState(KEYCODE_MOUSE_LEFT) == KEYSTATE::KEY_DOWN)
	{
		Create();
	}

	//true‚ÅCreate
	if (bCreate)
	{
		Create();
	}
}

void OBJ_Emitter::TexCreate(const char* _name)
{
	p_mTexture->Create(_name);
}

void OBJ_Emitter::Create()
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
