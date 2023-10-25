#include "Scene_Game.h"
#include "GameInclude.h"
#include "../main.h"
#include "../System/manager.h"
#include "Scene_Clear.h"
#include "Scene_Title.h"
#include "../InternCodeAdachi/OBJ_BackPenguinBlue.h"
#include "../InternCodeAdachi/OBJ_BackPenguinRed.h"
#include "../InternCodeAdachi/OBJ_Sky.h"
#include "../InternCodeAdachi/OBJ_Warning.h"


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
		AManager->SetTarget(p_mPlayer);
		AddGameObject(AManager, 0);

		

		//アザラシの残機（数字）
		ARemainNum = new OBJ_AzarashiRemain("Zanki", "asset/data/csv/AzarashiZankiUI.csv");
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
		seasprite->GetSpriteCom()->SetUV(60.0f, 60.0f);
		seasprite->GetSpriteCom()->SetSize(15000.0f, 15000.0f);
		AddGameObject(seasprite, 3);
	}
	// 背景
	OBJ_BackGround* back = new OBJ_BackGround("haikei");
	AddGameObject(back);


	// 背景ペンギン
	{
		//1
		OBJ_BackPenguinBlue* bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-115.0f, 3.8f, -40.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(70.0f), 0.0f);
		AddGameObject(bp);
		//2
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-115.0f, 3.8f, -22.0f);
		bp->SetDelay(1.2f);
		bp->SetRotation(0.0f, Euler_To_Radian(100.0f), 0.0f);
		AddGameObject(bp);
		//3
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(116.0f, 6.6f, -9.0f);
		bp->SetDelay(0.3f);
		bp->SetRotation(0.0f, Euler_To_Radian(-70.0f), 0.0f);
		AddGameObject(bp);
		//4
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(110.0f, 6.6f, 40.0f);
		bp->SetDelay(0.7f);
		bp->SetRotation(0.0f, Euler_To_Radian(-110.0f), 0.0f);
		AddGameObject(bp);
		//5
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-110.0f, 6.8f, -85.0f);
		bp->SetDelay(1.1f);
		bp->SetRotation(0.0f, Euler_To_Radian(60.0f), 0.0f);
		AddGameObject(bp);
		//6
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-100.0f, 6.8f, -95.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(40.0f), 0.0f);
		AddGameObject(bp);
		//7
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-10.0f, 11.0f, -122.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(0.0f), 0.0f);
		AddGameObject(bp);
		//8
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(22.0f, 11.0f, -128.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(-10.0f), 0.0f);
		AddGameObject(bp);
		//9
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(41.0f, 11.0f, -124.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(-20.0f), 0.0f);
		AddGameObject(bp);
		//10
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(58.0f, 11.0f, -126.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(-30.0f), 0.0f);
		AddGameObject(bp);
		//11
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-4.0f, 6.4f, -111.0f);
		bp->SetDelay(1.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(-6.0f), 0.0f);
		AddGameObject(bp);
		//12
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(4.0f, 4.5f, 133.0f);
		bp->SetDelay(0.8f);
		bp->SetRotation(0.0f, Euler_To_Radian(180.0f), 0.0f);
		AddGameObject(bp);
		//13
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-12.0f, 6.5f, 137.0f);
		bp->SetDelay(1.2f);
		bp->SetRotation(0.0f, Euler_To_Radian(175.0f), 0.0f);
		AddGameObject(bp);
		//14
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-78.0f, 8.5f, 110.0f);
		bp->SetDelay(0.4f);
		bp->SetRotation(0.0f, Euler_To_Radian(150.0f), 0.0f);
		AddGameObject(bp);
		//15
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-75.0f, 20.7f, 120.0f);
		bp->SetDelay(2.5f);
		bp->SetRotation(0.0f, Euler_To_Radian(160.0f), 0.0f);
		AddGameObject(bp);
		//16
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-110.0f, 2.5f, 90.0f);
		bp->SetDelay(1.8f);
		bp->SetRotation(0.0f, Euler_To_Radian(120.0f), 0.0f);
		AddGameObject(bp);
		//17
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-40.0f, 21.4f, -137.0f);
		bp->SetDelay(2.0f);
		bp->SetRotation(0.0f, Euler_To_Radian(10.0f), 0.0f);
		AddGameObject(bp);
		//18
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-55.0f, 21.4f, -137.0f);
		bp->SetDelay(0.2f);
		bp->SetRotation(0.0f, Euler_To_Radian(20.0f), 0.0f);
		AddGameObject(bp);
		//19
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-134.0f, 12.4f, -96.0f);
		bp->SetDelay(1.0f);
		bp->SetRotation(0.0f, Euler_To_Radian(48.0f), 0.0f);
		AddGameObject(bp);
		//20
		bp = new OBJ_BackPenguinBlue("blue");
		bp->SetPosition(-104.0f, 12.4f, -115.0f);
		bp->SetDelay(1.3f);
		bp->SetRotation(0.0f, Euler_To_Radian(38.0f), 0.0f);
		AddGameObject(bp);



		// 背景用ペンギン(赤)
		//1
		OBJ_BackPenguinRed* rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(121.0f, 6.6f, 0.0f);
		rp->SetDelay(0.2f);
		rp->SetRotation(0.0f, Euler_To_Radian(-90.0f), 0.0f);
		AddGameObject(rp);
		//2
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(110.0f, 6.6f, 10.0f);
		rp->SetDelay(0.0f);
		rp->SetRotation(0.0f, Euler_To_Radian(-100.0f), 0.0f);
		AddGameObject(rp);
		//3
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(6.0f, 6.4f, -111.0f);
		rp->SetDelay(0.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(0.0f), 0.0f);
		AddGameObject(rp);
		//4
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-18.0f, 6.4f, -118.0f);
		rp->SetDelay(0.6f);
		rp->SetRotation(0.0f, Euler_To_Radian(10.0f), 0.0f);
		AddGameObject(rp);
		//5
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-41.0f, 11.0f, -121.0f);
		rp->SetDelay(1.4f);
		rp->SetRotation(0.0f, Euler_To_Radian(12.0f), 0.0f);
		AddGameObject(rp);
		//6
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(18.0f, 6.4f, -110.0f);
		rp->SetDelay(2.2f);
		rp->SetRotation(0.0f, Euler_To_Radian(-10.0f), 0.0f);
		AddGameObject(rp);
		//7
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(29.0f, 6.4f, -120.0f);
		rp->SetDelay(0.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(-12.0f), 0.0f);
		AddGameObject(rp);
		//8
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(110.0f, 6.6f, 52.0f);
		rp->SetDelay(1.6f);
		rp->SetRotation(0.0f, Euler_To_Radian(-85.0f), 0.0f);
		AddGameObject(rp);
		//9
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(19.0f, 11.5f, 138.0f);
		rp->SetDelay(0.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(189.0f), 0.0f);
		AddGameObject(rp);
		//10
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-90.0f, 8.5f, 100.0f);
		rp->SetDelay(1.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(140.0f), 0.0f);
		AddGameObject(rp);
		//11
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-107.0f, 14.9f, 100.0f);
		rp->SetDelay(1.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(140.0f), 0.0f);
		AddGameObject(rp);
		//12
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-89.0f, 15.1f, 115.0f);
		rp->SetDelay(2.8f);
		rp->SetRotation(0.0f, Euler_To_Radian(140.0f), 0.0f);
		AddGameObject(rp);
		//13
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-20.0f, 21.4f, -141.0f);
		rp->SetDelay(2.2f);
		rp->SetRotation(0.0f, Euler_To_Radian(0.0f), 0.0f);
		AddGameObject(rp);
		//14
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-120.0f, 12.4f, -101.0f);
		rp->SetDelay(2.2f);
		rp->SetRotation(0.0f, Euler_To_Radian(45.0f), 0.0f);
		AddGameObject(rp);
		//15
		rp = new OBJ_BackPenguinRed("red");
		rp->SetPosition(-110.0f, 12.4f, -106.0f);
		rp->SetDelay(1.3f);
		rp->SetRotation(0.0f, Euler_To_Radian(38.0f), 0.0f);
		AddGameObject(rp);
	}

	// 空
	OBJ_Sky* sky = new OBJ_Sky("sky");
	AddGameObject(sky);

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
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 200.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit - ((scale.x * size.x) * 3), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(2.0f, 40.0f, 200.0f);
		AddGameObject(fobj);
		// 右側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 200.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 2)), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(2.0f, 40.0f, 200.0f);
		AddGameObject(fobj);
		// 上側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(200.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit + ((scale.z * size.z) * (stagenum + 2)));
		fobj->GetColliderCom()->SetSize(200.0f, 40.0f, 2.0f);
		AddGameObject(fobj);
		// 下側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit - ((scale.z * size.z) * 2));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(200.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit - ((scale.z * size.z) * 3));
		fobj->GetColliderCom()->SetSize(200.0f, 40.0f, 2.0f);
		AddGameObject(fobj);
	}


	// スコア表示オブジェクト
	ScoreObj = new OBJ_DisplayScore("dis", "asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// スコアマネージャー
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// コンボ表示オブジェクト
	ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
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

	// ゲームオーバー遷移用
	p_mHalfFade = new OBJ_HalfFade("half");
	p_mHalfFade->SetState(OBJ_Transition::FadeState::InEnd);
	p_mHalfFade->SetAlpha(0.9f);
	AddGameObject(p_mHalfFade);

	// 氷
	ice1 = new GameObject("ice");
	Com_Shader* shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	ice1->AddComponent(shader);
	Com_Sprite* sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(1);
	ice1->AddComponent(sprite);
	ice1->SetScale(1920.0f * 0.175f, 1080.0f * 0.175f, 1.0f);
	ice1->SetPosition(SCREEN_WIDTH/2, 540.0f, 0.0f);
	AddGameObject(ice1);

	ice2 = new GameObject("ice");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	ice2->AddComponent(shader);
	sprite = new Com_Sprite();
	sprite->SetTexture("asset/texture/ressult_sozai.png");
	sprite->SetSeparateNum(2, 2);
	sprite->SetCurrent(3);
	ice2->AddComponent(sprite);
	ice2->SetScale(1920.0f * 0.175f, 1080.0f * 0.175f, 1.0f);
	ice2->SetPosition(SCREEN_WIDTH/2, 650.0f, 0.0f);
	AddGameObject(ice2);

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
	p_mBanner->SetPosition(SCREEN_WIDTH/2, 545.0f, 0.0f);
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
	p_mReturn->SetPosition(SCREEN_WIDTH / 2, 600.0f, 1.0f);
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
	p_mOnemore->SetPosition(SCREEN_WIDTH / 2, 550.0f, 1.0f);
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
	p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 150.0f, 545.0f, 0.0f);
	AddGameObject(p_mAllow);

	p_mOvobj = new OBJ_GameOver("over");
	p_mOvobj->SetPosition(SCREEN_WIDTH / 2, -300.0f, 0.0f);
	p_mOvobj->SetScale(1920.0f * 0.3f, 1080.0f * 0.3f, 1.0f);
	p_mOvobj->SetStopPosA(SCREEN_WIDTH / 2, -0.0f);
	p_mOvobj->SetStopPosB(SCREEN_WIDTH / 2, 150.0f);
	p_mOvobj->SetFinalPos(SCREEN_WIDTH / 2, 300.0f);
	p_mOvobj->SetWaitTime(0.2f);
	AddGameObject(p_mOvobj);


	// 遷移用オブジェクト
	p_mTransition = new OBJ_Transition("tra");
	p_mTransition->SetState(OBJ_Transition::FadeState::OutEnd);
	AddGameObject(p_mTransition,7);

	// サウンド
	// 開始音
	p_mSEGo = new Com_Audio();
	p_mSEGo->Load("asset\\audio\\SE\\SE その他\\ゲーム開始.wav");
	// カウントダウン音
	p_mSECount = new Com_Audio();
	p_mSECount->Load("asset\\audio\\SE\\SE その他\\カウントダウン.wav");
	// ゲームオーバー音
	p_mSEOver = new Com_Audio();
	p_mSEOver->Load("asset\\audio\\SE\\SE その他\\ゲームオーバー.wav");
	// カーソル
	p_mSECursor = new Com_Audio();
	p_mSECursor->Load("asset\\audio\\SE\\SE その他\\カーソル移動.wav");
	// 決定
	p_mSEDecide = new Com_Audio();
	p_mSEDecide->Load("asset\\audio\\SE\\SE その他\\決定.wav");
	// クリア
	p_mSEClear = new Com_Audio();
	p_mSEClear->Load("asset\\audio\\SE\\SE その他\\ゲームクリア.wav");
}

