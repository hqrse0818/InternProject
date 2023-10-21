#if defined (DEBUG) || defined(_DEBUG)

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

	// 描画用
	// 横線
	mRenderVertex[0] = Vector3(-fRadius, 0.0f, 0.0f);
	mRenderVertex[1] = Vector3(fRadius, 0.0f, 0.0f);

	// 縦線
	mRenderVertex[2] = Vector3(0.0f, fRadius, 0.0f);
	mRenderVertex[3] = Vector3(0.0f, -fRadius, 0.0f);

	// 奥行き線
	mRenderVertex[4] = Vector3(0.0f, 0.0f, fRadius);
	mRenderVertex[5] = Vector3(0.0f, 0.0f, -fRadius);

	// 各線をつなぐ
	// 中心
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

	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(Vector3) * 30;	// 頂点データの数分だけ指定
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

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

	Com_SphereCollider* col = p_mObject->GetComponent<Com_SphereCollider>();
	Sphere sphere = col->GetSphere();

	fRadius = sphere.Radius;
	mCenter = sphere.Center;

	D3D11_MAPPED_SUBRESOURCE ms;
	Renderer::GetDeviceContext()->Map(p_mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

	Vector3* vertex = (Vector3*)ms.pData;

	// 描画用
	// 横線
	vertex[0] = Vector3(-fRadius, 0.0f, 0.0f);
	vertex[1] = Vector3(fRadius, 0.0f, 0.0f);

	// 縦線
	vertex[2] = Vector3(0.0f, fRadius, 0.0f);
	vertex[3] = Vector3(0.0f, -fRadius, 0.0f);

	// 奥行き線
	vertex[4] = Vector3(0.0f, 0.0f, fRadius);
	vertex[5] = Vector3(0.0f, 0.0f, -fRadius);

	// 各線をつなぐ
	// 中心
	vertex[6] = vertex[0];
	vertex[7] = vertex[4];

	vertex[8] = vertex[4];
	vertex[9] = vertex[1];

	vertex[10] = vertex[1];
	vertex[11] = vertex[5];

	vertex[12] = vertex[5];
	vertex[13] = vertex[0];

	vertex[14] = vertex[0];
	vertex[15] = vertex[2];

	vertex[16] = vertex[1];
	vertex[17] = vertex[2];

	vertex[18] = vertex[4];
	vertex[19] = vertex[2];

	vertex[20] = vertex[5];
	vertex[21] = vertex[2];

	vertex[22] = vertex[0];
	vertex[23] = vertex[3];

	vertex[24] = vertex[1];
	vertex[25] = vertex[3];

	vertex[26] = vertex[4];
	vertex[27] = vertex[3];

	vertex[28] = vertex[5];
	vertex[29] = vertex[3];

	for (int i = 0; i < 30; i++)
	{
		vertex[i] += mCenter;
	}

	Renderer::GetDeviceContext()->Unmap(p_mVertexBuffer, 0);
}

void Com_RenderCollisionLine_Sphere::Draw()
{
	Com_RenderCollider::Draw();

	// 描画
	Renderer::GetDeviceContext()->Draw(30, 0);
}

#endif