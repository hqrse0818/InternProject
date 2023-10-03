#pragma once
#include	<cinttypes>
#include "../Scene/Scene.h"

// ‘O•ûQÆ
class Application;

class Manager
{
private:
	static Scene* p_mCurrentScene;

public:
	static void Init(Application* ap);
	static void Uninit();
	static void Update(uint64_t d);
	static void Draw(uint64_t d);

	static class Scene* GetScene()
	{
		return p_mCurrentScene;
	}

	template <typename T>
	static void SetScene()
	{
		if (p_mCurrentScene)
		{
			p_mCurrentScene->UninitBase();
			delete p_mCurrentScene;
		}
		p_mCurrentScene = new T();
		p_mCurrentScene->InitBase();
		p_mCurrentScene->Start();
	}
};