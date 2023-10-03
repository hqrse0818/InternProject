#pragma once
#include <SimpleMath.h>
#include <unordered_map>
#include <string>
#include <d3d11.h>

typedef DirectX::SimpleMath::Vector3 POINT3D;
typedef DirectX::SimpleMath::Vector2 POINT2D;

// 6方向衝突場所
enum HitFrom
{
	NoCollision, Top, Bottom, Left, Right, Front, Back
};

// 基本の頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Normal;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Vector2 TexCoord;
};

// AABB
struct AABB
{
	DirectX::SimpleMath::Vector3 Center = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 Size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	DirectX::SimpleMath::Vector3 getmin()
	{
		return Center - Size / 2;
	}
	DirectX::SimpleMath::Vector3 getmax()
	{
		return Center + Size / 2;
	}
};

// 2次元Box
struct Box2D
{
	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	DirectX::SimpleMath::Vector2 Size = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
};

// 矩形構造体
struct STRUCTRECT
{
	POINT2D LeftTop, RightTop, LeftBottom, RightBottom;
};

// 球体
struct Sphere
{
	DirectX::SimpleMath::Vector3 Center = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	float Radius = 1.0f;
};

// 円柱
struct Cylinder
{
	DirectX::SimpleMath::Vector3 Top = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 Bottom = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	float Radius = 1.0f;
};

// 円
struct Circle
{
	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	float Radius  = 1.0f;
};


// マテリアル
struct MATERIAL
{
	DirectX::SimpleMath::Color	Ambient;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Specular;
	DirectX::SimpleMath::Color	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2];

	MATERIAL()
	{
		Ambient = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
		Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
		Specular = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
		Emission = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
		Shininess = 1.0f;
		TextureEnable = true;
		Dummy[0] = 0.0f;
		Dummy[1] = 0.0f;
	}
};


// 平行光源
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	DirectX::SimpleMath::Vector4	Direction;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Ambient;
};

// モデルのマテリアル構造体
struct MODEL_MATERIAL
{
	char						name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned int				StartIndex;
	unsigned int				IndexNum;
	MODEL_MATERIAL				Material;
};

// モデル構造体
struct MODEL_OBJ
{
	VERTEX_3D*					VertexArray;
	unsigned int				VertexNum;

	unsigned int*				IndexArray;
	unsigned int				IndexNum;
	SUBSET*						SubsetArray;
	unsigned int				SubsetNum;
};

// モデル
struct MODEL
{
	ID3D11Buffer*				VertexBuffer;
	ID3D11Buffer*				IndexBuffer;

	SUBSET*						SubsetArray;
	unsigned int				SubsetNum;
};

// 定数バッファ用構造体
struct MatrixBufferData
{
	// ワールド変換行列
	DirectX::SimpleMath::Matrix World;
	// ビュー変換行列
	DirectX::SimpleMath::Matrix View;
	// プロジェクション変換行列
	DirectX::SimpleMath::Matrix Projection;
};