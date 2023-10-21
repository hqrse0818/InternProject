#pragma once
#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_Audio.h"

// スコア計算用オブジェクト

class OBJ_Score :public GameObject
{
private:
	// ゲームのスコア
	static int s_iScore;
	// コンボの受付時間
	static float s_fComReceptionTime;
	// 受付時間のカウント
	static float s_fComCnt;
	// 現在コンボ中か
	static bool s_bNowCombo;
	// 現在のコンボのカウント
	static int s_iCurrentComCount;
	// 1コンボ当たりのスコア加算率
	static float s_fComAddPerCombo;
	// 現在の加算率
	static float s_fCurrentAddVal;
	// 最大加算率
	static float s_fMaxAddVal;

	static Com_Audio* SEs[10];
public:
	OBJ_Score();
	OBJ_Score(const char* _name);
	OBJ_Score(const char* _name, const char* _FileName);

	void Update();

	// コンボを加算しないポイント加算関数
	static void AddNoComboScore(int _val);
	// アザラシ用スコアの加算
	static void CalcScore(int _val);
	// スコアを取得
	static int GetScore()
	{
		return s_iScore;
	}
	// コンボのリセット関数
	static void ResetCombo();
	// 現在のコンボ数の取得
	static int GetCurrentCombo()
	{
		return s_iCurrentComCount;
	}

	// 経過時間の取得
	static float GetComCnt()
	{
		return s_fComCnt;
	}
	// 受け付け時間の取得
	static float GetComTime()
	{
		return s_fComReceptionTime;
	}

	// スコアのリセット
	static void ResetScore()
	{
		s_iScore = 0;
	}
};