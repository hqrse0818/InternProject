#include "Com_BoxCollider.h"
#include "../GameObject/GameObject.h"
// コリジョン範囲描画用
#include "Com_RenderCollisionLine_Box.h"
#include "../System/CustomMath.h"

using namespace DirectX::SimpleMath;

Com_BoxCollider::Com_BoxCollider()
{
	
}

void Com_BoxCollider::Init()
{
	mAABB.Size = mSize * p_mObject->p_mTransform->mScale;
#if defined(DEBUG) || defined(_DEBUG)
	// 表示用コンポーネントを追加
	Com_RenderCollisionLine_Box* CollisionLine = new Com_RenderCollisionLine_Box;
	p_mObject->AddComponent(CollisionLine);
#endif // 
}

void Com_BoxCollider::Update()
{
	if (p_mObject->mCollisionvector.size() > 0)
	{
		bHit = true;
	}
	else
	{
		bHit = false;
	}
	// ボックス位置の設定
	mAABB.Center = p_mObject->p_mTransform->mPosition + mCenter;
	mAABB.Size = mSize * p_mObject->p_mTransform->mScale;
}

void Com_BoxCollider::UpdateAABB()
{
	mAABB.Size = mSize * p_mObject->p_mTransform->mScale;
	mAABB.Center = p_mObject->p_mTransform->mPosition + mCenter;
}

//================//
//					Box2D				   //
//================//
Com_BoxCollider2D::Com_BoxCollider2D()
{
	
}

void Com_BoxCollider2D::Init()
{
	mBox.Center.x = p_mObject->p_mTransform->mPosition.x + mCenter.x;
	mBox.Center.y = p_mObject->p_mTransform->mPosition.y + mCenter.y;
	mBox.Size.x = p_mObject->p_mTransform->mScale.x / 2 * mSize.x;
	mBox.Size.y = p_mObject->p_mTransform->mScale.y / 2 * mSize.y;
#if defined(DEBUG) || defined(_DEBUG)
	// 表示用コンポーネントを追加
	Com_RenderCollisionLine_Box2D* CollisionLine = new Com_RenderCollisionLine_Box2D();
	p_mObject->AddComponent(CollisionLine);
#endif // 
}

void Com_BoxCollider2D::Update()
{
	mBox.Center.x = p_mObject->p_mTransform->mPosition.x + mCenter.x;
	mBox.Center.y = p_mObject->p_mTransform->mPosition.y + mCenter.y;
	mBox.Size.x = p_mObject->p_mTransform->mScale.x / 2 * mSize.x;
	mBox.Size.y = p_mObject->p_mTransform->mScale.y / 2 * mSize.y;
}
