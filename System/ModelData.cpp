#include "ModelData.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include<DirectXTex.h>
#include <iostream>
#include "../main.h"
#include "../System/Time.h"
#include "../System/TextureCreate.h"
#include "../Utility.h"
#include "ModelPool.h"
#include "../Debug.h"

using namespace DirectX::SimpleMath;
using namespace std;

ID3D11ShaderResourceView* ModelData::LoadDiffuseTexture(std::string _FileName, std::string _ModelFileName)
{
	// �t�@�C���̊g���q���擾
	std::string fileext = GetFileExt(_FileName);

	// �t�@�C����(UTF-16)���擾����
	std::wstring widefilename = GetFileNameWide(_FileName.c_str());

	// ���f���f�[�^�̐e�f�B���N�g�����擾
	std::wstring parentdirectory = GetParentDirectoryWide(_ModelFileName);// +L"";

	// �e�N�X�`���̃p�X���擾
	std::wstring filepath = parentdirectory + widefilename;

	// SRV
	ID3D11ShaderResourceView* srv = nullptr;

	// TGA�H
	if (fileext == ".tga") {
		// TGA�̏ꍇ
		DirectX::TexMetadata meta;
		DirectX::GetMetadataFromTGAFile(filepath.c_str(), meta);

		std::unique_ptr<DirectX::ScratchImage> image(new DirectX::ScratchImage);

		HRESULT hr = LoadFromTGAFile(filepath.c_str(), &meta, *image);
		if (FAILED(hr)) {
			DEBUG_LOG("LoadFromTGAFile Error (" << _FileName << ")");
			return nullptr;
		}

		ID3D11Resource* tex = nullptr;

		// �e�N�X�`������
		hr = CreateTexture(
			Renderer::GetDevice(),
			image->GetImages(),
			image->GetImageCount(),
			meta,
			&tex);

		tex->Release();

		if (FAILED(hr)) {
			DEBUG_LOG("CreateTexture Error (" << _FileName << ")");
			return nullptr;
		}

		// �V�F�[�_�[���\�[�X�r���[�쐬
		hr = DirectX::CreateShaderResourceView(Renderer::GetDevice(),
			image->GetImages(),
			image->GetImageCount(),
			meta,
			&srv);

		if (FAILED(hr)) {
			DEBUG_LOG(L"CreateShaderResourceView Error (" << filepath.c_str() << L")");
			return nullptr;
		}
	}
	else {
		// �e�N�X�`���ǂݍ���
		TextureCreate::CreateTexture(filepath.c_str(), &srv);
		if (srv == nullptr) {
			DEBUG_LOG(L"CreateWICTextureFromFile Error (" << filepath.c_str() << widefilename.c_str() << L")");
			return nullptr;
		}
	}

	return srv;
}

void ModelData::CreateBone(aiNode* _node)
{
	BONE bone;

	mModelData->map_mBone[_node->mName.C_Str()] = bone;

	// �ċA�I�ɌĂяo��
	for (unsigned int index = 0; index < _node->mNumChildren; index++)
	{
		CreateBone(_node->mChildren[index]);
	}
}

ModelData::ModelData()
{
	mModelData = new MODEL_DATA();
}

