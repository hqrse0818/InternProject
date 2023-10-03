#include "Collision.h"
using namespace DirectX::SimpleMath;
using namespace std;

// AABB同士の当たり判定
bool Collision::AABB2AABB(const AABB& Box1, const AABB& Box2)
{
	Vector3 myMin = Box1.Center - Box1.Size / 2;
	Vector3 myMax = Box1.Center + Box1.Size / 2;
	Vector3 _oMin = Box2.Center - Box2.Size / 2;
	Vector3 _oMax = Box2.Center + Box2.Size / 2;
	
	if (myMin.x > _oMax.x)return false;
	if (myMax.x < _oMin.x)return false;
	if (myMin.y > _oMax.y)return false;
	if (myMax.y < _oMin.y)return false;
	if (myMin.z > _oMax.z)return false;
	if (myMax.z < _oMin.z)return false;

	return true;
}

bool Collision::AABB2Sphere(const AABB& Box, const Sphere& Ball)
{
	// XY平面
	Box2D BoxXY;
	BoxXY.Center = Vector2(Box.Center.x, Box.Center.y);
	BoxXY.Size = Vector2(Box.Size.x / 2, Box.Size.y / 2);
	Circle CircleXY;
	CircleXY.Center = Vector2(Ball.Center.x, Ball.Center.y);
	CircleXY.Radius = Ball.Radius;

	if (Collision::Box2D2Circle(BoxXY, CircleXY) == false)
		return false;

	// XZ平面
	Box2D BoxXZ;
	BoxXZ.Center = Vector2(Box.Center.x, Box.Center.z);
	BoxXZ.Size = Vector2(Box.Size.x / 2, Box.Size.z / 2);
	Circle CircleXZ;
	CircleXZ.Center = Vector2(Ball.Center.x, Ball.Center.z);
	CircleXZ.Radius = Ball.Radius;
	if (Collision::Box2D2Circle(BoxXZ, CircleXZ) == false)
		return false;

	// YZ平面
	Box2D BoxYZ;
	BoxYZ.Center = Vector2(Box.Center.y, Box.Center.z);
	BoxYZ.Size = Vector2(Box.Size.y / 2, Box.Size.z / 2);
	Circle CircleYZ;
	CircleYZ.Center = Vector2(Ball.Center.y, Ball.Center.z);
	CircleYZ.Radius = Ball.Radius;
	if (Collision::Box2D2Circle(BoxYZ, CircleYZ) == false)
		return false;

	return true;
}

bool Collision::AABB2Cylinder(const AABB& Box, const Cylinder& Col)
{
	return false;
}

// Box2に対してBox1がどれだけめり込んでいるか取得する
DirectX::SimpleMath::Vector3 Collision::GetAABB2AABBDepthVector3(const AABB& Box1, const AABB& Box2)
{
	Vector3 ret = Vector3(0.0f,0.0f,0.0f);

	Vector3 myMin = Box1.Center - Box1.Size / 2;
	Vector3 myMax = Box1.Center + Box1.Size / 2;
	Vector3 _oMin = Box2.Center - Box2.Size / 2;
	Vector3 _oMax = Box2.Center + Box2.Size / 2;

	// Box1が左側にある
	if (myMin.x < _oMin.x && myMax.x > _oMin.x)
	{
		ret.x = _oMin.x - myMax.x;
	}
	// Box1が右側にある
	if (myMax.x > _oMax.x && myMin.x < _oMax.x)
	{
		ret.x = _oMax.x - myMin.x;
	}
	// Box1が下側にある
	if (myMin.y < _oMin.y && myMax.y > _oMin.y && myMax.y < _oMax.y)
	{
		ret.y = _oMin.y - myMax.y;
	}
	// Box1が上側にある
	if (myMax.y > _oMax.y && myMin.y < _oMax.y && myMin.y > _oMin.y)
	{
		ret.y = _oMax.y - myMin.y;
	}
	// 間にあるもしくはBox1の底辺がBox2よりも低く、Box1の上辺がBox2の上辺よりも高い
	if (myMax.y < _oMax.y && myMin.y > _oMin.y || myMax.y > _oMax.y && myMin.y < _oMin.y)
	{
		//ret.y = 0.0f;
	}
	// Box1が手前側にある
	if (myMin.z < _oMin.z && myMax.z > _oMin.z)
	{
		ret.z = _oMin.z - myMax.z;
	}
	// Box1が奥側にある
	if (myMax.z > _oMax.z && myMin.z < _oMax.z)
	{
		ret.z = _oMax.z - myMin.z;
	}
	return ret;
}

float Collision::GetAABB2AABBDepthX(const AABB& Box1, const AABB& Box2)
{
	float Box1Min = Box1.Center.x - Box1.Size.x / 2;
	float Box1Max = Box1.Center.x + Box1.Size.x / 2;
	float Box2Min = Box2.Center.x - Box2.Size.x / 2;
	float Box2Max = Box2.Center.x + Box2.Size.x / 2;

	float ret = 0.0f;

	if (Box1Min < Box2Min && Box1Max > Box2Min)
	{
		ret = Box2Min - Box1Max;
	}
	else if (Box1Max > Box2Max && Box1Min < Box2Max)
	{
		ret = Box2Max - Box1Min;
	}

	return ret;
}

