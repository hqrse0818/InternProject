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
	ice->SetPosition(1000.0f, 540.0f, 0.0f);
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
	ice->SetPosition(1000.0f, 650.0f, 0.0f);
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
	p_mBanner->SetPosition(1000.0, 545.0f, 0.0f);
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
	p_mReturn->SetPosition(1000.0f, 600.0f, 1.0f);
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
	p_mOnemore->SetPosition(1000.0f, 550.0f, 1.0f);
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
	p_mAllow->SetPosition(850.0f, 545.0f, 0.0f);
	AddGameObject(p_mAllow);

	

	// トータルスコア
	string sState = ReadDataFromCSV("asset/data/csv/TotalScoreUI.csv", 1);
	vector<string> sv = SeparateString(sState, ',');

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

	InitPos.x = stof(sv[5]);
	InitPos.y = stof(sv[6]);
	Scale.x = stof(sv[7]);
	Scale.y = stof(sv[8]);
	duration = stof(sv[9]);

	// 氷の数字
	for (int i = 0; i < 5; i++)
	{
		p_mICes[i] = new OBJ_Number();
		p_mICes[i]->GetSpriteCom()->SetTexture("asset/texture/result_score.png");
		p_mICes[i]->SetScale(Scale.x, Scale.y, 0.0f);
		p_mICes[i]->SetPosition(InitPos.x - (Scale.x * i) - (duration * i), InitPos.y, 0.0f);
		AddGameObject(p_mICes[i]);
	}


	// コンボ数
	InitPos.x = stof(sv[10]);
	InitPos.y = stof(sv[11]);
	Scale.x = stof(sv[12]);
	Scale.y = stof(sv[13]);
	duration = stof(sv[14]);

	for (int i = 0; i < 3; i++)
	{
		p_mComs[i] = new OBJ_Number();
		p_mComs[i]->GetSpriteCom()->SetTexture("asset/texture/result_score.png");
		p_mComs[i]->SetScale(Scale.x, Scale.y, 0.0f);
		p_mComs[i]->SetPosition(InitPos.x - (Scale.x * i) - (duration * i), InitPos.y, 0.0f);
		AddGameObject(p_mComs[i]);
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
	obj->SetPosition(stof(sp[4]), stof(sp[5]), 0.0f);
	obj->SetScale(stof(sp[6]), stof(sp[7]), 0.0f);
	AddGameObject(obj);

	GameObject* pFontIce = new GameObject("icef");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	pFontIce->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset//texture/result_submozi.png");
	sprite->SetSeparateNum(1, 2);
	sprite->SetCurrent(1);
	pFontIce->AddComponent(sprite);
	pFontIce->SetPosition(stof(sp[8]), stof(sp[9]), 0.0f);
	pFontIce->SetScale(stof(sp[10]), stof(sp[11]), 0.0f);
	AddGameObject(pFontIce);

	GameObject* pFontCom = new GameObject("comf");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	pFontCom->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset//texture/result_submozi.png");
	sprite->SetSeparateNum(1, 2);
	sprite->SetCurrent(2);
	pFontCom->AddComponent(sprite);
	pFontCom->SetPosition(stof(sp[12]), stof(sp[13]), 0.0f);
	pFontCom->SetScale(stof(sp[14]), stof(sp[15]), 0.0f);
	AddGameObject(pFontCom);

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

	p_mPoint = new Com_Audio();
	p_mPoint->Load("asset\\audio\\SE\\SE その他\\ポイント.wav");
	p_mPoint->SetVolume(0.125f);

	p_mVoice = new Com_Audio();
	p_mVoice->Load("asset\\audio\\SE\\SE その他\\patipati.wav");
	p_mVoice->SetVolume(0.15f);

	p_mVoice2 = new Com_Audio();
	p_mVoice2->Load("asset\\audio\\SE\\SE その他\\patipati.wav");
	p_mVoice2->SetVolume(0.15f);
}

