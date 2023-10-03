#pragma once
#include <iostream>
#include <random>
#include <chrono>


class HighRand
{
private:
	static unsigned seed;
	static std::default_random_engine generator;
	static HighRand* instance;
	
public:
	static void HighRandInit();
	
	static int GetRand(const int _min, const int _max);

	// in/ int 最小値, int 最大値, int 小数点位
	// out/ 最小値より大きく、最大値未満の値を返す
	static float fGetRand(const int _min, const int _max, const int period);

	static HighRand* GetInstance();

	static void Uninit();
};

#define HighRandom HighRand::GetInstance()