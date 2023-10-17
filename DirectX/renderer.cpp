#include "../main.h"
#include "renderer.h"
#include <io.h>

using namespace DirectX::SimpleMath;


D3D_FEATURE_LEVEL       Renderer::mFeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           Renderer::p_mDevice{};
ID3D11DeviceContext*    Renderer::p_mDeviceContext{};
IDXGISwapChain*         Renderer::p_mSwapChain{};
ID3D11RenderTargetView* Renderer::p_mRenderTargetView{};
ID3D11DepthStencilView* Renderer::p_mDepthStencilView{};

// まとめ後行列の定数バッファデータ
ID3D11Buffer* Renderer::p_mMatrixBuffer{};
MatrixBufferData Renderer::mMatrixData{};

ID3D11Buffer*			Renderer::p_mWorldBuffer{};
ID3D11Buffer*			Renderer::p_mViewBuffer{};
ID3D11Buffer*			Renderer::p_mProjectionBuffer{};
ID3D11Buffer*			Renderer::p_mMaterialBuffer{};
ID3D11Buffer*			Renderer::p_mLightBuffer{};


ID3D11DepthStencilState* Renderer::p_mDepthStateEnable{};
ID3D11DepthStencilState* Renderer::p_mDepthStateDisable{};


ID3D11BlendState*		Renderer::p_mBlendState{};
ID3D11BlendState*		Renderer::p_mBlendStateATC{};

Application*			Renderer::p_mApplication;


void Renderer::Init(Application* ap)
{
	HRESULT hr = S_OK;

	// 持ち主オブジェクトのアドレスをセット
	p_mApplication = ap;

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = p_mApplication->GetWidth();
	swapChainDesc.BufferDesc.Height = p_mApplication->GetHeight();
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = p_mApplication->GetWindow();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&swapChainDesc,
										&p_mSwapChain,
										&p_mDevice,
										&mFeatureLevel,
										&p_mDeviceContext );


	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget{};
	p_mSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&renderTarget );
	p_mDevice->CreateRenderTargetView( renderTarget, NULL, &p_mRenderTargetView );
	renderTarget->Release();


	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	p_mDevice->CreateTexture2D(&textureDesc, NULL, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	p_mDevice->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &p_mDepthStencilView);
	depthStencile->Release();


	p_mDeviceContext->OMSetRenderTargets(1, &p_mRenderTargetView, p_mDepthStencilView);


	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)p_mApplication->GetWidth();
	viewport.Height = (FLOAT)p_mApplication->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	p_mDeviceContext->RSSetViewports( 1, &viewport );



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID; 
	rasterizerDesc.CullMode = D3D11_CULL_BACK; 
