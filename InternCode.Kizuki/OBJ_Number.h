#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Sprite.h"

using namespace DirectX::SimpleMath;

class OBJ_Number :public GameObject
{
private:
	int iNum = 0;

	Vector4 mUV = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	float fCurrentx;
	float fCurrenty;
	float fCurrentz;
	float fCurrentw;

	Com_Sprite* p_mSprite = nullptr;

public:
	OBJ_Number();
	void Update();
};