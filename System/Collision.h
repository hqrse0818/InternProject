#pragma once
#include "../Format.h"
#include "CustomMath.h"

// �����蔻�菈��

namespace Collision
{
	// AABB���m�̏Փ˔���
	bool AABB2AABB(const AABB& Box1, const AABB& Box2);
	// AABB��Sphere�̏Փ˔���
	bool AABB2Sphere(const AABB& Box, const Sphere& Ball);
	// AABB��Cylinder�̏Փ˔���
	bool AABB2Cylinder(const AABB& Box, const Cylinder& Col);
	// Box1��Box2�ɑ΂��Ăǂꂾ���߂荞��ł��邩�擾Vector3
	DirectX::SimpleMath::Vector3 GetAABB2AABBDepthVector3(const AABB& Box1, const AABB& Box2);
	// Box1��x������Box2�ɑ΂��Ăǂꂾ���߂荞��ł��邩�擾
	float GetAABB2AABBDepthX(const AABB& Box1, const AABB& Box2);
	// Box1��y������Box2�ɑ΂��Ăǂꂾ���߂荞��ł��邩�擾
	float GetAABB2AABBDepthY(const AABB& Box1, const AABB& Box2);
	// Box1��z������Box2�ɑ΂��Ăǂꂾ���߂荞��ł��邩�擾
	float GetAABB2AABBDepthZ(const AABB& Box1, const AABB& Box2);

	// Cylinder���m�̏Փ˔���
	bool Cylinder2Cylinder(const Cylinder& Col1, const Cylinder& Col2);

	bool Sphere2Sphere(const Sphere& Ball1, const Sphere& Ball2);

	bool Box2D2Box2D(const Box2D& Box1, const Box2D& Box2);

	bool Box2D2Circle(const Box2D& Box, const Circle& Cir);

	bool Circle2Circle(const Circle& Circle1, const Circle& Circle2);

	bool Point2D2Rect(const POINT2D& point, const STRUCTRECT& rect);
}