#pragma once
#include "Component.h"
#include "Com_Camera.h"
#include "../Utility.h"
#include "../DirectX/renderer.h"
#include "../DirectX/ShaderResourceView.h"
class Com_Billboard : 
	public Component 
{
protected:
	//カメラへのポインタ
	static Com_Camera* p_mCamera;

	ID3D11Buffer* m_VertexBuffer{};
	ShaderResourceView* m_Texture;
	
	int m_Count;

public:
	Com_Billboard();
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
};
