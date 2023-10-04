#pragma once
#include "../Format.h"
#include "../System/CustomMath.h"

bool CollisionBox2Sphere(AABB& _box,  Sphere& _sphere)
{
	// 球体の中心点とボックスの中心点の距離を計算
	float distanceX = Math::Abs(_sphere.Center.x - _box.Center.x);
	float distanceY = Math::Abs(_sphere.Center.y - _box.Center.y);
	float distanceZ = Math::Abs(_sphere.Center.z - _box.Center.z);

	// 球体の中心点からボックスの最も近い点までの距離を計算
	float closeX = (distanceX - _box.Size.x / 2);
	float closeY = (distanceY - _box.Size.y / 2);
	float closeZ = (distanceZ - _box.Size.z / 2);

	if (closeX < 0.0f)
		closeX = 0.0f;
	if (closeY < 0.0f)
		closeY = 0.0f;
	if (closeZ < 0.0f)
		closeZ = 0.0f;

	// 2乗同士で計算
	float distanceRoot = Math::GetPower(closeX, 2) + Math::GetPower(closeY, 2) + Math::GetPower(closeZ, 2);
	float radiusRoot = Math::GetPower(_sphere.Radius, 2);

	return distanceRoot <= radiusRoot;
}