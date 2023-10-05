#pragma once
#if defined (DEBUG) || defined(_DEBUG)
#include "../Component/Com_RenderCollider.h"
#include "../DirectX//Shader.h"
#include "../Format.h"

// ����R���C�_�[�̊ȈՕ`��p�R���|�[�l���g���ʑ̂�`�悷��

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

#endif
