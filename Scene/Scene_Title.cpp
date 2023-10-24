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
#include "Scene_Clear.h"
#include "../InternCodeAdachi/CSVLoad.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Title::Init()
{
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
	AddGameObject(Title);

	//タイトルロゴ生成
	OBJ_TitleLogo* TitleLogo = new OBJ_TitleLogo;
	TitleLogo->p_mTransform->SetPosition(SCREEN_WIDTH / 2, 225.0f, 0.0f);
	TitleLogo->p_mTransform->mScale.x = 1920.0f *0.5f;
	TitleLogo->p_mTransform->mScale.y = 1080.0f * 0.5f;
	TitleLogo->bRotate = true;
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

	// バナー
	p_mBanner = new GameObject("Banner");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mBanner->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/banner.png");
	Sprite_buf->SetSeparateNum(1, 1);
	Sprite_buf->SetCurrent(1);
	Sprite_buf->SetUpdate(true);
	p_mBanner->AddComponent(Sprite_buf);
	p_mBanner->SetScale(600.0f, 600.0f, 0.0f);
	p_mBanner->SetPosition(SCREEN_WIDTH / 2, 485.0f, 0.0f);
	AddGameObject(p_mBanner);

	string ss = ReadDataFromCSV("asset/data/csv/TitleSetting.csv", 1);

	vector<string> sv = SeparateString(ss, ',');

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
	Sprite_buf->SetUpdate(true);
	p_mStartLogo->AddComponent(Sprite_buf);
	p_mStartScale = new Com_Scaling();
	p_mStartScale->SetSpeed(30.0f, -30.0f);
	p_mStartScale->SetTime(0.6f);
	p_mStartScale->SetUpdate(true);
	p_mStartLogo->AddComponent(p_mStartScale);
	p_mStartLogo->SetPosition(stof(sv[0]), stof(sv[1]), 0.0f);
	p_mStartLogo->SetScale(stof(sv[2]), stof(sv[3]), 1.0f);
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
	p_mTutoScale = new Com_Scaling();
	p_mTutoScale->SetSpeed(30.0f, -30.0f);
	p_mTutoScale->SetTime(0.6f);
	p_mTutolialLogo->AddComponent(p_mTutoScale);
	p_mTutolialLogo->SetPosition(stof(sv[4]), stof(sv[5]), 0.0f);
	p_mTutolialLogo->SetScale(stof(sv[6]), stof(sv[7]), 1.0f);
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
	p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 475.0f, 0.0f);
	AddGameObject(p_mAllow);

	// 説明1
	p_mExp1 = new GameObject("exp1");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mExp1->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/tyutorial_rule.png");
	Sprite_buf->SetSeparateNum(1,1);
	Sprite_buf->SetCurrent(1);
	p_mExp1->AddComponent(Sprite_buf);
	p_mExp1->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	//p_mExp1->SetScale(1980.0f * 0.7f, 1080.0f * 0.7f, 1.0f);
	p_mExp1->SetScale(1280, 720, 1.0f);
	AddGameObject(p_mExp1);
	// 説明2
	p_mExp2 = new GameObject("exp1");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	p_mExp1->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/tyutorial_sousa.png");
	Sprite_buf->SetSeparateNum(1, 1);
	Sprite_buf->SetCurrent(1);
	p_mExp2->AddComponent(Sprite_buf);
	p_mExp2->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1.0f, 0.0f);
	//p_mExp2->SetScale(1980.0f * 0.7f, 1080.0f * 0.7f, 1.0f);
	p_mExp2->SetScale(1280, 720, 1.0f);
	AddGameObject(p_mExp2);

	pBackFont = new GameObject("modoru");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	pBackFont->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/modoru_bottun.png");
	Sprite_buf->SetSeparateNum(1, 1);
	Sprite_buf->SetCurrent(1);
	pBackFont->AddComponent(Sprite_buf);
	pBackFont->SetPosition(stof(sv[8]), stof(sv[9]), 0.0f);
	pBackFont->SetScale(stof(sv[10]), stof(sv[11]), 0.0f);
	AddGameObject(pBackFont);

	pBackButton = new GameObject("Button");
	Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);
	pBackButton->AddComponent(Shader_buf);
	Sprite_buf = new Com_Sprite();
	Sprite_buf->SetTexture("asset/texture/modoru.png");
	Sprite_buf->SetSeparateNum(1, 1);
	Sprite_buf->SetCurrent(1);
	pBackButton->AddComponent(Sprite_buf);
	pBackButton->SetPosition(stof(sv[12]), stof(sv[13]), 0.0f);
	pBackButton->SetScale(stof(sv[14]), stof(sv[15]), 0.0f);
	AddGameObject(pBackButton);

	// 音
	p_mAudio = new Com_Audio();
	p_mAudio->Load("asset\\audio\\BGM\\タイトル画面 BGM.wav");
	p_mAudio->SetUseTarget(false);

	p_mSECursor = new Com_Audio();
	p_mSECursor->Load("asset\\audio\\SE\\SE その他\\カーソル移動.wav");

	p_mSEDecide = new Com_Audio();
	p_mSEDecide->Load("asset\\audio\\SE\\SE その他\\決定.wav");

	p_mTransition = new OBJ_Transition("Transition");
	p_mTransition->SetState(OBJ_Transition::FadeState::OutEnd);
	AddKeyObject(p_mTransition);
}

