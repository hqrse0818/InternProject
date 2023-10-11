#include "Com_Model.h"
#include "../System/ModelPool.h"
#include "../DirectX/renderer.h"
#include "../System/Time.h"

#include <iostream>

using namespace std;
using namespace DirectX::SimpleMath;

void Com_Model::UpdateBoneMatrix(aiNode* _Node, aiMatrix4x4 _Matrix)
{
	// �����œn���ꂽ�m�[�h�����L�[�Ƃ��ă{�[�������擾
	BONE* bone = &mModelData->map_mBone[_Node->mName.C_Str()];

	// �}�g���N�X�̏�Z���Ԃɒ��ӂ���
	aiMatrix4x4 worldMatrix;

	// �e�̎p���ƈʒu��������Ԃɂ���
	worldMatrix = _Matrix;
	// �����œn���ꂽ�s����|����
	worldMatrix *= bone->AnimationMatrix;

	// �v���O�������ɗp�ӂ��Ă���s��ɔ��f
	bone->Matrix = worldMatrix;
	// �I�t�Z�b�g�s��𔽉f
	bone->Matrix *= bone->OffsetMatrix;

	for (unsigned int index = 0; index < _Node->mNumChildren; index++)
	{
		UpdateBoneMatrix(_Node->mChildren[index], worldMatrix);
	}
}

Com_Model::Com_Model()
{
	mScale.x = 1.0f;
	mScale.y = 1.0f;
	mScale.z = 1.0f;
	mScale.w = 1.0f;
}

bool Com_Model::SetModelData(const char* _ModelName)
{
	mModelData = ModelPool::GetModelData(_ModelName);

	if (mModelData)
	{
		cout << "���f���擾����" << endl;
		// �萔�o�b�t�@���쐬
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(BoneCompMatrix);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		

		HRESULT hr = Renderer::GetDevice()->CreateBuffer(&bd, nullptr, &p_mCombBuffer);
		if (FAILED(hr))
		{
			std::cout << "�{�[���R���r�l�[�V�����s��o�b�t�@�쐬���s" << endl;
			return false;
		}
		assert(p_mCombBuffer);

		// �{�[���̃R���r�l�[�V�����s��̔z��𐶐�
		std::vector<aiMatrix4x4> BoneCombContainer;
		BoneCombContainer.resize(mModelData->map_mBone.size());
		for (auto data : mModelData->map_mBone)
		{
			BoneCombContainer[data.second.mIndex] = data.second.Matrix;
		}

		// �]�u
		for (auto& mtx : BoneCombContainer)
		{
			mtx.Transpose();
		}

		// �萔�o�b�t�@�X�V
		D3D11_MAPPED_SUBRESOURCE ms;
		BoneCompMatrix* pData = nullptr;

		hr = Renderer::GetDeviceContext()->Map(
			p_mCombBuffer,
			0, D3D11_MAP_WRITE_DISCARD,
			0, &ms);
		if (SUCCEEDED(hr))
		{
			pData = (BoneCompMatrix*)ms.pData;
			memcpy(pData->BoneCombMtx,
				BoneCombContainer.data(),
				sizeof(aiMatrix4x4) * BoneCombContainer.size());
			Renderer::GetDeviceContext()->Unmap(p_mCombBuffer, 0);
		}

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector4);
		bd.CPUAccessFlags = 0;

		hr = Renderer::GetDevice()->CreateBuffer(&bd, NULL, &p_mScaleBuffer);
		if (FAILED(hr))
		{
			std::cout << "�X�P�[���p�o�b�t�@�쐬���s" << endl;
			return false;
		}

		return true;
	}
	
	cout << "���f���̎擾�Ɏ��s : ���f���� " << _ModelName << endl;
	return false;
}

