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
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_jump1_v3.fbx", "ToJump");
	CreatePenguin->LoadAnimation("asset\\model\\Penguin\\pengin_jump2_v2.fbx", "Jump");
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

void LoadBackPenguinA()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\pengin_haikei_blue.fbx", true);
	Creator->LoadAnimation("asset\\model\\BackGround\\pengin_haikei_blue.fbx", "Idle");
	Creator->Push("BluePenguin");
}

void LoadBackPenguinB()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\pengin_haikei_red.fbx", true);
	Creator->LoadAnimation("asset\\model\\BackGround\\pengin_haikei_red.fbx", "Idle");
	Creator->Push("RedPenguin");
}

void LoadBackGround()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\haikei_v2.fbx", true);
	Creator->Push("BackGround");
}


void Scene_ModelLoad::Init()
{
	// 使用するモデルデータをここで読み込む
	LoadPenguin();
	LoadAzarashi();
	LoadAzarashi2();
	LoadStage();
	LoadBackPenguinA();
	LoadBackPenguinB();
	LoadBackGround();
}

void Scene_ModelLoad::Update()
{
	Manager::SetScene<Scene_Title>();
}
