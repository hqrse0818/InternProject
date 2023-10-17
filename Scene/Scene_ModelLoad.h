#pragma once
#include "Scene.h"

#include <thread>

class Scene_ModelLoad :
    public Scene
{
private:
    std::thread th1;
    std::thread th2;
    std::thread th3;
    std::thread th4;
    std::thread th5;
    std::thread th6;
    std::thread th7;

    int threadwork = 0;

public:
    void Init();
    void Update();
};

