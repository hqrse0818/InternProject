#pragma once
#include "../GameObject/GameObject.h"

/*
Com_Sprite��SetUV
���̃I�u�W�F�N�g�ɐ�����n����悤�ɂ���
SetNum�֐��Ő������Z�b�g����ƃI�u�W�F�N�g�ɔ��f�����悤�ɂ���
switch��1�Ȃ�1���\�������
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