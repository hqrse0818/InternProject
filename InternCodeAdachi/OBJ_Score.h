#pragma once
#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Audio.h"

// �X�R�A�v�Z�p�I�u�W�F�N�g

class OBJ_Score :public GameObject
{
private:
	// �Q�[���̃X�R�A
	static int s_iScore;
	// �R���{�̎�t����
	static float s_fComReceptionTime;
	// ��t���Ԃ̃J�E���g
	static float s_fComCnt;
	// ���݃R���{����
	static bool s_bNowCombo;
	// ���݂̃R���{�̃J�E���g
	static int s_iCurrentComCount;
	// 1�R���{������̃X�R�A���Z��
	static float s_fComAddPerCombo;
	// ���݂̉��Z��
	static float s_fCurrentAddVal;
	// �ő���Z��
	static float s_fMaxAddVal;

	static Com_Audio* SEs[10];
public:
	OBJ_Score();
	OBJ_Score(const char* _name);
	OBJ_Score(const char* _name, const char* _FileName);

	void Update();

	// �R���{�����Z���Ȃ��|�C���g���Z�֐�
	static void AddNoComboScore(int _val);
	// �A�U���V�p�X�R�A�̉��Z
	static void CalcScore(int _val);
	// �X�R�A���擾
	static int GetScore()
	{
		return s_iScore;
	}
	// �R���{�̃��Z�b�g�֐�
	static void ResetCombo();
	// ���݂̃R���{���̎擾
	static int GetCurrentCombo()
	{
		return s_iCurrentComCount;
	}

	// �o�ߎ��Ԃ̎擾
	static float GetComCnt()
	{
		return s_fComCnt;
	}
	// �󂯕t�����Ԃ̎擾
	static float GetComTime()
	{
		return s_fComReceptionTime;
	}

	// �X�R�A�̃��Z�b�g
	static void ResetScore()
	{
		s_iScore = 0;
	}
};