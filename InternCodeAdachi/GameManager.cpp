#include "GameManager.h"
#include "../System/Time.h"
#include "../System/manager.h"

GameState GameManager::mState = GameState::None;
float GameManager::s_fToClearCnt = 0.0f;
float GameManager::s_fToClearTime = 2.0f;
float GameManager::s_fToOverCnt = 0.0f;
float GameManager::s_fToOverTime = 2.0f;

void GameManager::SetGameState(GameState _state)
{
	mState = _state;
}

void GameManager::Update()
{
	switch (mState)
	{
	case Game:
		break;
	case TransToClear:
		s_fToClearCnt += Time->GetDeltaTime();
		if (s_fToClearCnt > s_fToClearTime)
		{
			s_fToClearCnt = 0.0f;
			mState = GameState::None;

			// シーン切り替え
			//Manager::SetScene<Scene_Clear>();
		}
		break;
	case TransToOver:
		s_fToOverCnt += Time->GetDeltaTime();
		if (s_fToOverCnt > s_fToOverTime)
		{
			s_fToOverCnt = 0.0f;
			mState = GameState::None;

			// シーン切り替え
			//Manager::SetScene<Scene_Over>();
		}
		break;
	case None:
		break;
	default:
		break;
	}
}
