#include "Shader.h"
#include "renderer.h"
#include "../main.h"
#include <io.h>

void Shader::CreateBuffer(D3D11_BUFFER_DESC _desc)
{
	// �o�b�t�@���ő�ʂȂ�V�������Ȃ�
	if (p_mBuffers.size() >= BufferMaxSize)
	{
		return;
	}
	// �o�b�t�@�̍쐬
	ID3D11Buffer* buffer{};
	Renderer::GetDevice()->CreateBuffer(&_desc, NULL, &buffer);

	p_mBuffers.emplace_back(buffer);
}

void Shader::CreateBuffer(void* _pData)
{
	// �^����ꂽ�\���̂���o�b�t�@�f�X�N�𐶐�
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(_pData);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	// �萔�o�b�t�@���쐬
	CreateBuffer(bufferDesc);
}

void Shader::CreateBuffer(unsigned int _bytewidth)
{
	//�^����ꂽ�\���̂���o�b�t�@�f�X�N�𐶐�
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = _bytewidth;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	CreateBuffer(bufferDesc);
}

void Shader::WriteBuffer(UINT _slot, void* _pData)
{
	if(_slot < p_mBuffers.size())
		Renderer::GetDeviceContext()->UpdateSubresource(p_mBuffers[_slot], 0, nullptr, _pData, 0, 0);
}

void Shader::Uninit()
{
	for (auto buffer : p_mBuffers)
	{
		buffer->Release();
	}
	p_mBuffers.clear();
}

void VertexShader::Load(const char* _FileName)
{
	FILE* file;
	long int filesize;

	// �����ŗ^����ꂽ�t�@�C�����o�C�i���ǂݍ��݃��[�h�ŊJ��
	fopen_s(&file, _FileName, "rb");
	assert(file);

	filesize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[filesize];
	fread(buffer, filesize, 1, file);
	fclose(file);

	// ���_�V�F�[�_�[�̊i�[�ƕۑ�
	HRESULT hr = Renderer::GetDevice()->CreateVertexShader(buffer, filesize, NULL, &p_mVertexShader);
	if (FAILED(hr))
	{
		int a = 9;
	}

	// ���̓��C�A�E�g���`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT numElements = ARRAYSIZE(layout);

	// ���̓��C�A�E�g�̍쐬�ƕۑ�
	Renderer::GetDevice()->CreateInputLayout(layout, numElements, buffer, filesize, &p_mInputLayout);

	delete[] buffer;
}

void VertexShader::SetTexture(UINT _slot, ShaderResourceView* _pSRV)
{
	ID3D11ShaderResourceView* pTex = _pSRV->GetSRV();
	Renderer::GetDeviceContext()->VSSetShaderResources(_slot, 1, &pTex);
}

void VertexShader::Bind()
{
	Renderer::GetDeviceContext()->VSSetShader(p_mVertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->IASetInputLayout(p_mInputLayout);

	unsigned int index = CBufferStartIndex;
	for (auto buffer : p_mBuffers)
	{
		Renderer::GetDeviceContext()->VSSetConstantBuffers(index, 1, &buffer);
		index++;
	}
}

void VertexShader::Uninit()
{
	Shader::Uninit();
	p_mInputLayout->Release();
	p_mVertexShader->Release();
}

void PixelShader::Load(const char* _FileName)
{
	FILE* file;
	long int filesize;

	fopen_s(&file, _FileName, "rb");
	assert(file);

	filesize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[filesize];
	fread(buffer, filesize, 1, file);
	fclose(file);

	Renderer::GetDevice()->CreatePixelShader(buffer, filesize, NULL, &p_mPixelShader);

	delete[] buffer;
}

void PixelShader::SetTexture(UINT _slot, ShaderResourceView* _pSRV)
{
	ID3D11ShaderResourceView* pTex = _pSRV->GetSRV();
	Renderer::GetDeviceContext()->PSSetShaderResources(_slot, 1, &pTex);
}

void PixelShader::Bind()
{
	Renderer::GetDeviceContext()->PSSetShader(p_mPixelShader, nullptr, 0);

	unsigned int index = CBufferStartIndex;
	for (auto buffer : p_mBuffers)
	{
		Renderer::GetDeviceContext()->PSSetConstantBuffers(index, 1, &buffer);
		index++;
	}
}

void PixelShader::Uninit()
{
	Shader::Uninit();
	p_mPixelShader->Release();
}
