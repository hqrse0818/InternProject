#include "OBJ_Warning.h"
#include "../ComponentHeader.h"
#include "CSVLoad.h"
#include "../System/Time.h"
#include "GameManager.h"

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_Warning::OBJ_Warning()
{
	pBack = new GameObject("back");
	Com_Shader* pShader = new Com_Shader();
	pShader->p_mVS->Load(VS_SPRITE);
	pShader->p_mPS->Load(PS_SPRITE);
	pBack->AddComponent(pShader);
	pBackSp = new Com_Sprite();
	pBackSp->SetTexture("asset/texture/keikoku_haikei.png");
	pBackSp->SetUpdate(true);
	pBack->AddComponent(pBackSp);

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


	InitBack = pBack->p_mTransform->mScale;
	InitFont = pFont->p_mTransform->mScale;
	InitMark = pMark->p_mTransform->mScale;
}

void OBJ_Warning::Update()
{
	if (bActive)
	{
		switch (mState)
		{
		case OBJ_Warning::WarningState::No:
			mColor.w = 0.25;
			mBackColor.w = 0.25;
			pBackSp->SetDiffuse(mBackColor);
			pFontSp->SetDiffuse(mColor);
			pMarkSp->SetDiffuse(mColor);

			pBack->p_mTransform->mScale = InitBack;
			pFont->p_mTransform->mScale = InitFont;
			pMark->p_mTransform->mScale = InitMark;
			break;
		case OBJ_Warning::WarningState::Start:
			mColor.w += 2 * Time->GetDeltaTime();
			mBackColor.w += 2 * Time->GetDeltaTime();

			pBack->Scaling(fScaleSpeed * Time->GetDeltaTime(), fScaleSpeed * Time->GetDeltaTime(), 0.0f);
			pFont->Scaling(fScaleSpeed * Time->GetDeltaTime(), fScaleSpeed * Time->GetDeltaTime(), 0.0f);
			pMark->Scaling(fScaleSpeed * Time->GetDeltaTime(), fScaleSpeed * Time->GetDeltaTime(), 0.0f);

			if (mBackColor.w >= 1.0f)
			{
				mColor.w = 1;
				mBackColor.w = 1;
				mState = WarningState::Warning;
			}
			pBackSp->SetDiffuse(mBackColor);
			pFontSp->SetDiffuse(mColor);
			pMarkSp->SetDiffuse(mColor);

			break;
		case OBJ_Warning::WarningState::Warning:
			if (bRet)
			{
				mColor.w += fAlphaSpeed * Time->GetDeltaTime();
				if (mColor.w >= 1.0f)
				{
					mColor.w = 1;
					bRet = false;
				}
				pFontSp->SetDiffuse(mColor);
				pMarkSp->SetDiffuse(mColor);
			}
			else
			{
				mColor.w -= fAlphaSpeed * Time->GetDeltaTime();
				if (mColor.w <= 0.5f)
				{
					mColor.w = 0.5;
					bRet = true;
				}
				pFontSp->SetDiffuse(mColor);
				pMarkSp->SetDiffuse(mColor);
			}

			break;
		case OBJ_Warning::WarningState::End:
			mColor.w -= 2 * Time->GetDeltaTime();
			mBackColor.w -= 2 * Time->GetDeltaTime();
			pBack->Scaling(fScaleMinus* Time->GetDeltaTime(), fScaleMinus * Time->GetDeltaTime(), 0.0f);
			pFont->Scaling(fScaleMinus* Time->GetDeltaTime(), fScaleMinus * Time->GetDeltaTime(), 0.0f);
			pMark->Scaling(fScaleMinus* Time->GetDeltaTime(), fScaleMinus * Time->GetDeltaTime(), 0.0f);

			if (mBackColor.w  <= 0.25f)
			{
				mColor.w = 0.25;
				mBackColor.w = 0.25;
				mState = WarningState::No;
			}
			pBackSp->SetDiffuse(mBackColor);
			pFontSp->SetDiffuse(mColor);
			pMarkSp->SetDiffuse(mColor);
			break;
		default:
			break;
		}

		GameObject::Update();
	}
}
