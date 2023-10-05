#pragma once
#include "../Scene/Scene.h"
#include "OBJ_PlayerCharacter.h"

class Scene_Test2 :
    public Scene
{
private:
    OBJ_PlayerCharacter* Player;

public:
    void Init();
    void Update();
};