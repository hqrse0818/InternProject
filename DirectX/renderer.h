#pragma once

#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"../System/Application.h"
#include	"../Format.h"



// レンダラ
class Renderer
{
private:

	static D3D_FEATURE_LEVEL       mFeatureLevel;

	static ID3D11Device*           p_mDevice;
	static ID3D11DeviceContext*    p_mDeviceContext;
	static IDXGISwapChain*         p_mSwapChain;
	static ID3D11RenderTargetView* p_mRenderTargetView;
	static ID3D11DepthStencilView* p_mDepthStencilView;

	// 一つに統括したい
	static ID3D11Buffer*			p_mWorldBuffer;
	static ID3D11Buffer*			p_mViewBuffer;
	static ID3D11Buffer*			p_mProjectionBuffer;

	// まとめ先
	static ID3D11Buffer* p_mMatrixBuffer;
	static MatrixBufferData mMatrixData;

	// マテリアル用定数バッファ
	static ID3D11Buffer*			p_mMaterialBuffer;
	// ライト用定数バッファ
	static ID3D11Buffer*			p_mLightBuffer;


	static ID3D11DepthStencilState* p_mDepthStateEnable;
	static ID3D11DepthStencilState* p_mDepthStateDisable;

	static ID3D11BlendState*		p_mBlendState;
	static ID3D11BlendState*		p_mBlendStateATC;

	static Application* p_mApplication;

public:
	static void Init(Application* ap);
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
	static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static ID3D11Device* GetDevice( void ){ return p_mDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return p_mDeviceContext; }

	static void SetTopologyTriangleStrip();
	static void SetTopologyTriangleList();
	static void SetTopologyLineList();
	static void SetTopologyLineStrip();

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
};
