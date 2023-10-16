#include "Scene_Title.h"

// includeList
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../System/TextureCreate.h"
#include "../main.h"
#include "../System/manager.h"
#include "../System/Input.h"
#include "../TextureFilePath.h"
#include "Scene_Test.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Title::Init()
{
	p_mAudio = new Com_Audio();
	bCheckCol = true;

	p_mTransition = new OBJ_Transition("Transition");
	p_mTransition->FadeOut(0.0f);
	AddKeyObject(p_mTransition, 3);
	
	// カメラ生成
	GameObject* Camera = new GameObject("MainCamera");
	Com_Camera* Camera_buf = new Com_Camera();
	Camera_buf->SetTargetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Camera_buf->SetUseTarget(false);
	Camera->AddComponent(Camera_buf);
	Camera->p_mTransform->mPosition.z = -10.0f;
	AddGameObject(Camera, 0);
	
	GameObject* Title = new GameObject("TitleObj");

	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	Title->AddComponent(Shader_buf);
	Com_Sprite* Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start.png");

	Title->AddComponent(Sprite_buf);
	Title->p_mTransform->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f);
	Title->p_mTransform->mScale.x = SCREEN_WIDTH;
	Title->p_mTransform->mScale.y = SCREEN_HEIGHT;
	AddGameObject(Title, 4);

	//タイトルロゴ生成
	//OBJ_TitleLogo* TitleLogo = new OBJ_TitleLogo;
	//AddGameObject(TitleLogo);

	p_mAudio->Load("asset\\audio\\BGM\\タイトル画面 BGM.wav");
	p_mAudio->SetUseTarget(false);
}

void Scene_Title::Start()
{
	p_mAudio->Play(true);
}

void Scene_Title::Update()
{
	if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN)
	{
		Manager::SetScene<Scene_Test>();
	}
}

void Scene_Title::Uninit()
{
	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}
