#include "OBJ_Score.h"
#include "../System/Time.h"
#include <iostream>
#include "../Debug.h"
#include "CSVLoad.h"

using namespace std;

int OBJ_Score::s_iScore = 0;
int OBJ_Score::s_iCurrentComCount = 0;
bool OBJ_Score::s_bNowCombo = false;
float OBJ_Score::s_fComAddPerCombo = 0.0f;
float OBJ_Score::s_fComCnt = 0.0f;
float OBJ_Score::s_fComReceptionTime = 0.0f;
float OBJ_Score::s_fCurrentAddVal = 0.0f;
float OBJ_Score::s_fMaxAddVal = 0.0f;



OBJ_Score::OBJ_Score()
{
	
}

OBJ_Score::OBJ_Score(const char* _name)
{
	sObjectName = _name;
}

OBJ_Score::OBJ_Score(const char* _name, const char* _FileName)
{
	sObjectName = _name;
	string sState = ReadDataFromCSV(_FileName, 1);
	vector<string> sv = SeparateString(sState, ',');

	// コンボ受付時間設定
	s_fComReceptionTime = stof(sv[0]);
	// 1コンボ当たりの加算率
	s_fComAddPerCombo = stof(sv[1]);
	// 最大加算率
	s_fMaxAddVal = stof(sv[2]);
}

void OBJ_Score::CalcScore(int _val)
{
	if (_val != 0 && _val != 50)
	{
		// コンボの経過時間リセット
		s_fComCnt = 0.0f;
		// コンボ数を加算
		s_iCurrentComCount++;
		// コンボ開始合図
		s_bNowCombo = true;
		// ボーナス点を加算
		s_iScore += (_val / 100) * s_fCurrentAddVal;

		// コンボの加算率を増加
		s_fCurrentAddVal += s_fComAddPerCombo;
	}
	s_iScore += _val;

	DEBUG_LOG("加算値 : " << _val);
	DEBUG_LOG("スコア : " << s_iScore);
}

void OBJ_Score::AddNoComboScore(int _val)
{
	s_iScore += _val;
}

void OBJ_Score::Update()
{
	GameObject::Update();

	if (s_bNowCombo)
	{
		s_fComCnt += Time->GetDeltaTime();
		if (s_fComCnt > s_fComReceptionTime)
		{
			ResetCombo();
		}
	}
	else
	{
		// コンボしていない時
		s_fComCnt = 0.0f;
		// 加算率のリセット
		s_fCurrentAddVal = 0.0f;
		// コンボ数のリセット
		s_iCurrentComCount = 0;
	}
}



void OBJ_Score::ResetCombo()
{
	// カウントをリセット
	s_fComCnt = 0.0f;
	// 加算率のリセット
	s_fCurrentAddVal = 0.0f;
	// コンボ数のリセット
	s_iCurrentComCount = 0;
	s_bNowCombo = false;
}
