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

	DEBUG_LOG("���Z�l : " << _val);
	DEBUG_LOG("�X�R�A : " << s_iScore);
}