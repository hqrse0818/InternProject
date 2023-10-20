#include "Scene_Test.h"
#include "../ComponentHeader.h"
#include "../System/Input.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"
#include "../System/manager.h"

#include "../InternCodeAdachi/OBJ_Penguin.h"
#include "../InternCodeAdachi/OBJ_Azarashi.h"
#include "../InternCodeAdachi/Com_AngleCamera.h"
#include "../InternCodeAdachi/OBJ_Ice.h"
#include "../InternCodeAdachi/OBJ_Sea.h"
#include "../InternCodeAdachi/OBJ_AzarashiManager.h"
#include "../Component/Com_CameraTransform.h"
#include "../Component/Com_Billboard.h"
#include "../InternCodeAdachi/CSVLoad.h"
#include "../InternCode.Kizuki/OBJ_AzarashiRemain.h"
#include "../InternCodeAdachi/OBJ_BackGround.h"
#include "../InternCodeAdachi/OBJ_IceManager.h"
#include "../InternCodeAdachi/OBJ_DisplayScore.h"
#include "../InternCodeAdachi/OBJ_Score.h"
#include "../InternCodeAdachi/GameManager.h"
#include "../InternCodeAdachi/OBJ_ComboDisplay.h"
#include "../InternCodeAdachi/OBJ_SeaSprite.h"
#include "../InternCode.Kizuki/OBJ_HipEffect.h"
#include "../Component/Com_EffectBillboard.h"

#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Test::Init()
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
	
	// 当たり判定アクティブ化
	bCheckCol = true;

	// ペンギン
	Player = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");

	// レイヤーの指定なしでキーオブジェクトとして追加
	AddKeyObject(Player);

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

	// カメラ
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(Player);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);

	// ビルボードのカメラ設定
	Com_EffectBillboard::SetCamera(Camera_buf);

	// レイヤーを指定してオブジェクトを追加
	AddGameObject(Camera, 0);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);

	// 海オブジェクト
	OBJ_Sea* Sea = new OBJ_Sea("Sea");
	Sea->SetPosition(0.0f, -30.0f, 0.0f);

	AddGameObject(Sea);

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

	OBJ_BackGround* back = new OBJ_BackGround("haikei");
	AddGameObject(back);

	// 海用スプライト
	OBJ_SeaSprite* seasprite = new OBJ_SeaSprite("umi");
	seasprite->SetScale(1.0f, 1.0f, 1.0f);
	seasprite->GetSpriteCom()->SetUV(2.0f, 2.0f);
	seasprite->GetSpriteCom()->SetSize(500.0f, 500.0f);
	AddGameObject(seasprite,3);

	//音
	p_mAudio = new Com_Audio();
	p_mAudio->Load("asset\\audio\\BGM\\メイン BGM.wav");
	p_mAudio->SetUseTarget(false);

	// スコア表示オブジェクト
	OBJ_DisplayScore* ScoreObj = new OBJ_DisplayScore("dis","asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// スコアマネージャー
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// コンボ表示オブジェクト
	OBJ_ComboDisplay* ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
	AddGameObject(ComboObj);

	//エフェクト
	OBJ_HipEffect* HipEffect = new OBJ_HipEffect("HipEffect");
	AddGameObject(HipEffect);
	HipEffect->SetPlayer(Player);
	Player->SetHipEffect(HipEffect);
}

void Scene_Test::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 5.0f, 0.0f);
	ShowCursor(false);
	Input::SetCursorCenterEnable();
	p_mAudio->Play(true);
}

void Scene_Test::Update()
{
	// デバッグ用
	// カーソルを表示するように切り替えて毎フレーム中心に強制的にセットされることを止める
	if (Input::GetKeyState(KEYCODE_9) == KEYSTATE::KEY_DOWN)
	{
		ShowCursor(true);
		Input::SetCursorCenterDisable();
	}
	// カーソルを非表示に切り替えて毎フレーム中心に強制的にセットされる
	if (Input::GetKeyState(KEYCODE_0) == KEYSTATE::KEY_DOWN)
	{
		ShowCursor(false);
		Input::SetCursorCenterEnable();
	}

	// デバッグ用シーン再読み込み
#if defined (DEBUG) | defined(_DEBUG)
	if (Controller_Input::GetButton(0, GAMEPAD_START) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_R) == KEYSTATE::KEY_DOWN)
	{
		Manager::SetScene<Scene_Test>();
	}
#endif

	// ゲームマネージャーの更新
	GameManager::Update();
}

void Scene_Test::Uninit()
{
	ShowCursor(true);
	Input::SetCursorCenterDisable();

	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}
