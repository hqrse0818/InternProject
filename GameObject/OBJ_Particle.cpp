#include "OBJ_Particle.h"
#include "../System/HighGetRand.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;

OBJ_Particle::OBJ_Particle()
{
	// シェーダー
	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	AddComponent(Shader_buf);

	// モデル
	p_mBil = new Com_EffectBillboard();
	p_mBil->SetUVCut(4, 1); //UV分割数
	p_mBil->SetCurrent(HighRand::GetRand(1,100)); //分割した後どれだけ回すか
	AddComponent(p_mBil);

	// 斜方投射
	p_mTousyaBuf = new Com_DiagonalProjection();
	p_mTousyaBuf->SetGravity(0.0f);
	//p_mTousyaBuf->SetInitSpeed(Vector3(0.0f, 1.0f, 0.0f)); //初速
	//p_mTousyaBuf->SetThrowAngle(Vector3(-100.0f, 0.0f, -100.0f)); //投射角
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
	/*Vector3 angle;
	angle.x = HighRandom->fGetRand(-180, 180, 2);
	angle.y = HighRandom->fGetRand(-180, 180, 2);
	angle.z = HighRandom->fGetRand(-180, 180, 2);

	p_mTousyaBuf->SetThrowAngle(angle);

	Vector3 speed;
	speed.x = HighRandom->fGetRand(-2, 2, 2);
	speed.y = HighRandom->fGetRand(-2, 2, 2);
	speed.z = HighRandom->fGetRand(-2, 2, 2);

	p_mTousyaBuf->SetInitSpeed(speed);*/

	GameObject::Init();
}

void OBJ_Particle::Update()
{
	GameObject::Update();

	fLifetime -= Time->GetDeltaTime();
	fCount += Time->GetDeltaTime();

	if (fLifetime < 0.0f)
	{
		bDestroy = true;
	}

	if (fCount > 0.5f)
	{
		p_mBil->SetCurrent(p_mBil->GetCurrent() + 1);
		fCount = 0.0f;
	}
}
