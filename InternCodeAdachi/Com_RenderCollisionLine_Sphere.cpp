#include "Com_RenderCollisionLine_Sphere.h"
#include "../Component/Com_ModelRenderer.h"
#include "../GameObject/GameObject.h"
#include "../DirectX/renderer.h"
#include "../Component/Com_SphereCollider.h"

using namespace DirectX::SimpleMath;

void Com_RenderCollisionLine_Sphere::Init()
{
	Com_SphereCollider* col = p_mObject->GetComponent<Com_SphereCollider>();
	Sphere sphere = col->GetSphere();

	fRadius = sphere.Radius;
	mCenter = sphere.Center;

	// �`��p
	// ����
	mRenderVertex[0] = Vector3(-fRadius, 0.0f, 0.0f);
	mRenderVertex[1] = Vector3(fRadius, 0.0f, 0.0f);

	// �c��
	mRenderVertex[2] = Vector3(0.0f, fRadius, 0.0f);
	mRenderVertex[3] = Vector3(0.0f, -fRadius, 0.0f);

	// ���s����
	mRenderVertex[4] = Vector3(0.0f, 0.0f, fRadius);
	mRenderVertex[5] = Vector3(0.0f, 0.0f, -fRadius);

	// �e�����Ȃ�
	// ���S
	mRenderVertex[6] = mRenderVertex[0];
	mRenderVertex[7] = mRenderVertex[4];

	mRenderVertex[8] = mRenderVertex[4];
	mRenderVertex[9] = mRenderVertex[1];

	mRenderVertex[10] = mRenderVertex[1];
	mRenderVertex[11] = mRenderVertex[5];

	mRenderVertex[12] = mRenderVertex[5];
	mRenderVertex[13] = mRenderVertex[0];

	mRenderVertex[14] = mRenderVertex[0];
	mRenderVertex[15] = mRenderVertex[2];

	mRenderVertex[16] = mRenderVertex[1];
	mRenderVertex[17] = mRenderVertex[2];

	mRenderVertex[18] = mRenderVertex[4];
	mRenderVertex[19] = mRenderVertex[2];

	mRenderVertex[20] = mRenderVertex[5];
	mRenderVertex[21] = mRenderVertex[2];

	mRenderVertex[22] = mRenderVertex[0];
	mRenderVertex[23] = mRenderVertex[3];

	mRenderVertex[24] = mRenderVertex[1];
	mRenderVertex[25] = mRenderVertex[3];

	mRenderVertex[26] = mRenderVertex[4];
	mRenderVertex[27] = mRenderVertex[3];

	mRenderVertex[28] = mRenderVertex[5];
	mRenderVertex[29] = mRenderVertex[3];

	for (int i = 0; i < 30; i++)
	{
		mRenderVertex[i] += mCenter;
	}

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector3) * 30;	// ���_�f�[�^�̐��������w��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = mRenderVertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &p_mVertexBuffer);
	}
}

void Com_RenderCollisionLine_Sphere::Update()
{
	if (p_mObject->GetComponent<Com_SphereCollider>()->GetHit())
	{
		SetPixelShaderHit();
	}
	else
	{
		SetPixelShaderNoHit();
	}
}

void Com_RenderCollisionLine_Sphere::Draw()
{
	Com_RenderCollider::Draw();

	// �`��
	Renderer::GetDeviceContext()->Draw(30, 0);
}