#include "OBJ_DisplayScore.h"
#include "../Scene/Scene.h"
#include "CSVLoad.h"
#include "OBJ_Score.h"

using namespace DirectX::SimpleMath;
using namespace std;

OBJ_DisplayScore::OBJ_DisplayScore()
{
	p_mSRV = new ShaderResourceView();
	p_mSRV->Create("asset\\texture\\score.png");
	for (int i = 0; i < 6; i++)
	{
		Nums[i] = new OBJ_Number();
		Nums[i]->GetSpriteCom()->mType = Com_CustomSprite::CustomType::LeftTop;
		Nums[i]->GetSpriteCom()->SetTexture(p_mSRV);
		Nums[i]->SetPosition(300 + 100 * i, 0.0f, 0.0f);
		Nums[i]->SetScale(100.0f, 100.0f, 0.0f);
		Nums[i]->SetNum(0);
	}
	// âEè„Ç…çÏê¨
}

OBJ_DisplayScore::OBJ_DisplayScore(const char* _name)
	: OBJ_DisplayScore()
{
	sObjectName = _name;
}

OBJ_DisplayScore::OBJ_DisplayScore(const char* _name, const char* _FileName)
	: OBJ_DisplayScore()
{
	sObjectName = _name;

	string sState = ReadDataFromCSV(_FileName, 1);

	std::vector<string> sv = SeparateString(sState, ',');

	Vector2 InitialPos;
	InitialPos.x = stof(sv[0]);
	InitialPos.y = stof(sv[1]);
	Vector2 Scale;
	Scale.x = stof(sv[2]);
	Scale.y = stof(sv[3]);
	float duration = stof(sv[4]);

	for (int i = 0; i < 6; i++)
	{
		Nums[i]->SetPosition(InitialPos.x + (Scale.x * i), InitialPos.y, 0.0f);
		Nums[i]->SetScale(Scale.x, Scale.y, 0.0f);
	}
	for (int i = 1; i < 6; i++)
	{
		Nums[i]->p_mTransform->mPosition.x -= duration * i;
	}
}

void OBJ_DisplayScore::Init()
{
	GameObject::Init();

	for (int i = 0; i < 6; i++)
	{
		Nums[i]->Init();
	}
}

void OBJ_DisplayScore::Start()
{
	for (int i = 0; i < 6; i++)
	{
		GetScene()->AddGameObject(Nums[i]);
	}
}

void OBJ_DisplayScore::Update()
{
	unsigned int score = OBJ_Score::GetScore();
	
	int val = 1000000;
	int waru = 100000;
	for (int i = 0; i < 6; i++)
	{
		int num = score % val;
		Nums[i]->SetNum(num / waru);
		val *= 0.1f;
		waru *= 0.1f;
	}
}

void OBJ_DisplayScore::Uninit()
{
	GameObject::Uninit();
	p_mSRV->Uninit();
	delete p_mSRV;
}
