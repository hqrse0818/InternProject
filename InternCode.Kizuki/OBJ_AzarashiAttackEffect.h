#pragma once
#include "../ComponentHeader.h"
#include "../System/Time.h"
#include "../GameObject/OBJ_Particle.h"
#include "../Scene/Scene.h"
#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;

class OBJ_AzarashiAttackEffect :public GameObject
{
public:
	enum Kind
	{
		Particle,
	};

public:
	Kind mKind = Kind::Particle;
	int iCreateNum;

public:
	OBJ_AzarashiAttackEffect();
	OBJ_AzarashiAttackEffect(std::string _name);
	void Init();
	void Update();
	void Uninit();
	void TexCreate(const char* _name);

	/*void SetTarget(GameObject* _object)
	{
		Target = _object;
	}*/

	void Create();

protected:
	ShaderResourceView* p_mTexture;
	//GameObject* Target = nullptr;
	bool bEffectflg = false;
};