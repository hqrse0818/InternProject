#pragma once
#include "Component.h"
#include "Com_Camera.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"
#include "../DirectX/ShaderResourceView.h"
class Com_EffectBillboard : 
	public Component 
{
protected:
	//カメラへのポインタ
	static Com_Camera* p_mCamera;

	ID3D11Buffer* m_VertexBuffer{};
	ShaderResourceView* m_Texture;

	// 表示するUV座標の位置
	// 左
	float fCurrentx = 0;
	// 上
	float fCurrenty = 0;
	// 右
	float fCurrentz = 0;
	// 下
	float fCurrentw = 0;

	// UV分割数

	int iSeparateX;
	int iSeparateY;

	int iCurrent = 0;

public:
	Com_EffectBillboard();
	void Load();
	void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(const char* _name);
	static void SetCamera(Com_Camera* _cam)
	{
		p_mCamera = _cam;
	}
	void SetSRV(ID3D11ShaderResourceView* _pSRV)
	{
		m_Texture->SetSRV(_pSRV);
	}
	void SetUVCut(int _x, int _y)
	{
		iSeparateX = _x;
		iSeparateY = _y;
	}

	void SetCurrent(int _val);
};
