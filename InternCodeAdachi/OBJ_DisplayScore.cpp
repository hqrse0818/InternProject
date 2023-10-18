#include "OBJ_DisplayScore.h"

OBJ_DisplayScore::OBJ_DisplayScore()
{
	for (int i = 0; i < 6; i++)
	{
		Nums[i] = new OBJ_Number();
	}
}

OBJ_DisplayScore::OBJ_DisplayScore(const char* _name)
	: OBJ_DisplayScore()
{
	sObjectName = _name;
}

OBJ_DisplayScore::OBJ_DisplayScore(const char* _name, const char* _FileName)
	: OBJ_DisplayScore()
{
	sObjectName = _name;
}
