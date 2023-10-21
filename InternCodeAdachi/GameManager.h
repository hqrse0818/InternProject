#pragma once

enum GameState
{
	Title, WaitFade, WaitStart,Game, TransToClear, TransToOver,None,End
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

