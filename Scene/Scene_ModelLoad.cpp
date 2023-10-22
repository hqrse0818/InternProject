#include "Scene_ModelLoad.h"
#include "Scene_Title.h"
#include "Scene_Test.h"
#include "../InternCode.Kizuki/Scene_Debug.h"
#include "../System/manager.h"
#include "../InternCodeAdachi/CSVLoad.h"

#include <iostream>

using namespace std;

void LoadPenguin()
{
	// �y���M���̓ǂݍ���
	ModelData* CreatePenguin = new ModelData();
	//CreatePenguin->LoadModel("asset\\model\\Penguinv2\\pengin_rig_v1.fbx", true);
	CreatePenguin->LoadModel("asset\\model\\Penguinv2\\pengin_walk_v2.fbx", true);
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_walk_v2.fbx", "Walk");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_jump1_v4.fbx", "ToJump");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_jump2_v3.fbx", "Jump");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_hipdrop1_v2.fbx", "HipDrop");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_hipdrop2_v2.fbx", "AfterHipDrop");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_idle_v2.fbx", "Idle");
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_obore.fbx", "Fall");
	CreatePenguin->Push("Penguin");
}

void LoadAttackPenguin()
{
	ModelData* CreatePenguin = new ModelData();
	CreatePenguin->LoadModel("asset\\model\\Penguinv2\\pengin_hipdrop2_v2.fbx", true);
	CreatePenguin->LoadAnimation("asset\\model\\Penguinv2\\pengin_hipdrop2_v2.fbx", "AfterHipDrop");
	CreatePenguin->Push("AttackPenguin");
}

void LoadAzarashi()
{
	// �A�U���V�ǂݍ���
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
	// �킩�߃A�U���V�ǂݍ���
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
	// �X�̓ǂݍ���
	ModelData* CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stagev2\\1stage.fbx", true);
	CreateIce->Push("Ice_HP5");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stagev2\\2stage.fbx", true);
	CreateIce->Push("Ice_HP4");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stagev2\\3stage.fbx", true);
	CreateIce->Push("Ice_HP3");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stagev2\\4stage.fbx", true);
	CreateIce->Push("Ice_HP2");

	CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stagev2\\5stage.fbx", true);
	CreateIce->Push("Ice_HP1");
}

void LoadBackPenguinA()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\pengin_haikei_blue.fbx", true);
	Creator->LoadAnimation("asset\\model\\BackGround\\pengin_haikei_blue.fbx", "Blue");
	Creator->Push("BluePenguin");
}

void LoadBackPenguinB()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\pengin_haikei_red.fbx", true);
	Creator->LoadAnimation("asset\\model\\BackGround\\pengin_haikei_red.fbx", "Red");
	Creator->Push("RedPenguin");
}

void LoadBackGround()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\haikei_v2.fbx", true);
	Creator->Push("BackGround");
}

void LoadSky()
{
	ModelData* Creator = new ModelData();
	Creator->LoadModel("asset\\model\\BackGround\\sora.fbx", true);
	Creator->Push("Sky");
}

void Scene_ModelLoad::Init()
{
	// �g�p���郂�f���f�[�^�������œǂݍ���
	LoadPenguin();
	LoadAttackPenguin();
	LoadAzarashi();
	LoadAzarashi2();
	LoadStage();
	LoadBackPenguinA();
	LoadBackPenguinB();
	LoadBackGround();
	LoadSky();

	// ���C�g�̓ǂݍ���
	string sLightState = ReadDataFromCSV("asset/data/csv/LightSetting.csv", 1);

	vector<string> sv = SeparateString(sLightState, ',');

	LIGHT light;
	light.Enable = TRUE;
	light.Direction.x = stof(sv[0]);
	light.Direction.y = stof(sv[1]);
	light.Direction.z = stof(sv[2]);
	light.Direction.w = 0.0f;
	light.Direction.Normalize();
	light.Ambient.x = stof(sv[3]);
	light.Ambient.y = stof(sv[4]);
	light.Ambient.z = stof(sv[5]);
	light.Ambient.w = stof(sv[6]);
	light.Diffuse.x = stof(sv[7]);
	light.Diffuse.y = stof(sv[8]);
	light.Diffuse.z = stof(sv[9]);
	light.Diffuse.w = stof(sv[10]);
	// ���C�g��ݒ�
	Renderer::SetLight(light);

}

void Scene_ModelLoad::Update()
{
	Manager::SetNextScene<Scene_Title>();
}
