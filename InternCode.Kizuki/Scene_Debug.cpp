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
#include "../Component/Com_CameraTransform.h"
#include "../Component/Com_Billboard.h"

#define IceNum (11)
#define IceScale (7)
#define InitPos (-35)

using namespace DirectX::SimpleMath;

void Scene_Debug::Init()
{
	// �����蔻��A�N�e�B�u��
	bCheckCol = true;

	// �y���M��
	Player = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");

	// ���C���[�̎w��Ȃ��ŃL�[�I�u�W�F�N�g�Ƃ��Ēǉ�
	AddKeyObject(Player);

	// �X�e�[�W����
	for (int i = 0; i < IceNum; i++)
	{
		for (int j = 0; j < IceNum; j++)
		{
			// �X�̐���
			OBJ_Ice* Ice = new OBJ_Ice("Ice", "asset/data/csv/IceStatus.csv");
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

	// ���C���[���w�肵�ăI�u�W�F�N�g��ǉ�
	AddGameObject(Camera, 0);

	OBJ_Sea* Sea = new OBJ_Sea("Sea");
	AddGameObject(Sea);

	OBJ_AzarashiManager* Manager = new OBJ_AzarashiManager("Manager", "asset/data/csv/AzarashiManager.csv");
	AddGameObject(Manager);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);
}

void Scene_Debug::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 5.0f, 0.0f);
	GetGameObject("Azarashi")->p_mTransform->SetPosition(20.0f, 0.0f, -20.0f);
	GetGameObject("Azarashi2")->p_mTransform->SetPosition(10.0f, 0.0f, -30.0f);
	ShowCursor(false);
	Input::SetCursorCenterEnable();
}

void Scene_Debug::Update()
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
	//�ŏ��̏�ԂɃ��Z�b�g����
	if (Controller_Input::GetButton(0, GAMEPAD_Y) == KEYSTATE::KEY_DOWN || Input::GetKeyState(KEYCODE_1) == KEYSTATE::KEY_DOWN)
	{
		Manager::SetScene<Scene_Debug>();
	}
}

void Scene_Debug::Uninit()
{
	ShowCursor(true);
	Input::SetCursorCenterDisable();
}