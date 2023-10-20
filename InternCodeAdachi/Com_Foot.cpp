#include "Com_Foot.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Collider.h"
#include "../Component/Com_BoxCollider.h"
#include "Com_Jump.h"
#include "Com_Gravity.h"

void Com_Foot::Update()
{
	fLastFootPos = fFootPos;
	fFootPos = p_mObject->p_mTransform->mPosition.y + fFootHeight;
	if (p_mObject->mCollisionvector.size() < 1 && p_mGravityCom)
	{
		p_mGravityCom->SetGround(false);
	}
}

void Com_Foot::OnCollisionEnter(GameObject* _obj)
{
	// コライダーのタイプを取得
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		// ボックスならボックスコライダーを取得
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		// 乗ることができるなら
		if (col->bCanStepOn && p_mGravityCom)
		{
			// 且つ現在落下中
			if (!p_mGravityCom->GetGround())
			{
				// ボックスのy座標の最大値を取得。
				float heightY = col->Getmax().y;
				// フットポジションが
				if (fFootPos > heightY || fLastFootPos > heightY)
				{
					p_mObject->p_mTransform->mPosition.y = heightY;
					p_mGravityCom->SetGround(true);
					p_mGravityCom->SetGroundOnThisFrame(true);

					if (p_mJumpCom)
					{
						p_mJumpCom->SetJumpFlg(false);
						p_mJumpCom->SetDropFlg(false);
					}
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
		if (col->bCanStepOn && p_mGravityCom)
		{
			// ボックスのy座標の最大値を取得。
			float heightY = col->Getmax().y;
			// フットポジションが
			if (fFootPos > heightY || fLastFootPos > heightY)
			{
				p_mObject->p_mTransform->mPosition.y = heightY;
				p_mGravityCom->SetGround(true);
				p_mGravityCom->SetGroundOnThisFrame(true);
			}
		}
	}
}

void Com_Foot::OnCollisionExit(GameObject* _obj)
{
	// コライダーのタイプを取得
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->bCanStepOn)
		{
			if (p_mGravityCom)
			{
				// 今回のフレームで何かしらの上に乗った判定がされていなかったら
				if (!p_mGravityCom->GetGroundedAtThisFrame())
				{
					p_mGravityCom->SetGround(false);
				}
			}
		}
	}
}
