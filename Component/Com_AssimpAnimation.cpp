#include "Com_AssimpAnimation.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include<DirectXTex.h>
#include <iostream>
#include "../main.h"
#include "../System/Time.h"
#include "../System/TextureCreate.h"
#include "../Utility.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Com_AssimpAnimation::CreateBone(aiNode* _Node)
{
	BONE bone;

	map_mBone[_Node->mName.C_Str()] = bone;

	for (unsigned int index = 0; index < _Node->mNumChildren; index++)
	{
		CreateBone(_Node->mChildren[index]);
	}
}

void Com_AssimpAnimation::UpdateBoneMatrix(aiNode* _Node, aiMatrix4x4 _Matrix)
{
	// �����œn���ꂽ�m�[�h�����L�[�Ƃ��ă{�[�������擾
	BONE* bone = &map_mBone[_Node->mName.C_Str()];

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

void Com_AssimpAnimation::TransWorldToLocal(aiNode* _node, aiMatrix4x4& parentTransform)
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

ID3D11ShaderResourceView* Com_AssimpAnimation::LoadDiffuseTexture(std::string filename, std::string m_filename)
{
	// �t�@�C���̊g���q���擾
	std::string fileext = GetFileExt(filename);

	// �t�@�C����(UTF-16)���擾����
	std::wstring widefilename = GetFileNameWide(filename.c_str());

	// ���f���f�[�^�̐e�f�B���N�g�����擾
	std::wstring parentdirectory = GetParentDirectoryWide(m_filename);// +L"";

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
			std::cout << "LoadFromTGAFile Error (" << filename << ")" << std::endl;
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
			std::cout << "CreateTexture Error (" << filename << ")" << std::endl;
			return nullptr;
		}

		// �V�F�[�_�[���\�[�X�r���[�쐬
		hr = DirectX::CreateShaderResourceView(Renderer::GetDevice(),
			image->GetImages(),
			image->GetImageCount(),
			meta,
			&srv);

		if (FAILED(hr)) {
			std::wcout << L"CreateShaderResourceView Error (" << filepath.c_str() << L")" << std::endl;
			return nullptr;
		}
	}
	else {
		// �e�N�X�`���ǂݍ���
		TextureCreate::CreateTexture(filepath.c_str(), &srv);
		if (srv == nullptr) {
			std::wcout << L"CreateWICTextureFromFile Error (" << filepath.c_str() << widefilename.c_str() << L")" << std::endl;
			return nullptr;
		}
	}

	return srv;
}

