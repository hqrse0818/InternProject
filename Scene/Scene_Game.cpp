#include "Scene_Game.h"
#include "GameInclude.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Game::Init()
{
	// 当たり判定アクティブ化
	bCheckCol = true;

	// ペンギン
	p_mPlayer = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");
	AddKeyObject(p_mPlayer);

	// カメラ
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(p_mPlayer);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);

	// ビルボードのカメラ設定
	Com_EffectBillboard::SetCamera(Camera_buf);
	Com_Billboard::SetCamera(Camera_buf);

	// ペンギン関連のカメラ設定
	p_mPlayer->GetMoveCom()->SetCameraCom(Camera_buf);
	p_mPlayer->SetCameraCom(Camera_buf);

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
		fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 8.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		AddGameObject(fobj);
		// 右側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 8.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		AddGameObject(fobj);
		// 上側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 0.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 8.0f, 20.0f);
		AddGameObject(fobj);
		// 下側
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 0.0f, StageInit - ((scale.z * size.z) * 2));
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 8.0f, 20.0f);
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
	
}
