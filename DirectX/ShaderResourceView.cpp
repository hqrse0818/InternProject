#include "ShaderResourceView.h"
#include "../System/TextureCreate.h"
#include "../Utility.h"
#include <iostream>

using namespace std;

ShaderResourceView::ShaderResourceView()
	: p_mSRV(nullptr)
{
}

ID3D11ShaderResourceView* ShaderResourceView::GetSRV() const
{
	return p_mSRV;
}

void ShaderResourceView::SetSRV(ID3D11ShaderResourceView* _pSRV)
{
	p_mSRV = _pSRV;
}

bool ShaderResourceView::Create(const char* _FileName)
{
	TextureCreate::CreateTexture( _FileName, &p_mSRV);
	if (p_mSRV != nullptr)
	{
		return true;
	}
	cout << "テクスチャの作成に失敗 : " << _FileName << endl;
	return false;
}

void ShaderResourceView::Uninit()
{
	SAFE_RELEASE(p_mSRV);
}

Texture2D::Texture2D()
	: p_mTex(nullptr), mWidth(0), mHeight(0)
{
}

UINT Texture2D::GetWidth() const
{
	return mWidth;
}

UINT Texture2D::GetHeight() const
{
	return mHeight;
}

HRESULT Texture2D::Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData)
{
	D3D11_TEXTURE2D_DESC desc = MakeTexDesc(format, width, height);
	return CreateResource(desc, pData);
}

HRESULT Texture2D::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	return E_NOTIMPL;
}

D3D11_TEXTURE2D_DESC Texture2D::MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = format;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	return desc;
}
