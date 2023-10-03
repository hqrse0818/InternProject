#include "Com_RenderCollisionLine_Box.h"
#include "Com_BoxCollider.h"
#include "../GameObject/GameObject.h"

using namespace DirectX::SimpleMath;

void Com_RenderCollisionLine_Box::Init()
{
	// �R���|�[�l���g���ꎞ�I�Ɏ擾
	Com_BoxCollider* col = p_mObject->GetComponent<Com_BoxCollider>();
	AABB box = col->GetAABB();

	mSize = col->mSize;
	mCenter = col->mCenter;
	mScale = p_mObject->p_mTransform->mScale;

	// �\���p���_�̒�`
	// ���
	mRenderVertex[0] = Vector3(-mSize.x / 2, mSize.y / 2, mSize.z / 2);
	mRenderVertex[1] = Vector3(mSize.x / 2, mSize.y / 2, mSize.z / 2);
	mRenderVertex[2] = Vector3(-mSize.x / 2, mSize.y / 2, -mSize.z / 2);
	mRenderVertex[3] = Vector3(mSize.x / 2, mSize.y / 2, -mSize.z / 2);
	// ����
	mRenderVertex[4] = Vector3(-mSize.x / 2, -mSize.y / 2, mSize.z / 2);
	mRenderVertex[5] = Vector3(mSize.x / 2, -mSize.y / 2, mSize.z / 2);
	mRenderVertex[6] = Vector3(-mSize.x / 2, -mSize.y / 2, -mSize.z / 2);
	mRenderVertex[7] = Vector3(mSize.x / 2, -mSize.y / 2, -mSize.z / 2);

	// �����Ȃ�
	// ���
	mRenderVertex[8] = mRenderVertex[0];
	mRenderVertex[9] = mRenderVertex[2];
	mRenderVertex[10] = mRenderVertex[1];
	mRenderVertex[11] = mRenderVertex[3];

	// ����
	mRenderVertex[12] = mRenderVertex[4];
	mRenderVertex[13] = mRenderVertex[6];
	mRenderVertex[14] = mRenderVertex[5];
	mRenderVertex[15] = mRenderVertex[7];

	// ����
	mRenderVertex[16] = mRenderVertex[0];
	mRenderVertex[17] = mRenderVertex[4];

	mRenderVertex[18] = mRenderVertex[1];
	mRenderVertex[19] = mRenderVertex[5];

	mRenderVertex[20] = mRenderVertex[2];
	mRenderVertex[21] = mRenderVertex[6];

	mRenderVertex[22] = mRenderVertex[3];
	mRenderVertex[23] = mRenderVertex[7];

	for (int i = 0; i < RenderBoxVertexNum; i++)
	{
		mRenderVertex[i] *= mScale;
		mRenderVertex[i] += mCenter;
	}

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector3) * RenderBoxVertexNum;	// ���_�f�[�^�̐��������w��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = mRenderVertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &p_mVertexBuffer);
	}
}

void Com_RenderCollisionLine_Box::Update()
{
	if (p_mObject->GetComponent<Com_BoxCollider>()->GetHit())
	{
		SetPixelShaderHit();
	}
	else
	{
		SetPixelShaderNoHit();
	}
}

void Com_RenderCollisionLine_Box::Draw()
{
	Com_RenderCollider::Draw();

	// �`��
	Renderer::GetDeviceContext()->Draw(RenderBoxVertexNum, 0);
}

void Com_RenderCollisionLine_Box2D::Init()
{
	Com_BoxCollider2D* TmpCol = p_mObject->GetComponent<Com_BoxCollider2D>();
	Box2D box = TmpCol->GetBox();

	mRenderVertex[0] = Vector2(-box.Size.x / 2, -box.Size.y / 2);
	mRenderVertex[1] = Vector2(box.Size.x / 2, -box.Size.y / 2);
	mRenderVertex[2] = Vector2(-box.Size.x / 2, box.Size.y / 2);
	mRenderVertex[3] = Vector2(box.Size.x / 2, box.Size.y / 2);
	//RenderVertex[4] = RenderVertex[0];
	//RenderVertex[5] = RenderVertex[2];
	//RenderVertex[6] = RenderVertex[1];
	//RenderVertex[7] = RenderVertex[3];

	for (int i = 0; i < 8; i++)
	{
		mRenderVertex[i].x *= p_mObject->p_mTransform->mScale.x;
		mRenderVertex[i].y *= p_mObject->p_mTransform->mScale.y;
		mRenderVertex[i] += box.Center;
	}

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector2) * 8;	// ���_�f�[�^�̐��������w��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = mRenderVertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mVertexBuffer);
	}
}

void Com_RenderCollisionLine_Box2D::Update()
{

}

void Com_RenderCollisionLine_Box2D::Uninit()
{
	mVertexBuffer->Release();
}

void Com_RenderCollisionLine_Box2D::Draw()
{

	Renderer::SetWorldViewProjection2D();
	// ���_�o�b�t�@�̐ݒ�
	UINT stride = sizeof(Vector2);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);


	Matrix trans;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(p_mObject->p_mTransform->mPosition);
	Renderer::SetWorldMatrix(&trans);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::SetTopologyLineStrip();

	// �`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}
