#include "OBJ_Ice.h"
#include "../System/Input.h"
#include "../System/Time.h"
#include "../InternCodeAdachi/CSVLoad.h"
#include "../ModelName.h"

#define LoadRow (1)

using namespace DirectX::SimpleMath;
using namespace std;

void OBJ_Ice::CreateFromCSV(const char* _FileName)
{
	string Line = ReadDataFromCSV(_FileName, LoadRow);

	// 文字列を(,)で分割
	istringstream iss(Line);
	string word;
	std::vector<string> sv;
	while (getline(iss, word, ','))
	{
		sv.emplace_back(word);
	}

	fShakeTime = stof(sv[0]); //揺れる時間
	fShakePower = stof(sv[1]); // 揺れの範囲
	p_mCollider->SetCenter(stof(sv[2]), stof(sv[3]), stof(sv[4]));
	p_mCollider->SetSize(stof(sv[5]), stof(sv[6]), stof(sv[7]));
}

OBJ_Ice::OBJ_Ice()
{
	myColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

	// シェーダー
	p_mShaderCom = new Com_Shader();
	p_mShaderCom->p_mVS->Load(VS_MODEL);
	p_mShaderCom->p_mPS->Load(PS_MODEL);

	AddComponent(p_mShaderCom);

	// モデル
	p_mModelCom = new Com_Model();
	p_mModelCom->SetModelData(ICE_HP5);

	AddComponent(p_mModelCom);

	// コライダー
	p_mCollider = new Com_BoxCollider();
	p_mCollider->SetSize(7.0f, 2.0f, 7.0f);
	p_mCollider->SetCenter(0.0f, 1.0f, 0.0f);
	p_mCollider->bCanStepOn = true;
	p_mCollider->mColliderTag = ColliderKind::ColTag_Ice;

	AddComponent(p_mCollider);

	//音

	//ヒビ
	p_mAudio_Damage = new Com_Audio();
	p_mAudio_Damage->Load("asset\\audio\\SE\\SE その他\\氷 ヒビ.wav");
	p_mAudio_Damage->SetUseTarget(false);
	AddComponent(p_mAudio_Damage);
	//破壊
	p_mAudio_Break = new Com_Audio();
	p_mAudio_Break->Load("asset\\audio\\SE\\SE その他\\氷 破壊.wav");
	p_mAudio_Break->SetUseTarget(false);
	AddComponent(p_mAudio_Break);
}

OBJ_Ice::OBJ_Ice(const char* _name)
	: OBJ_Ice()
{
	sObjectName = _name;
}

OBJ_Ice::OBJ_Ice(const char* _ice, const char* _FileName)
	: OBJ_Ice()
{
	sObjectName = _ice;
	CreateFromCSV(_FileName);
}

void OBJ_Ice::Init()
{
	p_mShaderCom->p_mPS->CreateBuffer(16);

	//元の位置を保存
	originalPosition = p_mTransform->mPosition;

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
	GameObject::Update();

	switch (iHP)
	{
	case 1:
		p_mCollider->bEnable = false;
		fLastLifeWaitTime -= Time->GetDeltaTime();
		if (fLastLifeWaitTime < 0)
		{
			bDestroy = true; //GameObjectクラスのDestroy()を使うために必要
		}
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
}

//アザラシの待機時間によってHPが減るようにする
void OBJ_Ice::HpCalc()
{
	iHP--;
	fElapsedTime = 0.0f;

	if (iHP <= 4 && iHP > 1);
	{
		p_mAudio_Damage->Play();
	}

	switch (iHP)
	{
	case 4:
		p_mModelCom->SetModelData(ICE_HP4);
		break;
	case 3:
		p_mModelCom->SetModelData(ICE_HP3);
		break;
	case 2:
		p_mModelCom->SetModelData(ICE_HP2);
		break;
	case 1:
		p_mAudio_Break->Play();
		p_mModelCom->SetModelData(ICE_HP1);
		break;
	}
}

//足場が揺れる処理
void OBJ_Ice::Shake()
{
	//タイマーを更新
	fElapsedTime += Time->GetDeltaTime();

	//揺れる時間が終了したら揺れを停止
	if (fElapsedTime >= fShakeTime)
	{
		//揺れが終了したら元の位置に戻す
		p_mTransform->mPosition = originalPosition;
		return;
	}

	// 足場をランダムに揺らす
	float fPowerX = RandomRange(-fShakePower, fShakePower);
	float fPowerY = RandomRange(-fShakePower, fShakePower);
	float fPowerZ = RandomRange(-fShakePower, fShakePower);

	// 現在の位置を取得し、揺れた位置に設定
	Vector3 currentPosition = p_mTransform->mPosition;
	p_mTransform->SetPosition(currentPosition.x + fPowerX, currentPosition.y + fPowerY, currentPosition.z + fPowerZ);
}
