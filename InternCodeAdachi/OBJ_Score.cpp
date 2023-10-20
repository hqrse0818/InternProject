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

	// �R���{��t���Ԑݒ�
	s_fComReceptionTime = stof(sv[0]);
	// 1�R���{������̉��Z��
	s_fComAddPerCombo = stof(sv[1]);
	// �ő���Z��
	s_fMaxAddVal = stof(sv[2]);
}

void OBJ_Score::CalcScore(int _val)
{
	if (_val != 0 && _val != 50)
	{
		// �R���{�̌o�ߎ��ԃ��Z�b�g
		s_fComCnt = 0.0f;
		// �R���{�������Z
		s_iCurrentComCount++;
		// �R���{�J�n���}
		s_bNowCombo = true;
		// �{�[�i�X�_�����Z
		s_iScore += (_val / 100) * s_fCurrentAddVal;

		// �R���{�̉��Z���𑝉�
		s_fCurrentAddVal += s_fComAddPerCombo;
	}
	s_iScore += _val;

	DEBUG_LOG("���Z�l : " << _val);
	DEBUG_LOG("�X�R�A : " << s_iScore);
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
		// �R���{���Ă��Ȃ���
		s_fComCnt = 0.0f;
		// ���Z���̃��Z�b�g
		s_fCurrentAddVal = 0.0f;
		// �R���{���̃��Z�b�g
		s_iCurrentComCount = 0;
	}
}



void OBJ_Score::ResetCombo()
{
	// �J�E���g�����Z�b�g
	s_fComCnt = 0.0f;
	// ���Z���̃��Z�b�g
	s_fCurrentAddVal = 0.0f;
	// �R���{���̃��Z�b�g
	s_iCurrentComCount = 0;
	s_bNowCombo = false;
}
