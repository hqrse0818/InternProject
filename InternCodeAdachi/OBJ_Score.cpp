#include "OBJ_Score.h"

#include <iostream>
#include "../Debug.h"

using namespace std;

int OBJ_Score::s_iScore = 0;



OBJ_Score::OBJ_Score()
{
	
}

void OBJ_Score::CalcScore(int _val)
{
	s_iScore += _val;

	DEBUG_LOG("加算値 : " << _val);
	DEBUG_LOG("スコア : " << s_iScore);
}