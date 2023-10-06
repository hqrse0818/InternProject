#pragma once

#include <d3d11.h>
#include <vector>
#include "ShaderResourceView.h"

// スプライト用汎用シェーダー
#define VS_SPRITE ("shader\\unlitTextureVS.cso")
#define PS_SPRITE ("shader\\unlitTexturePS.cso")

// モデル用汎用シェーダー
#define VS_MODEL ("shader\\vertexLightingVS.cso")
#define PS_MODEL ("shader\\vertexLightingPS.cso")

#define BufferMaxSize 9
#define CBufferStartIndex 2

class Shader
{
protected:
	std::vector<ID3D11Buffer*> p_mBuffers;
public:
	void CreateBuffer(D3D11_BUFFER_DESC _desc);
	void CreateBuffer(void* _pData);
	void CreateBuffer(unsigned int _bytewidth);
	void WriteBuffer(UINT _slot, void* _pData);
	// 0に入れないこと
	virtual void SetTexture(UINT _slot, ShaderResourceView* _pSRV) = 0;
	virtual void Bind() = 0;
	virtual void Load(const char*) = 0;

	virtual void Uninit();
};

class VertexShader
	: public Shader
{
protected:
	ID3D11VertexShader* p_mVertexShader{};
	ID3D11InputLayout* p_mInputLayout{};
public:
	// VertexShaderの作成
	virtual void Load(const char* _FileName)override;
	// 0に入れないこと
	void SetTexture(UINT _slot, ShaderResourceView* _pSRV)override;
	void Bind()override;

	void Uninit()override;
};

class PixelShader
	: public Shader
{
private:
	ID3D11PixelShader* p_mPixelShader{};
public:
	void Load(const char* _FileName)override;
	// 0にいれないこと
	void SetTexture(UINT _slot, ShaderResourceView* _pSRV)override;
	void Bind()override;

	void Uninit()override;
};