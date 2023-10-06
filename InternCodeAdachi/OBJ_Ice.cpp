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
	/*
	HPの量で変更(テクスチャに変更予定)
	〇耐久値が2以上の時
	・ぶるっと一瞬震える
	・テクスチャ切り替え
	・ひびが入るSEを再生
	・耐久値を-1

	〇耐久値が1の時
	・オブジェクトを消去
	・割れるSEを再生
	・割れるエフェクトを再生
	*/

	switch (iHP) 
	{
	case 1:
		bDestroy = true; //GameObjectクラスのDestroy()を使うために必要
		break;
	case 2:
		Shake();
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		Shake();
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		Shake();
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 5:
		myColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	}

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);

	GameObject Update();

	//計算処理
	HpCalc();

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

//足場が揺れる処理
void OBJ_Ice::Shake()
{
	// 足場をランダムに揺らす
	float shakeAmount = 0.1f; // 揺れの範囲
	float offsetX = RandomRange(-shakeAmount, shakeAmount);
	float offsetY = RandomRange(-shakeAmount, shakeAmount);
	float offsetZ = RandomRange(-shakeAmount, shakeAmount);

	// 現在の位置を取得し、揺れた位置に設定します
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + offsetX, currentPosition.y + offsetY, currentPosition.z + offsetZ);
}