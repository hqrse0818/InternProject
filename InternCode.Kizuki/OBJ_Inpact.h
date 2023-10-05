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
protected:
	float fLifeTime = 0.0f; //存在する時間

public:
	OBJ_Inpact();
	void Update();
};