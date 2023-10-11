#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_CustomSprite.h"

class OBJ_TitleTutorial :public GameObject
{
private:
	Com_Sprite* p_mSprite;

public:
	OBJ_TitleTutorial();
	void Init();
};