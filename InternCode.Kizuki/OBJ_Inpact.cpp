#include "OBJ_Inpact.h"
#include "../System/Time.h"

OBJ_Inpact::OBJ_Inpact()
{
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 1.0f; //範囲
	fCnt = 0.0f;

	AddComponent(p_mColliderCom);
}

OBJ_Inpact::OBJ_Inpact(const char* _name) :OBJ_Inpact()
{
	sObjectName = _name;
}

void OBJ_Inpact::Update()
{
	GameObject::Update();

	// スケールに加算する値
	fCnt += Time->GetDeltaTime() / 2;

	// ライフタイムを減少
	fLifeTime -= Time->GetDeltaTime();
	if (fLifeTime < 0)
	{
		bDestroy = true;
		return;
	}
	
	// どこにあっても当たる原因
	// p_mColliderCom->fRadius += p_mColliderCom->fRadius + fCnt;
	// 修正後(半径をカウント分大きくしていく)
	// 衝撃波のような周りに広がる感じができる
	p_mColliderCom->fRadius += fCnt;
}
