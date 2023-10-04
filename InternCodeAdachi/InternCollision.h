#pragma once
#include "../Format.h"
#include "../System/CustomMath.h"

bool CollisionBox2Sphere(AABB& _box,  Sphere& _sphere)
{
	// ���̂̒��S�_�ƃ{�b�N�X�̒��S�_�̋������v�Z
	float distanceX = Math::Abs(_sphere.Center.x - _box.Center.x);
	float distanceY = Math::Abs(_sphere.Center.y - _box.Center.y);
	float distanceZ = Math::Abs(_sphere.Center.z - _box.Center.z);

	// ���̂̒��S�_����{�b�N�X�̍ł��߂��_�܂ł̋������v�Z
	float closeX = (distanceX - _box.Size.x / 2);
	float closeY = (distanceY - _box.Size.y / 2);
	float closeZ = (distanceZ - _box.Size.z / 2);

	if (closeX < 0.0f)
		closeX = 0.0f;
	if (closeY < 0.0f)
		closeY = 0.0f;
	if (closeZ < 0.0f)
		closeZ = 0.0f;

	// 2�擯�m�Ōv�Z
	float distanceRoot = Math::GetPower(closeX, 2) + Math::GetPower(closeY, 2) + Math::GetPower(closeZ, 2);
	float radiusRoot = Math::GetPower(_sphere.Radius, 2);

	return distanceRoot <= radiusRoot;
}