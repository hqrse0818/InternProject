#pragma once

enum GameState
{
	// �^�C�g��
	Title, 
	// �Q�[����ʑO�̃t�F�[�h
	GameFade,
	// �Q�[���J�n�҂�
	WaitStart,
	// �Q�[����
	Game, 
	// �N���A��ʂɑJ�ڗ\��
	TransToClear, 
	// �N���A��ʂւ̃t�F�[�h
	ClearFade,
	// �N���A���
	Clear,
	// �I�[�o�[��ʂɑJ�ڗ\��
	TransToOver,
	// �I�[�o�[��ʂւ̃t�F�[�h
	OverFade,
	// �I�[�o�[���
	Over,
	// �I��
	End
};

class GameManager
{
private:
	static GameState mState;
	static float s_fToClearTime;
	static float s_fToClearCnt;
	static float s_fToOverTime;
	static float s_fToOverCnt;
public:
	static void SetGameState(GameState _state);
	static GameState GetGameState()
	{
		return mState;
	}
	static void Update();
};

