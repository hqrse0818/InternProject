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
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData("Ice_PatA");

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

	GameObject::Init();
}

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
void OBJ_Ice::Update()
{
	switch (iHP)
	{
	case 1:
		bDestroy = true; //GameObjectクラスのDestroy()を使うために必要
		break;
	case 2:
		myColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
		Shake();
		break;
	case 3:
		myColor = Color(1.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 4:
		myColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
		Shake();
		break;
	case 5:
		myColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}

	p_mShaderCom->p_mPS->WriteBuffer(0, &myColor);

	GameObject::Update();

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
	float fShakeTime = 0.0f; //

	// 足場をランダムに揺らす
	float fShakePower = 0.1f; // 揺れの範囲
	float fPowerX = RandomRange(-fShakePower, fShakePower);
	float fPowerY = RandomRange(-fShakePower, fShakePower);
	float fPowerZ = RandomRange(-fShakePower, fShakePower);

	// 現在の位置を取得し、揺れた位置に設定
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + fPowerX, currentPosition.y + fPowerY, currentPosition.z + fPowerZ);
}
