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
	//�J�����ւ̃|�C���^
	static Com_Camera* p_mCamera;

	ID3D11Buffer* m_VertexBuffer{};
	ShaderResourceView* m_Texture;

	float fCurrentx;
	float fCurrenty;
	float fCurrentz;
	float fCurrentw;

	float fSetx;
	float fSety;
	
	int m_Count;

public:
	Com_EffectBillboard();
	void Load();
	void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(const char* _name);
	static void SetCamera(Com_Camera*_cam)
	{
		p_mCamera = _cam;
	}
	void SetSRV(ID3D11ShaderResourceView* _pSRV)
	{
		m_Texture->SetSRV(_pSRV);
	}
	void SetUVCut(float _x, float _y)
	{
		fSetx = _x;
		fSety = _y;
	}
};
