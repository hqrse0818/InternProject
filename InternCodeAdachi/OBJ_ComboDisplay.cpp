#include "OBJ_ComboDisplay.h"
#include "../Scene/Scene.h"
#include "OBJ_Score.h"
#include "CSVLoad.h"
#include "../System/Time.h"

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_ComboDisplay::OBJ_ComboDisplay()
{
	p_mSRV = new ShaderResourceView();
	p_mSRV->Create("asset/texture/combonum.png");
	p_mShader = new Com_Shader();
	p_mShader->p_mVS->Load(VS_SPRITE);
	p_mShader->p_mPS->Load(PS_SPRITE);
	AddComponent(p_mShader);

	p_mSprite = new Com_CustomSprite();
	p_mSprite->mType = Com_CustomSprite::CustomType::Center;
	p_mSprite->SetTexture("asset/texture/COMBO.png");
	p_mSprite->SetUpdate(true);
	AddComponent(p_mSprite);

	for (int i = 0; i < 3; i++)
	{
		Nums[i] = new OBJ_Number();
		Nums[i]->GetSpriteCom()->SetTexture(p_mSRV);
		Nums[i]->GetSpriteCom()->mType = Com_CustomSprite::CustomType::Center;
	}

	p_ComboFrame = new GameObject("frame");
	Com_Shader* shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_ComboFrame->AddComponent(shader);
	Com_CustomSprite* frameSp = new Com_CustomSprite();
	frameSp->SetTexture("asset/texture/combo1.png");
	frameSp->SetUpdate(true);
	frameSp->mType = Com_CustomSprite::CustomType::Left;
	p_ComboFrame->AddComponent(frameSp);
	p_ComboFrame->SetPosition(900.0f, 700.0f, 0.0f);
	p_ComboFrame->SetScale(1175.0f * 0.3f, 48.0f * 0.3f, 0.0);

	p_ComboGage = new GameObject("gage");
	shader = new Com_Shader();
	shader->p_mVS->Load(VS_SPRITE);
	shader->p_mPS->Load(PS_SPRITE);
	p_ComboGage->AddComponent(shader);
	p_GageSp = new Com_CustomSprite();
	p_GageSp->SetTexture("asset/texture/combo2.png");
	p_GageSp->SetUpdate(true);
	p_GageSp->mType = Com_CustomSprite::CustomType::Left;
	p_ComboGage->AddComponent(p_GageSp);
	p_ComboGage->SetPosition(900.0f, 700.0f, 0.0f);
	p_ComboGage->SetScale(0.0f, 48.0f * 0.25f, 0.0f);

	fComboScale = p_ComboFrame->p_mTransform->mScale.x;
}

OBJ_ComboDisplay::OBJ_ComboDisplay(const char* _name)
	: OBJ_ComboDisplay()
{
	sObjectName = _name;
}

OBJ_ComboDisplay::OBJ_ComboDisplay(const char* _name, const char* _FileName)
	: OBJ_ComboDisplay()
{
	sObjectName = _name;

	string sState = ReadDataFromCSV(_FileName, 1);
	vector<string> sv = SeparateString(sState, ',');

	// オブジェクトのポジション
	SetPosition(stof(sv[0]), stof(sv[1]), 0.0f);
	// オブジェクトのスケール
	SetScale(0.0, 0.0, 0.0f);
	// 自身の初期スケール
	mMyInitScale.x = stof(sv[2]);
	mMyInitScale.y = stof(sv[3]);
	// 自身の最大スケール
	mMyMaxScale.x = stof(sv[4]);
	mMyMaxScale.y = stof(sv[5]);
	// 数字の初期スケール
	mNumInitScale.x = stof(sv[6]);
	mNumInitScale.y = stof(sv[7]);
	// 数字の最大スケール
	mNumMaxScale.x = stof(sv[8]);
	mNumMaxScale.y = stof(sv[9]);
	// 拡大速度
	fScaleSpeed = stof(sv[10]);
	// メインとなるポジション
	mMainPos.x = stof(sv[11]);
	mMainPos.y = stof(sv[12]);
	// 数字の間隔
	fNumDuration = stof(sv[13]);
	// スケールを無視した調整
	fScaleDuration = stof(sv[14]);
	// 回転速度
	fRotSpeed = stof(sv[15]);
	// 既定の角度
	fEuler = stof(sv[16]);

	fEuler = Euler_To_Radian(fEuler);

	Nums[0]->SetRotation(0.0f,  0.0f, fEuler);
	Nums[1]->SetRotation(0.0f, 0.0f, fEuler);
	Nums[2]->SetRotation(0.0f, 0.0f, fEuler);

	SetRotation(0.0f, 0.0f, fEuler);
}

