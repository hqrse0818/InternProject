#include "Scene_ModelLoad.h"
#include "Scene_Title.h"
#include "Scene_Test.h"
#include "../InternCode.Kizuki/Scene_Debug.h"
#include "../System/manager.h"

void LoadPenguin()
{
	// ペンギンの読み込み
	ModelData* CreatePenguin = new ModelData();
	CreatePenguin->LoadModel("asset\\model\\Penguin\\pengin_rig_v1.fbx", true);
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_walk_v1.fbx", "Walk");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_jump3_v1.fbx", "ToJump");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_jump2_v1.fbx", "Jump");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_hipdrop1_v1.fbx", "HipDrop");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_hipdrop2_v1.fbx", "AfterHipDrop");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_idle_v1.fbx", "Idle");
	CreatePenguin->Push("Penguin");
}

void LoadAzarashi()
{
	// アザラシ読み込み
	ModelData* CreateAzarashi = new ModelData();
	CreateAzarashi->LoadModel("asset\\model\\Azarashi\\riging_azarasi_v1.fbx", true);
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\jump_azarasi_v1.fbx", "Jump");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\attack_azarasi_v1.fbx", "Attack");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\hidan_azarasi_v1.fbx", "Damage");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\dive_azarasi_v1.fbx", "Dive");
	CreateAzarashi->Push("Azarashi");
}

void LoadAzarashi2()
{
	// わかめアザラシ読み込み
	ModelData* CreateAzarashi = new ModelData();
	CreateAzarashi->LoadModel("asset\\model\\Azarashi\\riging_azarasi_wakame_v1.fbx", true);
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\jump_azarasi_wakame_v1.fbx", "Jump");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\attack_azarasi_wakame_v1.fbx", "Attack");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\hidan_azarasi_wakame_v1.fbx", "Damage");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\dive_azarasi_wakame_v1.fbx", "Dive");
	CreateAzarashi->Push("AzarashiWakame");
}

void LoadStage()
{
	// 氷の読み込み
	ModelData* CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\1_stage.fbx", true);
	CreateIce->Push("Ice_HP5");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\2_stage.fbx", true);
	CreateIce->Push("Ice_HP4");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\3_stage.fbx", true);
	CreateIce->Push("Ice_HP3");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\4_stage.fbx", true);
	CreateIce->Push("Ice_HP2");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\5_stage.fbx", true);
	CreateIce->Push("Ice_HP1");
}

void Scene_ModelLoad::Init()
{
	// 使用するモデルデータをここで読み込む
	th1 = std::thread(LoadPenguin);
	th1.join();
	th2 = std::thread(LoadAzarashi);
	th2.join();
	th3 = std::thread(LoadAzarashi2);
	th3.join();
	th4 = std::thread(LoadStage);
	th4.join();

	// 背景読み込み
	ModelData* BackGround = new ModelData();
	BackGround->LoadModel("asset\\model\\BackGround\\haikei.fbx", true);
	BackGround->Push("Haikei");
}

void Scene_ModelLoad::Update()
{
	/*if (th1.joinable())
	{
		th1.join();
		threadwork++;
	}
	if (th2.joinable())
	{
		th2.join();
		threadwork++;
	}
	if (th3.joinable())
	{
		th3.join();
		threadwork++;
	}
	if (th4.joinable())
	{
		th4.join();
		threadwork++;
	}


	if (threadwork == 4)
	{
		Manager::SetScene<Scene_Test>();
	}*/
	
	Manager::SetScene<Scene_Title>();
}
