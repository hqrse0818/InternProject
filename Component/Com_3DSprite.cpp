#include "Com_3DSprite.h"
#include "../Format.h"
#include "../DirectX/renderer.h"
#include "../GameObject/GameObject.h"
#include "../System/TextureCreate.h"

using namespace DirectX::SimpleMath;

Com_3DSprite::Com_3DSprite()
{
	p_mSRV = new ShaderResourceView();
}

void Com_3DSprite::Init()
{
	// ���_���̐ݒ�
	
	VERTEX_3D vertex[4];
	vertex[0].Position = Vector3(-50.0f, 0.0f, 50.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(50.0f, 0.0f, 50.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(p_mObject->p_mTransform->mScale.x*20, 0.0f);

	vertex[2].Position = Vector3(-50.0f, 0.0f, -50.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, p_mObject->p_mTransform->mScale.y*20);

	vertex[3].Position = Vector3(50.0f, 0.0f, -50.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(p_mObject->p_mTransform->mScale.x*20, p_mObject->p_mTransform->mScale.y*20);

	// ���_�o�b�t�@����
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

	// �e�N�X�`���̓ǂݍ���
	p_mSRV->Create("asset/texture/field.jpg");

	p_mMaterial.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	p_mMaterial.TextureEnable = true;
}

void Com_3DSprite::Uninit()
{
	p_mVertexBuffer->Release();
	p_mSRV->Uninit();

	delete p_mSRV;
}

void Com_3DSprite::Update()
{
}

void Com_3DSprite::Draw()
{
	// ���[���h�}�g���b�N�X�̐ݒ�
	Matrix world, scale, rot, trans;
	scale = Matrix::CreateScale(p_mObject->p_mTransform->mScale.x);
	rot = Matrix::CreateFromYawPitchRoll(p_mObject->p_mTransform->mRotation.y, p_mObject->p_mTransform->mRotation.x, p_mObject->p_mTransform->mRotation.z);
	trans = Matrix::CreateTranslation(p_mObject->p_mTransform->mPosition);

	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	// ���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &p_mVertexBuffer, &stride, &offset);

	Renderer::SetMaterial(p_mMaterial);

	// �e�N�X�`���ݒ�
	auto context = Renderer::GetDeviceContext(); 
	ID3D11ShaderResourceView* srv = p_mSRV->GetSRV();
	context->PSSetShaderResources(0, 1, &srv);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �v���~�e�B�u�g�|���W�ݒ�
//	Renderer::SetTopologyTriangleStrip();

	// �`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Com_3DSprite::SetTexture(const char* _name)
{
	p_mSRV->Create(_name);
}

void Com_3DSprite::SetMaterial(MATERIAL mat)
{
	p_mMaterial = mat;
}