void OBJ_ComboDisplay::Init()
{
	GameObject::Init();
}

void OBJ_ComboDisplay::Start()
{
	GameObject::Start();
	fComboResetTime = OBJ_Score::GetComTime();
	for (int i = 0; i < 3; i++)
	{
		GetScene()->AddGameObject(Nums[i]);
	}

	GetScene()->AddGameObject(p_ComboFrame);
	p_ComboFrame->Init();
	p_ComboFrame->Start();
	GetScene()->AddGameObject(p_ComboGage);
	p_ComboGage->Init();
	p_ComboGage->Start();

	p_ComboFrame->SetActive(false);
	p_ComboGage->SetActive(false);
}

void OBJ_ComboDisplay::Update()
{
	iLastCombo = iCurrentCombo;
	iCurrentCombo = OBJ_Score::GetCurrentCombo();

	if (iCurrentCombo > iLastCombo && !(iLastCombo < 10 && iCurrentCombo >= 10) && !(iLastCombo < 100 && iCurrentCombo >= 100) && !bUpNum)
	{
		// コンボが続いた
		// スケールのリセット
		mCurrentNumScale = mNumInitScale;
		mCurrentMyScale = mMyInitScale;
		fComboCnt = 0.0f;
		p_ComboFrame->SetActive(true);
		p_ComboGage->SetActive(true);
		fComboScale = p_ComboFrame->p_mTransform->mScale.x;
		mComboColor.x = 0.0f;
		mComboColor.y = 1.0f;
		mComboColor.z = 0.0f;
		mComboColor.w = 1.0f;
	}
	if (iCurrentCombo == iLastCombo && iCurrentCombo != 0)
	{
		// コンボの変動なし
		fComboCnt += Time->GetDeltaTime();
		mCurrentNumScale.x += fScaleSpeed * Time->GetDeltaTime();
		if (mCurrentNumScale.x > mNumMaxScale.x)
		{
			mCurrentNumScale.x = mNumMaxScale.x;
		}
		mCurrentNumScale.y += fScaleSpeed * Time->GetDeltaTime();
		if (mCurrentNumScale.y > mNumMaxScale.y)
		{
			mCurrentNumScale.y = mNumMaxScale.y;
		}
		mCurrentMyScale.x += fScaleSpeed * Time->GetDeltaTime();
		if (mCurrentMyScale.x > mMyMaxScale.x)
		{
			mCurrentMyScale.x = mMyMaxScale.x;
		}
		mCurrentMyScale.y += fScaleSpeed * Time->GetDeltaTime();
		if (mCurrentMyScale.y > mMyMaxScale.y)
		{
			mCurrentMyScale.y = mMyMaxScale.y;
		}
	}
	else if(iCurrentCombo == 0)
	{
		mComboColor.x = 0.0f;
		mComboColor.y = 1.0f;
		mComboColor.z = 0.0f;
		mComboColor.w = 1.0f;

		mColor.x = 1.0f;
		mColor.y = 1.0f;
		mColor.z = 1.0f;
		mColor.w = 1.0f;
		p_mSprite->SetDiffuse(mColor);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(mColor);
		}

		fComboCnt = 0.0f;
		mCurrentNumScale.x = 0.0f;
		mCurrentNumScale.y = 0.0f;
		Nums[0]->SetNum(0);
		Nums[1]->SetNum(0);
		Nums[2]->SetNum(0);
		SetScale(0.0f, 0.0f, 0.0f);

		p_ComboFrame->SetActive(false);
		p_ComboGage->SetActive(false);
	}

	p_GageSp->SetDiffuse(mComboColor);

	if (fComboCnt < fComboResetTime / 4)
	{
		
	}
	else if (fComboCnt < fComboResetTime / 4 * 2)
	{
		mComboColor.x += 1.0f * Time->GetDeltaTime();
	}
	else if (fComboCnt < fComboResetTime / 4 * 3)
	{
		mComboColor.y -= 1.0f * Time->GetDeltaTime();
	}

	if (iLastCombo %10 != 0 && iCurrentCombo % 10 == 0)
	{
		mColor.x += 0.2f;
		mColor.y += 0.2f;
		mColor.z += 0.2f;
		mColor.w = 1.0f;

		if (mColor.y <= 0.0f)
		{
			mColor.y = 0.0f;
		}
		if (mColor.z <= 0.0f)
		{
			mColor.z = 0.0f;
		}
		p_mSprite->SetDiffuse(mColor);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(mColor);
		}

		// 桁上げの発生
		bUpNum = true;
	}
	else if (iCurrentCombo % 10 == 0)
	{
		p_mSprite->SetDiffuse(mColor);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(mColor);
		}
	}
	else
	{
		Color col{};
		col.x = 1.0f;
		col.y = 1.0f;
		col.z = 1.0f;
		p_mSprite->SetDiffuse(col);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(col);
		}
	}
	
	if (iCurrentCombo > 99)
		{
			// 100の位
			int com = iCurrentCombo;
			Nums[0]->SetNum(com / 100);
			com = com % 100;
			Nums[1]->SetNum(com / 10);
			com = com % 10;
			Nums[2]->SetNum(com);

			// 10の位を中心にして配置していく
			Nums[1]->SetPosition(mMainPos.x, mMainPos.y, 0.0f);
			Nums[1]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 1の位
			Nums[2]->SetPosition(mMainPos.x + mCurrentNumScale.x + fNumDuration + fScaleDuration, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100の位
			Nums[0]->SetPosition(mMainPos.x - mCurrentNumScale.x - fNumDuration - fScaleDuration, mMainPos.y, 0.0f);
			Nums[0]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else if (iCurrentCombo > 9)
		{
			// 100の位
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(com / 10);
			com = com % 10;
			Nums[2]->SetNum(com);
			// 10の位を中心にして配置していく
			Nums[1]->SetPosition(mMainPos.x - mCurrentNumScale.x - fNumDuration - fScaleDuration, mMainPos.y, 0.0f);
			Nums[1]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 1の位
			Nums[2]->SetPosition(mMainPos.x + mCurrentNumScale.x + fNumDuration + fScaleDuration, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100の位
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else if (iCurrentCombo > 0)
		{
			// 100の位
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(0);
			Nums[2]->SetNum(com);
			// 10の位を中心にして配置していく
			Nums[1]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[1]->SetScale(0.0f, 0.0f, 0.0f);
			// 1の位
			Nums[2]->SetPosition(mMainPos.x, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100の位
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else
		{
			// 100の位
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(0);
			Nums[2]->SetNum(com);
			// 10の位を中心にして配置していく
			Nums[1]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[1]->SetScale(0.0f, 0.0f, 0.0f);
			// 1の位
			Nums[2]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[2]->SetScale(0.0f, 0.0f, 0.0f);
			// 100の位
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(0.0f, 0.0f, 0.0f);
		}
	if(bUpNum)
	{
		fRotCnt += Time->GetDeltaTime();
		// 回転させる
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->Rotate(0.0f, 0.0f, fRotSpeed * Time->GetDeltaTime());
		}
		if (fRotCnt > fRotTime)
		{
			fRotCnt = 0.0f;
			bUpNum = false;
			// 回転矯正
			for (int i = 0; i < 3; i++)
			{
				Nums[i]->SetRotation(0.0f, 0.0f, fEuler);
			}
		}
	}

	GameObject::Update();

	fComboScale -= p_ComboFrame->p_mTransform->mScale.x * (Time->GetDeltaTime() / fComboResetTime);
	p_ComboGage->SetScale(fComboScale, 48.0f * 0.25f, 0.0f);
}

void OBJ_ComboDisplay::Uninit()
{
	GameObject::Uninit();
	p_mSRV->Uninit();
	delete p_mSRV;
}
