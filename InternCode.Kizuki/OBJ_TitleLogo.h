#pragma once
#include "../GameObject/GameObject.h"

class OBJ_TitleLogo :public GameObject
{
private:
	bool bReturn = false;
public:
	bool bRotate = false;

	OBJ_TitleLogo();

	void Update();
};