void ModelData::LoadModel(const char* _FileName, bool _bLoadMaterial)
{
	const std::string modelPath(_FileName);

	Time->CountStart();

	Assimp::Importer importer;

	unsigned int flg = 0;
	//flg |= aiProcess_Triangulate;	// �O�p�`�ɕϊ�
	//flg |= aiProcess_JoinIdenticalVertices;	// ���꒸�_�̌���
	//flg |= aiProcess_PreTransformVertices;	// �S�Ă̒��_���W�����[���h���W�Ƃ��ďo�͂ł��邪�����̏�񂪍폜����邽�߂��܂萄�����Ȃ�
	//flg |= aiProcess_MakeLeftHanded;				// ������W�n�ō��//(UV���W���Ԃ�Ȃ�)
	flg |= aiProcess_ConvertToLeftHanded;	// ������W�n�ɃR���o�[�g����
	//flg |= aiProcess_FlipUVs;								// UV���W�̔��](���Ԃ邯�ǃA�j���[�V����������ƃe�N�X�`������邱�Ƃ�����)
	//flg |= aiProcessPreset_TargetRealtime_Quality;
	flg |= aiProcessPreset_TargetRealtime_MaxQuality;
	//flg |= aiProcess_FindInstances ;
	//flg |= aiProcess_ValidateDataStructure;
	//flg |= aiProcess_OptimizeMeshes;

	mModelData->p_mAiScene = aiImportFile(_FileName, flg);

	if (mModelData->p_mAiScene == nullptr)
	{
		DEBUG_LOG(_FileName << " is Error");
		DEBUG_LOG(aiGetErrorString());
	}
	
	assert(mModelData->p_mAiScene);

	// �o�b�t�@�̍쐬
	mModelData->pp_mVertexBuffer = new ID3D11Buffer * [mModelData->p_mAiScene->mNumMeshes];
	mModelData->pp_mIndexBuffer = new ID3D11Buffer * [mModelData->p_mAiScene->mNumMeshes];
	mModelData->vec_mDeformVertex = new std::vector<DEFORM_VERTEX>[mModelData->p_mAiScene->mNumMeshes];

	// �{�[���𐶐�
	CreateBone(mModelData->p_mAiScene->mRootNode);

	// �{�[���̔z��ʒu���i�[
	unsigned int num = 0;
	for (auto& bone : mModelData->map_mBone)
	{
		bone.second.mIndex = num;
		num++;
	}

	for (unsigned int index = 0; index < mModelData->p_mAiScene->mNumMeshes; index++)
	{
		aiMesh* p_mesh = mModelData->p_mAiScene->mMeshes[index];

		// ���_�o�b�t�@����
		if (p_mesh != nullptr)
		{
			VERTEX_3D* p_vertex = new VERTEX_3D[p_mesh->mNumVertices];

			for (unsigned int ver = 0; ver < p_mesh->mNumVertices; ver++)
			{
				p_vertex[ver].Position = Vector3(p_mesh->mVertices[ver].x, p_mesh->mVertices[ver].y, p_mesh->mVertices[ver].z);

				if (p_mesh->mNormals != nullptr)
				{
					p_vertex[ver].Normal = Vector3(p_mesh->mNormals[ver].x, p_mesh->mNormals[ver].y, p_mesh->mNormals[ver].z);
				}
				else
				{

				}
				if (p_mesh->mTextureCoords[index])
				{
					p_vertex[ver].TexCoord = Vector2(p_mesh->mTextureCoords[0][ver].x, p_mesh->mTextureCoords[0][ver].y);
				}
				else
				{
					p_vertex[ver].TexCoord = Vector2(0, 1);
				}
				p_vertex[ver].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * p_mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = p_vertex;

			HRESULT hr = Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mModelData->pp_mVertexBuffer[index]);
			if (FAILED(hr))
			{
				DEBUG_LOG(_FileName << "���_�o�b�t�@�̍쐬�Ɏ��s : " << index);
			}

			delete[] p_vertex;
		}

		// �C���f�b�N�X�o�b�t�@����
		if (p_mesh != nullptr)
		{
			{
				unsigned int* p_index = new unsigned int[p_mesh->mNumFaces * 3];

				for (unsigned int f = 0; f < p_mesh->mNumFaces; f++)
				{
					const aiFace* p_face = &p_mesh->mFaces[f];

					assert(p_face->mNumIndices == 3);

					p_index[f * 3 + 0] = p_face->mIndices[0];
					p_index[f * 3 + 1] = p_face->mIndices[1];
					p_index[f * 3 + 2] = p_face->mIndices[2];
				}

				D3D11_BUFFER_DESC bd;
				ZeroMemory(&bd, sizeof(bd));
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(unsigned int) * p_mesh->mNumFaces * 3;
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;

				D3D11_SUBRESOURCE_DATA sd;
				ZeroMemory(&sd, sizeof(sd));
				sd.pSysMem = p_index;

				Renderer::GetDevice()->CreateBuffer(&bd, &sd, &mModelData->pp_mIndexBuffer[index]);

				delete[] p_index;
			}

			// �ό`�㒸�_�f�[�^������
			for (unsigned int vec = 0; vec < p_mesh->mNumVertices; vec++)
			{
				DEFORM_VERTEX deformVertex;
				deformVertex.Position = p_mesh->mVertices[vec];
				deformVertex.Normal = p_mesh->mNormals[vec];
				deformVertex.BoneNum = 0;

				for (unsigned bone = 0; bone < 4; bone++)
				{
					deformVertex.BoneName[bone] = "";
					deformVertex.BoneWeight[bone] = 0.0f;
				}
				mModelData->vec_mDeformVertex[index].emplace_back(deformVertex);
			}


			// �{�[���f�[�^�̏�����
			for (unsigned int bone = 0; bone < p_mesh->mNumBones; bone++)
			{
				aiBone* p_bone = p_mesh->mBones[bone];

				mModelData->map_mBone[p_bone->mName.C_Str()].OffsetMatrix = p_bone->mOffsetMatrix;

				// �ό`�㒸�_�Ƀ{�[���f�[�^�i�[
				for (unsigned int w = 0; w < p_bone->mNumWeights; w++)
				{
					aiVertexWeight weight = p_bone->mWeights[w];

					int num = mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneNum;

					mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneWeight[num] = weight.mWeight;
					mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneName[num] = p_bone->mName.C_Str();

					mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneIndex[num] = mModelData->map_mBone[p_bone->mName.C_Str()].mIndex;

					mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneNum++;

					assert(mModelData->vec_mDeformVertex[index][weight.mVertexId].BoneNum <= 4);
				}
			}
		}
	}

		// ���_�o�b�t�@�Ƀ{�[���C���f�b�N�X�Əd�ݒl���Z�b�g
	for (unsigned int m = 0; m < mModelData->p_mAiScene->mNumMeshes; m++)
	{
		aiMesh* p_mesh = mModelData->p_mAiScene->mMeshes[m];

		if (p_mesh != nullptr)
		{
			// ���_�o�b�t�@�����b�N
			D3D11_MAPPED_SUBRESOURCE ms;
			HRESULT hr = Renderer::GetDeviceContext()->Map(mModelData->pp_mVertexBuffer[m], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			if (SUCCEEDED(hr))
			{
				VERTEX_3D* p_vertex = (VERTEX_3D*)ms.pData;
				for (unsigned int v = 0; v < p_mesh->mNumVertices; v++)
				{
					DEFORM_VERTEX* dvx = &mModelData->vec_mDeformVertex[m][v];

					p_vertex->Position = Vector3(p_mesh->mVertices[v].x, p_mesh->mVertices[v].y, p_mesh->mVertices[v].z);
					p_vertex->Normal = Vector3(p_mesh->mNormals[v].x, p_mesh->mNormals[v].y, p_mesh->mNormals[v].z);
					p_vertex->TexCoord = Vector2(p_mesh->mTextureCoords[0][v].x, p_mesh->mTextureCoords[0][v].y);
					p_vertex->Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);

					p_vertex->BoneIndex[0] = dvx->BoneIndex[0];
					p_vertex->BoneIndex[1] = dvx->BoneIndex[1];
					p_vertex->BoneIndex[2] = dvx->BoneIndex[2];
					p_vertex->BoneIndex[3] = dvx->BoneIndex[3];

					p_vertex->BoneWeight[0] = dvx->BoneWeight[0];
					p_vertex->BoneWeight[1] = dvx->BoneWeight[1];
					p_vertex->BoneWeight[2] = dvx->BoneWeight[2];
					p_vertex->BoneWeight[3] = dvx->BoneWeight[3];

					p_vertex++;
				}
				Renderer::GetDeviceContext()->Unmap(mModelData->pp_mVertexBuffer[m], 0);
			}
		}
	}

	// �e�N�X�`���̓ǂݍ���
	for (int i = 0; i < mModelData->p_mAiScene->mNumTextures; i++)
	{
		ID3D11ShaderResourceView* p_texture;

		aiTexture* p_aitexture = mModelData->p_mAiScene->mTextures[i];

		const size_t size = p_aitexture->mWidth;

		HRESULT hr = DirectX::CreateWICTextureFromMemory(
			Renderer::GetDevice(),
			Renderer::GetDeviceContext(),
			reinterpret_cast<const unsigned char*>(p_aitexture->pcData),
			p_aitexture->mWidth,
			nullptr,
			&p_texture);

		assert(p_texture);

		mModelData->map_mTexture[p_aitexture->mFilename.data] = p_texture;
	}

	// �}�e���A���ǂݍ���
	if (_bLoadMaterial)
	{
		for (unsigned int i = 0; i < mModelData->p_mAiScene->mNumMaterials; i++)
		{
			aiMaterial* mat = mModelData->p_mAiScene->mMaterials[i];
			aiString name = mat->GetName();

			MATERIAL myMat{};

			// �g�U����
			{
				aiColor3D color(0.0f, 0.0f, 0.0f);
				if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
				{
					myMat.Diffuse.x = color.r;
					myMat.Diffuse.y = color.g;
					myMat.Diffuse.z = color.b;
					myMat.Diffuse.w = 1.0f;
				}
				else
				{
					myMat.Diffuse.x = 0.5f;
					myMat.Diffuse.y = 0.5f;
					myMat.Diffuse.z = 0.5f;
					myMat.Diffuse.w = 1.0f;
				}
			}

			// ���ʔ���
			{
				aiColor3D color(0.0f, 0.0f, 0.0f);
				if (mat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
				{
					myMat.Specular.x = color.r;
					myMat.Specular.y = color.g;
					myMat.Specular.z = color.b;
					myMat.Specular.w = 1.0f;
				}
				else
				{
					myMat.Specular.x = 0.0f;
					myMat.Specular.y = 0.0f;
					myMat.Specular.z = 0.0f;
					myMat.Specular.w = 0.0f;
				}
			}

			// ���ʔ��ˋ��x
			{
				float Shinness = 0.0f;
				if (mat->Get(AI_MATKEY_SHININESS, Shinness) == AI_SUCCESS)
				{
					myMat.Shininess = Shinness;
				}
				else
				{
					myMat.Shininess = 0.0f;
				}

				// �����ˌ�����
				{
					aiColor3D color(0.0f, 0.0f, 0.0f);
					if (mat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
					{
						myMat.Ambient.x = color.r;
						myMat.Ambient.y = color.g;
						myMat.Ambient.z = color.b;
						myMat.Ambient.w = 1.0f;
					}
					else
					{
						myMat.Ambient.x = 0.0f;
						myMat.Ambient.y = 0.0f;
						myMat.Ambient.z = 0.0f;
						myMat.Ambient.w = 0.0f;
					}
				}

				// ���Ɣ�������
				{
					aiColor3D color(0.0f, 0.0f, 0.0f);
					if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
					{
						myMat.Emission.x = color.r;
						myMat.Emission.y = color.g;
						myMat.Emission.z = color.b;
						myMat.Emission.w = 1.0f;
					}
					else
					{
						myMat.Emission.x = 0.0f;
						myMat.Emission.y = 0.0f;
						myMat.Emission.z = 0.0f;
						myMat.Emission.w = 0.0f;
					}
				}

				// �f�B�t�[�Y�e�N�X�`�����擾
				aiTextureType type = aiTextureType_DIFFUSE;
				int texnum = mat->GetTextureCount(type);

				// 1���b�V����1����������
				assert(texnum <= 1);

				// �}�e���A�������擾
				aiString matName;
				mat->GetTexture(type, 0, &matName);

				ID3D11ShaderResourceView* srv = nullptr;

				// ���݂��Ă��邩�m�F
				if (mModelData->map_mTexture.find(matName.data) == mModelData->map_mTexture.end())
				{
					myMat.TextureEnable = FALSE;
					srv = nullptr;

					// �t�@�C�����擾
					std::string fileName = GetFileName(matName.C_Str());

					// �e�N�X�`���̓ǂݍ��݂Ǝ擾
					srv = LoadDiffuseTexture(fileName, _FileName);

					if (srv == nullptr)
					{
						myMat.TextureEnable = FALSE;
					}
					else
					{
						myMat.TextureEnable = TRUE;
						mModelData->map_mTexture[matName.data] = srv;
					}
				}
				// �}�e���A���̕ۑ�
				mModelData->vec_material.emplace_back(myMat);
			}
		}
	}

	float time = Time->CountStop();
	DEBUG_LOG(_FileName);
	DEBUG_LOG("���f���ǂݍ��݊���");
	DEBUG_LOG("Time : " << time << "sec");
}

void ModelData::LoadAnimation(const char* _FileName, const char* _AnimName)
{
	Time->CountStart();
	mModelData->map_mAnimation[_AnimName] = aiImportFile(_FileName, aiProcess_ConvertToLeftHanded);
	if (mModelData->map_mAnimation[_AnimName])
	{
		float time = Time->CountStop();
		DEBUG_LOG(_FileName << " : " << _AnimName);
		DEBUG_LOG("�A�j���[�V�����ǂݍ��ݐ���");
		DEBUG_LOG("Time : " << time << "sec");
	}
	else
	{
		float time = Time->CountStop();
		DEBUG_LOG( _FileName << " : " << _AnimName);
		DEBUG_LOG( _FileName << " , " << _AnimName);
		DEBUG_LOG( "�A�j���[�V�����ǂݍ��ݎ��s");
		DEBUG_LOG( "Time : " << time << "sec");
	}

	assert(mModelData->map_mAnimation[_AnimName]);
}

void ModelData::Push(const char* _ModelName)
{
	ModelPool::Push(_ModelName, this);
}

void ModelData::Uninit()
{
	for (unsigned int m = 0; m < mModelData->p_mAiScene->mNumMeshes; m++)
	{
		mModelData->pp_mVertexBuffer[m]->Release();
		mModelData->pp_mIndexBuffer[m]->Release();
	}

	delete[] mModelData->pp_mVertexBuffer;
	delete[] mModelData->pp_mIndexBuffer;

	delete[] mModelData->vec_mDeformVertex;

	for (std::pair<const std::string, ID3D11ShaderResourceView*>pair : mModelData->map_mTexture)
	{
		if (pair.second)
		{
			pair.second->Release();
		}
	}

	aiReleaseImport(mModelData->p_mAiScene);

	for (std::pair<const std::string, const aiScene*> pair : mModelData->map_mAnimation)
	{
		aiReleaseImport(pair.second);
	}
	delete mModelData;
}


/*
* // �ǂݍ��ݎ��̍��W�������������f���f�[�^�ɑ΂��Ē��_�ʒu�����[�J�����W�n�̌��_����Ɍv�Z���Ȃ���
* void Com_AssimpAnimation::TransWorldToLocal(aiNode* _node, aiMatrix4x4& parentTransform)
{
	aiMatrix4x4 currentTransform = _node->mTransformation;

	currentTransform *= parentTransform;

	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		aiMesh* p_mesh = p_mAiScene->mMeshes[_node->mMeshes[i]];
		for (unsigned int j = 0; j < p_mesh->mNumVertices; j++)
		{
			p_mesh->mVertices[j] = currentTransform * p_mesh->mVertices[j];
		}
	}

	// �q�m�[�h�ɑ΂��čċA�I�ɏ���
	for (unsigned int i = 0; i < _node->mNumChildren; i++)
	{
		TransWorldToLocal(_node->mChildren[i], currentTransform);
	}
}
* 
*/