#include "Scene_Clear.h"
#include "../System/Time.h"
#include "../System/Input.h"
#include "../main.h"
#include "Scene_Title.h"
#include "Scene_Test.h"
#include "Scene_Game.h"

#include "../System/manager.h"
#include "../InternCodeAdachi/GameManager.h"
#include "../InternCodeAdachi/OBJ_Score.h"
#include "../InternCodeAdachi/CSVLoad.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Clear::Init()
{
	// カメラ
	GameObject* Camera = new GameObject("cam");
	Com_Camera* cam = new Com_Camera();
	cam->SetTargetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Camera->AddComponent(cam);
	Camera->SetPosition(0.0f, -100.0f, 0.0f);
	AddGameObject(Camera, 0);

	// 背景
	GameObject* obj = new GameObject("Back");
	Com_Shader* shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	obj->AddComponent(shader);
	Com_Sprite* sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/result_haikei.png");
	sprite->SetCurrent(1);
	obj->AddComponent(sprite);
	obj->SetScale(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f);
	obj->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f);
	AddGameObject(obj);

	// 文字ゲームクリアー
	obj = new GameObject("font");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	obj->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/result_mozi.png");
	sprite->SetSeparateNum(1, 2);
	sprite->SetCurrent(1);
	obj->AddComponent(sprite);
	obj->SetScale(1920.0f * 0.5f, 1080.0f / 4, 0.0f);
	obj->SetPosition(SCREEN_WIDTH / 2, 75.0f, 0.0f);
	AddGameObject(obj);

	// 文字トータルスコア
	obj = new GameObject("font");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	obj->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/result_mozi.png");
	sprite->SetSeparateNum(1, 2);
	sprite->SetCurrent(2);
	obj->AddComponent(sprite);
	obj->SetScale(1920.0f * 0.5f * 0.7, 1080.0f / 4 * 0.7, 0.0f);
	obj->SetPosition(SCREEN_WIDTH / 2 + 400.0f, 250.0f, 0.0f);
	AddGameObject(obj);

	// 氷
	GameObject* ice = new GameObject("ice");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	ice->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(1);
	ice->AddComponent(sprite);
	ice->SetScale(1920.0f * 0.175f, 1080.0f * 0.175f, 1.0f);
	ice->SetPosition(1100.0f, 540.0f, 0.0f);
	AddGameObject(ice);

	ice = new GameObject("ice");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	ice->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(3);
	ice->AddComponent(sprite);
	ice->SetScale(1920.0f * 0.175f, 1080.0f * 0.175f, 1.0f);
	ice->SetPosition(1100.0f, 650.0f, 0.0f);
	AddGameObject(ice);

	// バナー
	p_mBanner = new GameObject("banner");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_mBanner->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/banner.png");
	sprite->SetSeparateNum(1, 1);
	sprite->SetCurrent(1);
	sprite->SetUpdate(true);
	p_mBanner->AddComponent(sprite);
	p_mBanner->SetScale(420.0f, 420.0f, 0.0f);
	p_mBanner->SetPosition(1100.0, 545.0f, 0.0f);
	AddGameObject(p_mBanner);

	// タイトルに戻る
	p_mReturn = new GameObject("rettitle");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_mReturn->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(2);
	sprite->SetUpdate(true);
	p_mReturn->AddComponent(sprite);
	p_mRetScale = new Com_Scaling();
	p_mRetScale->SetSpeed(30.0f, -30.0f);
	p_mRetScale->SetTime(0.6f);
	p_mRetScale->SetUpdate(false);
	p_mReturn->AddComponent(p_mRetScale);
	p_mReturn->SetScale(1920.0f * 0.15f, 1080.0f * 0.15f, 1.0f);
	p_mReturn->SetPosition(1100.0f, 530.0f, 1.0f);
	AddGameObject(p_mReturn);

	// もう一度遊ぶ
	p_mOnemore = new GameObject("more");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_mOnemore->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(4);
	sprite->SetUpdate(true);
	p_mOnemore->AddComponent(sprite);
	p_mOneScale = new Com_Scaling();
	p_mOneScale->SetSpeed(30.0f, -30.0f);
	p_mOneScale->SetTime(0.6f);
	p_mOneScale->SetUpdate(false);
	p_mOnemore->AddComponent(p_mOneScale);
	p_mOnemore->SetScale(1920.0f * 0.15f, 1080.0f * 0.15f, 1.0f);
	p_mOnemore->SetPosition(1100.0f, 635.0f, 1.0f);
	AddGameObject(p_mOnemore);

	// 矢印
	p_mAllow = new GameObject("allow");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_mAllow->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/sozai3.png");
	sprite->SetSeparateNum(1, 1);
	sprite->SetCurrent(1);
	sprite->SetUpdate(true);
	p_mAllow->AddComponent(sprite);
	p_mAllow->SetScale(80.0f, 80.0f, 1.0f);
	p_mAllow->SetPosition(950.0f, 545.0f, 0.0f);
	AddGameObject(p_mAllow);

	

	// トータルスコア
	string sState = ReadDataFromCSV("asset/data/csv/TotalScoreUI.csv", 1);
	vector<string> sv = SeparateString(sState,',');

	Vector2 InitPos;
	InitPos.x = stof(sv[0]);
	InitPos.y = stof(sv[1]);
	Vector2 Scale;
	Scale.x = stof(sv[2]);
	Scale.y = stof(sv[3]);
	float duration = stof(sv[4]);
	for (int i = 0; i < 6; i++)
	{
		p_mScores[i] = new OBJ_Number();
		p_mScores[i]->GetSpriteCom()->SetTexture("asset/texture/result_score.png");
		p_mScores[i]->SetScale(Scale.x, Scale.y, 1.0f);
		p_mScores[i]->SetPosition(InitPos.x - (Scale.x * i) - (duration * i), InitPos.y, 1.0f);
		AddGameObject(p_mScores[i]);
	}

	//// モデル2D表示テスト
	//GameObject* pen = new GameObject("pn");
	//shader = new Com_Shader();
	//shader->p_mVS->Load("shader\\VS_OneSkinAnimation.cso");
	//shader->p_mPS->Load(PS_MODEL);
	//pen->AddComponent(shader);
	//Com_Model* mod = new Com_Model();
	//mod->SetModelData("Penguin");
	//mod->b2D = true;
	//pen->AddComponent(mod);
	//pen->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -3.0f);
	//pen->SetScale(100.0f, 100.0f, 100.0f);
	//AddGameObject(pen, 7);

	string ss = ReadDataFromCSV("asset/data/csv/ClearSetting.csv", 1);
	vector<string> sp = SeparateString(ss, ',');

	// リザルトぺんぺん
	p_mPenguin = new OBJ_ResultPenguin("pen");
	p_mPenguin->SetPosition(stof(sp[0]), stof(sp[1]), 1.0f);
	p_mPenguin->SetScale(stof(sp[2]), stof(sp[3]), 1.0f);
	AddGameObject(p_mPenguin);

	// 遷移用オブジェクト
	p_mTransition = new OBJ_Transition();
	p_mTransition->SetState(OBJ_Transition::FadeState::InEnd);
	AddGameObject(p_mTransition);

	// 音
	p_mSECursor = new Com_Audio();
	p_mSECursor->Load("asset\\audio\\SE\\SE その他\\カーソル移動.wav");

	p_mSEDecide = new Com_Audio();
	p_mSEDecide->Load("asset\\audio\\SE\\SE その他\\決定.wav");

	p_mSEDrum = new Com_Audio();
	p_mSEDrum->Load("asset\\audio\\SE\\SE その他\\リザルトドラムロール.wav");

	p_mSEResult = new Com_Audio();
	p_mSEResult->Load("asset\\audio\\SE\\SE その他\\リザルト発表.wav");
}

