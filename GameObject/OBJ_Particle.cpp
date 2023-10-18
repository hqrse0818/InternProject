#include "OBJ_Particle.h"
#include "../System/HighGetRand.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;

OBJ_Particle::OBJ_Particle()
{
	// シェーダー
	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_MODEL);
	Shader_buf->p_mPS->Load("shader\\PS_HitLine.cso");
	AddComponent(Shader_buf);

	// モデル
	p_mBil = new Com_Billboard();
	//Bill_buf->Load("asset\\model\\WhiteBlock.obj");
	AddComponent(p_mBil);

	// 斜方投射
	p_mTousyaBuf = new Com_DiagonalProjection();
	AddComponent(p_mTousyaBuf);

	fLifetime = HighRandom->fGetRand(4.0f, 6.0f, 2);
}

OBJ_Particle::OBJ_Particle(const char* _name)
	: OBJ_Particle()
{
	sObjectName = _name;
}

void OBJ_Particle::Init()
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

void OBJ_Particle::Update()
{
	GameObject::Update();

	fLifetime -= Time->GetDeltaTime();

	if (fLifetime < 0.0f)
	{
		bDestroy = true;
	}
}