void Scene_Game::Start()
{
	ice1->SetActive(false);
	ice2->SetActive(false);
	p_mOnemore->SetActive(false);
	p_mReturn->SetActive(false);
	p_mBanner->SetActive(false);
	p_mAllow->SetActive(false);

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
			p_mSECount->Play();
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
		else if (fWaitCnt > 3)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjGo->Scaling(800.0f * Time->GetDeltaTime(), 800.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > fWaitTime)
			{
				p_mObjGo->SetScale(0.0f, 0.0f, 0.0f);
				p_mObjGo->bDestroy = true;
			}
		}
		else if (fWaitCnt > 2)
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjNum->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > 3)
			{
				p_mSEGo->Play();
				p_mObjNum->SetScale(0.0f, 0.0f, 0.0f);
				p_mObjNum->bDestroy = true;
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
				p_mSpriteNum->SetCurrent(1);
			}
		}
		else
		{
			fWaitCnt += Time->GetDeltaTime();
			p_mObjNum->Scaling(300.0f * Time->GetDeltaTime(), 300.0f * Time->GetDeltaTime(), 0.0f);
			if (fWaitCnt > 1)
			{
				p_mSECount->Play();
				p_mObjNum->SetScale(0.0f, 0.0f, 0.0f);
				p_mSpriteNum->SetCurrent(2);
			}
		}
	}
		break;

	case GameState::TransToClear:
		p_mTransition->FadeOut(1.5);
		p_mSEClear->Play();
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
		// UIを非表示
		ARemainNum->SetDisplay(false);
		ComboObj->SetDisplay(false);
		ScoreObj->SetDisplay(false);
		p_mHalfFade->FadeOut(1.5);
		// ゲームオーバーオブジェクトを落としてくる
		p_mOvobj->FallStart();
		p_mBGM->Stop();
		p_mSEOver->Play();
		GameManager::SetGameState(GameState::OverFade);
		break;

	case GameState::OverFade:
		if (p_mHalfFade->GetState() == OBJ_Transition::FadeState::OutEnd && p_mOvobj->GetState() == OBJ_GameOver::GameOverObjState::Finish)
		{
			GameManager::SetGameState(GameState::Over);
			// 入力待ちに移行
			mState = OverState::WaitInput;
			ice1->SetActive(true);
			ice2->SetActive(true);
			p_mOnemore->SetActive(true);
			p_mReturn->SetActive(true);
			p_mBanner->SetActive(true);
			p_mAllow->SetActive(true);
		}
		break;
	case GameState::Over:
		break;
	}

	switch (mState)
	{
	case Scene_Game::OverState::Game:
		break;
	case Scene_Game::OverState::WaitInput:
		if (Controller_Input::GetButton(0, GAMEPAD_A) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_RETURN) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_SPACE) == KEYSTATE::KEY_DOWN)
		{
			p_mSEDecide->Play();
			if (bisUP)
			{
				p_mTransition->FadeOut(1.5);
				mState = OverState::ToGame;
			}
			else
			{
				p_mTransition->FadeOut(1.5);
				mState = OverState::ToTitle;
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
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 150.0f, 545.0f, 0.0f);
			p_mBanner->SetPosition(SCREEN_WIDTH / 2, 545.0f, 0.0f);
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
			p_mAllow->SetPosition(SCREEN_WIDTH / 2 - 150.0f, 620.0f, 0.0f);
			p_mBanner->SetPosition(SCREEN_WIDTH / 2, 620.0f, 0.0f);
			p_mRetScale->SetUpdate(true);
			p_mOneScale->SetUpdate(false);
		}
		break;
	case Scene_Game::OverState::ToGame:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
		{
			GameManager::SetGameState(GameState::GameFade);
			Manager::SetNextScene<Scene_Game>();
		}
		break;
	case Scene_Game::OverState::ToTitle:
		if (p_mTransition->GetState() == OBJ_Transition::FadeState::OutEnd)
		{
			GameManager::SetGameState(GameState::Title);
			Manager::SetNextScene<Scene_Title>();
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

	p_mSECursor->Stop();
	p_mSECursor->Uninit();
	delete p_mSECursor;

	p_mSEDecide->Stop();
	p_mSEDecide->Uninit();
	delete p_mSEDecide;

	p_mSEOver->Stop();
	p_mSEOver->Uninit();
	delete p_mSEOver;

	p_mSEClear->Stop();
	p_mSEClear->Uninit();
	delete p_mSEClear;
}
