#pragma once

// �O���錾
class GameObject;

class Component
{
public:
	// �R���|�[�l���g���������Ă�e�I�u�W�F�N�g
	GameObject* p_mObject;

	// �R���|�[�l���g���L�����ǂ���
	bool bEnable;

public:
	// �R���X�g���N�^
	Component()
	{
		p_mObject = nullptr;
		bEnable = true;
	}

	// �f�X�g���N�^
	virtual ~Component() {};

	virtual void Init() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void PreDraw() {};
	virtual void Draw() {};
	virtual void OnCollisionEnter(GameObject* _obj) {};
	virtual void OnCollisionStay(GameObject* _obj) {};
	virtual void OnCollisionExit(GameObject* _obj) {};

	virtual void Uninit() {};
};