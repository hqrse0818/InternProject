#pragma once
#include <d3d11.h>
class ShaderResourceView
{
protected:
	ID3D11ShaderResourceView* p_mSRV{};

public:
	ShaderResourceView();
	ID3D11ShaderResourceView* GetSRV() const;
	virtual bool Create(const char* _FileName);
	virtual void Uninit();
};

class Texture2D
	: public ShaderResourceView
{
protected:
	UINT mWidth;
	UINT mHeight;
	ID3D11Texture2D* p_mTex{};

public:
	Texture2D();

	UINT GetWidth()const;
	UINT GetHeight()const;
	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData = nullptr);
protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData);
	D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height);
};