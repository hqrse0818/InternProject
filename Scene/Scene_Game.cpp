#include "Scene_Game.h"
#include "GameInclude.h"
#include "../main.h"
#include "../System/manager.h"
#include "Scene_Clear.h"


using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Game::Init()
{
	// 当たり判定アクティブ化
	bCheckCol = true;

	// ペンギン
	p_mPlayer = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");
	AddKeyObject(p_mPlayer);

	//ヒップインパクト用エフェクト
	OBJ_HipEffect* HipEffect = new OBJ_HipEffect("HipEffect");
	HipEffect->SetTarget(p_mPlayer);
	p_mPlayer->SetHipEffect(HipEffect);
	AddGameObject(HipEffect);
	// ジャンプ用エフェクト
	OBJ_JumpEffect* JumpEffect = new OBJ_JumpEffect("JumpEff");
	JumpEffect->SetTarget(p_mPlayer);
	p_mPlayer->SetJumpEffect(JumpEffect);
	AddGameObject(JumpEffect);
	

	// カメラ
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(p_mPlayer);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);
	AddGameObject(Camera, 0);

	// ビルボードのカメラ設定
	Com_EffectBillboard::SetCamera(Camera_buf);
	Com_Billboard::SetCamera(Camera_buf);

	// ペンギン関連のカメラ設定
	p_mPlayer->GetMoveCom()->SetCameraCom(Camera_buf);
	p_mPlayer->SetCameraCom(Camera_buf);

	// アザラシ
	{
		// アザラシマネージャー
		OBJ_AzarashiManager* AManager = new OBJ_AzarashiManager("manager", "asset/data/csv/AzarashiManager.csv");
		AddGameObject(AManager, 0);

		//アザラシの残機
		GameObject* ARemain = new GameObject("ARemainOBJ");

		Com_CustomSprite* Sprite_buf = new Com_CustomSprite;
		Sprite_buf->mType = Com_CustomSprite::CustomType::LeftTop; //CustomSpriteでポジション設定
		Sprite_buf->SetTexture("asset/texture/nokori.png");

		Com_Shader* Shader_buf = new Com_Shader();
		Shader_buf->p_mVS->Load(VS_SPRITE);
		Shader_buf->p_mPS->Load(PS_SPRITE);

		ARemain->AddComponent(Shader_buf);
		ARemain->AddComponent(Sprite_buf);

		ARemain->p_mTransform->mScale.x = 100.0f;
		ARemain->p_mTransform->mScale.y = 100.0f;
		AddGameObject(ARemain);

		//アザラシの残機（数字）
		OBJ_AzarashiRemain* ARemainNum = new OBJ_AzarashiRemain("Zanki", "asset/data/csv/AzarashiZankiUI.csv");
		AddGameObject(ARemainNum);
	}

	// 海オブジェクト
	{
		OBJ_Sea* Sea = new OBJ_Sea("Sea");
		Sea->SetPosition(0.0f, -30.0f, 0.0f);
		AddGameObject(Sea);
		// 海用スプライト
		OBJ_SeaSprite* seasprite = new OBJ_SeaSprite("umi");
		seasprite->SetScale(1.0f, 1.0f, 1.0f);
		seasprite->GetSpriteCom()->SetUV(2.0f, 2.0f);
		seasprite->GetSpriteCom()->SetSize(500.0f, 500.0f);
		AddGameObject(seasprite, 3);
	}
	// 背景
	OBJ_BackGround* back = new OBJ_BackGround("haikei");
	AddGameObject(back);

	// ステージ設計
	{
		// ステージのブロック数の読み込み
		string sStageNum = ReadDataFromCSV("asset/data/csv/Stage.csv", 1);
		std::vector<string> IceSetting = SeparateString(sStageNum, ',');
		unsigned int stagenum = stoi(IceSetting[0]);
		// ステージの最大のインデックスを格納
		OBJ_Ice::s_iMaxNumIndex = stagenum - 1;
		float IceScale = stof(IceSetting[1]);

		int Stagecenter = 0;

		if (stagenum % 2 == 0)
		{
			Stagecenter = stagenum / 2;
		}
		else
		{
			Stagecenter = stagenum / 2 + 1;
		}

		// 生成の開始位置計算
		int StageInit = IceScale * -Stagecenter;

		// 氷マネージャー
		OBJ_IceManager* iMana = new OBJ_IceManager("iMana", "asset/data/csv/IceStatus.csv");
		AddGameObject(iMana);

		float time = iMana->GetShakeTime();
		float pow = iMana->GetShakePower();
		Vector3 cen = iMana->GetColCenter();
		Vector3 size = iMana->GetColSize();
		Vector3 scale = iMana->GetScale();

		// ステージ生成
		for (int i = 0; i < stagenum; i++)
		{
			for (int j = 0; j < stagenum; j++)
			{
				// 氷の生成
				OBJ_Ice* Ice = new OBJ_Ice("Ice");
				Ice->SetShakeTime(time);
				Ice->SetShakePower(pow);
				Ice->SetScale(scale.x, scale.y, scale.z);
				Com_BoxCollider* col = Ice->GetColliderCom();
				col->mCenter = cen;
				col->mSize = size;
				Ice->p_mTransform->SetPosition(StageInit + i * col->mSize.x * Ice->p_mTransform->mScale.x, 0.0f, StageInit + j * col->mSize.z * Ice->p_mTransform->mScale.z);
				Ice->myRow = j;
				Ice->myLine = i;
				AddGameObject(Ice);
				iMana->RegisterIce(Ice);

				int r = HighRand::GetRand(1, 4);
				switch (r)
				{
				case 1:
					Ice->SetRotation(0.0f, Euler_To_Radian(90), 0.0f);
					break;
				case 2:
					Ice->SetRotation(0.0f, Euler_To_Radian(180), 0.0f);
					break;
				case 3:
					Ice->SetRotation(0.0f, Euler_To_Radian(270), 0.0f);
					break;
				case 4:
					break;
				default:
					break;
				}
			}
		}
		// 氷の位置と数から落下用オブジェクトの位置を決める
		// 左側
		OBJ_Fall* fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		// 右側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		// 上側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
		// 下側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit - ((scale.z * size.z) * 2));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
	}


	// スコア表示オブジェクト
	OBJ_DisplayScore* ScoreObj = new OBJ_DisplayScore("dis", "asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// スコアマネージャー
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// コンボ表示オブジェクト
	OBJ_ComboDisplay* ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
	AddGameObject(ComboObj);
	

	// ゲームBGM
	p_mBGM = new Com_Audio();
	p_mBGM->Load("asset\\audio\\BGM\\メイン BGM.wav");
	p_mBGM->SetUseTarget(false);

	// カウントダウン用のオブジェクト作成
	p_mObjNum = new GameObject("Num");
	p_mSpriteNum = new Com_CustomSprite();
	p_mSpriteNum->SetTexture("asset\\texture\\cowntdown.png");
	p_mSpriteNum->mType = Com_CustomSprite::CustomType::Center;
	p_mSpriteNum->SetSeparateNum(5, 2);
	p_mSpriteNum->SetCurrent(3);
	p_mSpriteNum->SetUpdate(true);
	p_mObjNum->AddComponent(p_mSpriteNum);
	p_mObjNum->SetScale(0.0f, 0.0f, 1.0f);
	p_mObjNum->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	AddGameObject(p_mObjNum);
	p_mSECount = new Com_Audio();
	p_mSECount->Load("asset\\audio\\SE\\SE その他\\カウントダウン.wav");
	// 開始用オブジェクト
	p_mObjGo = new GameObject("Go");
	p_mSpriteGo = new Com_CustomSprite();
	p_mSpriteGo->SetTexture("asset\\texture\\countdown_go.png");
	p_mSpriteGo->mType = Com_CustomSprite::CustomType::Center;
	p_mSpriteGo->SetSeparateNum(1, 1);
	p_mSpriteGo->SetCurrent(1);
	p_mSpriteGo->SetUpdate(true);
	p_mObjGo->AddComponent(p_mSpriteGo);
	p_mObjGo->SetScale(0.0f, 0.0f, 1.0f);
	p_mObjGo->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	AddGameObject(p_mObjGo);
	p_mSEGo = new Com_Audio();
	p_mSEGo->Load("asset\\audio\\SE\\SE その他\\ゲーム開始.wav");

	// 遷移用オブジェクト
	p_mTransition = new OBJ_Transition("tra");
	p_mTransition->SetState(OBJ_Transition::FadeState::OutEnd);
	AddGameObject(p_mTransition);
}

