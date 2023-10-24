#include "OBJ_Score.h"
#include "../System/Time.h"
#include <iostream>
#include "../Debug.h"
#include "CSVLoad.h"

using namespace std;

int OBJ_Score::s_iScore = 999999;
int OBJ_Score::s_iCurrentComCount = 0;
int OBJ_Score::s_iBreakNum = 0;
int OBJ_Score::s_iMaxCombo = 999;
int OBJ_Score::s_iLastIceNum = 0;
int OBJ_Score::s_iIceScore = 99999;
bool OBJ_Score::s_bNowCombo = false;
float OBJ_Score::s_fComAddPerCombo = 0.0f;
float OBJ_Score::s_fComCnt = 0.0f;
float OBJ_Score::s_fComReceptionTime = 0.0f;
float OBJ_Score::s_fCurrentAddVal = 0.0f;
float OBJ_Score::s_fMaxAddVal = 0.0f;


Com_Audio* OBJ_Score::SEs[10]{};



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


	for (int i = 0; i < 10; i++)
	{
		SEs[i] = new Com_Audio();
		AddComponent(SEs[i]);
	}
	SEs[0]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{1.wav");
	SEs[1]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{2.wav");
	SEs[2]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{3.wav");
	SEs[3]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{4.wav");
	SEs[4]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{5.wav");
	SEs[5]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{6.wav");
	SEs[6]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{7.wav");
	SEs[7]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{8.wav");
	SEs[8]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{9.wav");
	SEs[9]->Load("asset\\audio\\SE\\SE ���̑�\\�R���{10.wav");

	// ������
	s_iBreakNum = 0;
	s_iMaxCombo = 0;
	s_iScore = 0;
	s_fCurrentAddVal = 0.0f;
	s_fComCnt = 0.0f;
	s_iLastIceNum = 0;
	s_bNowCombo = false;
	s_iIceScore = 0;
}

void OBJ_Score::CalcScore(int _val)
{
	if (_val != 0 && _val != 50)
	{
		// �R���{�̌o�ߎ��ԃ��Z�b�g
		s_fComCnt = 0.0f;
		// �R���{�������Z
		s_iCurrentComCount++;
		if (s_iCurrentComCount > s_iMaxCombo)
		{
			s_iMaxCombo = s_iCurrentComCount;
		}
		s_iBreakNum++;
		// �R���{�J�n���}
		s_bNowCombo = true;
		// �{�[�i�X�_�����Z
		s_iScore += (_val / 100) * s_fCurrentAddVal;

		// �R���{�̉��Z���𑝉�
		s_fCurrentAddVal += s_fComAddPerCombo;

		switch (s_iCurrentComCount)
		{
		case 0:
			break;
		case 1:
			SEs[0]->Play();
			break;
		case 2:
			SEs[1]->Play();
			break;
		case 3:
			SEs[2]->Play();
			break;
		case 4:
			SEs[3]->Play();
			break;
		case 5:
			SEs[4]->Play();
			break;
		case 6:
			SEs[5]->Play();
			break;
		case 7:
			SEs[6]->Play();
			break;
		case 8:
			SEs[7]->Play();
			break;
		case 9:
			SEs[8]->Play();
			break;
		default:
			SEs[9]->Play();
			break;
		}
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
