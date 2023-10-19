#include "OBJ_Inpact.h"
#include "../System/Time.h"

OBJ_Inpact::OBJ_Inpact()
{
	p_mColliderCom = new Com_SphereCollider();
	p_mColliderCom->fRadius = 1.0f; //”ÍˆÍ
	p_mColliderCom->mColliderTag = ColliderKind::ColTag_Attack;

	AddComponent(p_mColliderCom);
}

OBJ_Inpact::OBJ_Inpact(const char* _name) :OBJ_Inpact()
{
	sObjectName = _name;
}

void OBJ_Inpact::Update()
{
	GameObject::Update();



	// ƒ‰ƒCƒtƒ^ƒCƒ€‚ðŒ¸­
	fLifeTime -= Time->GetDeltaTime();
	if (fLifeTime < 0)
	{
		bDestroy = true;
		return;
	}
	
	// ‚Ç‚±‚É‚ ‚Á‚Ä‚à“–‚½‚éŒ´ˆö
	// p_mColliderCom->fRadius += p_mColliderCom->fRadius + fCnt;
	// C³Œã(”¼Œa‚ðƒJƒEƒ“ƒg•ª‘å‚«‚­‚µ‚Ä‚¢‚­)
	// ÕŒ‚”g‚Ì‚æ‚¤‚ÈŽü‚è‚ÉL‚ª‚éŠ´‚¶‚ª‚Å‚«‚é
	p_mColliderCom->fRadius += fScaleSpeed * Time->GetDeltaTime();
}