void Scene_Clear::Start()
{
	// スコア関連の取得
	iTotalScore = OBJ_Score::GetScore();
	iTotalScore = iTotalScore + OBJ_Score::GetIceScore();
	isc = iTotalScore;
	isc = isc / fDrumDuration;

	iMaxCombo = OBJ_Score::GetMaxCombo();
	ico = 100;

	iBreakAzarashiNum = OBJ_Score::GetBreakNum();
	
	iIceScore = OBJ_Score::GetIceScore();
	iic = iIceScore / (fDrumDuration / 2);

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

	if (iIceScore < 10000)
	{
		p_mICes[4]->SetActive(false);
	}
	if (iIceScore < 1000)
	{
		p_mICes[3]->SetActive(false);
	}
	if (iIceScore < 100)
	{
		p_mICes[2]->SetActive(false);
		p_mICes[1]->SetActive(false);
	}

	if (iMaxCombo < 100)
	{
		p_mComs[2]->SetActive(false);
	}
	if (iMaxCombo < 10)
	{
		p_mComs[1]->SetActive(false);
	}

	// テスト用入力待ち
	mState = ClearState::WaitIce;
}

void Scene_Clear::Update()
{
	if (bThisOne)
	{
		cnt++;
		if (cnt > 2)
		{
			bThisOne = false;
			p_mPoint->Play(true);
		}
	}
	else
	{
		switch (mState)
		{
		case Scene_Clear::ClearState::WaitIce:
		{
			currentice += static_cast<int>(iic * Time->GetDeltaTime());

			if (currentice >= iIceScore)
			{
				currentice = iIceScore;
			}

			if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
			{
				currentice = iIceScore;
			}

			int val = 100000;
			int waru = 10000;
			for (int i = 4; i >= 0; i--)
			{
				int num = currentice % val;

				int s = num / waru;

				p_mICes[i]->SetNum(num / waru);
				val *= 0.1f;
				waru *= 0.1f;
			}
			

			if (currentice == iIceScore)
			{
				mState = ClearState::WaitCombo;
			}
		}
			break;
		case Scene_Clear::ClearState::WaitCombo:
		{
			currentcom += static_cast<int>(ico * Time->GetDeltaTime());

			if (currentcom >= iMaxCombo)
			{
				currentcom = iMaxCombo;
			}

			if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
			{
				currentcom = iMaxCombo;
			}

			int val = 1000;
			int waru = 100;

			for (int i = 2; i >= 0; i--)
			{
				int num = currentcom % val;
				p_mComs[i]->SetNum(num / waru);
				val *= 0.1f;
				waru *= 0.1f;
			}

			if (currentcom == iMaxCombo)
			{
				p_mPoint->Stop();
				p_mSEDrum->Play();
				mState = ClearState::WaitTotal;
			}

		}
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
				p_mVoice->Play();
				p_mPenguin->SetUpdate(true);
				p_mOneScale->SetUpdate(true);
				mState = ClearState::WaitInput;
			}
		}
		break;
		case Scene_Clear::ClearState::WaitInput:
			
			if (!bVoice)
			{
				fVoiceCnt += Time->GetDeltaTime();
				if (fVoiceCnt >= fVoiceDuration)
				{
					bVoice = true;
					p_mVoice2->Play();
				}
			}

			if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
			{
				p_mSEDecide->Play();
				if (bisUP)
				{
					p_mVoice->Stop();
					p_mVoice2->Stop();
					mState = ClearState::ToGame;
					p_mTransition->FadeOut(1);
				}
				else
				{	
					p_mVoice->Stop();
					p_mVoice2->Stop();
					mState = ClearState::ToTitle;
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
				p_mAllow->SetPosition(850.0f, 545.0f, 0.0f);
				p_mBanner->SetPosition(1000.0, 545.0f, 0.0f);
				p_mRetScale->SetUpdate(false);
				p_mOneScale->SetUpdate(true);
			}
			else if (Controller_Input::GetLeftStick(0).y < -0.5f || Controller_Input::GetButton(0, GAMEPAD_DOWN) == KEYSTATE::KEY_DOWN ||
				Input::GetKeyState(KEYCODE_S) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_DOWN) == KEYSTATE::KEY_DOWN)
			{
				if (bisUP)
				{
					p_mSECursor->Play();
				}
				bisUP = false;
				p_mAllow->SetPosition(850.0f, 620.0f, 0.0f);
				p_mBanner->SetPosition(1000.0, 620.0f, 0.0f);
				p_mRetScale->SetUpdate(true);
				p_mOneScale->SetUpdate(false);
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
	p_mVoice2->Stop();
	p_mVoice2->Uninit();
	delete p_mVoice2;

	p_mVoice->Stop();
	p_mVoice->Uninit();
	delete p_mVoice;

	p_mPoint->Stop();
	p_mPoint->Uninit();
	delete p_mPoint;

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
