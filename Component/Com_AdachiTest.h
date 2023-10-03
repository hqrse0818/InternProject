#pragma once
#include "Component.h"

class Com_AdachiTest
	: public Component
{
public:
	float mValue = 0;
	float move = 0;

public:
	void Update() { mValue += 1; };
};