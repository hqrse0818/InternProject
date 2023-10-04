#if defined(DEBUG) | (_DEBUG)
#include "Com_RenderCollider.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_RenderCollider::Uninit()
{
	p_mVertexBuffer->Release();
	p_mPixelShader->Release();
}

void Com_RenderCollider::Draw()
{
	Renderer::GetDeviceContext()->PSSetShader(p_mPixelShader, nullptr, 0);

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
	Renderer::CreatePixelShader(&p_mPixelShader, "shader\\PS_NoHitLine.cso");
}

void Com_RenderCollider::SetPixelShaderHit()
{
	Renderer::CreatePixelShader(&p_mPixelShader, "shader\\PS_HitLine.cso");
}

#endif