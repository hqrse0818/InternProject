#include "OBJ_Score.h"

#include <iostream>

using namespace std;

int OBJ_Score::s_iScore = 0;



OBJ_Score::OBJ_Score()
{
	
}

void OBJ_Score::CalcScore(int _val)
{
	s_iScore += _val;

	cout << "加算値 : " << _val << endl;
	cout << "スコア : " << s_iScore << endl;
}