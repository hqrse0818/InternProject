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

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Test::Init()
{
	// �X�e�[�W�̃u���b�N���̓ǂݍ���
	string sStageNum = ReadDataFromCSV("asset/data/csv/Stage.csv", 1);
	std::vector<string> IceSetting = SeparateString(sStageNum, ',');
	unsigned int stagenum = stoi(IceSetting[0]);
	// �X�e�[�W�̍ő�̃C���f�b�N�X���i�[
	OBJ_Ice::s_iMaxNumIndex = stagenum;
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

	// �X�e�[�W����
	for (int i = 0; i < stagenum; i++)
	{
		for (int j = 0; j < stagenum; j++)
		{
			// �X�̐���
			OBJ_Ice* Ice = new OBJ_Ice("Ice", "asset/data/csv/IceStatus.csv");
			Com_BoxCollider* col = Ice->GetColliderCom();
			Ice->p_mTransform->SetPosition(StageInit + i * col->mSize.x * Ice->p_mTransform->mScale.x, 0.0f, StageInit + j * col->mSize.z * Ice->p_mTransform->mScale.z);
			Ice->myLine = i;
			Ice->myRow = j;
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

	// ���C���[���w�肵�ăI�u�W�F�N�g��ǉ�
	AddGameObject(Camera, 0);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);

	// �C�I�u�W�F�N�g
	OBJ_Sea* Sea = new OBJ_Sea("Sea");
	Sea->SetPosition(0.0f, -30.0f, 0.0f);

	AddGameObject(Sea);

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

	//��
	p_mAudio = new Com_Audio();
	p_mAudio->Load("asset\\audio\\BGM\\���C�� BGM.wav");
	p_mAudio->SetUseTarget(false);
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
	// �f�o�b�O�p
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

	// �f�o�b�O�p�V�[���ēǂݍ���
#if defined (DEBUG) | defined(_DEBUG)
	if (Controller_Input::GetButton(0, GAMEPAD_START) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_R) == KEYSTATE::KEY_DOWN)
	{
		Manager::SetScene<Scene_Test>();
	}
#endif
}

void Scene_Test::Uninit()
{
	ShowCursor(true);
	Input::SetCursorCenterDisable();

	p_mAudio->Stop();
	p_mAudio->Uninit();
	delete p_mAudio;
}
