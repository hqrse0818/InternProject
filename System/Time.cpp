#include "Time.h"
#include <winapifamily.h>
#include	<timeapi.h>
#include <iostream>
#include "../Debug.h"

using namespace std;

Times* Times::p_mInstance = nullptr;

float Times::s_fDeltaTime = 0;
float Times::s_fTimeScale = 1.0f;
float Times::s_fCount = 0.0f;
DWORD Times::s_mLastTime = 0;
DWORD Times::s_mCountTime = 0;
DWORD Times::s_mDeltaTime = 0;
int Times::FPSTimer = 1000;
int Times::iFrameCount = 0;

void Times::Init()
{
	if (p_mInstance == nullptr)
	{
		p_mInstance = new Times;

		// バグをなくすためのデルタタイムを初期化
		timeBeginPeriod(1); // 精度を１ミリ秒に上げる
		DWORD CurrentTime = timeGetTime();
		s_fDeltaTime = CurrentTime - s_mLastTime;

		s_fDeltaTime /= 1000.0f;

		s_mLastTime = CurrentTime;
	}
}

void Times::Update()
{
	iFrameCount++;
	timeBeginPeriod(1); // 精度を１ミリ秒に上げる

	DWORD CurrentTime = timeGetTime();
	s_mDeltaTime = CurrentTime - s_mLastTime;
	s_fDeltaTime = CurrentTime - s_mLastTime;
	FPSTimer -= s_mDeltaTime;
	if (FPSTimer < 1)
	{
		FPSTimer = 1000;
		//DEBUG_LOG(iFrameCount << "FPS");
		iFrameCount = 0;
	}

	s_fDeltaTime /= 1000.0f;

	s_mLastTime = CurrentTime;
}

void Times::Uninit()
{
	delete p_mInstance;
}

void Times::CountStart()
{
	s_mCountTime = timeGetTime();
}

float Times::CountStop()
{
	DWORD Current = timeGetTime();
	s_fCount = Current - s_mCountTime;

	s_fCount /= 1000.0f;

	return s_fCount;
}
