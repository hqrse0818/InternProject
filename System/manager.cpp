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

void Manager::Init(Application* ap)
{
	// タイマ解像度を１ミリ秒にする
	timeBeginPeriod(1);

	// レンダラーを初期化
	Renderer::Init(ap);
	Com_Audio::InitMaster();
	// マスターボリューム設定
	Com_Audio::SetMasterVolume(0.5f);

	// 乱数初期化
	void RandInit();

	// 高性能乱数初期化
	HighRandom->HighRandInit();

	// モデルデータの初期化
	ModelPool::GetInsatance();

	// テクスチャ作成クラスの初期化
	TextureCreate::GetInstance();

	// Input初期化
	Input::Init();

	// タイムの初期化
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

	// レンダラー終了処理
	Renderer::Uninit();

	// タイマ解像度を元に戻す
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
