#pragma once
#include "Scene.h"
#include "../GameObject/OBJ_PlayerCharacter.h"

class Scene_Test2 :
    public Scene
{
private:
    OBJ_PlayerCharacter* Player;

public:
    void Init();
    void Update();
};