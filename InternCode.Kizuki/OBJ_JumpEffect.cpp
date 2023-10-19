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
	p_mBil->SetTexture("asset/texture/start.png");
	AddComponent(p_mBil);

	//スプライト
	//Com_Sprite* Sprite_buf = new Com_Sprite();
	//Sprite_buf->SetTexture("asset/texture/start.png");
	//AddComponent(Sprite_buf);

	// 斜方投射
	p_mTousyaBuf = new Com_DiagonalProjection();
	AddComponent(p_mTousyaBuf);

	fLifetime = HighRandom->fGetRand(4.0f, 6.0f, 2);
}

OBJ_JumpEffect::OBJ_JumpEffect(const char* _name)
	:OBJ_JumpEffect()
{
	sObjectName = _name;
}

void OBJ_JumpEffect::Init()
{
	Vector3 angle;
	angle.x = HighRandom->fGetRand(-180, 180, 2);
	angle.y = HighRandom->fGetRand(-180, 180, 2);
	angle.z = HighRandom->fGetRand(-180, 180, 2);

	p_mTousyaBuf->SetThrowAngle(angle);

	Vector3 speed;
	speed.x = HighRandom->fGetRand(-2, 2, 2);
	speed.y = HighRandom->fGetRand(-2, 2, 2);
	speed.z = HighRandom->fGetRand(-2, 2, 2);

	p_mTousyaBuf->SetInitSpeed(speed);

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
