#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "Com_ModelRenderer.h"
#include "../DirectX/renderer.h"
#include "../System/utftosjisconv.h"
#include <WICTextureLoader.h>

using namespace DirectX::SimpleMath;
std::unordered_map<std::string, MODEL*> Com_ModelRenderer::map_mModelPool{};

// ���f���̍쐬
void Com_ModelRenderer::LoadModel(const char* _FileName, MODEL* _Model, float _LoadScale)
{
	MODEL_OBJ _ModelObj;
	LoadObj(_FileName, &_ModelObj, _LoadScale);	// ���f�������[�h����

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * _ModelObj.VertexNum;	// ���_�f�[�^�̐��������w��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = _ModelObj.VertexArray;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_Model->VertexBuffer);
	}

	// �C���f�b�N�X�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * _ModelObj.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = _ModelObj.IndexArray;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_Model->IndexBuffer);
	}

	// �T�u�Z�b�g�ݒ�
	{
		// �T�u�Z�b�g�̐������z����m��
		_Model->SubsetArray = new SUBSET[_ModelObj.SubsetNum];
		// �T�u�Z�b�g�̐���ݒ�
		_Model->SubsetNum = _ModelObj.SubsetNum;

		for (unsigned int i = 0; i < _ModelObj.SubsetNum; i++)
		{
			// �T�u�Z�b�g�̊J�n����C���f�b�N�X�̐ݒ�
			_Model->SubsetArray[i].StartIndex = _ModelObj.SubsetArray[i].StartIndex;
			// �T�u�Z�b�g�̃C���f�b�N�X���̐ݒ�
			_Model->SubsetArray[i].IndexNum = _ModelObj.SubsetArray[i].IndexNum;
			// �T�u�Z�b�g�̃}�e���A����ݒ�
			_Model->SubsetArray[i].Material.Material = _ModelObj.SubsetArray[i].Material.Material;
			// �e�N�X�`���ւ̃|�C���^�̏�����
			_Model->SubsetArray[i].Material.Texture = nullptr;

			std::wstring ws = sjis_to_wide_winapi(_ModelObj.SubsetArray[i].Material.TextureName);

			DirectX::CreateWICTextureFromFile(
				Renderer::GetDevice(),
				ws.c_str(),
				nullptr,
				&_Model->SubsetArray[i].Material.Texture);

			// �������ǂݍ��܂��΃e�N�X�`����\���ł���悤�ɂ���
			if (_Model->SubsetArray[i].Material.Texture)
			{
				_Model->SubsetArray[i].Material.Material.TextureEnable = true;
			}
			else
			{
				_Model->SubsetArray[i].Material.Material.TextureEnable = false;
			}
		}
	}
	delete[] _ModelObj.VertexArray;
	delete[] _ModelObj.IndexArray;
	delete[] _ModelObj.SubsetArray;
}


