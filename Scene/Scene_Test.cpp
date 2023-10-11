#include "Scene_Test.h"
#include "../ComponentHeader.h"
#include "../System/Input.h"
#include "../System/CustomMath.h"
#include "../System/Time.h"


#include "../InternCodeAdachi/OBJ_Penguin.h"
#include "../InternCodeAdachi/OBJ_Azarashi.h"
#include "../InternCodeAdachi/Com_AngleCamera.h"
#include "../InternCodeAdachi/OBJ_Ice.h"
#include "../Component/Com_CameraTransform.h"
#include "../Component/Com_Billboard.h"

#define IceNum (11)
#define IceScale (7)
#define InitPos (-35)

using namespace DirectX::SimpleMath;

void Scene_Test::Init()
{
	// �����蔻��A�N�e�B�u��
	bCheckCol = true;

	// �y���M��
	Player = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");

	// ���C���[�̎w��Ȃ��ŃL�[�I�u�W�F�N�g�Ƃ��Ēǉ�
	AddKeyObject(Player);

	// �A�U���V
	OBJ_Azarashi* Azarashi = new OBJ_Azarashi("Azarashi");
	Azarashi->SetTargetPosition(0.0f, 9.0f, 0.0f);
	AddGameObject(Azarashi);

	// �X�e�[�W����
	for (int i = 0; i < IceNum; i++)
	{
		for (int j = 0; j < IceNum; j++)
		{
			// �X�̐���
			OBJ_Ice* Ice = new OBJ_Ice("Ice");
			Ice->p_mTransform->SetPosition(InitPos + i * IceScale, 0.0f, InitPos + j * IceScale);
			AddGameObject(Ice);
		}
	}

	
	GameObject* BilObj = new GameObject();

	//�r���{�[�h
	Com_Shader* BilShader = new Com_Shader();
	BilShader->p_mVS->Load(VS_SPRITE);
	BilShader->p_mPS->Load(PS_SPRITE);
	BilObj->AddComponent(BilShader);

	Com_Billboard* Bil_buf = new Com_Billboard();
	Bil_buf->SetTexture("asset/texture/GameTitle.png");
	BilObj->p_mTransform->mPosition.x = 3.0f;
	BilObj->p_mTransform->SetScale(10.0f, 10.0f, 1.0f);
	BilObj->AddComponent(Bil_buf);

	AddGameObject(BilObj);


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

	//�r���{�[�h�p�̃J�������Z�b�g
	Bil_buf->SetCamera(Camera_buf);

	Player->GetMoveCom()->SetCameraCom(Camera_buf);
	Player->SetCameraCom(Camera_buf);
}

void Scene_Test::Start()
{
	Player->p_mTransform->SetPosition(0.0f, 5.0f, 0.0f);
	GetGameObject("Azarashi")->p_mTransform->SetPosition(20.0f, 0.0f, -20.0f);
	ShowCursor(false);
	Input::SetCursorCenterEnable();
}

void Scene_Test::Update()
{
	// �f�o�b�O�p
	if (Input::GetKeyState(KEYCODE_END) == KEYSTATE::KEY_DOWN)
	{
		ShowCursor(true);
		Input::SetCursorCenterDisable();
	}
}

void Scene_Test::Uninit()
{
	ShowCursor(true);
}
