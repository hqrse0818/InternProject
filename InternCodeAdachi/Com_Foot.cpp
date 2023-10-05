#include "Com_Foot.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Collider.h"
#include "../Component/Com_BoxCollider.h"
#include "Com_Gravity.h"

void Com_Foot::Update()
{
	fFootPos = p_mObject->p_mTransform->mPosition.y + fFootHeight;
}

void Com_Foot::OnCollisionEnter(GameObject* _obj)
{
	// コライダーのタイプを取得
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		// ボックスならボックスコライダーを取得
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		// 乗ることができるなら
		if (col->bCanStepOn && p_mGravityTarget)
		{
			// 且つ現在落下中
			if (p_mGravityTarget->GetGround() == false)
			{
				// ボックスのy座標の最大値を取得。
				float heightY = col->Getmax().y;
				// フットポジションが
				if (fFootPos > heightY)
				{
					p_mObject->p_mTransform->mPosition.y = heightY;
					p_mGravityTarget->SetGround(true);
				}
			}
		}
	}
}

void Com_Foot::OnCollisionStay(GameObject* _obj)
{
	// コライダーのタイプを取得
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		// ボックスならボックスコライダーを取得
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		// 乗ることができるなら
		if (col->bCanStepOn && p_mGravityTarget)
		{
			// 且つ現在落下中
			if (p_mGravityTarget->GetGround() == false)
			{
				// ボックスのy座標の最大値を取得。
				float heightY = col->Getmax().y;
				// フットポジションが
				if (fFootPos > heightY)
				{
					p_mObject->p_mTransform->mPosition.y = heightY;
					p_mGravityTarget->SetGround(true);
				}
			}
		}
	}
}

void Com_Foot::OnCollisionExit(GameObject* _obj)
{
	if (p_mGravityTarget)
	{
		p_mGravityTarget->SetGround(false);
	}
}


// タイトル案
// ペンギンドロップ
// ペンギンアイスドロップ
// ペンギンvsアザラシ~氷上の死闘~