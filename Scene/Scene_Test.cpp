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
#include "../InternCode.Kizuki/OBJ_JumpEffect.h"
#include "../InternCode.Kizuki/OBJ_AzarashiAttackEffect.h"
#include "../InternCode.Kizuki/OBJ_AzarashiDeadEffect.h"
#include "../Component/Com_EffectBillboard.h"
#include "../InternCodeAdachi/OBJ_Fall.h"
#include "../InternCodeAdachi/OBJ_BackPenguinBlue.h"
#include "../InternCodeAdachi/OBJ_BackPenguinRed.h"


#include "../System/HighGetRand.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Test::Init()
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
	
	// �����蔻��A�N�e�B�u��
	bCheckCol = true;

	// �y���M��
	Player = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");

	// ���C���[�̎w��Ȃ��ŃL�[�I�u�W�F�N�g�Ƃ��Ēǉ�
	AddKeyObject(Player);

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
	fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 0.0f, 0.0f);
	//fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 1.0f, 0.0f);
	fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
	fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
	AddGameObject(fobj);
	// �E��
	fobj = new OBJ_Fall("fall");
	fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 0.0f, 0.0f);
	//fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 1.0f, 0.0f);
	fobj->GetColliderCom()->SetSize(20.0f, 3.0f, 100.0f);
	fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
	AddGameObject(fobj);
	// �㑤
	fobj = new OBJ_Fall("fall");
	fobj->SetPosition(0.0f, 0.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
	//fobj->SetPosition(0.0f, 1.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
	fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
	fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
	AddGameObject(fobj);
	// ����
	fobj = new OBJ_Fall("fall");
	fobj->SetPosition(0.0f, 0.0f, StageInit - ((scale.z * size.z) * 2));
	//fobj->SetPosition(0.0f, 1.0f, StageInit - ((scale.z * size.z) * 2));
	fobj->GetColliderCom()->SetCenter(0.0f, 0.0f, 0.0f);
	fobj->GetColliderCom()->SetSize(100.0f, 3.0f, 20.0f);
	AddGameObject(fobj);

	// �J����
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(Player);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);

	// �r���{�[�h�̃J�����ݒ�
	Com_EffectBillboard::SetCamera(Camera_buf);

	// ���C���[���w�肵�ăI�u�W�F�N�g��ǉ�
	AddGameObject(Camera, 0);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);

	// �C�I�u�W�F�N�g
	OBJ_Sea* Sea = new OBJ_Sea("Sea");
	Sea->SetPosition(0.0f, -22.0f, 0.0f);

	AddGameObject(Sea);

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

	OBJ_BackGround* back = new OBJ_BackGround("haikei");
	AddGameObject(back);

	// �C�p�X�v���C�g
	/*OBJ_SeaSprite* seasprite = new OBJ_SeaSprite("umi");
	seasprite->SetScale(1.0f, 1.0f, 1.0f);
	seasprite->GetSpriteCom()->SetUV(2.0f, 2.0f);
	seasprite->GetSpriteCom()->SetSize(500.0f, 500.0f);
	AddGameObject(seasprite,3);*/

	//��
	p_mAudio = new Com_Audio();
	p_mAudio->Load("asset\\audio\\BGM\\���C�� BGM.wav");
	p_mAudio->SetUseTarget(false);

	// �X�R�A�\���I�u�W�F�N�g
	OBJ_DisplayScore* ScoreObj = new OBJ_DisplayScore("dis","asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// �X�R�A�}�l�[�W���[
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// �R���{�\���I�u�W�F�N�g
	OBJ_ComboDisplay* ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
	AddGameObject(ComboObj);

	//�G�t�F�N�g
	// �q�b�v�C���p�N�g
	OBJ_HipEffect* HipEffect = new OBJ_HipEffect("HipEffect");
	AddGameObject(HipEffect);
	HipEffect->SetTarget(Player);
	Player->SetHipEffect(HipEffect);

	// �W�����v�G�t�F�N�g
	OBJ_JumpEffect* JumpEffect = new OBJ_JumpEffect("jumpEffect");
	JumpEffect->SetTarget(Player);
	Player->SetJumpEffect(JumpEffect);
	AddGameObject(JumpEffect);

	// �w�i�p�y���M��(��)
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

	// �w�i�p�y���M��(��)
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
	rp->SetPosition(-4.0f, 6.4f, -111.0f);
	rp->SetDelay(1.4f);
	rp->SetRotation(0.0f, Euler_To_Radian(0.0f), 0.0f);
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
	rp->SetRotation(0.0f, Euler_To_Radian(-16.0f), 0.0f);
	AddGameObject(rp);
	//8
	rp = new OBJ_BackPenguinRed("red");
	rp->SetPosition(110.0f, 6.6f, 52.0f);
	rp->SetDelay(1.6f);
	rp->SetRotation(0.0f, Euler_To_Radian(-100.0f), 0.0f);
	AddGameObject(rp);

	// ��̃X�v���C�g
	GameObject* SkyA = new GameObject("Sky");
	Com_Shader* SkyShader = new Com_Shader();
	SkyShader->p_mVS->Load(VS_SPRITE);
	SkyShader->p_mPS->Load(PS_SPRITE);
	SkyA->AddComponent(SkyShader);

	Com_3DSprite* sprite3D = new Com_3DSprite();
	sprite3D->SetTexture("asset\\texture\\sora.png");
	sprite3D->SetSize(1920.0f * 0.5f, 1080.0f * 0.5f);
	sprite3D->SetUV(1.0f, 1.0f);
	SkyA->AddComponent(sprite3D);

	SkyA->SetPosition(400.0f, 200.0f, 0.0f);
	SkyA->SetRotation(Euler_To_Radian(-90.0f), Euler_To_Radian(90.0f), 0.0f);

	AddGameObject(SkyA);

	SkyA = new GameObject("Sky");
	SkyShader = new Com_Shader();
	SkyShader->p_mVS->Load(VS_SPRITE);
	SkyShader->p_mPS->Load(PS_SPRITE);
	SkyA->AddComponent(SkyShader);
	sprite3D = new Com_3DSprite();
	sprite3D->SetTexture("asset\\texture\\sora.png");
	sprite3D->SetSize(1920.0f * 0.5f, 1080.0f * 0.5f);
	sprite3D->SetUV(1.0f, 1.0f);
	SkyA->AddComponent(sprite3D);

	SkyA->SetPosition(-400.0f, 200.0f, 0.0f);
	SkyA->SetRotation(Euler_To_Radian(-90.0f), Euler_To_Radian(270.0f), 0.0f);

	AddGameObject(SkyA);

	SkyA = new GameObject("Sky");
	SkyShader = new Com_Shader();
	SkyShader->p_mVS->Load(VS_SPRITE);
	SkyShader->p_mPS->Load(PS_SPRITE);
	SkyA->AddComponent(SkyShader);
	sprite3D = new Com_3DSprite();
	sprite3D->SetTexture("asset\\texture\\sora.png");
	sprite3D->SetSize(1920.0f * 0.5f, 1080.0f * 0.5f);
	sprite3D->SetUV(1.0f, 1.0f);
	SkyA->AddComponent(sprite3D);

	SkyA->SetPosition(0.0f, 200.0f, 400.0f);
	SkyA->SetRotation(Euler_To_Radian(-90.0f), 0.0, 0.0f);

	AddGameObject(SkyA);

	SkyA = new GameObject("Sky");
	SkyShader = new Com_Shader();
	SkyShader->p_mVS->Load(VS_SPRITE);
	SkyShader->p_mPS->Load(PS_SPRITE);
	SkyA->AddComponent(SkyShader);
	sprite3D = new Com_3DSprite();
	sprite3D->SetTexture("asset\\texture\\sora.png");
	sprite3D->SetSize(1920.0f * 0.5f, 1080.0f * 0.5f);
	sprite3D->SetUV(1.0f, 1.0f);
	SkyA->AddComponent(sprite3D);

	SkyA->SetPosition(0.0f, 200.0f, -400.0f);
	SkyA->SetRotation(Euler_To_Radian(-90.0f), Euler_To_Radian(180.0f), 0.0f);

	AddGameObject(SkyA);
}

