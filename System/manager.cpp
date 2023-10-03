#include	"../DirectX/renderer.h"
#include	"manager.h"
#include "../Component/Com_Audio.h"
#include	"TextureCreate.h"
#include	"../Scene/Scene.h"
#include	"Input.h"
#include	"Time.h"
#include	"../Scene/Scene_Title.h"
#include "HighGetRand.h"

Scene* Manager::p_mCurrentScene{};

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

	// Input������
	Input::Init();

	// �^�C���̏�����
	Time->Init();

	SetScene<Scene_Title>();
}

void Manager::Uninit()
{
	p_mCurrentScene->UninitBase();
	delete p_mCurrentScene;

	Time->Uninit();

	HighRandom->Uninit();

	Com_Audio::UninitMaster();

	Com_ModelRenderer::UnloadAll();

	// �����_���[�I������
	Renderer::Uninit();

	// �^�C�}�𑜓x�����ɖ߂�
	timeEndPeriod(1);
}

void Manager::Update(uint64_t d)
{
	Input::Update();
	Controller_Input::UpdateCurrentController();
	p_mCurrentScene->UpdateBase();
	Input::RefreshMouse();
}

void Manager::Draw(uint64_t d)
{
	Renderer::Begin();

	p_mCurrentScene->DrawBase();
	
	Renderer::End();
}
