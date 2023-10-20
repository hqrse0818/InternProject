#include "Com_EffectBillboard.h"
#include "../GameObject/GameObject.h"
#include "../System/TextureCreate.h"

Com_Camera* Com_EffectBillboard::p_mCamera = nullptr;
using namespace DirectX::SimpleMath;

Com_EffectBillboard::Com_EffectBillboard()
{
	m_Texture = new ShaderResourceView();
}

void Com_EffectBillboard::Load()
{
	
	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f);

	vertex[1].Position = Vector3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f);

	vertex[2].Position = Vector3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f);

	vertex[3].Position = Vector3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	/*
	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(
		Renderer::GetDevice(),
		L"asset/texture/explosion.png",
		nullptr,
		&m_Texture);
	*/

	//assert(m_Texture);
}

void Com_EffectBillboard::Unload()
{
	m_VertexBuffer->Release();
}

void Com_EffectBillboard::Init()
{
	Load();
}

void Com_EffectBillboard::Uninit()
{
	Unload();
	delete m_Texture;
}

void Com_EffectBillboard::Update()
{
}

void Com_EffectBillboard::Draw()
{
	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = Vector3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(fCurrentx, fCurrenty);

	vertex[1].Position = Vector3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(fCurrentz, fCurrenty);

	vertex[2].Position = Vector3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(fCurrentx, fCurrentw);

	vertex[3].Position = Vector3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(fCurrentz, fCurrentw);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// �J�����̃r���[�}�g���N�X�擾
	Matrix view = p_mCamera->GetViewMatrix();

	// �r���[�̋t�s��
	Matrix invView;
	invView = view.Invert();		//�t�s��

	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	
	// ���[���h�}�g���N�X�ݒ�
	Matrix world, scale, /*rot,*/ trans;
	
	scale = Matrix::CreateScale(p_mObject->p_mTransform->mScale.x);
	trans = Matrix::CreateTranslation(p_mObject->p_mTransform->mPosition.x, p_mObject->p_mTransform->mPosition.y, p_mObject->p_mTransform->mPosition.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(&world);
	

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	ID3D11DeviceContext* pDC = Renderer::GetDeviceContext();

	// �e�N�X�`���ݒ�
	ID3D11ShaderResourceView* pSRV = m_Texture->GetSRV();
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &pSRV);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void Com_EffectBillboard::SetTexture(const char* _name)
{
	m_Texture->Create(_name);
}

void Com_EffectBillboard::SetCurrent(int _val)
{
	iCurrent = _val;

	//�e�N�X�`�����W�Z�o

	// UV����������ɕ\���ʒu�̌v�Z
	int SeparateNum = iSeparateX * iSeparateY;
	if (iCurrent > SeparateNum)
	{
		iCurrent = iCurrent % SeparateNum;
	}

	int x = iCurrent % iSeparateX;
	fCurrentx = (1 / iSeparateX) * (x - 1);
	fCurrentz = (1 / iSeparateX) * x;

	int y = iCurrent & iSeparateY;
	fCurrenty = (1 / iSeparateY) * (y - 1);
	fCurrenty = (1 / iSeparateY) * y;
}
