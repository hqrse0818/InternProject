#include "Scene_Title.h"

// includeList
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../System/TextureCreate.h"
#include "../main.h"
#include "../System/manager.h"
#include "../System/Input.h"
#include "../TextureFilePath.h"
#include "../InternCode.Kizuki/OBJ_TitleLogo.h"
#include "Scene_Test.h"
#include "Scene_Game.h"
#include "../InternCodeAdachi/GameManager.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Title::Init()
{
	p_mAudio = new Com_Audio();

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
	Sprite_buf->SetTexture("asset/texture/starthaikei.png");

	Title->AddComponent(Sprite_buf);
	Title->p_mTransform->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f);
	Title->p_mTransform->mScale.x = SCREEN_WIDTH;
	Title->p_mTransform->mScale.y = SCREEN_HEIGHT;
	AddGameObject(Title, 4);

	//タイトルロゴ生成
	OBJ_TitleLogo* TitleLogo = new OBJ_TitleLogo;
	TitleLogo->p_mTransform->SetPosition(SCREEN_WIDTH / 2, 225.0f, 0.0f);
	TitleLogo->p_mTransform->mScale.x = 1920.0f *0.5f;
	TitleLogo->p_mTransform->mScale.y = 1080.0f * 0.5f;
	AddGameObject(TitleLogo);

	// 氷ロゴ
	GameObject* pIceLogo = new GameObject("Icelogo");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	pIceLogo->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start_icon.png");
	Sprite_buf->SetSeparateNum(2, 2);
	Sprite_buf->SetCurrent(4);
	pIceLogo->AddComponent(Sprite_buf);
	pIceLogo->SetScale(1920.0f * 0.275f, 1080.0f * 0.275f, 1.0f);
	pIceLogo->SetPosition(SCREEN_WIDTH / 2, 500.0f, 0.0f);
	AddGameObject(pIceLogo);

	pIceLogo = new GameObject("Icelogo");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	pIceLogo->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start_icon.png");
	Sprite_buf->SetSeparateNum(2, 2);
	Sprite_buf->SetCurrent(4);
	pIceLogo->AddComponent(Sprite_buf);
	pIceLogo->SetScale(1920.0f * 0.275f, 1080.0f * 0.275f, 1.0f);
	pIceLogo->SetPosition(SCREEN_WIDTH / 2, 650.0f, 0.0f);
	AddGameObject(pIceLogo);

	// スタートロゴ
	p_mStartLogo = new GameObject("start");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mStartLogo->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start_icon.png");
	Sprite_buf->SetSeparateNum(2, 2);
	Sprite_buf->SetCurrent(1);
	p_mStartLogo->AddComponent(Sprite_buf);
	p_mStartLogo->SetScale(1920.0f * 0.175f, 1080.0f * 0.175f, 1.0f);
	p_mStartLogo->SetPosition(SCREEN_WIDTH / 2, 475.0f, 0.0f);
	AddGameObject(p_mStartLogo);

	// チュートリアルロゴ
	p_mTutolialLogo = new GameObject("tuto");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mTutolialLogo->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start_icon.png");
	Sprite_buf->SetSeparateNum(2, 2);
	Sprite_buf->SetCurrent(3);
	Sprite_buf->SetUpdate(true);
	p_mTutolialLogo->AddComponent(Sprite_buf);
	p_mTutolialLogo->SetScale(1920.0f * 0.2f, 1080.0f * 0.2f, 1.0f);
	p_mTutolialLogo->SetPosition(SCREEN_WIDTH / 2, 650.0f, 0.0f);
	AddGameObject(p_mTutolialLogo);

	// 矢印
	p_mAllow = new GameObject("allow");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mAllow->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/start_icon.png");
	Sprite_buf->SetSeparateNum(2, 2);
	Sprite_buf->SetCurrent(2);
	Sprite_buf->SetUpdate(true);
	p_mAllow->AddComponent(Sprite_buf);
	p_mAllow->SetScale(1920.0f * 0.2f, 1080.0f * 0.2f, 1.0f);
	p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 500.0f, 0.0f);
	AddGameObject(p_mAllow);

	p_mAudio->Load("asset\\audio\\BGM\\タイトル画面 BGM.wav");
	p_mAudio->SetUseTarget(false);
}

void Scene_Title::Start()
{
	p_mAudio->Play(true);
	GameManager::SetGameState(GameState::Title);
}

void Scene_Title::Update()
{
	switch (mStatus)
	{
	case Scene_Title::TitleState::Start:
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN)
		{
			if (bisUP)
			{
				//Manager::SetNextScene<Scene_Game>();
				Manager::SetNextScene<Scene_Test>();
			}
			else
			{

			}
		}
		else if (Controller_Input::GetButton(0, GAMEPAD_UP) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_UP) == KEYSTATE::KEY_DOWN)
		{
			bisUP = true;
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 500.0f, 0.0f);
			p_mTutolialLogo->SetScale(1920.0f * 0.2f, 1080.0f * 0.2f, 1.0f);
		}
		else if (Controller_Input::GetButton(0, GAMEPAD_DOWN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_DOWN) == KEYSTATE::KEY_DOWN)
		{
			bisUP = false;
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 650.0f, 0.0f);
			p_mTutolialLogo->SetScale(1920.0f * 0.21f, 1080.0f * 0.21f, 1.0f);
		}
		break;
	case Scene_Title::TitleState::Tutorial:
		break;
	case Scene_Title::TitleState::ToGame:
		break;
	default:
		break;
	}
	
}

void Scene_Title::Uninit()
{
	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}