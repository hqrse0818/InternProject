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
	float fCnt = 0.0f;
	float fInpactPower = 0.0f;

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

	void SetInpactPower(float _val)
	{
		fInpactPower = _val;
	}

	float GetInpactPower()
	{
		return fInpactPower;
	}
};