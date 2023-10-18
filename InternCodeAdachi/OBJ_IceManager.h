#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Ice.h"

#include <list>

class OBJ_IceManager :
    public GameObject
{
private:
    std::list<OBJ_Ice*> IceList{};

public:
    std::list<OBJ_Ice*>GetIceList()
    {
        return IceList;
    }

};