void Scene_Test::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 5.0f, 0.0f);
	ShowCursor(false);
	Input::SetCursorCenterEnable();
	p_mAudio->Play(true);

	GameManager::SetGameState(GameState::Game);
}

void Scene_Test::Update()
{
	
	

	
#if defined (DEBUG) | defined(_DEBUG)
	// �f�o�b�O�p�V�[���ēǂݍ���
	if (Controller_Input::GetButton(0, GAMEPAD_START) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_R) == KEYSTATE::KEY_DOWN)
	{
		Manager::SetScene<Scene_Test>();
	}
	// �J�[�\����\������悤�ɐ؂�ւ��Ė��t���[�����S�ɋ����I�ɃZ�b�g����邱�Ƃ��~�߂�
	if (Input::GetKeyState(KEYCODE_9) == KEYSTATE::KEY_DOWN)
	{
		ShowCursor(true);
		Input::SetCursorCenterDisable();
	}
	// �J�[�\�����\���ɐ؂�ւ��Ė��t���[�����S�ɋ����I�ɃZ�b�g�����
	if (Input::GetKeyState(KEYCODE_0) == KEYSTATE::KEY_DOWN)
	{
		ShowCursor(false);
		Input::SetCursorCenterEnable();
	}
#endif

	// �Q�[���}�l�[�W���[�̍X�V
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
