#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_CustomSprite.h"
#include "../Component/Com_Shader.h"

using namespace DirectX::SimpleMath;

class OBJ_Number :public GameObject
{
protected:
	int iNum = 0;

	Vector4 mUV = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	float fCurrentx;
	float fCurrenty;
	float fCurrentz;
	float fCurrentw;

	Com_CustomSprite* p_mSprite = nullptr;

public:
	OBJ_Number();
	void Update();

	void SetNum(int _num)
	{
		iNum = _num;
	}

	int GetNum()
	{
		return iNum;
	}
};