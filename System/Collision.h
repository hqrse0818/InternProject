#pragma once
#include "../Format.h"
#include "CustomMath.h"

// 当たり判定処理

namespace Collision
{
	// AABB同士の衝突判定
	bool AABB2AABB(const AABB& Box1, const AABB& Box2);
	// AABBとSphereの衝突判定
	bool AABB2Sphere(const AABB& Box, const Sphere& Ball);
	// AABBとCylinderの衝突判定
	bool AABB2Cylinder(const AABB& Box, const Cylinder& Col);
	// Box1がBox2に対してどれだけめり込んでいるか取得Vector3
	DirectX::SimpleMath::Vector3 GetAABB2AABBDepthVector3(const AABB& Box1, const AABB& Box2);
	// Box1がx方向にBox2に対してどれだけめり込んでいるか取得
	float GetAABB2AABBDepthX(const AABB& Box1, const AABB& Box2);
	// Box1がy方向にBox2に対してどれだけめり込んでいるか取得
	float GetAABB2AABBDepthY(const AABB& Box1, const AABB& Box2);
	// Box1がz方向にBox2に対してどれだけめり込んでいるか取得
	float GetAABB2AABBDepthZ(const AABB& Box1, const AABB& Box2);

	// Cylinder同士の衝突判定
	bool Cylinder2Cylinder(const Cylinder& Col1, const Cylinder& Col2);

	bool Sphere2Sphere(const Sphere& Ball1, const Sphere& Ball2);

	bool Box2D2Box2D(const Box2D& Box1, const Box2D& Box2);

	bool Box2D2Circle(const Box2D& Box, const Circle& Cir);

	bool Circle2Circle(const Circle& Circle1, const Circle& Circle2);

	bool Point2D2Rect(const POINT2D& point, const STRUCTRECT& rect);
}