void Com_Model::Update()
{
	bRotLastKey = false;
	bPosLastKey = false;

	Time->CountStart();
	// ���̍X�V�Ŗ�0.02�b�������Ă���(���̌Ăяo������̏ꍇ��50FPS)

	if (!bPlayAnim)
	{
		// �X�P�[���o�b�t�@�̍X�V
		Renderer::GetDeviceContext()->UpdateSubresource(p_mScaleBuffer, 0, nullptr, &mScale, 0, 0);
		return;
	}
		

	// �Đ�����A�j���[�V���������o�^����Ă��邩�m�F
	if (mModelData->map_mAnimation.count(p_cPlayAnimationName) == 0)
	{
		// �X�P�[���o�b�t�@�̍X�V
		Renderer::GetDeviceContext()->UpdateSubresource(p_mScaleBuffer, 0, nullptr, &mScale, 0, 0);
		return;
	}
		

	// �Đ�����A�j���[�V���������邩�m�F
	if (!mModelData->map_mAnimation[p_cPlayAnimationName]->HasAnimations())
	{
		// �X�P�[���o�b�t�@�̍X�V
		Renderer::GetDeviceContext()->UpdateSubresource(p_mScaleBuffer, 0, nullptr, &mScale, 0, 0);
		return;
	}
		

	// �A�j���[�V�������擾
	aiAnimation* animation = mModelData->map_mAnimation[p_cPlayAnimationName]->mAnimations[0];


	for (unsigned int i = 0; i < animation->mNumChannels; i++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[i];

		BONE* bone = &mModelData->map_mBone[nodeAnim->mNodeName.C_Str()];

		int f;
		// �t���[���ɑ΂���A�j���[�V�����̉�]���擾
		f = iFrame1 % nodeAnim->mNumRotationKeys;
		if (f == nodeAnim->mNumRotationKeys - 1)
			bRotLastKey = true;
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		// �t���[���ɑ΂���|�W�V�����̈ʒu���擾
		f = iFrame1 % nodeAnim->mNumPositionKeys;
		if (f == nodeAnim->mNumPositionKeys -1)
			bPosLastKey = true;
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		bone->AnimationMatrix =
			aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f),
				rot, pos);
	}

	// �{�[���s��̍X�V
	aiMatrix4x4 rootMatrix = aiMatrix4x4(
		aiVector3D(1.0f, 1.0f, 1.0f),
		aiQuaternion(AI_MATH_PI, 0.0f, 0.0f),
		aiVector3D(0.0f, 0.0f, 0.0f));

	// �ċA�I�ɏ���
	UpdateBoneMatrix(mModelData->p_mAiScene->mRootNode, rootMatrix);

	// �{�[���̃R���r�l�[�V�����s��̔z��𐶐�
	std::vector<aiMatrix4x4> BoneCombContainer;
	BoneCombContainer.resize(mModelData->map_mBone.size());
	for (auto data : mModelData->map_mBone)
	{
		BoneCombContainer[data.second.mIndex] = data.second.Matrix;
	}

	// �]�u
	for (auto& mtx : BoneCombContainer)
	{
		mtx.Transpose();
	}

	// �萔�o�b�t�@�X�V
	D3D11_MAPPED_SUBRESOURCE ms;
	BoneCompMatrix* pData = nullptr;

	HRESULT hr = Renderer::GetDeviceContext()->Map(
		p_mCombBuffer,
		0, D3D11_MAP_WRITE_DISCARD,
		0, &ms);
	if (SUCCEEDED(hr))
	{
		pData = (BoneCompMatrix*)ms.pData;
		memcpy(pData->BoneCombMtx,
			BoneCombContainer.data(),
			sizeof(aiMatrix4x4) * BoneCombContainer.size());
		Renderer::GetDeviceContext()->Unmap(p_mCombBuffer, 0);
	}


	//// ���_�̕ϊ�
	//for (unsigned int m = 0; m < mModelData->p_mAiScene->mNumMeshes; m++)
	//{
	//	aiMesh* p_mesh = mModelData->p_mAiScene->mMeshes[m];

	//	D3D11_MAPPED_SUBRESOURCE ms;
	//	Renderer::GetDeviceContext()->Map(pp_mVertexBuffer[m], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

	//	VERTEX_3D* vx = (VERTEX_3D*)ms.pData;

	//	for (unsigned int v = 0; v < p_mesh->mNumVertices; v++)
	//	{
	//		DEFORM_VERTEX* dvx = &mModelData->vec_mDeformVertex[m][v];

	//		std::vector<int> bNum;
	//		bNum.resize(dvx->BoneNum);

	//		for (unsigned int i = 0; i < bNum.size(); i++)
	//		{
	//			bNum[i] = dvx->BoneIndex[i];
	//		}

	//		aiMatrix4x4 mat[4];
	//		aiMatrix4x4 outmat;

	//		//// �[���}�g���b�N�X
	//		//aiMatrix4x4 zeromat = {
	//		//	0.0f, 0.0f, 0.0f, 0.0f,
	//		//	0.0f, 0.0f, 0.0f, 0.0f,
	//		//	0.0f, 0.0f, 0.0f, 0.0f,
	//		//	0.0f, 0.0f, 0.0f, 0.0f };

	//		//// ������
	//		//for (unsigned int j = 0; j < 4; j++)
	//		//{
	//		//	mat[j] = zeromat;
	//		//}

	//		for (unsigned int i = 0; i < bNum.size(); i++)
	//		{
	//			mat[i] = BoneCombContainer[bNum[i]];
	//		}

	//		{
	//			outmat.a1 = mat[0].a1 * dvx->BoneWeight[0]
	//				+ mat[1].a1 * dvx->BoneWeight[1]
	//				+ mat[2].a1 * dvx->BoneWeight[2]
	//				+ mat[3].a1 * dvx->BoneWeight[3];

	//			outmat.a2 = mat[0].a2 * dvx->BoneWeight[0]
	//				+ mat[1].a2 * dvx->BoneWeight[1]
	//				+ mat[2].a2 * dvx->BoneWeight[2]
	//				+ mat[3].a2 * dvx->BoneWeight[3];

	//			outmat.a3 = mat[0].a3 * dvx->BoneWeight[0]
	//				+ mat[1].a3 * dvx->BoneWeight[1]
	//				+ mat[2].a3 * dvx->BoneWeight[2]
	//				+ mat[3].a3 * dvx->BoneWeight[3];

	//			outmat.a4 = mat[0].a4 * dvx->BoneWeight[0]
	//				+ mat[1].a4 * dvx->BoneWeight[1]
	//				+ mat[2].a4 * dvx->BoneWeight[2]
	//				+ mat[3].a4 * dvx->BoneWeight[3];


	//			outmat.b1 = mat[0].b1 * dvx->BoneWeight[0]
	//				+ mat[1].b1 * dvx->BoneWeight[1]
	//				+ mat[2].b1 * dvx->BoneWeight[2]
	//				+ mat[3].b1 * dvx->BoneWeight[3];

	//			outmat.b2 = mat[0].b2 * dvx->BoneWeight[0]
	//				+ mat[1].b2 * dvx->BoneWeight[1]
	//				+ mat[2].b2 * dvx->BoneWeight[2]
	//				+ mat[3].b2 * dvx->BoneWeight[3];

	//			outmat.b3 = mat[0].b3 * dvx->BoneWeight[0]
	//				+ mat[1].b3 * dvx->BoneWeight[1]
	//				+ mat[2].b3 * dvx->BoneWeight[2]
	//				+ mat[3].b3 * dvx->BoneWeight[3];

	//			outmat.b4 = mat[0].b4 * dvx->BoneWeight[0]
	//				+ mat[1].b4 * dvx->BoneWeight[1]
	//				+ mat[2].b4 * dvx->BoneWeight[2]
	//				+ mat[3].b4 * dvx->BoneWeight[3];


	//			outmat.c1 = mat[0].c1 * dvx->BoneWeight[0]
	//				+ mat[1].c1 * dvx->BoneWeight[1]
	//				+ mat[2].c1 * dvx->BoneWeight[2]
	//				+ mat[3].c1 * dvx->BoneWeight[3];

	//			outmat.c2 = mat[0].c2 * dvx->BoneWeight[0]
	//				+ mat[1].c2 * dvx->BoneWeight[1]
	//				+ mat[2].c2 * dvx->BoneWeight[2]
	//				+ mat[3].c2 * dvx->BoneWeight[3];

	//			outmat.c3 = mat[0].c3 * dvx->BoneWeight[0]
	//				+ mat[1].c3 * dvx->BoneWeight[1]
	//				+ mat[2].c3 * dvx->BoneWeight[2]
	//				+ mat[3].c3 * dvx->BoneWeight[3];

	//			outmat.c4 = mat[0].c4 * dvx->BoneWeight[0]
	//				+ mat[1].c4 * dvx->BoneWeight[1]
	//				+ mat[2].c4 * dvx->BoneWeight[2]
	//				+ mat[3].c4 * dvx->BoneWeight[3];


	//			outmat.d1 = mat[0].d1 * dvx->BoneWeight[0]
	//				+ mat[1].d1 * dvx->BoneWeight[1]
	//				+ mat[2].d1 * dvx->BoneWeight[2]
	//				+ mat[3].d1 * dvx->BoneWeight[3];

	//			outmat.d2 = mat[0].d2 * dvx->BoneWeight[0]
	//				+ mat[1].d2 * dvx->BoneWeight[1]
	//				+ mat[2].d2 * dvx->BoneWeight[2]
	//				+ mat[3].d2 * dvx->BoneWeight[3];

	//			outmat.d3 = mat[0].d3 * dvx->BoneWeight[0]
	//				+ mat[1].d3 * dvx->BoneWeight[1]
	//				+ mat[2].d3 * dvx->BoneWeight[2]
	//				+ mat[3].d3 * dvx->BoneWeight[3];

	//			outmat.d4 = mat[0].d4 * dvx->BoneWeight[0]
	//				+ mat[1].d4 * dvx->BoneWeight[1]
	//				+ mat[2].d4 * dvx->BoneWeight[2]
	//				+ mat[3].d4 * dvx->BoneWeight[3];
	//		}

	//		dvx->Position = p_mesh->mVertices[v];
	//		dvx->Position *= outmat;	// ���_���W * �s��

	//		// �@���ϊ��p�Ɉړ��������폜
	//		outmat.a4 = 0.0f;
	//		outmat.b4 = 0.0f;
	//		outmat.c4 = 0.0f;

	//		dvx->Normal = p_mesh->mNormals[v];
	//		dvx->Normal *= outmat;

	//		// ���_�o�b�t�@�֏�������
	//		vx[v].Position.x = dvx->Position.x;
	//		vx[v].Position.y = dvx->Position.y;
	//		vx[v].Position.z = dvx->Position.z;

	//		vx[v].Normal.x = dvx->Normal.x;
	//		vx[v].Normal.y = dvx->Normal.y;
	//		vx[v].Normal.z = dvx->Normal.z;

	//		vx[v].TexCoord.x = p_mesh->mTextureCoords[0][v].x;
	//		vx[v].TexCoord.y = p_mesh->mTextureCoords[0][v].y;

	//		vx->Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	//	}
	//	Renderer::GetDeviceContext()->Unmap(pp_mVertexBuffer[m], 0);
	//}

	float f = Time->CountStop();
	cout << "Time : " << f << "sec" << endl;
}

