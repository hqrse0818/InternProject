#include "OBJ_Ice.h"
#include "../System/Input.h"

using namespace DirectX::SimpleMath;

OBJ_Ice::OBJ_Ice()
{
	myColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	// シェーダー
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	//p_mShaderCom->p_mPS->Load(PS_MODEL);
	p_mShaderCom->p_mPS->Load("shader\\PS_IceState.cso");

	AddComponent(p_mShaderCom);

	// モデル
	p_mModelCom = new Com_AssimpAnimation();
	p_mModelCom->LoadModel("asset\\model\\stage_v2.fbx", 1.0f, false);

	AddComponent(p_mModelCom);

	// コライダー
	p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(7.0f, 1.0f, 7.0f);
	p_mCollider->SetCenter(0.0f, 0.5f, 0.0f);
	p_mCollider->bCanStepOn = true;

	AddComponent(p_mCollider);
}

OBJ_Ice::OBJ_Ice(const char* _name)
	: OBJ_Ice()
{
	sObjectName = _name;
}

void OBJ_Ice::Init()
{
	p_mShaderCom->p_mPS->CreateBuffer(16);
}

void OBJ_Ice::Update()
{
	//HPの量で変更(テクスチャに変更予定)
	switch (iHP) 
	{
	case 1:
		bDestroy = true; //GameObjectクラスのDestroy()を使うために必要
		break;
	case 2:
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 5:
		myColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);

	GameObject Update();

	//テスト（ボタンを押してHPが減る）
	if (Input::GetKeyState(KEYCODE_1) == KEYSTATE::KEY_DOWN)
	{
		iHP--;
	}
}

//アザラシの待機時間によってHPが減るようにする
void OBJ_Ice::HpCalc()
{

}
