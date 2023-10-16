#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Number.h"
#include "../InternCodeAdachi/OBJ_AzarashiManager.h"

//アザラシの残機
class OBJ_AzarashiRemain :public OBJ_Number
{
private:
	OBJ_Number* Nums[3];
	int iRemainNum = 0;

public:
	OBJ_AzarashiRemain();
	void Start();
	void Update();
};