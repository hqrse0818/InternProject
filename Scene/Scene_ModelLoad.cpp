#include "Scene_ModelLoad.h"
#include "Scene_Test.h"
#include "../System/manager.h"

void LoadPenguin()
{
	// �y���M���̓ǂݍ���
	ModelData* CreatePenguin = new ModelData();
	CreatePenguin->LoadModel("asset\\model\\Penguin\\pengin_rig_v1.fbx", true);
	CreatePenguin->Push("Penguin");
}

void LoadAzarashi()
{
	// �A�U���V�ǂݍ���
	ModelData* CreateAzarashi = new ModelData();
	CreateAzarashi->LoadModel("asset\\model\\Azarashi\\riging_azarasi_v1.fbx", true);
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\jump_azarasi_v1.fbx", "Jump");
	CreateAzarashi->LoadAnimation("asset\\model\\Azarashi\\attack_azarasi_v1.fbx", "Attack");
	CreateAzarashi->Push("Azarashi");
}

void LoadAzarashi2()
{
	// �킩�߃A�U���V�ǂݍ���
	ModelData* CreateAzarashi = new ModelData();
	CreateAzarashi->LoadModel("asset\\model\\Azarashi\\riging_azarasi_wakame_v1.fbx", true);
	CreateAzarashi->Push("AzarashiWakame");
}

void LoadStage()
{
	// �X�̓ǂݍ���
	ModelData* CreateIce = new ModelData();
	CreateIce->LoadModel("asset\\model\\Stage\\stage_rep.fbx", true);
	CreateIce->Push("Ice_PatA");
}

void Scene_ModelLoad::Init()
{
	// �g�p���郂�f���f�[�^�������œǂݍ���
	th1 = std::thread(LoadPenguin);
	th1.join();
	th2 = std::thread(LoadAzarashi);
	th2.join();
	th3 = std::thread(LoadAzarashi2);
	th3.join();
	th4 = std::thread(LoadStage);
	th4.join();
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

	Manager::SetScene<Scene_Test>();
}