float Collision::GetAABB2AABBDepthY(const AABB& Box1, const AABB& Box2)
{
	float Box1Min = Box1.Center.y - Box1.Size.y / 2;
	float Box1Max = Box1.Center.y + Box1.Size.y / 2;
	float Box2Min = Box2.Center.y - Box2.Size.y / 2;
	float Box2Max = Box2.Center.y + Box2.Size.y / 2;

	float ret = 0.0f;

	if (Box1Min < Box2Min && Box1Max > Box2Min)
	{
		ret = Box2Min - Box1Max;
	}
	else if (Box1Max > Box2Max && Box1Min < Box2Max)
	{
		ret = Box2Max - Box1Min;
	}

	return ret;
}

float Collision::GetAABB2AABBDepthZ(const AABB& Box1, const AABB& Box2)
{
	float Box1Min = Box1.Center.z - Box1.Size.z / 2;
	float Box1Max = Box1.Center.z+ Box1.Size.z / 2;
	float Box2Min = Box2.Center.z - Box2.Size.z / 2;
	float Box2Max = Box2.Center.z + Box2.Size.z / 2;

	float ret = 0.0f;

	if (Box1Min < Box2Min && Box1Max > Box2Min)
	{
		ret = Box2Min - Box1Max;
	}
	else if (Box1Max > Box2Max && Box1Min < Box2Max)
	{
		ret = Box2Max - Box1Min;
	}

	return ret;
}

bool Collision::Cylinder2Cylinder(const Cylinder& Col1, const Cylinder& Col2)
{
	float rr = Col1.Radius + Col2.Radius;

	Vector2 pos1 = Vector2(Col1.Bottom.x, Col1.Bottom.z);
	Vector2 pos2 = Vector2(Col2.Bottom.x, Col2.Bottom.z);

	float dis = Math::GetDistance(pos1, pos2);

	// 二つの半径を足した値が距離以下ならば
	if (dis > rr)return false;

	// y座標を比較
	if (Col1.Bottom.y > Col2.Top.y)return false;
	if (Col1.Top.y < Col2.Bottom.y)return false;

	return true;
}

bool Collision::Sphere2Sphere(const Sphere& Ball1, const Sphere& Ball2)
{
	// 距離を取得
	float distance = 0;

	Vector3 Sub = Ball2.Center - Ball1.Center;
	distance += Math::GetPower(Sub.x, 2);
	distance += Math::GetPower(Sub.y, 2);
	distance += Math::GetPower(Sub.z, 2);

	float rr = Ball1.Radius + Ball2.Radius;
	rr = Math::GetPower(rr, 2);

	if (rr > distance)
	{
		return true;
	}

	return false;
}

bool Collision::Box2D2Box2D(const Box2D& Box1, const Box2D& Box2)
{
	Vector2 bo1min = Box1.Center - Box1.Size;
	Vector2 bo1max = Box1.Center + Box1.Size;
	Vector2 bo2min = Box2.Center - Box2.Size;
	Vector2 bo2max = Box2.Center + Box2.Size;

	if (bo1min.x > bo2max.x)return false;
	if (bo1max.x < bo2min.x)return false;
	if (bo1min.y > bo2max.y)return false;
	if (bo1max.y < bo2min.y)return false;

	return true;
}

bool Collision::Box2D2Circle(const Box2D& Box, const Circle& Cir)
{
	float boxmax = Math::GetDistance(Box.Center, Box.Center + Box.Size);
	float distance = Math::GetDistance(Box.Center, Cir.Center);

	POINT2D point;
	point.x = Cir.Center.x;
	point.y = Cir.Center.y;
	STRUCTRECT tmpRect;


	tmpRect.LeftTop.x = Box.Center.x - (Box.Size.x / 2) - Cir.Radius;
	tmpRect.LeftBottom.x = Box.Center.x - (Box.Size.x / 2) - Cir.Radius;
	tmpRect.RightTop.x = Box.Center.x + (Box.Size.x / 2) + Cir.Radius;
	tmpRect.RightBottom.x = Box.Center.x + (Box.Size.x / 2) + Cir.Radius;
	tmpRect.LeftTop.y = Box.Center.y - (Box.Size.y / 2) - Cir.Radius;
	tmpRect.RightTop.y = Box.Center.y - (Box.Size.y / 2) - Cir.Radius;
	tmpRect.LeftBottom.y = Box.Center.y + (Box.Size.y / 2) + Cir.Radius;
	tmpRect.RightBottom.y = Box.Center.y + (Box.Size.y / 2) + Cir.Radius;

	return Point2D2Rect(point, tmpRect);
}

bool Collision::Circle2Circle(const Circle& Circle1, const Circle& Circle2)
{
	float distance = Math::GetDistance(Circle1.Center, Circle2.Center);

	if (distance < Circle1.Radius + Circle2.Radius)
	{
		return true;
	}
	return false;
}

bool Collision::Point2D2Rect(const POINT2D& point, const STRUCTRECT& rect)
{
	if (point.x < rect.LeftTop.x)return false;
	if (point.x > rect.RightTop.x)return false;
	if (point.y < rect.LeftTop.y)return false;
	if (point.y > rect.RightBottom.y)return false;

	return true;
}
