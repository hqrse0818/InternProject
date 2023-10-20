#pragma once
#include "../Component/Com_Billboard.h"
#include "../GameObject/GameObject.h"
#include "../DirectX/ShaderResourceView.h"

class OBJ_HipEffect :public GameObject
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
	OBJ_HipEffect();
	OBJ_HipEffect(std::string _name);
	void Init();
	void Update();
	void Uninit();
	void TexCreate(const char* _name);
	void SetEffectFlg(bool _flg)
	{
		bEffectflg = _flg;
	}

	void SetPlayer(GameObject* _object)
	{
		Player = _object;
	}

	void Create();

protected:
	ShaderResourceView* p_mTexture;
	GameObject* Player;
	bool bEffectflg = false;
};