#pragma once
#include <d3d11.h>
#include <unordered_map>
#include <string>
#include <WICTextureLoader.h>

// �e�N�X�`���쐬�N���X
class TextureCreate
{
public:
	static void CreateTexture(const char* _FileName, ID3D11ShaderResourceView** _pTex);
	static void CreateTexture(const wchar_t* _FileName, ID3D11ShaderResourceView** _pTex);
};