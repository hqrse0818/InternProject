#pragma once
#include "../Component/Component.h"
#include "../Component/Com_Billboard.h"

class Com_Effect :public Component
{
private:
	Com_Billboard* p_mBil;

public:
	Com_Effect();

	void Init();
	void Update();
	void Draw();
};