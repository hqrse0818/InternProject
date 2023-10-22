#include "Scene_Game.h"
#include "GameInclude.h"
#include "../main.h"
#include "../System/manager.h"
#include "Scene_Clear.h"


using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Game::Init()
{
	// �����蔻��A�N�e�B�u��
	bCheckCol = true;

	// �y���M��
	p_mPlayer = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");
	AddKeyObject(p_mPlayer);

	//�q�b�v�C���p�N�g�p�G�t�F�N�g
	OBJ_HipEffect* HipEffect = new OBJ_HipEffect("HipEffect");
	HipEffect->SetTarget(p_mPlayer);
	p_mPlayer->SetHipEffect(HipEffect);
	AddGameObject(HipEffect);
	// �W�����v�p�G�t�F�N�g
	OBJ_JumpEffect* JumpEffect = new OBJ_JumpEffect("JumpEff");
	JumpEffect->SetTarget(p_mPlayer);
	p_mPlayer->SetJumpEffect(JumpEffect);
	AddGameObject(JumpEffect);
	

	// �J����
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(p_mPlayer);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);
	AddGameObject(Camera, 0);

	// �r���{�[�h�̃J�����ݒ�
	Com_EffectBillboard::SetCamera(Camera_buf);
	Com_Billboard::SetCamera(Camera_buf);

	// �y���M���֘A�̃J�����ݒ�
	p_mPlayer->GetMoveCom()->SetCameraCom(Camera_buf);
	p_mPlayer->SetCameraCom(Camera_buf);

	// �A�U���V
	{
		// �A�U���V�}�l�[�W���[
		OBJ_AzarashiManager* AManager = new OBJ_AzarashiManager("manager", "asset/data/csv/AzarashiManager.csv");
		AddGameObject(AManager, 0);

		//�A�U���V�̎c�@
		GameObject* ARemain = new GameObject("ARemainOBJ");

		Com_CustomSprite* Sprite_buf = new Com_CustomSprite;
		Sprite_buf->mType = Com_CustomSprite::CustomType::LeftTop; //CustomSprite�Ń|�W�V�����ݒ�
		Sprite_buf->SetTexture("asset/texture/nokori.png");

		Com_Shader* Shader_buf = new Com_Shader();
		Shader_buf->p_mVS->Load(VS_SPRITE);
		Shader_buf->p_mPS->Load(PS_SPRITE);

		ARemain->AddComponent(Shader_buf);
		ARemain->AddComponent(Sprite_buf);

		ARemain->p_mTransform->mScale.x = 100.0f;
		ARemain->p_mTransform->mScale.y = 100.0f;
		AddGameObject(ARemain);

		//�A�U���V�̎c�@�i�����j
		OBJ_AzarashiRemain* ARemainNum = new OBJ_AzarashiRemain("Zanki", "asset/data/csv/AzarashiZankiUI.csv");
		AddGameObject(ARemainNum);
	}

	// �C�I�u�W�F�N�g
	{
		OBJ_Sea* Sea = new OBJ_Sea("Sea");
		Sea->SetPosition(0.0f, -30.0f, 0.0f);
		AddGameObject(Sea);
		// �C�p�X�v���C�g
		OBJ_SeaSprite* seasprite = new OBJ_SeaSprite("umi");
		seasprite->SetScale(1.0f, 1.0f, 1.0f);
		seasprite->GetSpriteCom()->SetUV(2.0f, 2.0f);
		seasprite->GetSpriteCom()->SetSize(500.0f, 500.0f);
		AddGameObject(seasprite, 3);
	}
	// �w�i
	OBJ_BackGround* back = new OBJ_BackGround("haikei");
	AddGameObject(back);

	// �X�e�[�W�݌v
	{
		// �X�e�[�W�̃u���b�N���̓ǂݍ���
		string sStageNum = ReadDataFromCSV("asset/data/csv/Stage.csv", 1);
		std::vector<string> IceSetting = SeparateString(sStageNum, ',');
		unsigned int stagenum = stoi(IceSetting[0]);
		// �X�e�[�W�̍ő�̃C���f�b�N�X���i�[
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

		// �����̊J�n�ʒu�v�Z
		int StageInit = IceScale * -Stagecenter;

		// �X�}�l�[�W���[
		OBJ_IceManager* iMana = new OBJ_IceManager("iMana", "asset/data/csv/IceStatus.csv");
		AddGameObject(iMana);

		float time = iMana->GetShakeTime();
		float pow = iMana->GetShakePower();
		Vector3 cen = iMana->GetColCenter();
		Vector3 size = iMana->GetColSize();
		Vector3 scale = iMana->GetScale();

		// �X�e�[�W����
		for (int i = 0; i < stagenum; i++)
		{
			for (int j = 0; j < stagenum; j++)
			{
				// �X�̐���
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
		// �X�̈ʒu�Ɛ����痎���p�I�u�W�F�N�g�̈ʒu�����߂�
		// ����
		OBJ_Fall* fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		// �E��
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 1.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		AddGameObject(fobj);
		// �㑤
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
		// ����
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 1.0f, StageInit - ((scale.z * size.z) * 2));
		fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
		AddGameObject(fobj);
	}


	// �X�R�A�\���I�u�W�F�N�g
	OBJ_DisplayScore* ScoreObj = new OBJ_DisplayScore("dis", "asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// �X�R�A�}�l�[�W���[
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// �R���{�\���I�u�W�F�N�g
	OBJ_ComboDisplay* ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
	AddGameObject(ComboObj);
	

	// �Q�[��BGM
	p_mBGM = new Com_Audio();
	p_mBGM->Load("asset\\audio\\BGM\\���C�� BGM.wav");
	p_mBGM->SetUseTarget(false);

	// �J�E���g�_�E���p�̃I�u�W�F�N�g�쐬
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
	p_mSECount->Load("asset\\audio\\SE\\SE ���̑�\\�J�E���g�_�E��.wav");
	// �J�n�p�I�u�W�F�N�g
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
	p_mSEGo->Load("asset\\audio\\SE\\SE ���̑�\\�Q�[���J�n.wav");

	// �J�ڗp�I�u�W�F�N�g
	p_mTransition = new OBJ_Transition("tra");
	p_mTransition->SetState(OBJ_Transition::FadeState::OutEnd);
	AddGameObject(p_mTransition);
}

void Scene_Game::Start()
{
	p_mTransition->FadeIn(1.5);
	// �J�n�O��Ԃɐݒ�
	GameManager::SetGameState(GameState::GameFade);

	// �v���C���[�̈ʒu��ݒ�
	p_mPlayer->p_mTransform->SetPosition(0.0f, 2.0f, 0.0f);
	
	// �J�[�\�����\��
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
