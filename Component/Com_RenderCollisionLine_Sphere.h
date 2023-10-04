#pragma once
#include "Com_RenderCollider.h"
#include "../DirectX//Shader.h"
#include "../Format.h"

class Com_RenderCollisionLine_Sphere
	: public Com_RenderCollider
{
private:
	DirectX::SimpleMath::Vector3 mRenderVertex[30];
public:
	float fRadius;
	DirectX::SimpleMath::Vector3 mCenter;
	DirectX::SimpleMath::Vector3 mScale;

	void Init();
	void Update();
	void Draw();
};
