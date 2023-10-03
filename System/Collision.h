#pragma once
#include "../Format.h"
#include "CustomMath.h"

// “–‚½‚è”»’èˆ—

namespace Collision
{
	// AABB“¯m‚ÌÕ“Ë”»’è
	bool AABB2AABB(const AABB& Box1, const AABB& Box2);
	// AABB‚ÆSphere‚ÌÕ“Ë”»’è
	bool AABB2Sphere(const AABB& Box, const Sphere& Ball);
	// AABB‚ÆCylinder‚ÌÕ“Ë”»’è
	bool AABB2Cylinder(const AABB& Box, const Cylinder& Col);
	// Box1‚ªBox2‚É‘Î‚µ‚Ä‚Ç‚ê‚¾‚¯‚ß‚è‚ñ‚Å‚¢‚é‚©æ“¾Vector3
	DirectX::SimpleMath::Vector3 GetAABB2AABBDepthVector3(const AABB& Box1, const AABB& Box2);
	// Box1‚ªx•ûŒü‚ÉBox2‚É‘Î‚µ‚Ä‚Ç‚ê‚¾‚¯‚ß‚è‚ñ‚Å‚¢‚é‚©æ“¾
	float GetAABB2AABBDepthX(const AABB& Box1, const AABB& Box2);
	// Box1‚ªy•ûŒü‚ÉBox2‚É‘Î‚µ‚Ä‚Ç‚ê‚¾‚¯‚ß‚è‚ñ‚Å‚¢‚é‚©æ“¾
	float GetAABB2AABBDepthY(const AABB& Box1, const AABB& Box2);
	// Box1‚ªz•ûŒü‚ÉBox2‚É‘Î‚µ‚Ä‚Ç‚ê‚¾‚¯‚ß‚è‚ñ‚Å‚¢‚é‚©æ“¾
	float GetAABB2AABBDepthZ(const AABB& Box1, const AABB& Box2);

	// Cylinder“¯m‚ÌÕ“Ë”»’è
	bool Cylinder2Cylinder(const Cylinder& Col1, const Cylinder& Col2);

	bool Sphere2Sphere(const Sphere& Ball1, const Sphere& Ball2);

	bool Box2D2Box2D(const Box2D& Box1, const Box2D& Box2);

	bool Box2D2Circle(const Box2D& Box, const Circle& Cir);

	bool Circle2Circle(const Circle& Circle1, const Circle& Circle2);

	bool Point2D2Rect(const POINT2D& point, const STRUCTRECT& rect);
}