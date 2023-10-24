#include "OBJ_Warning.h"
#include "../ComponentHeader.h"
#include "CSVLoad.h"

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_Warning::OBJ_Warning()
{
	pBack = new GameObject("back");
	Com_Shader* pShader = new Com_Shader();
	pShader->p_mVS->Load(VS_SPRITE);
	pShader->p_mPS->Load(PS_SPRITE);
	pBack->AddComponent(pShader);
	Com_Sprite* pSprite = new Com_Sprite();
	pSprite->SetTexture("asset/texture/keikoku_haikei.png");
	pSprite->SetUpdate(true);
	pBack->AddComponent(pSprite);

	AddChild(pBack);

	pFont = new GameObject("font");
	pShader = new Com_Shader();
	pShader->p_mVS->Load(VS_SPRITE);
	pShader->p_mPS->Load(PS_SPRITE);
	pFont->AddComponent(pShader);
	pFontSp = new Com_Sprite();
	pFontSp->SetTexture("asset/texture/keikoku_mozi.png");
	pFontSp->SetUpdate(true);
	pFont->AddComponent(pFontSp);

	AddChild(pFont);

	pMark = new GameObject("mark");
	pShader = new Com_Shader();
	pShader->p_mVS->Load(VS_SPRITE);
	pShader->p_mPS->Load(PS_SPRITE);
	pMark->AddComponent(pShader);
	pMarkSp = new Com_Sprite();
	pMarkSp->SetTexture("asset/texture/keikokuhyousiki.png");
	pMarkSp->SetUpdate(true);
	pMark->AddComponent(pMarkSp);

	AddChild(pMark);
}

OBJ_Warning::OBJ_Warning(const char* _name)
	: OBJ_Warning()
{
	sObjectName = _name;
}

OBJ_Warning::OBJ_Warning(const char* _name, const char* _FileName)
	: OBJ_Warning()
{
	sObjectName = _name;

	string ss = ReadDataFromCSV(_FileName, 1);

	vector<string>sv = SeparateString(ss, ',');

	pBack->SetScale(stof(sv[0]), stof(sv[1]), 0.0f);
	pBack->SetPosition(stof(sv[2]), stof(sv[3]), 0.0f);
	pFont->SetScale(stof(sv[4]), stof(sv[5]), 0.0f);
	pFont->SetPosition(stof(sv[6]), stof(sv[7]), 0.0f);
	pMark->SetScale(stof(sv[8]), stof(sv[9]), 0.0f);
	pMark->SetPosition(stof(sv[10]), stof(sv[11]), 0.0f);
}
