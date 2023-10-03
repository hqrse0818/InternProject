#pragma once
#include <SimpleMath.h>
#include <unordered_map>
#include <string>
#include <d3d11.h>

typedef DirectX::SimpleMath::Vector3 POINT3D;
typedef DirectX::SimpleMath::Vector2 POINT2D;

// 6�����Փˏꏊ
enum HitFrom
{
	NoCollision, Top, Bottom, Left, Right, Front, Back
};

// ��{�̒��_�f�[�^
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

// 2����Box
struct Box2D
{
	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	DirectX::SimpleMath::Vector2 Size = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
};

// ��`�\����
struct STRUCTRECT
{
	POINT2D LeftTop, RightTop, LeftBottom, RightBottom;
};

// ����
struct Sphere
{
	DirectX::SimpleMath::Vector3 Center = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	float Radius = 1.0f;
};

// �~��
struct Cylinder
{
	DirectX::SimpleMath::Vector3 Top = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 Bottom = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	float Radius = 1.0f;
};

// �~
struct Circle
{
	DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	float Radius  = 1.0f;
};


// �}�e���A��
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


// ���s����
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	DirectX::SimpleMath::Vector4	Direction;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Ambient;
};

// ���f���̃}�e���A���\����
struct MODEL_MATERIAL
{
	char						name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;
};

// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int				StartIndex;
	unsigned int				IndexNum;
	MODEL_MATERIAL				Material;
};

// ���f���\����
struct MODEL_OBJ
{
	VERTEX_3D*					VertexArray;
	unsigned int				VertexNum;

	unsigned int*				IndexArray;
	unsigned int				IndexNum;
	SUBSET*						SubsetArray;
	unsigned int				SubsetNum;
};

// ���f��
struct MODEL
{
	ID3D11Buffer*				VertexBuffer;
	ID3D11Buffer*				IndexBuffer;

	SUBSET*						SubsetArray;
	unsigned int				SubsetNum;
};

// �萔�o�b�t�@�p�\����
struct MatrixBufferData
{
	// ���[���h�ϊ��s��
	DirectX::SimpleMath::Matrix World;
	// �r���[�ϊ��s��
	DirectX::SimpleMath::Matrix View;
	// �v���W�F�N�V�����ϊ��s��
	DirectX::SimpleMath::Matrix Projection;
};