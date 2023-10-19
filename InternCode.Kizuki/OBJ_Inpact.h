#pragma once
#include "../GameObject/GameObject.h"
#include "../Component/Com_SphereCollider.h"

//Inpactのオブジェクトを作ってスフィアコライダーを入れる
//メンバ変数にlifetimeとスフィアコライダーを持たせる
//update内でlifetimeを減らすようにする
//スフィアコライダーnew
//ムーバブルにする
//fradiusで半径を持たせる
//SetCenter設定
//radius

class OBJ_Inpact :public GameObject
{
private:
	//コライダーコンポーネント
	Com_SphereCollider* p_mColliderCom = nullptr;
	float fLifeTime = 1.0f; //存在する時間
	float fScaleSpeed = 0.0f;	// 拡大速度

public:
	OBJ_Inpact();
	OBJ_Inpact(const char* _name);

	float SetLifeTime(float _val)
	{
		fLifeTime = _val;
	}

	void Update();

	Com_SphereCollider* GetColliderCom() 
	{
		return p_mColliderCom;
	}

	void SetScaleSpeed(float _val)
	{
		fScaleSpeed = _val;
	}
};