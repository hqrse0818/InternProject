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

	// in/ int �ŏ��l, int �ő�l, int �����_��
	// out/ �ŏ��l���傫���A�ő�l�����̒l��Ԃ�
	static float fGetRand(const int _min, const int _max, const int period);

	static HighRand* GetInstance();

	static void Uninit();
};

#define HighRandom HighRand::GetInstance()