// ���f���̓ǂݍ���
void Com_ModelRenderer::LoadObj(const char* _FileName, MODEL_OBJ* _ModelObj, float _LoadScale)
{
	char dir[MAX_PATH];
	strcpy(dir, _FileName);
	PathRemoveFileSpec(dir);





	Vector3* positionArray;
	Vector3* normalArray;
	Vector2* texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL* materialArray = nullptr;
	unsigned int	materialNum = 0;

	char str[256];
	char* s;
	char c;


	FILE* file;
	file = fopen(_FileName, "rt");
	assert(file);



	//�v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;

			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//�������m��
	positionArray = new Vector3[positionNum];
	normalArray = new Vector3[normalNum];
	texcoordArray = new Vector2[texcoordNum];


	_ModelObj->VertexArray = new VERTEX_3D[vertexNum];
	_ModelObj->VertexNum = vertexNum;

	_ModelObj->IndexArray = new unsigned int[indexNum];
	_ModelObj->IndexNum = indexNum;

	_ModelObj->SubsetArray = new SUBSET[subsetNum];
	_ModelObj->SubsetNum = subsetNum;




	//�v�f�Ǎ�
	Vector3* position = positionArray;
	Vector3* normal = normalArray;
	Vector2* texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//�}�e���A���t�@�C��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//�I�u�W�F�N�g��
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//���_���W
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position->x *= _LoadScale;
			position->y *= _LoadScale;
			position->z *= _LoadScale;
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//�@��
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//�e�N�X�`�����W
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->x = 1.0f - texcoord->x;
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//�}�e���A��
			fscanf(file, "%s", str);

			if (sc != 0)
				_ModelObj->SubsetArray[sc - 1].IndexNum = ic - _ModelObj->SubsetArray[sc - 1].StartIndex;

			_ModelObj->SubsetArray[sc].StartIndex = ic;


			for (unsigned int i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].name) == 0)
				{
					_ModelObj->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(_ModelObj->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(_ModelObj->SubsetArray[sc].Material.name, materialArray[i].name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//��
			in = 0;

			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				_ModelObj->VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//�e�N�X�`�����W�����݂��Ȃ��ꍇ������
					s = strtok(nullptr, "/");
					_ModelObj->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(nullptr, "/");
				_ModelObj->VertexArray[vc].Normal = normalArray[atoi(s) - 1];

				_ModelObj->VertexArray[vc].Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);

				_ModelObj->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//�l�p�͎O�p�ɕ���
			if (in == 4)
			{
				_ModelObj->IndexArray[ic] = vc - 4;
				ic++;
				_ModelObj->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if (sc != 0)
		_ModelObj->SubsetArray[sc - 1].IndexNum = ic - _ModelObj->SubsetArray[sc - 1].StartIndex;


	fclose(file);


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

// �}�e���A���ǂݍ���
void Com_ModelRenderer::LoadMaterial(const char* _FileName, MODEL_MATERIAL** _MaterialArray, unsigned int* _MaterialNum)
{
	char dir[MAX_PATH];
	strcpy(dir, _FileName);
	PathRemoveFileSpec(dir);


	char str[256];

	FILE* file;
	file = fopen(_FileName, "rt");
	assert(file);

	MODEL_MATERIAL* materialArray;
	unsigned int materialNum = 0;

	// �v�f���J�E���g
	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}

		if (strcmp(str, "newmtl") == 0)
		{
			// �V�����}�e���A��������
			materialNum++;
		}
	}

	// �������m��
	materialArray = new MODEL_MATERIAL[materialNum];

	// �v�f�̓ǂݍ���
	int mc = -1;

	fseek(file, 0, SEEK_SET);

	while (true)
	{
		fscanf(file, "%s", str);
		if (feof(file) != 0)
		{
			break;
		}

		if (strcmp(str, "newmtl") == 0)
		{
			// �}�e���A����
			mc++;
			fscanf(file, "%s", materialArray[mc].name);
			strcpy(materialArray[mc].TextureName, "");

			materialArray[mc].Material.Emission.x = 0.0f;
			materialArray[mc].Material.Emission.y = 0.0f;
			materialArray[mc].Material.Emission.z = 0.0f;
			materialArray[mc].Material.Emission.w = 0.0f;
		}
		else if (strcmp(str, "Ka") == 0)
		{
			// �A���r�G���g
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.x);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.y);
			fscanf(file, "%f", &materialArray[mc].Material.Ambient.z);
			materialArray[mc].Material.Ambient.w = 1.0f;
		}
		else if (strcmp(str, "Kd") == 0)
		{
			// �f�B�t���[�Y
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.x);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.y);
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.z);
			materialArray[mc].Material.Diffuse.w = 1.0f;
		}
		else if (strcmp(str, "Ks") == 0)
		{
			// �X�y�L����
			fscanf(file, "%f", &materialArray[mc].Material.Specular.x);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.y);
			fscanf(file, "%f", &materialArray[mc].Material.Specular.z);
			materialArray[mc].Material.Specular.w = 1.0f;
		}
		else if (strcmp(str, "Ns") == 0)
		{
			// �X�y�L�������x
			fscanf(file, "%f", &materialArray[mc].Material.Shininess);
		}
		else if (strcmp(str, "d") == 0)
		{
			// �A���t�@
			fscanf(file, "%f", &materialArray[mc].Material.Diffuse.w);
		}
		else if (strcmp(str, "map_Kd") == 0)
		{
			// �e�N�X�`��
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, dir);
			strcat(path, "\\");
			strcat(path, str);

			strcat(materialArray[mc].TextureName, path);
		}
	}

	fclose(file);

	*_MaterialArray = materialArray;
	*_MaterialNum = materialNum;
}

