#pragma once
#pragma once
#include "../GameObject/GameObject.h"

// �X�R�A�v�Z�p�I�u�W�F�N�g

class OBJ_Score :public GameObject
{
private:
	static int s_iScore;

public:
	OBJ_Score();

	static void CalcScore(int _val);
	static int GetScore()
	{
		return s_iScore;
	}
};