#pragma once
#include "Scene.h"
class OBJ_Penguin;
class Scene_Test :
    public Scene
{
private:
    OBJ_Penguin* Player;

public:
    void Init();
    void Start();
    void Update();
};

