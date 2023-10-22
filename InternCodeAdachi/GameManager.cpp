#include "GameManager.h"
#include "../System/Time.h"
#include "../System/manager.h"

GameState GameManager::mState = GameState::Title;
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
	
}