void Com_Model::Draw()
{
	//Time->CountStart();
	Renderer::SetTopologyTriangleList();

	// ���W�X�^�ɒ萔�o�b�t�@���Z�b�g
	Renderer::GetDeviceContext()->VSSetConstantBuffers(3, 1, &p_mCombBuffer);
	Renderer::GetDeviceContext()->VSSetConstantBuffers(4, 1, &p_mScaleBuffer);

	for (unsigned int m = 0; m < mModelData->p_mAiScene->mNumMeshes; m++)
	{
		aiMesh* p_mesh = mModelData->p_mAiScene->mMeshes[m];

		// ���̃}�e���A�����g�p����
		if (bUseMaterial)
		{
			Renderer::SetMaterial(mModelData->vec_material[m]);
		}
		else
		{
			MATERIAL mat;
			ZeroMemory(&mat, sizeof(mat));
			mat.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
			mat.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
			mat.TextureEnable = true;
			Renderer::SetMaterial(mat);
		}

		aiMaterial* material = mModelData->p_mAiScene->mMaterials[p_mesh->mMaterialIndex];

		// �e�N�X�`���ݒ�
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &mModelData->map_mTexture[path.data]);

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mModelData->pp_mVertexBuffer[m], &stride, &offset);

		// �C���f�b�N�X�o�b�t�@
		Renderer::GetDeviceContext()->IASetIndexBuffer(mModelData->pp_mIndexBuffer[m], DXGI_FORMAT_R32_UINT, 0);

		//���b�V���̃t�F�[�X���`��
		Renderer::GetDeviceContext()->DrawIndexed(p_mesh->mNumFaces * 3, 0, 0);
	}
	//float f = Time->CountStop();
	//cout << "Time : " << f << "sec" << endl;
}

void Com_Model::Uninit()
{
	if (p_mCombBuffer)
	{
		p_mCombBuffer->Release();
		p_mCombBuffer = nullptr;
	}
	if (p_mScaleBuffer)
	{
		p_mScaleBuffer->Release();
		p_mScaleBuffer = nullptr;
	}
}

void Com_Model::PlayAnimation(const char* _name)
{
	if (mModelData->map_mAnimation.count(_name) > 0)
	{
		p_cPlayAnimationName = _name;
		bPlayAnim = true;
	}
}

void Com_Model::StopAnimation()
{
	bPlayAnim = false;
}

void Com_Model::UpdateFrame(int _val)
{
	iFrame1 += _val;
}
