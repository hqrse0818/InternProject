#pragma once
#include "../Component/Com_Billboard.h"
#include "../GameObject/GameObject.h"
#include "../DirectX/ShaderResourceView.h"

class OBJ_AzarashiDeadEffect :public GameObject
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
	OBJ_AzarashiDeadEffect();
	OBJ_AzarashiDeadEffect(std::string _name);
	void Init();
	void Update();
	void Uninit();
	void TexCreate(const char* _name);

	void SetTarget(GameObject* _object)
	{
		Target = _object;
	}

	void Create();

protected:
	ShaderResourceView* p_mTexture;
	GameObject* Target = nullptr;
	bool bEffectflg = false;
};