void Scene_Title::Start()
{
	p_mExp1->SetActive(false);
	p_mExp2->SetActive(false);
	pBackFont->SetActive(false);
	pBackButton->SetActive(false);

	p_mAudio->Play(true);
	GameManager::SetGameState(GameState::Title);

	p_mTransition->FadeIn(1);
}

void Scene_Title::Update()
{
	switch (mState)
	{
	case Scene_Title::TitleState::WaitFade:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::InEnd)
		{
			mState = TitleState::WaitInput;
		}
		break;
	case Scene_Title::TitleState::WaitInput:
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
		{
			p_mSEDecide->Play();
			if (bisUP)
			{
				p_mTransition->FadeOut(1);
				mState = TitleState::ToGame;
			}
			else
			{
				mState = TitleState::Tutorial;
				bisLeft = true;
				p_mExp1->SetActive(true);
				p_mExp2->SetActive(false);
				pBackFont->SetActive(true);
				pBackButton->SetActive(true);
			}
		}
		else if (Controller_Input::GetButton(0, GAMEPAD_UP) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_UP) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_DOWN)
		{
			if (!bisUP)
			{
				p_mSECursor->Play();
			}
			bisUP = true;
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 475.0f, 0.0f);
			p_mBanner->SetPosition(SCREEN_WIDTH / 2, 485.0f, 0.0f);
			p_mStartScale->SetUpdate(true);
			p_mTutoScale->SetUpdate(false);
		}
		else if (Controller_Input::GetButton(0, GAMEPAD_DOWN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_DOWN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_DOWN)
		{
			if (bisUP)
			{
				p_mSECursor->Play();
			}
			bisUP = false;
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 220.0f, 625.0f, 0.0f);
			p_mBanner->SetPosition(SCREEN_WIDTH / 2, 630.0f, 0.0f);
			p_mStartScale->SetUpdate(false);
			p_mTutoScale->SetUpdate(true);
		}
		break;
	case Scene_Title::TitleState::Tutorial:
		if (Controller_Input::GetLeftStick(0).x < -0.5f || Controller_Input::GetButton(0, GAMEPAD_LEFT) == KEYSTATE::KEY_DOWN || Controller_Input::GetButton(0, GAMEPAD_SHOULDER_L) == KEYSTATE::KEY_DOWN ||
			Input::GetKeyState(KEYCODE_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_LEFT) == KEYSTATE::KEY_DOWN)
		{
			if (!bisLeft)
			{
				p_mSECursor->Play();
			}
			bisLeft = true;
			p_mExp1->SetActive(true);
			p_mExp2->SetActive(false);
		}
		else if (Controller_Input::GetLeftStick(0).x > 0.5f || Controller_Input::GetButton(0, GAMEPAD_RIGHT) == KEYSTATE::KEY_DOWN || Controller_Input::GetButton(0, GAMEPAD_SHOULDER_R) == KEYSTATE::KEY_DOWN ||
			Input::GetKeyState(KEYCODE_D) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RIGHT) == KEYSTATE::KEY_DOWN)
		{
			if (bisLeft)
			{
				p_mSECursor->Play();
			}
			bisLeft = false;
			p_mExp1->SetActive(false);
			p_mExp2->SetActive(true);
		}
		else if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN || Controller_Input::GetButton(0, GAMEPAD_B) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN)
		{
			p_mSEDecide->Play();
			bisLeft = true;
			p_mExp1->SetActive(false);
			p_mExp2->SetActive(false);
			pBackFont->SetActive(false);
			pBackButton->SetActive(false);
			mState = TitleState::WaitInput;
		}
		break;
	case Scene_Title::TitleState::ToGame:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
		{
			//Manager::SetNextScene<Scene_Game>();
			Manager::SetNextScene<Scene_Test>();
			//Manager::SetNextScene<Scene_Clear>();
		}
		break;
	default:
		break;
	}
	
}

void Scene_Title::Uninit()
{
	p_mSECursor->Stop();
	p_mSECursor->Uninit();
	delete p_mSECursor;

	p_mSEDecide->Stop();
	p_mSEDecide->Uninit();
	delete p_mSEDecide;

	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}