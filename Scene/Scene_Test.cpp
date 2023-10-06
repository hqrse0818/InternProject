#include "Scene_Test.h"
#include "../ComponentHeader.h"
#include "../System/Input.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"


#include "../InternCodeAdachi/OBJ_Penguin.h"
#include "../InternCodeAdachi/Com_AngleCamera.h"
#include "../InternCodeAdachi/OBJ_Ice.h"

#define IceNum (11)
#define IceScale (8)
#define InitPos (-40)

using namespace DirectX::SimpleMath;

void Scene_Test::Init()
{
	// 当たり判定アクティブ化
	bCheckCol = true;

	// ペンギン
	Player = new OBJ_Penguin("Test");
	

	// レイヤーの指定なしでキーオブジェクトとして追加
	AddKeyObject(Player);

	// アザラシ
	GameObject* Azarashi = new GameObject("Azarashi");
	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_MODEL);
	Shader_buf->p_mPS->Load(PS_MODEL);

	Azarashi->AddComponent(Shader_buf);

	Com_AssimpAnimation* Model_buf = new Com_AssimpAnimation();
	Model_buf->LoadModel("asset\\model\\Azarashi\\azarasi_v2.fbx", 1.0f, true);
	Azarashi->AddComponent(Model_buf);

	Com_SphereCollider* Col_buf = new Com_SphereCollider();
	Col_buf->fRadius = 2.0f;
	Col_buf->SetCenter(0.0f, 1.0f, 0.0f);
	Col_buf->bMovable = true;
	Azarashi->AddComponent(Col_buf);

	AddGameObject(Azarashi);

	// ステージ生成
	for (int i = 0; i < IceNum; i++)
	{
		for (int j = 0; j < IceNum; j++)
		{
			// 氷の生成
			OBJ_Ice* Ice = new OBJ_Ice("Ice");
			Ice->p_mTransform->SetPosition(InitPos + i * IceScale, 0.0f, InitPos + j * IceScale);
			AddGameObject(Ice);
		}
	}

	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(Player);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);

	// レイヤーを指定してオブジェクトを追加
	AddGameObject(Camera, 0);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);
}

void Scene_Test::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 7.0f, 0.0f);
	GetGameObject("Azarashi")->p_mTransform->SetPosition(10.0f, 8.0f, -2.0f);
}

void Scene_Test::Update()
{
	
}