//	rasterizerDesc.CullMode = D3D11_CULL_NONE;
//	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE; 

	ID3D11RasterizerState *rs;
	p_mDevice->CreateRasterizerState( &rasterizerDesc, &rs );

	p_mDeviceContext->RSSetState( rs );




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	p_mDevice->CreateBlendState( &blendDesc, &p_mBlendState );

	blendDesc.AlphaToCoverageEnable = TRUE;
	p_mDevice->CreateBlendState( &blendDesc, &p_mBlendStateATC );

	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	p_mDeviceContext->OMSetBlendState(p_mBlendState, blendFactor, 0xffffffff );





	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	p_mDevice->CreateDepthStencilState( &depthStencilDesc, &p_mDepthStateEnable );//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	p_mDevice->CreateDepthStencilState( &depthStencilDesc, &p_mDepthStateDisable );//深度無効ステート

	p_mDeviceContext->OMSetDepthStencilState( p_mDepthStateEnable, NULL );




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	p_mDevice->CreateSamplerState( &samplerDesc, &samplerState );

	p_mDeviceContext->PSSetSamplers( 0, 1, &samplerState );



	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(MatrixBufferData);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	p_mDevice->CreateBuffer(&bufferDesc, NULL, &p_mMatrixBuffer);
	p_mDeviceContext->VSSetConstantBuffers(0, 1, &p_mMatrixBuffer);

	/*p_mDevice->CreateBuffer( &bufferDesc, NULL, &p_mWorldBuffer );
	p_mDeviceContext->VSSetConstantBuffers( 0, 1, &p_mWorldBuffer);

	p_mDevice->CreateBuffer( &bufferDesc, NULL, &p_mViewBuffer );
	p_mDeviceContext->VSSetConstantBuffers( 1, 1, &p_mViewBuffer );

	p_mDevice->CreateBuffer( &bufferDesc, NULL, &p_mProjectionBuffer );
	p_mDeviceContext->VSSetConstantBuffers( 2, 1, &p_mProjectionBuffer );*/


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	p_mDevice->CreateBuffer( &bufferDesc, NULL, &p_mMaterialBuffer );
	//p_mDeviceContext->VSSetConstantBuffers( 3, 1, &p_mMaterialBuffer );
	//p_mDeviceContext->PSSetConstantBuffers( 3, 1, &p_mMaterialBuffer );

	p_mDeviceContext->VSSetConstantBuffers(1, 1, &p_mMaterialBuffer);
	p_mDeviceContext->PSSetConstantBuffers(1, 1, &p_mMaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	p_mDevice->CreateBuffer( &bufferDesc, NULL, &p_mLightBuffer );
	//p_mDeviceContext->VSSetConstantBuffers( 4, 1, &p_mLightBuffer );
	//p_mDeviceContext->PSSetConstantBuffers( 4, 1, &p_mLightBuffer );

	p_mDeviceContext->VSSetConstantBuffers(2, 1, &p_mLightBuffer);
	p_mDeviceContext->PSSetConstantBuffers(2, 1, &p_mLightBuffer);





	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	light.Ambient = Color(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = Color(1.5f, 1.5f, 1.5f, 1.0f);
	SetLight(light);



	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

}



void Renderer::Uninit()
{
	p_mMatrixBuffer->Release();

	//p_mWorldBuffer->Release();
	//p_mViewBuffer->Release();
	//p_mProjectionBuffer->Release();
	p_mLightBuffer->Release();
	p_mMaterialBuffer->Release();

	p_mDeviceContext->ClearState();
	p_mRenderTargetView->Release();
	p_mSwapChain->Release();
	p_mDeviceContext->Release();
	p_mDevice->Release();

	/*SAFE_RELEASE(p_mMatrixBuffer);
	SAFE_RELEASE(p_mLightBuffer);
	SAFE_RELEASE(p_mMaterialBuffer);
	p_mDeviceContext->ClearState();
	SAFE_RELEASE(p_mRenderTargetView);
	SAFE_RELEASE(p_mSwapChain);
	SAFE_RELEASE(p_mDeviceContext);
	SAFE_RELEASE(p_mDevice);*/
}




void Renderer::Begin()
{
	float clearColor[4] = { 0.5f, 0.5f, 1.0f, 1.0f };
	p_mDeviceContext->ClearRenderTargetView( p_mRenderTargetView, clearColor );
	p_mDeviceContext->ClearDepthStencilView( p_mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}



void Renderer::End()
{
	p_mSwapChain->Present( 1, 0 );
}




void Renderer::SetDepthEnable( bool Enable )
{
	if( Enable )
		p_mDeviceContext->OMSetDepthStencilState( p_mDepthStateEnable, NULL );
	else
		p_mDeviceContext->OMSetDepthStencilState( p_mDepthStateDisable, NULL );

}



void Renderer::SetATCEnable( bool Enable )
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		p_mDeviceContext->OMSetBlendState(p_mBlendStateATC, blendFactor, 0xffffffff);
	else
		p_mDeviceContext->OMSetBlendState(p_mBlendState, blendFactor, 0xffffffff);

}

void Renderer::SetWorldViewProjection2D()
{
	Matrix world;
	world = Matrix::Identity;			// 単位行列にする
	world = world.Transpose();			// 転置


	mMatrixData.World = Matrix::Identity;
	mMatrixData.World = mMatrixData.World.Transpose();

	//p_mDeviceContext->UpdateSubresource(p_mWorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view;
	view = Matrix::Identity;
	view = view.Transpose();

	mMatrixData.View = Matrix::Identity;
	mMatrixData.View = mMatrixData.View.Transpose();

	//p_mDeviceContext->UpdateSubresource(p_mViewBuffer, 0, NULL, &view, 0, 0);

	Matrix projection;
/*
// update 右手系＝＝＝＞左手系  （DIRECTXTKのメソッドは右手系だった） 20230511 update by tomoki.suzuki　
	projection = projection.CreateOrthographicOffCenter(
		static_cast<float>(m_Application->GetWidth() * -0.5f),			// ビューボリュームの最小Ｘ
		static_cast<float>(m_Application->GetWidth() * 0.5f),			// ビューボリュームの最大Ｘ
		static_cast<float>(m_Application->GetHeight() * 0.5f),			// ビューボリュームの最小Ｙ
		static_cast<float>(m_Application->GetHeight() * -0.5f),			// ビューボリュームの最大Ｙ
		0.0f,
		1000.0f);
*/

/*
	// update 右手系＝＝＝＞左手系  （DIRECTXTKのメソッドは右手系だった） 20230511 update by tomoki.suzuki　
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		static_cast<float>(m_Application->GetWidth() * -0.5f),			// ビューボリュームの最小Ｘ
		static_cast<float>(m_Application->GetWidth() * 0.5f),			// ビューボリュームの最大Ｘ
		static_cast<float>(m_Application->GetHeight() * 0.5f),			// ビューボリュームの最小Ｙ
		static_cast<float>(m_Application->GetHeight() * -0.5f),			// ビューボリュームの最大Ｙ
		0.0f,
		1000.0f);
*/

	// 2D描画を左上原点にする  (20230512 update by tomoki.suzuki　
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(p_mApplication->GetWidth()),					// ビューボリュームの最小Ｘ
		static_cast<float>(p_mApplication->GetHeight()),					// ビューボリュームの最小Ｙ
		0.0f,															// ビューボリュームの最大Ｙ
		0.0f,
		1.0f);


	projection = projection.Transpose();

	mMatrixData.Projection = projection;

	//p_mDeviceContext->UpdateSubresource( p_mProjectionBuffer, 0, NULL, &projection, 0, 0 );
	p_mDeviceContext->UpdateSubresource(p_mMatrixBuffer, 0, NULL, &mMatrixData, 0, 0);
}


