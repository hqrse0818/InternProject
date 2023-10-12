#pragma once
#include "../GameObject/GameObject.h"

/*
Com_SpriteのSetUV
このオブジェクトに数字を渡せるようにする
SetNum関数で数字をセットするとオブジェクトに反映されるようにする
switchで1なら1が表示される
*/

class OBJ_Score :public GameObject
{
private:
	int iNum = 0;

public:
	OBJ_Score();
	void Init();
	void Update();
};