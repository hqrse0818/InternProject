#include "OBJ_JumpEffect.h"
#include "../System/HighGetRand.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;

OBJ_JumpEffect::OBJ_JumpEffect()
{
	// シェーダー
	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	AddComponent(Shader_buf);

	// モデル
	p_mBil = new Com_Billboard();
	AddComponent(p_mBil);
}

OBJ_JumpEffect::OBJ_JumpEffect(const char* _name)
	:OBJ_JumpEffect()
{
	sObjectName = _name;
}

void OBJ_JumpEffect::Init()
{
	GameObject::Init();
}

void OBJ_JumpEffect::Update()
{
	GameObject::Update();

	fLifetime -= Time->GetDeltaTime();

	if (fLifetime < 0.0f)
	{
		bDestroy = true;
	}
}