void Com_AssimpAnimation::LoadModel(const char* _FileName, float _importScale, bool _bLoadMaterial)
{
	const std::string modelPath(_FileName);

	Time->CountStart();

	Assimp::Importer importer;

	bUseMaterial = _bLoadMaterial;

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


	//p_mAiScene = importer.ReadFile(_FileName, flg);
	p_mAiScene = aiImportFile(_FileName, flg);
	//p_mAiScene = aiImportFile(_FileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	if (p_mAiScene == nullptr)
	{
		cout << _FileName << " is Error" << endl;
		cout << aiGetErrorString() << endl;
	}

	assert(p_mAiScene);

	pp_mVertexBuffer = new ID3D11Buffer*[p_mAiScene->mNumMeshes];
	pp_mIndexBuffer = new ID3D11Buffer*[p_mAiScene->mNumMeshes];
	vec_subsets.resize(p_mAiScene->mNumMeshes);
	// �ό`�㒸�_�z�񐶐�
	vec_mDeformVertex = new std::vector<DEFORM_VERTEX>[p_mAiScene->mNumMeshes];

	// �ċA�I�Ƀ{�[������
	CreateBone(p_mAiScene->mRootNode);
	// ���[���h���W�n���烍�[�J�����W�n�֕ϊ�
	if (p_mAiScene->mNumMeshes > 1)
	{
		TransWorldToLocal(p_mAiScene->mRootNode, p_mAiScene->mRootNode->mTransformation);
	}

	for (unsigned int index = 0; index < p_mAiScene->mNumMeshes; index++)
	{
		aiMesh* p_mesh = p_mAiScene->mMeshes[index];

		// ���_�o�b�t�@����
		if(p_mesh != nullptr)
		{
			vec_subsets[index].VertexNum = p_mesh->mNumVertices;
			vec_subsets[index].MaterialIdx = p_mesh->mMaterialIndex;
			vec_subsets[index].IndexNum = p_mesh->mNumFaces * 3;

			VERTEX_3D* p_vertex = new VERTEX_3D[p_mesh->mNumVertices];

			for (unsigned int ver = 0; ver < p_mesh->mNumVertices; ver++)
			{
				p_vertex[ver].Position = Vector3(p_mesh->mVertices[ver].x, p_mesh->mVertices[ver].y, p_mesh->mVertices[ver].z) * _importScale;

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

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &pp_mVertexBuffer[index]);

			delete[] p_vertex;
		}

		// �C���f�b�N�X�o�b�t�@����
		if (p_mesh != nullptr)
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

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &pp_mIndexBuffer[index]);

			delete[] p_index;
		}

		// �ό`�㒸�_�f�[�^������
		for (unsigned int vec = 0; vec < p_mesh->mNumVertices; vec++)
		{
			DEFORM_VERTEX deformVertex;
			deformVertex.Position = p_mesh->mVertices[vec] * _importScale;
			deformVertex.Normal = p_mesh->mNormals[vec];
			deformVertex.BoneNum = 0;

			for (unsigned bone = 0; bone < 4; bone++)
			{
				deformVertex.BoneName[bone] = "";
				deformVertex.BoneWeight[bone] = 0.0f;
			}
			vec_mDeformVertex[index].emplace_back(deformVertex);
		}


		// �{�[���f�[�^�̏�����
		for (unsigned int bone = 0; bone < p_mesh->mNumBones; bone++)
		{
			aiBone* p_bone = p_mesh->mBones[bone];

			map_mBone[p_bone->mName.C_Str()].OffsetMatrix = p_bone->mOffsetMatrix * _importScale;

			// �ό`�㒸�_�Ƀ{�[���f�[�^�i�[
			for (unsigned int w = 0; w < p_bone->mNumWeights; w++)
			{
				aiVertexWeight weight = p_bone->mWeights[w];

				int num = vec_mDeformVertex[index][weight.mVertexId].BoneNum;

				vec_mDeformVertex[index][weight.mVertexId].BoneWeight[num] = weight.mWeight;
				vec_mDeformVertex[index][weight.mVertexId].BoneName[num] = p_bone->mName.C_Str();
				vec_mDeformVertex[index][weight.mVertexId].BoneNum++;

				assert(vec_mDeformVertex[index][weight.mVertexId].BoneNum <= 4);
			}
		}
	}

	// �e�N�X�`���̓ǂݍ���
	for (int i = 0; i < p_mAiScene->mNumTextures; i++)
	{
		ID3D11ShaderResourceView* p_texture;

		aiTexture* p_aitexture = p_mAiScene->mTextures[i];

		const size_t size = p_aitexture->mWidth;

		HRESULT hr = DirectX::CreateWICTextureFromMemory(
			Renderer::GetDevice(),
			Renderer::GetDeviceContext(),
			reinterpret_cast<const unsigned char*>(p_aitexture->pcData),
			p_aitexture->mWidth,
			nullptr,
			&p_texture);
		
		assert(p_texture);

		map_mTexture[p_aitexture->mFilename.data] = p_texture;
	}

	// �}�e���A���ǂݍ���
	if (_bLoadMaterial)
	{
		for (unsigned int i = 0; i < p_mAiScene->mNumMaterials; i++)
		{
			aiMaterial* mat = p_mAiScene->mMaterials[i];
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
						myMat.Emission.x = color.g;
						myMat.Emission.x = color.b;
						myMat.Emission.x = 1.0f;
					}
					else
					{
						myMat.Emission.x = 0.0f;
						myMat.Emission.x = 0.0f;
						myMat.Emission.x = 0.0f;
						myMat.Emission.x = 0.0f;
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
				if (map_mTexture.find(matName.data) == map_mTexture.end())
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
						map_mTexture[matName.data] = srv;
					}
				}
				// �}�e���A���̕ۑ�
				vec_material.emplace_back(myMat);
			}
		}
	}
	
	float time = Time->CountStop();
	cout << "���f���ǂݍ��݊���" << endl;
	cout << "Time : " << time << "sec" << endl;
}

