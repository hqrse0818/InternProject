#pragma once
#include "Scene.h"
class Scene_Test :
    public Scene
{
private:
    GameObject* Player;

public:
    void Init();
    void Update();
};