void Scene_Clear::Start()
{
	// スコア関連の取得
	iTotalScore = OBJ_Score::GetScore();
	isc = iTotalScore;
	isc = isc / fDrumDuration;
	iMaxCombo = OBJ_Score::GetMaxCombo();
	iBreakAzarashiNum = OBJ_Score::GetBreakNum();
	iRemainIceNum = OBJ_Score::GetIceNum();

	if (iTotalScore < 100000)
	{
		p_mScores[5]->SetActive(false);
	}
	if (iTotalScore < 10000)
	{
		p_mScores[4]->SetActive(false);
	}
	if (iTotalScore < 1000)
	{
		p_mScores[3]->SetActive(false);
	}
	if (iTotalScore < 100)
	{
		p_mScores[2]->SetActive(false);
	}
	if (iTotalScore < 10)
	{
		p_mScores[1]->SetActive(false);
	}

	// テスト用入力待ち
	mState = ClearState::WaitTotal;

	p_mSEDrum->Play();
}

void Scene_Clear::Update()
{
	if (bThisOne)
	{
		cnt++;
		if (cnt > 2)
		{
			bThisOne = false;
		}
	}
	else
	{
		switch (mState)
		{
		case Scene_Clear::ClearState::WaitState:

			break;
		case Scene_Clear::ClearState::WaitTotal:
		{
			fDrumCnt += Time->GetDeltaTime();
			if (fDrumCnt > fDrumDuration)
			{
				fDrumCnt = 0.0f;
				bSEEnd = true;
			}

			currentsco += static_cast<int>(isc * Time->GetDeltaTime());
			if (currentsco >= iTotalScore)
			{
				currentsco = iTotalScore;
				bSEEnd = true;
			}
			if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
			{
				currentsco = iTotalScore;
			}
			int val = 1000000;
			int waru = 100000;
			for (int i = 5; i >= 0; i--)
			{
				int num = currentsco % val;
				p_mScores[i]->SetNum(num / waru);
				val *= 0.1f;
				waru *= 0.1f;
			}



			if (currentsco == iTotalScore && bSEEnd == true)
			{
				p_mSEDrum->Stop();
				p_mSEResult->Play();
				p_mPenguin->SetUpdate(true);
				mState = ClearState::WaitInput;
			}
		}
		break;
		case Scene_Clear::ClearState::WaitInput:
			if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
			{
				p_mSEDecide->Play();
				if (bisUP)
				{
					mState = ClearState::ToTitle;
					p_mTransition->FadeOut(1);
				}
				else
				{
					mState = ClearState::ToGame;
					p_mTransition->FadeOut(1);
				}
			}
			else if (Controller_Input::GetLeftStick(0).y > 0.5f || Controller_Input::GetButton(0, GAMEPAD_UP) == KEYSTATE::KEY_DOWN ||
				Input::GetKeyState(KEYCODE_W) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_UP) == KEYSTATE::KEY_DOWN)
			{
				if (!bisUP)
				{
					p_mSECursor->Play();
				}
				bisUP = true;
				p_mAllow->SetPosition(950.0f, 545.0f, 0.0f);
				p_mBanner->SetPosition(1100.0, 545.0f, 0.0f);
				p_mRetScale->SetUpdate(true);
				p_mOneScale->SetUpdate(false);
			}
			else if (Controller_Input::GetLeftStick(0).y < -0.5f || Controller_Input::GetButton(0, GAMEPAD_DOWN) == KEYSTATE::KEY_DOWN ||
				Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_DOWN) == KEYSTATE::KEY_DOWN)
			{
				if (bisUP)
				{
					p_mSECursor->Play();
				}
				bisUP = false;
				p_mAllow->SetPosition(950.0f, 620.0f, 0.0f);
				p_mBanner->SetPosition(1100.0, 620.0f, 0.0f);
				p_mRetScale->SetUpdate(false);
				p_mOneScale->SetUpdate(true);
			}

			break;
		case Scene_Clear::ClearState::ToTitle:
			if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
			{
				GameManager::SetGameState(GameState::Title);
				Manager::SetNextScene<Scene_Title>();
			}
			break;
		case Scene_Clear::ClearState::ToGame:
			if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
			{
				GameManager::SetGameState(GameState::GameFade);
				Manager::SetNextScene<Scene_Game>();
			}
			break;
		default:
			break;
		}
	}
	
}

void Scene_Clear::Uninit()
{

	p_mSEDrum->Stop();
	p_mSEDrum->Uninit();
	delete p_mSEDrum;

	p_mSEResult->Stop();
	p_mSEResult->Uninit();
	delete p_mSEResult;

	p_mSECursor->Stop();
	p_mSECursor->Uninit();
	delete p_mSECursor;

	p_mSEDecide->Stop();
	p_mSEDecide->Uninit();
	delete p_mSEDecide;
}