void Com_AssimpAnimation::LoadAnimation(const char* _FileName, const char* _Name)
{
	Time->CountStart();
	map_mAnimation[_Name] = aiImportFile(_FileName, aiProcess_ConvertToLeftHanded);
	assert(map_mAnimation[_Name]);

	float time = Time->CountStop();

	cout << "�A�j���[�V�����ǂݍ��݊���" << endl;
	cout << "Time : " << time << "sec" << endl;
}

void Com_AssimpAnimation::Uninit()
{
	for (unsigned int m = 0; m < p_mAiScene->mNumMeshes; m++)
	{
		pp_mVertexBuffer[m]->Release();
		pp_mIndexBuffer[m]->Release();
	}

	delete[] pp_mVertexBuffer;
	delete[] pp_mIndexBuffer;

	delete[] vec_mDeformVertex;

	for (std::pair<const std::string, ID3D11ShaderResourceView*>pair : map_mTexture)
	{
		if(pair.second)
			pair.second->Release();
	}

	aiReleaseImport(p_mAiScene);

	for (std::pair<const std::string, const aiScene*> pair : map_mAnimation)
	{
		aiReleaseImport(pair.second);
	}


}

void Com_AssimpAnimation::Update()
{
	if (!bPlayAnim)
		return;

	// �A�j���[�V�������肩�H
	if (map_mAnimation.count(p_cPlayAnimationName) == 0)
		return;
	/*if (map_mAnimation.count(AnimationName2) == 0)
		return;*/

	if (!map_mAnimation[p_cPlayAnimationName]->HasAnimations())
		return;
	/*if (!map_mAnimation[AnimationName2]->HasAnimations())
		return;*/

	//�A�j���[�V�����f�[�^����{�[���}�g���N�X�Z�o
	aiAnimation* animation1 = map_mAnimation[p_cPlayAnimationName]->mAnimations[0];
	//aiAnimation* animation2 = map_mAnimation[AnimationName2]->mAnimations[0];


	for (unsigned int c = 0; c < animation1->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation1->mChannels[c];

		BONE* bone = &map_mBone[nodeAnim->mNodeName.C_Str()];

		int f;

		f = iFrame1 % nodeAnim->mNumRotationKeys;//�ȈՎ���
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;

		f = iFrame1 % nodeAnim->mNumPositionKeys;//�ȈՎ���
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;

		bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
	}

	//�ċA�I�Ƀ{�[���}�g���N�X���X�V
//	aiMatrix4x4 rootMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), aiQuaternion(AI_MATH_PI, 0.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f));
	aiMatrix4x4 rootMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), aiQuaternion(AI_MATH_PI, 0.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f));

	UpdateBoneMatrix(p_mAiScene->mRootNode, rootMatrix);


	//���_�ϊ��iCPU�X�L�j���O�j
	for (unsigned int m = 0; m < p_mAiScene->mNumMeshes; m++)
	{
		aiMesh* mesh = p_mAiScene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		Renderer::GetDeviceContext()->Map(pp_mVertexBuffer[m], 0,
			D3D11_MAP_WRITE_DISCARD, 0, &ms);

		VERTEX_3D* vertex = (VERTEX_3D*)ms.pData;

		for (unsigned int v = 0; v < vec_mDeformVertex[m].size(); v++)
		{
			DEFORM_VERTEX* deformVertex = &vec_mDeformVertex[m][v];

			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;
			matrix[0] = map_mBone[deformVertex->BoneName[0]].Matrix;
			matrix[1] = map_mBone[deformVertex->BoneName[1]].Matrix;
			matrix[2] = map_mBone[deformVertex->BoneName[2]].Matrix;
			matrix[3] = map_mBone[deformVertex->BoneName[3]].Matrix;

			{
				outMatrix.a1 = matrix[0].a1 * deformVertex->BoneWeight[0]
					+ matrix[1].a1 * deformVertex->BoneWeight[1]
					+ matrix[2].a1 * deformVertex->BoneWeight[2]
					+ matrix[3].a1 * deformVertex->BoneWeight[3];

				outMatrix.a2 = matrix[0].a2 * deformVertex->BoneWeight[0]
					+ matrix[1].a2 * deformVertex->BoneWeight[1]
					+ matrix[2].a2 * deformVertex->BoneWeight[2]
					+ matrix[3].a2 * deformVertex->BoneWeight[3];

				outMatrix.a3 = matrix[0].a3 * deformVertex->BoneWeight[0]
					+ matrix[1].a3 * deformVertex->BoneWeight[1]
					+ matrix[2].a3 * deformVertex->BoneWeight[2]
					+ matrix[3].a3 * deformVertex->BoneWeight[3];

				outMatrix.a4 = matrix[0].a4 * deformVertex->BoneWeight[0]
					+ matrix[1].a4 * deformVertex->BoneWeight[1]
					+ matrix[2].a4 * deformVertex->BoneWeight[2]
					+ matrix[3].a4 * deformVertex->BoneWeight[3];



				outMatrix.b1 = matrix[0].b1 * deformVertex->BoneWeight[0]
					+ matrix[1].b1 * deformVertex->BoneWeight[1]
					+ matrix[2].b1 * deformVertex->BoneWeight[2]
					+ matrix[3].b1 * deformVertex->BoneWeight[3];

				outMatrix.b2 = matrix[0].b2 * deformVertex->BoneWeight[0]
					+ matrix[1].b2 * deformVertex->BoneWeight[1]
					+ matrix[2].b2 * deformVertex->BoneWeight[2]
					+ matrix[3].b2 * deformVertex->BoneWeight[3];

				outMatrix.b3 = matrix[0].b3 * deformVertex->BoneWeight[0]
					+ matrix[1].b3 * deformVertex->BoneWeight[1]
					+ matrix[2].b3 * deformVertex->BoneWeight[2]
					+ matrix[3].b3 * deformVertex->BoneWeight[3];

				outMatrix.b4 = matrix[0].b4 * deformVertex->BoneWeight[0]
					+ matrix[1].b4 * deformVertex->BoneWeight[1]
					+ matrix[2].b4 * deformVertex->BoneWeight[2]
					+ matrix[3].b4 * deformVertex->BoneWeight[3];



				outMatrix.c1 = matrix[0].c1 * deformVertex->BoneWeight[0]
					+ matrix[1].c1 * deformVertex->BoneWeight[1]
					+ matrix[2].c1 * deformVertex->BoneWeight[2]
					+ matrix[3].c1 * deformVertex->BoneWeight[3];

				outMatrix.c2 = matrix[0].c2 * deformVertex->BoneWeight[0]
					+ matrix[1].c2 * deformVertex->BoneWeight[1]
					+ matrix[2].c2 * deformVertex->BoneWeight[2]
					+ matrix[3].c2 * deformVertex->BoneWeight[3];

				outMatrix.c3 = matrix[0].c3 * deformVertex->BoneWeight[0]
					+ matrix[1].c3 * deformVertex->BoneWeight[1]
					+ matrix[2].c3 * deformVertex->BoneWeight[2]
					+ matrix[3].c3 * deformVertex->BoneWeight[3];

				outMatrix.c4 = matrix[0].c4 * deformVertex->BoneWeight[0]
					+ matrix[1].c4 * deformVertex->BoneWeight[1]
					+ matrix[2].c4 * deformVertex->BoneWeight[2]
					+ matrix[3].c4 * deformVertex->BoneWeight[3];



				outMatrix.d1 = matrix[0].d1 * deformVertex->BoneWeight[0]
					+ matrix[1].d1 * deformVertex->BoneWeight[1]
					+ matrix[2].d1 * deformVertex->BoneWeight[2]
					+ matrix[3].d1 * deformVertex->BoneWeight[3];

				outMatrix.d2 = matrix[0].d2 * deformVertex->BoneWeight[0]
					+ matrix[1].d2 * deformVertex->BoneWeight[1]
					+ matrix[2].d2 * deformVertex->BoneWeight[2]
					+ matrix[3].d2 * deformVertex->BoneWeight[3];

				outMatrix.d3 = matrix[0].d3 * deformVertex->BoneWeight[0]
					+ matrix[1].d3 * deformVertex->BoneWeight[1]
					+ matrix[2].d3 * deformVertex->BoneWeight[2]
					+ matrix[3].d3 * deformVertex->BoneWeight[3];

				outMatrix.d4 = matrix[0].d4 * deformVertex->BoneWeight[0]
					+ matrix[1].d4 * deformVertex->BoneWeight[1]
					+ matrix[2].d4 * deformVertex->BoneWeight[2]
					+ matrix[3].d4 * deformVertex->BoneWeight[3];

			}

			deformVertex->Position = mesh->mVertices[v];
			deformVertex->Position *= outMatrix;						// ���_���W�~�s��


			//�@���ϊ��p�Ɉړ��������폜
			outMatrix.a4 = 0.0f;
			outMatrix.b4 = 0.0f;
			outMatrix.c4 = 0.0f;

			deformVertex->Normal = mesh->mNormals[v];
			deformVertex->Normal *= outMatrix;


			//���_�o�b�t�@�֏�������
			vertex[v].Position.x = deformVertex->Position.x;
			vertex[v].Position.y = deformVertex->Position.y;
			vertex[v].Position.z = deformVertex->Position.z;

			vertex[v].Normal.x = deformVertex->Normal.x;
			vertex[v].Normal.y = deformVertex->Normal.y;
			vertex[v].Normal.z = deformVertex->Normal.z;

			vertex[v].TexCoord.x = mesh->mTextureCoords[0][v].x;
			vertex[v].TexCoord.y = mesh->mTextureCoords[0][v].y;

			vertex[v].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
		}
		Renderer::GetDeviceContext()->Unmap(pp_mVertexBuffer[m], 0);
	}
}

