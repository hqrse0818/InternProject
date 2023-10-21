#include "Scene_Game.h"
#include "GameInclude.h"

using namespace DirectX::SimpleMath;
using namespace std;

void Scene_Game::Init()
{
	// �����蔻��A�N�e�B�u��
	bCheckCol = true;

	// �y���M��
	p_mPlayer = new OBJ_Penguin("Test", "asset/data/csv/PlayerStatus.csv");
	AddKeyObject(p_mPlayer);

	// �J����
	GameObject* Camera = new GameObject("Camera");
	Com_AngleCamera* Camera_buf = new Com_AngleCamera();
	Camera_buf->SetTarget(p_mPlayer);
	Camera_buf->SetUseTarget(true);
	Camera_buf->SetAngle(0.0f);
	Camera_buf->SetDistance(50.0f);
	Camera->p_mTransform->SetPosition(0.0f, 20.0f, -30.0f);
	Camera->AddComponent(Camera_buf);

	// �r���{�[�h�̃J�����ݒ�
	Com_EffectBillboard::SetCamera(Camera_buf);
	Com_Billboard::SetCamera(Camera_buf);

	// �y���M���֘A�̃J�����ݒ�
	p_mPlayer->GetMoveCom()->SetCameraCom(Camera_buf);
	p_mPlayer->SetCameraCom(Camera_buf);

	// �C�I�u�W�F�N�g
	{
		OBJ_Sea* Sea = new OBJ_Sea("Sea");
		Sea->SetPosition(0.0f, -30.0f, 0.0f);
		AddGameObject(Sea);
		// �C�p�X�v���C�g
		OBJ_SeaSprite* seasprite = new OBJ_SeaSprite("umi");
		seasprite->SetScale(1.0f, 1.0f, 1.0f);
		seasprite->GetSpriteCom()->SetUV(2.0f, 2.0f);
		seasprite->GetSpriteCom()->SetSize(500.0f, 500.0f);
		AddGameObject(seasprite, 3);
	}
	

	// �X�e�[�W�݌v
	{
		// �X�e�[�W�̃u���b�N���̓ǂݍ���
		string sStageNum = ReadDataFromCSV("asset/data/csv/Stage.csv", 1);
		std::vector<string> IceSetting = SeparateString(sStageNum, ',');
		unsigned int stagenum = stoi(IceSetting[0]);
		// �X�e�[�W�̍ő�̃C���f�b�N�X���i�[
		OBJ_Ice::s_iMaxNumIndex = stagenum - 1;
		float IceScale = stof(IceSetting[1]);

		int Stagecenter = 0;

		if (stagenum % 2 == 0)
		{
			Stagecenter = stagenum / 2;
		}
		else
		{
			Stagecenter = stagenum / 2 + 1;
		}

		// �����̊J�n�ʒu�v�Z
		int StageInit = IceScale * -Stagecenter;

		// �X�}�l�[�W���[
		OBJ_IceManager* iMana = new OBJ_IceManager("iMana", "asset/data/csv/IceStatus.csv");
		AddGameObject(iMana);

		float time = iMana->GetShakeTime();
		float pow = iMana->GetShakePower();
		Vector3 cen = iMana->GetColCenter();
		Vector3 size = iMana->GetColSize();
		Vector3 scale = iMana->GetScale();

		// �X�e�[�W����
		for (int i = 0; i < stagenum; i++)
		{
			for (int j = 0; j < stagenum; j++)
			{
				// �X�̐���
				OBJ_Ice* Ice = new OBJ_Ice("Ice");
				Ice->SetShakeTime(time);
				Ice->SetShakePower(pow);
				Ice->SetScale(scale.x, scale.y, scale.z);
				Com_BoxCollider* col = Ice->GetColliderCom();
				col->mCenter = cen;
				col->mSize = size;
				Ice->p_mTransform->SetPosition(StageInit + i * col->mSize.x * Ice->p_mTransform->mScale.x, 0.0f, StageInit + j * col->mSize.z * Ice->p_mTransform->mScale.z);
				Ice->myRow = j;
				Ice->myLine = i;
				AddGameObject(Ice);
				iMana->RegisterIce(Ice);

				int r = HighRand::GetRand(1, 4);
				switch (r)
				{
				case 1:
					Ice->SetRotation(0.0f, Euler_To_Radian(90), 0.0f);
					break;
				case 2:
					Ice->SetRotation(0.0f, Euler_To_Radian(180), 0.0f);
					break;
				case 3:
					Ice->SetRotation(0.0f, Euler_To_Radian(270), 0.0f);
					break;
				case 4:
					break;
				default:
					break;
				}
			}
		}
		// �X�̈ʒu�Ɛ����痎���p�I�u�W�F�N�g�̈ʒu�����߂�
		// ����
		OBJ_Fall* fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit - ((scale.x * size.x) * 2), 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 8.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		AddGameObject(fobj);
		// �E��
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(StageInit + ((scale.x * size.x) * (stagenum + 1)), 0.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(20.0f, 8.0f, 100.0f);
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		AddGameObject(fobj);
		// �㑤
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 0.0f, StageInit + ((scale.z * size.z) * (stagenum + 1)));
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 8.0f, 20.0f);
		AddGameObject(fobj);
		// ����
		fobj = new OBJ_Fall("fall");
		fobj->SetPosition(0.0f, 0.0f, StageInit - ((scale.z * size.z) * 2));
		fobj->GetColliderCom()->SetCenter(0.0f, 4.0f, 0.0f);
		fobj->GetColliderCom()->SetSize(100.0f, 8.0f, 20.0f);
		AddGameObject(fobj);
	}


	// �X�R�A�\���I�u�W�F�N�g
	OBJ_DisplayScore* ScoreObj = new OBJ_DisplayScore("dis", "asset/data/csv/ScoreUI.csv");
	AddGameObject(ScoreObj);

	// �X�R�A�}�l�[�W���[
	OBJ_Score* ScoreManager = new OBJ_Score("score", "asset/data/csv/ComboSetting.csv");
	AddGameObject(ScoreManager);

	// �R���{�\���I�u�W�F�N�g
	OBJ_ComboDisplay* ComboObj = new OBJ_ComboDisplay("combo", "asset/data/csv/ComboUI.csv");
	AddGameObject(ComboObj);
	
}