void Scene_Game::Start()
{
	p_mTransition->FadeIn(1.5);
	// 開始前状態に設定
	GameManager::SetGameState(GameState::GameFade);

	// プレイヤーの位置を設定
	p_mPlayer->p_mTransform->SetPosition(0.0f, 2.0f, 0.0f);
	
	// カーソルを非表示
	ShowCursor(false);
	Input::SetCursorCenterEnable();
}

void Scene_Game::Update()
{
	GameManager::Update();

	switch (GameManager::GetGameState())
	{
	case GameState::GameFade:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::InEnd)
		{
			GameManager::SetGameState(GameState::WaitStart);
		}
		break;

	case GameState::WaitStart:
	{
		if (fWaitCnt > fWaitTime)
		{
			GameManager::SetGameState(GameState::Game);
			p_mBGM->Play(true);
		}
		else if (fWaitCnt > 4)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjGo->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > fWaitTime)
			{
				p_mSEGo->Play();
				p_mObjGo->SetScale(0.0f, 0.0f, 0.0f);
				p_mObjGo->bDestroy = true;
			}
		}
		else if (fWaitCnt > 3)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjNum->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > 4)
			{
				p_mSECount->Play();
				p_mObjNum->SetScale(0.0f, 0.0f, 0.0f);
				p_mObjNum->bDestroy = true;
			}
		}
		else if (fWaitCnt > 2)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjNum->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > 3)
			{
				p_mSECount->Play();
				p_mObjNum->SetScale(0.0f, 0.0f, 0.0f);
				p_mSpriteNum->SetCurrent(1);
			}
		}
		else if (fWaitCnt > 1)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjNum->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > 2)
			{
				p_mSECount->Play();
				p_mObjNum->SetScale(0.0f, 0.0f, 0.0f);
				p_mSpriteNum->SetCurrent(2);
			}
		}
		else
		{
			fWaitCnt += Time->GetDeltaTime();
		}
	}
		break;

	case GameState::TransToClear:
		p_mTransition->FadeOut(1.5);
		GameManager::SetGameState(GameState::ClearFade);
		break;

	case GameState::ClearFade:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
		{
			GameManager::SetGameState(GameState::Clear);
			Manager::SetNextScene<Scene_Clear>();
		}
		break;

	case GameState::TransToOver:
		p_mTransition->FadeOut(1.5);
		GameManager::SetGameState(GameState::OverFade);
		break;

	case GameState::OverFade:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
		{
			GameManager::SetGameState(GameState::Over);
			Manager::SetNextScene<Scene_Clear>();
		}
		break;

	default:
		break;
	}
}

void Scene_Game::Uninit()
{
	ShowCursor(true);
	Input::SetCursorCenterDisable();

	p_mBGM->Stop();
	p_mBGM->Uninit();
	delete p_mBGM;

	p_mSECount->Stop();
	p_mSECount->Uninit();
	delete p_mSECount;

	p_mSEGo->Stop();
	p_mSEGo->Uninit();
	delete p_mSEGo;
}
