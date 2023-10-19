#include "Com_Jump.h"
#include "../GameObject/GameObject.h"
#include "../System/Time.h"
#include "../System/Input.h"
#include "../Component/Com_BoxCollider.h"
#include "../InternCode.Kizuki/OBJ_Inpact.h"
#include "../Scene/Scene.h"
#include <iostream>

using namespace DirectX::SimpleMath;
using namespace std;

//ジャンプ処理
void Com_Jump::Jump()
{
	fFallTime = 1.0f;

	Vector3 Velocity = Vector3(0.0f, 0.0f, 0.0f);
	Velocity.y = fJumpPower;
	Velocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(Velocity);
}

//着地処理
void Com_Jump::HipDrop()
{
	fDropCnt += Time->GetDeltaTime();
	Vector3 fDropVelocity = Vector3(0.0f, 0.0f, 0.0f);
	fDropVelocity.y = fDropSpeed * fDropCnt + fDropInitialSpeed;
	fDropVelocity *= Time->GetDeltaTime();

	p_mObject->p_mTransform->Translate(fDropVelocity);
}

void Com_Jump::Update()
{
	//ジャンプフラグがtrue
	if (bJump)
	{
		Jump(); //ジャンプ関数
	}
	if (bDrop)
	{
		HipDrop();
	}
}

void Com_Jump::OnCollisionEnter(GameObject* _obj)
{
	//コライダーのタイプを取得
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		//ボックスならボックスコライダーを取得
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		if (col->mColliderTag == ColliderKind::ColTag_Ice)
		{
			//ドロップフラグがtrue
			if (bDrop)
			{
				//衝撃オブジェクトを呼び出す
				OBJ_Inpact* Inpact = new OBJ_Inpact("Inpact");

				//高さから範囲と威力を設定
				Inpact->GetColliderCom()->fRadius = fImpactRenge; //範囲
				Inpact->GetColliderCom()->bMovable = true;
				Inpact->GetColliderCom()->bIsTrigger = true;
				// 拡大速度の設定
				Inpact->SetScaleSpeed(fImpactSpeed);

				Inpact->Init();

				Inpact->p_mTransform->mPosition = p_mObject->p_mTransform->mPosition;

				GameObject::GetScene()->AddGameObject(Inpact);
			}
		}
	}
}