void Renderer::SetWorldMatrix( Matrix* WorldMatrix )
{
	Matrix world;
	world = WorldMatrix->Transpose();					// 転置

	mMatrixData.World = WorldMatrix->Transpose();	// まとめ用

	//p_mDeviceContext->UpdateSubresource(p_mWorldBuffer, 0, NULL, &world, 0, 0);
	p_mDeviceContext->UpdateSubresource(p_mMatrixBuffer, 0, NULL, &mMatrixData, 0, 0);
}

void Renderer::SetViewMatrix(Matrix* ViewMatrix )
{
	Matrix view;
	view = ViewMatrix->Transpose();						// 転置

	mMatrixData.View = ViewMatrix->Transpose();

	//p_mDeviceContext->UpdateSubresource(p_mViewBuffer, 0, NULL, &view, 0, 0);
	p_mDeviceContext->UpdateSubresource(p_mMatrixBuffer, 0, NULL, &mMatrixData, 0, 0);
}

void Renderer::SetProjectionMatrix( Matrix* ProjectionMatrix )
{
	Matrix projection;
	projection = ProjectionMatrix->Transpose();

	mMatrixData.Projection = ProjectionMatrix->Transpose();

	//p_mDeviceContext->UpdateSubresource(p_mProjectionBuffer, 0, NULL, &projection, 0, 0);
	p_mDeviceContext->UpdateSubresource(p_mMatrixBuffer, 0, NULL, &mMatrixData, 0, 0);
}



void Renderer::SetMaterial( MATERIAL Material )
{
	p_mDeviceContext->UpdateSubresource( p_mMaterialBuffer, 0, NULL, &Material, 0, 0 );
}

void Renderer::SetLight( LIGHT Light )
{
	p_mDeviceContext->UpdateSubresource(p_mLightBuffer, 0, NULL, &Light, 0, 0);
}




void Renderer::SetTopologyTriangleStrip()
{
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Renderer::SetTopologyTriangleList()
{
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::SetTopologyLineList()
{
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void Renderer::SetTopologyLineStrip()
{
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

void Renderer::CreateVertexShader( ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName )
{

	FILE* file;
	long int fsize;

	fopen_s(&file,FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	p_mDevice->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	p_mDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void Renderer::CreatePixelShader( ID3D11PixelShader** PixelShader, const char* FileName )
{
	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	p_mDevice->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}