void Com_AssimpAnimation::Draw()
{
	Renderer::SetTopologyTriangleList();

	// ���b�V�����Ƃ�Draw���Ă���
	for (unsigned int m = 0; m < p_mAiScene->mNumMeshes; m++)
	{
		aiMesh* mesh = p_mAiScene->mMeshes[m];
		
		if (bUseMaterial)
		{
			Renderer::SetMaterial(vec_material[m]);
		}
		else
		{
			MATERIAL mat;
			mat.TextureEnable = false;
			mat.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
			Renderer::SetMaterial(mat);
		}

		aiMaterial* material = p_mAiScene->mMaterials[mesh->mMaterialIndex];

		// �e�N�X�`���ݒ�
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &map_mTexture[path.data]);

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &pp_mVertexBuffer[m], &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		Renderer::GetDeviceContext()->IASetIndexBuffer(pp_mIndexBuffer[m], DXGI_FORMAT_R32_UINT, 0);

		// �|���S���`��
		// ���b�V���̃t�F�[�X��
		Renderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
	}
}

void Com_AssimpAnimation::UpdateFrame()
{
	iFrame1++;
}

void Com_AssimpAnimation::ResetAnimationFrame()
{
	iFrame1 = 0;
	iFrame2 = 0;
}

void Com_AssimpAnimation::PlayAnimation(const char* _AnimName)
{
	if (map_mAnimation.count(_AnimName) > 0)
	{
		p_cPlayAnimationName = _AnimName;
		bPlayAnim = true;
	}
}

void Com_AssimpAnimation::StopAnimation()
{
	bPlayAnim = false;
}

void Com_AssimpAnimation::SetTexture(const char* _FileName)
{
	// �e�N�X�`���̓ǂݍ���
	for (int i = 0; i < p_mAiScene->mNumTextures; i++)
	{
		ID3D11ShaderResourceView* p_texture;
		TextureCreate::CreateTexture(_FileName, &p_texture);

		aiTexture* p_aitexture = p_mAiScene->mTextures[i];

		map_mTexture[p_aitexture->mFilename.data] = p_texture;
	}
}
