#include "OBJ_Number.h"

OBJ_Number::OBJ_Number()
{
	Com_Shader* p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);

	AddComponent(p_mShader);

	p_mSprite = new Com_CustomSprite();
	p_mSprite->mType = Com_CustomSprite::CustomType::LeftTop;
	p_mSprite->SetUpdate(true);
	p_mSprite->SetTexture("asset/texture/zanki.png");
	p_mSprite->SetSeparateNum(5, 2);
	p_mSprite->SetCurrent(1);
	AddComponent(p_mSprite);
}

void OBJ_Number::Update()
{
	GameObject::Update();

	p_mSprite->SetCurrent(iNum + 1);

	////0～4を出力
	//if (iNum < 5)
	//{
	//	fCurrentx = iNum * 0.2;
	//	fCurrentz = (iNum + 1) * 0.2;
	//	fCurrenty = 0;
	//	fCurrentw = 0.5;
	//}

	////5～9を出力
	//else
	//{
	//	fCurrentx = (iNum - 5) * 0.2;
	//	fCurrentz = (iNum - 4) * 0.2;
	//	fCurrenty = 0.5;
	//	fCurrentw = 1;
	//}

	//mUV.x = fCurrentx;
	//mUV.z = fCurrentz;
	//mUV.y = fCurrenty;
	//mUV.w = fCurrentw;

	//p_mSprite->SetUV(mUV); //UVにセット
}
