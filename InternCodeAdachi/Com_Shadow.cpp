#include "Com_Shadow.h"
#include "../System/TextureCreate.h"
#include "../GameObject/GameObject.h"
#include "../DirectX/renderer.h"
#include "../System/CustomMath.h"

using namespace DirectX::SimpleMath;

Com_Shadow::Com_Shadow()
{
	p_mSRV->Create("asset\\texture\\shadow.png");
}

void Com_Shadow::Init()
{
	// 頂点情報の設定
	Vector3 Pos = p_mObject->p_mTransform->mPosition;

	vertex[0].Position = Vector3(Pos.x - mOriginalSize.x, 0.0f, Pos.z + mOriginalSize.y);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(Pos.x + mOriginalSize.x, 0.0f, Pos.z + mOriginalSize.y);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(Pos.x - mOriginalSize.x, 0.0f, Pos.z - mOriginalSize.y);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(Pos.x + mOriginalSize.x, 0.0f, Pos.z - mOriginalSize.y);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &p_mVertexBuffer);

	p_mMaterial.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	p_mMaterial.TextureEnable = true;
}

void Com_Shadow::Update()
{
	mPosition.x = p_mObject->p_mTransform->mPosition.x;
	mPosition.z = p_mObject->p_mTransform->mPosition.z;
	mPosition.y = p_mObject->p_mTransform->mPosition.y + fHeight;

	//// 頂点情報の設定
	//Vector3 Pos = p_mObject->p_mTransform->mPosition;

	//vertex[0].Position = Vector3(Pos.x - mOriginalSize.x, fHeight, Pos.z - mOriginalSize.y);
	//vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	//vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	//vertex[1].Position = Vector3(Pos.x + mOriginalSize.x, fHeight, Pos.z - mOriginalSize.y);
	//vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	//vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	//vertex[2].Position = Vector3(Pos.x - mOriginalSize.x, fHeight, Pos.z + mOriginalSize.y);
	//vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	//vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	//vertex[3].Position = Vector3(Pos.x + mOriginalSize.x, fHeight, Pos.z + mOriginalSize.y);
	//vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	//vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[3].TexCoord = Vector2(1.0f, 1.0f);
}

void Com_Shadow::Draw()
{
	// ワールドマトリックスの設定
	Matrix world, scale, trans;
	scale = Matrix::CreateScale(p_mObject->p_mTransform->mScale.x);
	trans = Matrix::CreateTranslation(mPosition);

	world = scale * trans;

	Renderer::SetWorldMatrix(&world);

	// 頂点バッファの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &p_mVertexBuffer, &stride, &offset);

	Renderer::SetMaterial(p_mMaterial);

	// テクスチャ設定
	auto context = Renderer::GetDeviceContext();
	ID3D11ShaderResourceView* srv = p_mSRV->GetSRV();
	context->PSSetShaderResources(0, 1, &srv);

	// プリミティブトポロジ設定
	Renderer::SetTopologyTriangleStrip();

	// 描画
	Renderer::SetDepthEnable(false);

	Renderer::GetDeviceContext()->Draw(4, 0);

	Renderer::SetDepthEnable(true);
}
