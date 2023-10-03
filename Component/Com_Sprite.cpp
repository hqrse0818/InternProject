#include "Com_Sprite.h"
#include "../DirectX/renderer.h"
#include "../GameObject/GameObject.h"
#include "../System/TextureCreate.h"

using namespace DirectX::SimpleMath;

Com_Sprite::Com_Sprite()
{
	p_mSRV = new ShaderResourceView();
}

void Com_Sprite::Init()
{
	Create();
}


void Com_Sprite::Uninit()
{
	p_mVertexBuffer->Release();
	p_mSRV->Uninit();
	delete p_mSRV;
}

void Com_Sprite::Update()
{
	if (bUpdate)
	{
		Create();
	}
}

void Com_Sprite::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &p_mVertexBuffer, &stride, &offset);

	// テクスチャ設定
	ID3D11ShaderResourceView* srv = p_mSRV->GetSRV();
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &srv);

	// プリミティブトポロジ設定
	Renderer::SetTopologyTriangleStrip();

	// マテリアル設定
	Renderer::SetMaterial(mMaterial);

	Renderer::GetDeviceContext()->Draw(4, 0);

}

void Com_Sprite::SetDivision(float _u, float _v)
{
	if (_u != 0)
	{
		mDivision.x = _u;
	}
	if (_v != 0)
	{
		mDivision.y = _v;
	}
}

void Com_Sprite::SetUV(DirectX::SimpleMath::Vector4 _uv)
{
	mUV = _uv;
}

void Com_Sprite::SetTexture(const char* _name)
{
	// テクスチャを設定
	p_mSRV->Create(_name);

	mMaterial.TextureEnable = true;
}

void Com_Sprite::SetMaterial(MATERIAL mat)
{
	// マテリアルを設定
	mMaterial = mat;
}

void Com_Sprite::SetAmbient(DirectX::SimpleMath::Color _color)
{
	mMaterial.Ambient = _color;
}

void Com_Sprite::SetDiffuse(DirectX::SimpleMath::Color _color)
{
	mMaterial.Diffuse = _color;
}

void Com_Sprite::SetSpecular(DirectX::SimpleMath::Color _color)
{
	mMaterial.Specular = _color;
}

void Com_Sprite::SetEmission(DirectX::SimpleMath::Color _color)
{
	mMaterial.Emission = _color;
}

void Com_Sprite::Create()
{
	VERTEX_3D vertex[4];
	Vector3 vx[4];

	Vector3 center = Vector3(p_mObject->p_mTransform->mPosition.x, p_mObject->p_mTransform->mPosition.y, 0.0f);

	// トランスフォームコンポーネントに基づいてポジションとスケールを設定
	vx[0] = Vector3(p_mObject->p_mTransform->mPosition.x - p_mObject->p_mTransform->mScale.x / 2, p_mObject->p_mTransform->mPosition.y - p_mObject->p_mTransform->mScale.y / 2, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(mUV.x, mUV.y);

	vx[1] = Vector3(p_mObject->p_mTransform->mPosition.x + p_mObject->p_mTransform->mScale.x / 2, p_mObject->p_mTransform->mPosition.y - p_mObject->p_mTransform->mScale.y / 2, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(mUV.z, mUV.y);

	vx[2] = Vector3(p_mObject->p_mTransform->mPosition.x - p_mObject->p_mTransform->mScale.x / 2, p_mObject->p_mTransform->mPosition.y + p_mObject->p_mTransform->mScale.y / 2, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(mUV.x, mUV.w);

	vx[3] = Vector3(p_mObject->p_mTransform->mPosition.x + p_mObject->p_mTransform->mScale.x / 2, p_mObject->p_mTransform->mPosition.y + p_mObject->p_mTransform->mScale.y / 2, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(mUV.z, mUV.w);

	// 回転計算
	for (int i = 0; i < 4; i++)
	{
		vx[i] = vx[i] - center;
	}

	Matrix mat = Matrix::CreateFromYawPitchRoll(p_mObject->p_mTransform->mRotation.y, p_mObject->p_mTransform->mRotation.x, p_mObject->p_mTransform->mRotation.z);

	for (int i = 0; i < 4; i++)
	{
		vx[i] = Vector3::Transform(vx[i], mat);
		vx[i] = vx[i] + center;
		vertex[i].Position = vx[i];
	}

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &p_mVertexBuffer);
}
