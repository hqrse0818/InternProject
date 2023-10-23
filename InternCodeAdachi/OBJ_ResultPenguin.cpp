#include "OBJ_ResultPenguin.h"
#include "../System/Time.h"

using namespace std;

OBJ_ResultPenguin::OBJ_ResultPenguin()
{
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);
	p_mMainSprite = new Com_Sprite();
	AddComponent(p_mMainSprite);

	for (int i = 0; i < 109; i++)
	{
		string path = "asset/texture/result/result_penginfront_1_";
		path = path + std::to_string(i + 1) + ".png";
		p_mSprites[i] = new ShaderResourceView();

		const char* fpath = path.c_str();
		bool b = p_mSprites[i]->Create(fpath);
	}

	p_mMainSprite->SetTexture(p_mSprites[Current]);
}

OBJ_ResultPenguin::OBJ_ResultPenguin(const char* _name)
	: OBJ_ResultPenguin()
{
	sObjectName = _name;
}

void OBJ_ResultPenguin::Update()
{
	GameObject::Update();

	if (bUpdate)
	{
		fCnt += Time->GetDeltaTime();
		if (fCnt > fRate)
		{
			fCnt = 0;
			Current++;
			if (Current > 108)
			{
				bUpdate = false;
				Current = 0;
			}
			if(bUpdate)
				p_mMainSprite->SetTexture(p_mSprites[Current]);
		}
	}
}

void OBJ_ResultPenguin::Uninit()
{
	GameObject::Uninit();

	for (int i = 0; i < 109; i++)
	{
		p_mSprites[i]->Uninit();
		delete p_mSprites[i];
	}
}