#pragma once

enum GameState
{
	// タイトル
	Title, 
	// ゲーム画面前のフェード
	GameFade,
	// ゲーム開始待ち
	WaitStart,
	// ゲーム中
	Game, 
	// クリア画面に遷移予約
	TransToClear, 
	// クリア画面へのフェード
	ClearFade,
	// クリア画面
	Clear,
	// オーバー画面に遷移予約
	TransToOver,
	// オーバー画面へのフェード
	OverFade,
	// オーバー画面
	Over,
	// 終了
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

