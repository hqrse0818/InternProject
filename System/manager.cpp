#include	"../DirectX/renderer.h"
#include	"manager.h"
#include "../Component/Com_Audio.h"
#include	"TextureCreate.h"
#include	"../Scene/Scene.h"
#include	"Input.h"
#include	"Time.h"
#include	"../Scene/Scene_Test.h"
#include	"../Scene/Scene_ModelLoad.h"
#include "HighGetRand.h"
#include "ModelPool.h"
#include <thread>

using namespace std;

Scene* Manager::p_mCurrentScene{};
Scene* Manager::p_mNextScene{};
bool Manager::bChangeScene = false;

void Manager::Init(Application* ap)
{
	// �^�C�}�𑜓x���P�~���b�ɂ���
	timeBeginPeriod(1);

	// �����_���[��������
	Renderer::Init(ap);
	Com_Audio::InitMaster();
	// �}�X�^�[�{�����[���ݒ�
	Com_Audio::SetMasterVolume(0.5f);

	// ����������
	void RandInit();

	// �����\����������
	HighRandom->HighRandInit();

	// ���f���f�[�^�̏�����
	ModelPool::GetInsatance();

	// �e�N�X�`���쐬�N���X�̏�����
	TextureCreate::GetInstance();

	// Input������
	Input::Init();

	// �^�C���̏�����
	Time->Init();

	SetScene<Scene_ModelLoad>();
}

void Manager::Uninit()
{
	p_mCurrentScene->UninitBase();
	delete p_mCurrentScene;

	Time->Uninit();

	HighRandom->Uninit();

	Com_Audio::UninitMaster();

	TextureCreate::Uninit();

	ModelPool::Uninit();

	Com_ModelRenderer::UnloadAll();

	// �����_���[�I������
	Renderer::Uninit();

	// �^�C�}�𑜓x�����ɖ߂�
	timeEndPeriod(1);
}

void Manager::Update(uint64_t d)
{
	if (bChangeScene)
	{
		p_mCurrentScene->UninitBase();
		delete p_mCurrentScene;

		p_mCurrentScene = p_mNextScene;
		p_mCurrentScene->InitBase();
		p_mCurrentScene->StartBase();
		bChangeScene = false;
		p_mNextScene = nullptr;
	}
	// ���͍X�V
	Input::Update();
	// �R���g���[���[���͍X�V
	Controller_Input::UpdateCurrentController();
	// �V�[���A�b�v�f�[�g
	p_mCurrentScene->UpdateBase();
	// �}�E�X�̃��Z�b�g
	Input::RefreshMouse();
}

void Manager::Draw(uint64_t d)
{
	Renderer::Begin();

	p_mCurrentScene->DrawBase();
	
	Renderer::End();
}
