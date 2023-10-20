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

	// �I�u�W�F�N�g�̃|�W�V����
	SetPosition(stof(sv[0]), stof(sv[1]), 0.0f);
	// �I�u�W�F�N�g�̃X�P�[��
	SetScale(0.0, 0.0, 0.0f);
	// ���g�̏����X�P�[��
	mMyInitScale.x = stof(sv[2]);
	mMyInitScale.y = stof(sv[3]);
	// ���g�̍ő�X�P�[��
	mMyMaxScale.x = stof(sv[4]);
	mMyMaxScale.y = stof(sv[5]);
	// �����̏����X�P�[��
	mNumInitScale.x = stof(sv[6]);
	mNumInitScale.y = stof(sv[7]);
	// �����̍ő�X�P�[��
	mNumMaxScale.x = stof(sv[8]);
	mNumMaxScale.y = stof(sv[9]);
	// �g�呬�x
	fScaleSpeed = stof(sv[10]);
	// ���C���ƂȂ�|�W�V����
	mMainPos.x = stof(sv[11]);
	mMainPos.y = stof(sv[12]);
	// �����̊Ԋu
	fNumDuration = stof(sv[13]);
	// �X�P�[���𖳎���������
	fScaleDuration = stof(sv[14]);
	// ��]���x
	fRotSpeed = stof(sv[15]);
	// ����̊p�x
	fEuler = stof(sv[16]);
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
}

void OBJ_ComboDisplay::Update()
{
	iLastCombo = iCurrentCombo;
	iCurrentCombo = OBJ_Score::GetCurrentCombo();
	if (iCurrentCombo > iLastCombo && !(iLastCombo < 10 && iCurrentCombo >= 10) && !(iLastCombo < 100 && iCurrentCombo >= 100) && !bUpNum)
	{
		// �R���{��������
		// �X�P�[���̃��Z�b�g
		mCurrentNumScale = mNumInitScale;
		mCurrentMyScale = mMyInitScale;
		fComboCnt = 0.0f;

		Color col;
		col.x = 1.0f;
		col.y = 1.0f;
		col.z = 1.0f;
		col.w = 1.0f;

		p_mSprite->SetDiffuse(col);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(col);
		}
	}
	else if (iLastCombo < 10 && iCurrentCombo >= 10 || iLastCombo < 100 && iCurrentCombo >= 100)
	{
		// ���グ�̔���
		bUpNum = true;
	}
	else if (iCurrentCombo == iLastCombo && iCurrentCombo != 0)
	{
		// �R���{�̕ϓ��Ȃ�
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
		Color col;
		col.x = 1.0f;
		col.y = 1.0f;
		col.z = 1.0f;
		// ���Ԍo�߂œ����x���グ��
		col.w = fComboResetTime - fComboCnt / fComboResetTime;
		p_mSprite->SetDiffuse(col);
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->GetSpriteCom()->SetDiffuse(col);
		}
	}
	else
	{
		fComboCnt = 0.0f;
		mCurrentNumScale.x = 0.0f;
		mCurrentNumScale.y = 0.0f;
		Nums[0]->SetNum(0);
		Nums[1]->SetNum(0);
		Nums[2]->SetNum(0);
		SetScale(0.0f, 0.0f, 0.0f);
	}

	
	if (iCurrentCombo > 99)
		{
			// 100�̈�
			int com = iCurrentCombo;
			Nums[0]->SetNum(com / 100);
			com = com % 100;
			Nums[1]->SetNum(com / 10);
			com = com % 10;
			Nums[2]->SetNum(com);

			// 10�̈ʂ𒆐S�ɂ��Ĕz�u���Ă���
			Nums[1]->SetPosition(mMainPos.x, mMainPos.y, 0.0f);
			Nums[1]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 1�̈�
			Nums[2]->SetPosition(mMainPos.x + mCurrentNumScale.x + fNumDuration + fScaleDuration, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100�̈�
			Nums[0]->SetPosition(mMainPos.x - mCurrentNumScale.x - fNumDuration - fScaleDuration, mMainPos.y, 0.0f);
			Nums[0]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else if (iCurrentCombo > 9)
		{
			// 100�̈�
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(com / 10);
			com = com % 10;
			Nums[2]->SetNum(com);
			// 10�̈ʂ𒆐S�ɂ��Ĕz�u���Ă���
			Nums[1]->SetPosition(mMainPos.x - mCurrentNumScale.x - fNumDuration - fScaleDuration, mMainPos.y, 0.0f);
			Nums[1]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 1�̈�
			Nums[2]->SetPosition(mMainPos.x + mCurrentNumScale.x + fNumDuration + fScaleDuration, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100�̈�
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else if (iCurrentCombo > 0)
		{
			// 100�̈�
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(0);
			Nums[2]->SetNum(com);
			// 10�̈ʂ𒆐S�ɂ��Ĕz�u���Ă���
			Nums[1]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[1]->SetScale(0.0f, 0.0f, 0.0f);
			// 1�̈�
			Nums[2]->SetPosition(mMainPos.x, mMainPos.y, 0.0f);
			Nums[2]->SetScale(mCurrentNumScale.x, mCurrentNumScale.y, 0.0f);
			// 100�̈�
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(mCurrentMyScale.x, mCurrentMyScale.y, 0.0f);
		}
	else
		{
			// 100�̈�
			int com = iCurrentCombo;
			Nums[0]->SetNum(0);
			Nums[1]->SetNum(0);
			Nums[2]->SetNum(com);
			// 10�̈ʂ𒆐S�ɂ��Ĕz�u���Ă���
			Nums[1]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[1]->SetScale(0.0f, 0.0f, 0.0f);
			// 1�̈�
			Nums[2]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[2]->SetScale(0.0f, 0.0f, 0.0f);
			// 100�̈�
			Nums[0]->SetPosition(0.0f, 0.0f, 0.0f);
			Nums[0]->SetScale(0.0f, 0.0f, 0.0f);

			SetScale(0.0f, 0.0f, 0.0f);
		}
	if(bUpNum)
	{
		fRotCnt += Time->GetDeltaTime();
		// ��]������
		for (int i = 0; i < 3; i++)
		{
			Nums[i]->Rotate(0.0f, 0.0f, fRotSpeed * Time->GetDeltaTime());
		}
		if (fRotCnt > fRotTime)
		{
			fRotCnt = 0.0f;
			bUpNum = false;
			// ��]����
			for (int i = 0; i < 3; i++)
			{
				Nums[i]->SetRotation(0.0f, 0.0f, 0.0f);
			}
		}
	}

	GameObject::Update();
}

void OBJ_ComboDisplay::Uninit()
{
	GameObject::Uninit();
	p_mSRV->Uninit();
	delete p_mSRV;
}
