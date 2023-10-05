#include "Com_Foot.h"
#include "../GameObject/GameObject.h"
#include "../Component/Com_Collider.h"
#include "../Component/Com_BoxCollider.h"
#include "Com_Gravity.h"

void Com_Foot::Update()
{
	fFootPos = p_mObject->p_mTransform->mPosition.y + fFootHeight;
}

void Com_Foot::OnCollisionEnter(GameObject* _obj)
{
	// �R���C�_�[�̃^�C�v���擾
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		// �{�b�N�X�Ȃ�{�b�N�X�R���C�_�[���擾
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		// ��邱�Ƃ��ł���Ȃ�
		if (col->bCanStepOn && p_mGravityTarget)
		{
			// �����ݗ�����
			if (p_mGravityTarget->GetGround() == false)
			{
				// �{�b�N�X��y���W�̍ő�l���擾�B
				float heightY = col->Getmax().y;
				// �t�b�g�|�W�V������
				if (fFootPos > heightY)
				{
					p_mObject->p_mTransform->mPosition.y = heightY;
					p_mGravityTarget->SetGround(true);
				}
			}
		}
	}
}

void Com_Foot::OnCollisionStay(GameObject* _obj)
{
	// �R���C�_�[�̃^�C�v���擾
	if (_obj->mColType == Collider::ColliderForm::Box)
	{
		// �{�b�N�X�Ȃ�{�b�N�X�R���C�_�[���擾
		Com_BoxCollider* col = _obj->GetComponent<Com_BoxCollider>();
		// ��邱�Ƃ��ł���Ȃ�
		if (col->bCanStepOn && p_mGravityTarget)
		{
			// �����ݗ�����
			if (p_mGravityTarget->GetGround() == false)
			{
				// �{�b�N�X��y���W�̍ő�l���擾�B
				float heightY = col->Getmax().y;
				// �t�b�g�|�W�V������
				if (fFootPos > heightY)
				{
					p_mObject->p_mTransform->mPosition.y = heightY;
					p_mGravityTarget->SetGround(true);
				}
			}
		}
	}
}

void Com_Foot::OnCollisionExit(GameObject* _obj)
{
	if (p_mGravityTarget)
	{
		p_mGravityTarget->SetGround(false);
	}
}


// �^�C�g����
// �y���M���h���b�v
// �y���M���A�C�X�h���b�v
// �y���M��vs�A�U���V~�X��̎���~