void Com_ModelRenderer::PreLoad(const char* _FileName, float _LoadScale)
{
	// _FileName�̃��f�������ɓo�^����Ă���Ώ������I������
	if (map_mModelPool.count(_FileName) > 0)
	{
		return;
	}

	// �V�������f���I�u�W�F�N�g���쐬
	MODEL* model = new MODEL;

	// ���f���t�@�C����ǂݍ���
	LoadModel(_FileName, model, _LoadScale);

	// ���f���f�[�^�����X�g�ɓo�^
	map_mModelPool[_FileName] = model;
}

void Com_ModelRenderer::UnloadAll()
{

	for (std::pair<const std::string, MODEL*> pair : map_mModelPool)
	{
		pair.second->VertexBuffer->Release();
		pair.second->IndexBuffer->Release();

		for (unsigned int i = 0; i < pair.second->SubsetNum; i++)
		{
			if (pair.second->SubsetArray[i].Material.Texture)
			{
				pair.second->SubsetArray[i].Material.Texture->Release();
			}
		}
		delete[] pair.second->SubsetArray;

		delete pair.second;
	}

	map_mModelPool.clear();
}

void Com_ModelRenderer::Load(const char* _FileName, float _LoadScale)
{
	p_mModel = new MODEL;
	LoadModel(_FileName, p_mModel, _LoadScale);

	map_mModelPool[_FileName] = p_mModel;
}

void Com_ModelRenderer::Load(const char* _FileName)
{
	if (map_mModelPool.count(_FileName) > 0)
	{
		p_mModel = map_mModelPool[_FileName];
		return;
	}

	p_mModel = new MODEL;
	LoadModel(_FileName, p_mModel, 1.0);

	map_mModelPool[_FileName] = p_mModel;
}

void Com_ModelRenderer::Draw()
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &p_mModel->VertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->IASetIndexBuffer(p_mModel->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	Renderer::SetTopologyTriangleList();

	for (unsigned int i = 0; i < p_mModel->SubsetNum; i++)
	{
		// �}�e���A���ݒ�
		Renderer::SetMaterial(p_mModel->SubsetArray[i].Material.Material);

		// �e�N�X�`���ݒ�
		if (p_mModel->SubsetArray[i].Material.Texture)
		{
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &p_mModel->SubsetArray[i].Material.Texture);
		}

		// �|���S���`��
		Renderer::GetDeviceContext()->DrawIndexed(p_mModel->SubsetArray[i].IndexNum, p_mModel->SubsetArray[i].StartIndex, 0);
	}
}

void Com_ModelRenderer::Draw(MODEL* _model)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_model->VertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->IASetIndexBuffer(_model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	Renderer::SetTopologyTriangleList();

	for (unsigned int i = 0; i < _model->SubsetNum; i++)
	{
		// �}�e���A���ݒ�
		Renderer::SetMaterial(_model->SubsetArray[i].Material.Material);

		// �e�N�X�`���ݒ�
		if (_model->SubsetArray[i].Material.Texture)
		{
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &_model->SubsetArray[i].Material.Texture);
		}

		// �|���S���`��
		Renderer::GetDeviceContext()->DrawIndexed(_model->SubsetArray[i].IndexNum, _model->SubsetArray[i].StartIndex, 0);
	}
}

MODEL* Com_ModelRenderer::GetModelData(const char* _FileName)
{
	if (map_mModelPool.count(_FileName) > 0)
	{
		MODEL* tmp = map_mModelPool[_FileName];
		return tmp;
	}

	return nullptr;
}

void Com_ModelRenderer::ScaleModelData(MODEL* _model)
{
	
}

void Com_ModelRenderer::ScaleModelData()
{
}
