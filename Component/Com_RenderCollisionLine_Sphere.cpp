#include "Com_RenderCollisionLine_Sphere.h"
#include "Com_ModelRenderer.h"
#include "../GameObject/GameObject.h"
#include "../DirectX/renderer.h"
#include "Com_SphereCollider.h"

using namespace DirectX::SimpleMath;

void Com_RenderCollisionLine_Sphere::Init()
{
	Com_SphereCollider* col = p_mObject->GetComponent<Com_SphereCollider>();
	Sphere sphere = col->GetSphere();

	fRadius = sphere.Radius;
	mCenter = sphere.Center;
	mScale = p_mObject->p_mTransform->mScale;

	// 描画用
	// 横線
	mRenderVertex[0] = Vector3(-fRadius, mCenter.y, mCenter.z);
	mRenderVertex[1] = Vector3(fRadius, mCenter.y, mCenter.z);

	// 縦線
	mRenderVertex[2] = Vector3(mCenter.x, fRadius, mCenter.z);
	mRenderVertex[3] = Vector3(mCenter.x, -fRadius, mCenter.z);

	// 奥行き線
	mRenderVertex[4] = Vector3(mCenter.x, mCenter.y, fRadius);
	mRenderVertex[5] = Vector3(mCenter.x, mCenter.y, -fRadius);

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
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector3) * 30;	// 頂点データの数分だけ指定
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

	// 描画
	Renderer::GetDeviceContext()->Draw(30, 0);
}