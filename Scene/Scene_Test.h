#pragma once
#include "Scene.h"
class OBJ_Penguin;
class Scene_Test :
    public Scene
{
private:
    OBJ_Penguin* Player;
    Com_Audio* p_mAudio{};

public:
    void Init();
    void Start();
    void Update();
    void Uninit();
};

