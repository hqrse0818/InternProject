#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../Scene/Scene.h"

class OBJ_IceCalc :public GameObject
{
private:
	int iIceRemain = 0;

public:
	OBJ_IceCalc();
	void Update();
};