#pragma once
#include "../InternCode.Kizuki/OBJ_Number.h"
class OBJ_DisplayScore :
    public GameObject
{
private:
    OBJ_Number* Nums[6];

public:
    OBJ_DisplayScore();
    OBJ_DisplayScore(const char* _name);
    OBJ_DisplayScore(const char* _name, const char* _FileName);
};

