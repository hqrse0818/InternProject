#include "Com_CustomSprite.h"
#include "../DirectX/renderer.h"
#include "../GameObject/GameObject.h"
#include "../System/TextureCreate.h"

using namespace DirectX::SimpleMath;

void Com_CustomSprite::Init()
{
	Create();
}

void Com_CustomSprite::Draw()
{
	Com_Sprite::Draw();
}

void Com_CustomSprite::Create()
{
	VERTEX_3D vertex[4];

	Vector3 StartPoint;
	StartPoint = p_mObject->p_mTransform->mPosition;
	Vector3 Scale;
	Scale = p_mObject->p_mTransform->mScale;

	switch (mType)
	{
	case Com_CustomSprite::CustomType::Center:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y + Scale.y / 2, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y + Scale.y / 2, 0.0f);

		break;
	case Com_CustomSprite::CustomType::CenterTop:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y + Scale.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y + Scale.y, 0.0f);
		break;
	case Com_CustomSprite::CustomType::CenetrBottom:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y - Scale.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y - Scale.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x / 2, StartPoint.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x / 2, StartPoint.y, 0.0f);
		break;
	case Com_CustomSprite::CustomType::Left:
		vertex[0].Position = Vector3(StartPoint.x, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x, StartPoint.y + Scale.y / 2, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y + Scale.y / 2, 0.0f);
		break;
	case Com_CustomSprite::CustomType::LeftTop:
		vertex[0].Position = Vector3(StartPoint.x, StartPoint.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x, StartPoint.y + Scale.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y + Scale.y, 0.0f);
		break;
	case Com_CustomSprite::CustomType::LeftBottom:
		vertex[0].Position = Vector3(StartPoint.x, StartPoint.y - Scale.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y - Scale.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x, StartPoint.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x + Scale.x, StartPoint.y, 0.0f);
		break;
	case Com_CustomSprite::CustomType::Right:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x, StartPoint.y - Scale.y / 2, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y + Scale.y / 2, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x, StartPoint.y + Scale.y / 2, 0.0f);
		break;
	case Com_CustomSprite::CustomType::RightTop:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x, StartPoint.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y + Scale.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x, StartPoint.y + Scale.y, 0.0f);
		break;
	case Com_CustomSprite::CustomType::RightBottom:
		vertex[0].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y - Scale.y, 0.0f);
		vertex[1].Position = Vector3(StartPoint.x, StartPoint.y - Scale.y, 0.0f);
		vertex[2].Position = Vector3(StartPoint.x - Scale.x, StartPoint.y, 0.0f);
		vertex[3].Position = Vector3(StartPoint.x, StartPoint.y, 0.0f);
		break;
	}
	for (int i = 0; i < 4; i++)
	{
		vertex[i].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i].Normal = Vector3(0.0f, 0.0f, 0.0f);
	}
	vertex[0].TexCoord = Vector2(mUV.x, mUV.y);
	vertex[1].TexCoord = Vector2(mUV.z, mUV.y);
	vertex[2].TexCoord = Vector2(mUV.x, mUV.w);
	vertex[3].TexCoord = Vector2(mUV.z, mUV.w);

	// 回転計算
	for (int i = 0; i < 4; i++)
	{
		vertex[i].Position = vertex[i].Position - StartPoint;
	}

	Matrix mat = Matrix::CreateFromYawPitchRoll(p_mObject->p_mTransform->mRotation.y, p_mObject->p_mTransform->mRotation.x, p_mObject->p_mTransform->mRotation.z);

	for (int i = 0; i < 4; i++)
	{
		vertex[i].Position = Vector3::Transform(vertex[i].Position, mat);
		vertex[i].Position = vertex[i].Position+ StartPoint;
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
