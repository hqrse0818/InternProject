#if defined(DEBUG) | (_DEBUG)
#include "Com_RenderCollider.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

Com_RenderCollider::Com_RenderCollider()
{
	p_mVS = new VertexShader();
	p_mVS->Load(VS_MODEL);
	p_mPS = new PixelShader();
	p_mPS->Load(PS_MODEL);
}

void Com_RenderCollider::Uninit()
{
	p_mVS->Uninit();
	delete p_mVS;
	p_mPS->Uninit();
	delete p_mPS;
	if (p_mVertexBuffer)
	{
		p_mVertexBuffer->Release();
		p_mVertexBuffer = nullptr;
	}
}

void Com_RenderCollider::Draw()
{
	p_mVS->Bind();
	p_mPS->Bind();

	// 頂点バッファの設定
	UINT stride = sizeof(Vector3);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &p_mVertexBuffer, &stride, &offset);


	Matrix trans;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(p_mObject->p_mTransform->mPosition);
	Renderer::SetWorldMatrix(&trans);

	// プリミティブトポロジ設定
	Renderer::SetTopologyLineList();
}

void Com_RenderCollider::SetPixelShaderNoHit()
{
	p_mPS->Load("shader\\PS_NoHitLine.cso");
}

void Com_RenderCollider::SetPixelShaderHit()
{
	p_mPS->Load("shader\\PS_HitLine.cso");
}

#endif