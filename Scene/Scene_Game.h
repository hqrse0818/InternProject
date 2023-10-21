#pragma once
#include "Scene.h"

class OBJ_Penguin;

class Scene_Game :
    public Scene
{
private:
    OBJ_Penguin* p_mPlayer{};
    Com_Audio* p_mAudio{};
public:

    void Init();
    void Start();
    void Update();

};

