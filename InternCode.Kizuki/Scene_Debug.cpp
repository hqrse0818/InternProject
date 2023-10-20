#include "Scene_Debug.h"
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
#include "../InternCode.Kizuki/OBJ_AzarashiRemain.h"
#include "../Component/Com_CameraTransform.h"
#include "../Component/Com_Billboard.h"
#include "../Component/Com_EffectBillboard.h"
#include "../GameObject/OBJ_Emitter.h"
#include "../InternCode.Kizuki/OBJ_HipEffect.h"

#define IceNum (9)
#define IceScale (7)
#define InitPos (-35)

using namespace DirectX::SimpleMath;

void Scene_Debug::Init()
{
	// 当たり判定アクティブ化
	bCheckCol = true;

	// ペンギン
	Player = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");

	// レイヤーの指定なしでキーオブジェクトとして追加
	AddKeyObject(Player);

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

	Com_Billboard::SetCamera(Camera_buf);
	Com_EffectBillboard::SetCamera(Camera_buf);

	// レイヤーを指定してオブジェクトを追加
	AddGameObject(Camera, 0);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);

	// 海オブジェクト
	OBJ_Sea* Sea = new OBJ_Sea("Sea");
	Sea->SetPosition(0.0f, -30.0f, 0.0f);

	AddGameObject(Sea);

	OBJ_AzarashiManager* AManager = new OBJ_AzarashiManager("manager", "asset\\data\\csv\\AzarashiManager.csv");
	AddGameObject(AManager, 0);

	//アザラシの残機（キャラクター画像）
	GameObject* ARemainChar = new GameObject("ARemainChar");

	Com_CustomSprite* Sprite_buf = new Com_CustomSprite;
	Sprite_buf->mType = Com_CustomSprite::CustomType::LeftTop; //CustomSpriteでポジション設定
	Sprite_buf->SetTexture("asset/texture/nokori.png");

	Com_Shader* Shader_buf = new Com_Shader();
	Shader_buf->p_mVS->Load(VS_SPRITE);
	Shader_buf->p_mPS->Load(PS_SPRITE);

	ARemainChar->AddComponent(Shader_buf);
	ARemainChar->AddComponent(Sprite_buf);

	ARemainChar->p_mTransform->mScale.x = 100.0f;
	ARemainChar->p_mTransform->mScale.y = 100.0f;
	AddGameObject(ARemainChar);

	//アザラシの残機（数字）
	OBJ_AzarashiRemain* ARemainNum = new OBJ_AzarashiRemain("ARemainNum","asset/data/csv/AzarashiZankiUI.csv");
	AddGameObject(ARemainNum);

	//エフェクト
	//OBJ_Emitter* Effect = new OBJ_Emitter("Effect");
	//Effect->TexCreate("asset/texture/start.png");
	//AddGameObject(Effect);

	OBJ_HipEffect* HipEffect = new OBJ_HipEffect("HipEffect");
	HipEffect->SetPlayer(Player); //エフェクトポジション
	Player->SetHipEffect(HipEffect); //タイミング
	AddGameObject(HipEffect);

	//音
	p_mAudio = new Com_Audio();
	p_mAudio->Load("asset\\audio\\BGM\\メイン BGM.wav");
	p_mAudio->SetUseTarget(false);
}

void Scene_Debug::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 5.0f, 0.0f);
	ShowCursor(false);
	Input::SetCursorCenterEnable();
	p_mAudio->Play(true);
}

void Scene_Debug::Update()
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
		Manager::SetScene<Scene_Debug>();
	}
#endif
}

void Scene_Debug::Uninit()
{
	ShowCursor(true);
	Input::SetCursorCenterDisable();

	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}
