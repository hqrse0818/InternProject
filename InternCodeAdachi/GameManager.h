#pragma once

enum GameState
{
	Game, TransToClear, TransToOver,None
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

	static void Update();
};

