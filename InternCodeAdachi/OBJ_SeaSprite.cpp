#include "OBJ_SeaSprite.h"
#include "../System/Time.h"
#include "../System/HighGetRand.h"

OBJ_SeaSprite::OBJ_SeaSprite()
{
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load("shader\\PS_MirrorUV.cso");
	AddComponent(p_mShader);

	p_mSprite = new Com_3DSprite();
	p_mSprite->SetTexture("asset\\texture\\sea.jpg");
	AddComponent(p_mSprite);
}

OBJ_SeaSprite::OBJ_SeaSprite(const char* _name)
	: OBJ_SeaSprite()
{
	sObjectName = _name;
}

void OBJ_SeaSprite::Update()
{
	GameObject::Update();

	int r = HighRand::GetRand(1, 4);

	Translate(3.0f * Time->GetDeltaTime(), 0.0f, 3.0f * Time->GetDeltaTime());

	/*switch (r)
	{
	case 1:
		Translate(1.0f * Time->GetDeltaTime(), 0.0f, 1.0f * Time->GetDeltaTime());
		break;
	case 2:
		Translate(-1.0f * Time->GetDeltaTime(), 0.0f, -1.0f * Time->GetDeltaTime());
		break;
	case 3:
		Translate(1.0f * Time->GetDeltaTime(), 0.0f, -1.0f * Time->GetDeltaTime());
		break;
	case 4:
		Translate(-1.0f * Time->GetDeltaTime(), 0.0f, 1.0f * Time->GetDeltaTime());
		break;
	default:
		break;
	}*/

	
}
