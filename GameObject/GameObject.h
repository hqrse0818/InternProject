#pragma once

#include <list>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "../Component//Component.h"
#include "../Component/Com_Transform.h"

typedef std::list<Component*> Componentlist;
typedef std::list<GameObject*> Objectlist;
typedef std::vector<GameObject*> Objectvector;
typedef std::unordered_map<std::string, GameObject*> Objectmap;

class Scene;

namespace Collider
{
	enum class ColliderForm
	{
		None, Box, Sphere, Cylinder, Box2D, Circle
	};
}

// �I�u�W�F�N�gID��second�̍ő吔
#define ObjectIDSecondMax 1000

struct Wint
{
	unsigned int first;
	unsigned int second;
};

class GameObject
{
protected:
	// �Q�[���I�u�W�F�N�g�����ۂɎ���protected�ϐ�
	// ������
	static Wint s_mAllNum;

	// �I�u�W�F�N�gID
	Wint mID;

	// �A�N�e�B�x�[�V����
	bool bActive = true;

	static Scene* s_p_mScene;

	// �R���|�[�l���g���X�g
	Componentlist p_mComponentList;

public:
	// �q�I�u�W�F�N�g���X�g
	Objectlist p_mChildren;

	// �j��\��
	bool bDestroy = false;
	Collider::ColliderForm mColType = Collider::ColliderForm::None;

	// �I�u�W�F�N�g�̃q�b�g���X�g
	Objectvector mCollisionvector;
	Objectvector mLastCollisionvector;

	// �I�u�W�F�N�g��(�f�o�b�O�p)
	std::string sObjectName;
	// �I�u�W�F�N�g�̃^�O
	std::string sTag;

	// �e�I�u�W�F�N�g
	GameObject* p_mParent;

	// Com_Transform�̊ȈՃA�N�Z�X
	Com_Transform* p_mTransform;

public:
	// �R���X�g���N�^
	GameObject(const char* _name);
	GameObject(std::string _name);
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject() {};

	// �Q�[���I�u�W�F�N�g�����ۂɎ���public�֐�
	// ����������
	virtual void Init();

	// �J�n����
	virtual void Start();

	// �X�V����
	virtual void Update();

	// �`��O����
	virtual void PreDraw();

	// �`�揈��
	virtual void Draw();

	// �Փˎ�����
	virtual void OnCollisionEnter(GameObject* _obj);

	// �Փ˒�����
	virtual void OnCollisionStay(GameObject* _obj);

	// �Փˌ㏈��
	virtual void OnCollisionExit(GameObject* _obj);

	// �������
	virtual void Uninit();

	// �A�N�e�B�u�̃Z�b�^�[
	void SetActive(bool _val) { bActive = _val; }
	// �A�N�e�B�u�̃Q�b�^�[
	bool GetActive() { return bActive; }

	// �R���|�[�l���g�p�̃N���X�e���v���[�g
	template<typename T>
	T* GetComponent()
	{
		for (auto a : p_mComponentList)
		{
			// �^�������Ȃ�return
			if (typeid(*a) == typeid(T))
			{
				return static_cast<T*>(a);
			}
		}
		return nullptr;
	};

	// �R���|�[�l���g�̎擾
	Component* GetComponent(const type_info& type);

	// �R���|�[�l���g�̒ǉ�
	void AddComponent(Component* pCom);

	void AddChild(GameObject* _obj)
	{
		p_mChildren.push_back(_obj);
		_obj->p_mParent = this;
	};

	bool Destroy()
	{
		if (bDestroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	Wint GetID()
	{
		return mID;
	}

	void DrawBase(DirectX::SimpleMath::Matrix ParentMatrix);

	static void SetScene(Scene* _scene)
	{
		s_p_mScene = _scene;
	}
	static Scene* GetScene()
	{
		return s_p_mScene;
	}

	void SetPosition(float _x, float _y, float _z);
	void SetScale(float _x, float _y, float _z);
	void SetRotation(float _x, float _y, float _z);
	void Translate(float _x, float _y, float _z);
	void Translate(DirectX::SimpleMath::Vector3 _val);
	void Rotate(float _x, float _y, float _z);
	void Rotate(DirectX::SimpleMath::Vector3 _val);
};
