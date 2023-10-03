#pragma once
#include	<thread>
#include	<iostream>
#include	<windows.h>
#pragma comment(lib, "Winmm.lib")

// シングルトン管理のTimeクラス

class Times
{
private:

	static Times* p_mInstance;
	Times() {};
	~Times() {};

	static DWORD s_mLastTime;
	static DWORD s_mDeltaTime;

	static float s_fDeltaTime;

	static DWORD s_mCountTime;
	static float s_fCount;

	static int FPSTimer;
	static int iFrameCount;
public:
	// 画面上のオブジェクトの動きなどを止める場合は0にする
	static float s_fTimeScale;

public:

	static float GetDeltaTime()
	{
		return s_fDeltaTime;
	}

	static Times* GetInstance()
	{
		return p_mInstance;
	}

	static void Init();

	static void Update();

	static void Uninit();

	static void CountStart();
	static float CountStop();
};

#define Time Times::GetInstance()