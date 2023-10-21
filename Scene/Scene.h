#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentHeader.h"
#include "../System/ObjectManager.h"
#include "../System/Input.h"
#include "../System/TextureCreate.h"
#include <unordered_map>
#include <array>
#include <string>
#include <thread>
#include <iostream>
#include "../Debug.h"

#define LayerNum 8

// ���C���[�o�^�T�v //

// 0 �J�����ȂǗD�揇�ʍō�

// 1 �v���C���[��G�Ȃǂ�Movable�œ����蔻���������

// 2 �Œ�I�u�W�F�N�g�œ����蔻���������

// 3 ���̑��I�u�W�F�N�g

// 4 UI�X�v���C�g�����蔻��̂Ȃ�����

// 5  UI�X�v���C�gMovable�����蔻��̂������

// 6 UI�X�v���C�g�Œ蓖���蔻��̂������

// 7 UI�X�v���C�g���̑�

class Scene
{
protected:
	std::array<Objectlist, LayerNum> mList;
	int ListSize = 0;

	bool bLoadNextScene = false;

protected:
	ObjectManager mKeyObjectList;
	// �V�[���œ����蔻����s����
	bool bCheckCol = false;

	virtual void CollisionUpdate();
	virtual void CollisionUpdate3D();
	virtual void CollisionUpdate2D();
	bool CollisionCheck(GameObject* objA, GameObject* objB);

	std::thread mThreadA;
	std::thread mThreadB;
public:
	Scene()
	{
		for (auto& List : mList)
		{
			List.clear();
		}
	};
	virtual ~Scene() {};
	virtual void Init() {};
	// ���[�v�J�n�O����(BGM�I���Ȃ�)
	virtual void Start() {};
	virtual void Update() {};
	virtual void PreDraw() {};
	virtual void Draw() {};
	virtual void Uninit() {};

	// �������̃x�[�X����
	void InitBase()
	{
		// ���g�̏������������Ă�
		Init();

		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Init();
			}
		}
	}

	// �J�n�̃x�[�X����
	void StartBase()
	{
		// �Q�[���I�u�W�F�N�g�̃^�[�Q�b�g�V�[���̐ݒ�
		GameObject::SetScene(this);

		// �I�u�W�F�N�g���X�g�̐�������
		for (auto& List : mList)
		{
			// ���X�g�̒��g�̐����������
			for (auto& obj : List)
			{
				obj->Start();
			}
		}

		Start();
	}

	// �J���̃x�[�X����
	void UninitBase()
	{
		// �I�u�W�F�N�g���X�g�̐�������
		for (auto& List : mList)
		{
			// ���X�g�̒��g�̐����������
			for (auto& obj : List)
			{
				obj->Uninit();
				delete obj;
			}
			List.clear();
		}
		// ���g�̉���������Ă�
		Uninit();
	}

	// �X�V�̃x�[�X����
	void UpdateBase()
	{
		// �X�V����(List�d�l)
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Update();
			}
			// �����_���ɂ��j��`�F�b�N
			List.remove_if([](GameObject* object) 
			{
				bool des = object->Destroy(); 
				if (des)
				{
					object = nullptr;
				}
				return des;
			});
		}

		// �X�V����(vector�d�l)
		/*for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Update();
			}
		}*/

		// �f�X�g���C�`�F�b�N(vector�d�l)
		/*for (auto& List : mList)
		{
			for (auto it = List.begin(); it != List.end();)
			{
				if ((*it)->bDestroy)
				{
					(*it)->Uninit();
					delete* it;
					it = List.erase(it);
				}
				else
				{
					it++;
				}
			}
		}*/

		// ���g�̍X�V�������Ă�
		Update();

		if (bCheckCol == true)
		{
			CollisionUpdate();
		}
	}

	// �`��O�����̃x�[�X����
	void PreDrawBase()
	{
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->PreDraw();
			}
		}

		PreDraw();
	}

	// �`��̃x�[�X����
	void DrawBase()
	{
		DirectX::SimpleMath::Matrix matrix;
		matrix = DirectX::SimpleMath::Matrix::Identity;

		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->DrawBase(matrix);
			}
		}

		// ���g��Draw�������Ă�
		Draw();
	}

	// �ʏ�̃I�u�W�F�N�g�o�^
	void AddGameObject(GameObject* _obj)
	{
		int layer = LayerCheck(_obj);

		mList[layer].emplace_back(_obj);

		DEBUG_LOG(layer << " : " << mList[layer].size());
	}
	void AddGameObject(GameObject* _obj, int Layer)
	{
		mList[Layer].emplace_back(_obj);
	}
	// �i�[�z��̌���
	int LayerCheck(GameObject* _obj)
	{
		switch (_obj->mColType)
		{
		case Collider::ColliderForm::Box:
			if (_obj->GetComponent<Com_BoxCollider>()->bMovable)
			{
				return 1;
			}
			else
			{
				return 2;
			}
			break;
		case Collider::ColliderForm::Sphere:
			if (_obj->GetComponent<Com_SphereCollider>()->bMovable)
			{
				return 1;
			}
			else
			{
				return 2;
			}
			break;
		case Collider::ColliderForm::Cylinder:
			if (_obj->GetComponent<Com_CylinderCollider>()->bMovable)
			{
				return 1;
			}
			else
			{
				return 2;
			}
			break;
		case Collider::ColliderForm::Box2D:
			if (_obj->GetComponent<Com_BoxCollider2D>()->bMovable)
			{
				return 5;
			}
			else
			{
				return 6;
			}
			break;
		case Collider::ColliderForm::Circle:
			if (_obj->GetComponent<Com_CircleCollider>()->bMovable)
			{
				return 5;
			}
			else
			{
				return 6;
			}
			break;

		default:
			if (_obj->GetComponent<Com_Sprite>() || _obj->GetComponent<Com_CustomSprite>())
			{
				return 4;
			}
			else
			{
				return 3;
			}
			break;
		}
	}
	// �L�[�I�u�W�F�N�g�Ƃ��ēo�^

	// unordered_map�ɓo�^(�擾�܂ł̏����͑�����for���ɂ͓K���Ă��Ȃ�)
	void AddKeyObject(GameObject* _obj)
	{
		AddGameObject(_obj);
		mKeyObjectList.AddGameObject(_obj);
	}
	void AddKeyObject(GameObject* _obj, int Layer)
	{
		// �����̃��C���[�ɃI�u�W�F�N�g�̖��O�Ƃ��ēo�^
		mList[Layer].emplace_back(_obj);
		mKeyObjectList.AddGameObject(_obj);
	}
	// �o�^�I�u�W�F�N�g�̎擾(GetGameObject��������)
	GameObject* GetKeyObject(const char* _name)
	{
		return mKeyObjectList.GetGameObject(_name);
	}
	GameObject* GetKeyObject(std::string _name)
	{
		return mKeyObjectList.GetGameObject(_name);
	}

	// �ʏ�̃I�u�W�F�N�g�擾(for���ŉ񂵂Ă��镪�����͒x���Ȃ�)
	GameObject* GetGameObject(const char* _name)
	{
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				if (obj->sObjectName == _name)
				{
					return obj;
				}
			}
		}
		return nullptr;
	}
	GameObject* GetGameObject(std::string _name)
	{
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				if (obj->sObjectName == _name)
				{
					return obj;
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> ret;
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				if (typeid(*obj) == typeid(T))
				{
					ret.push_back(static_cast<T*>(obj));
				}
			}
		}

		return ret;
	}

	template<typename T>
	std::vector<T*>GetGameObjects(int _layer)
	{
		std::vector<T*>ret;
		for (auto & obj : mList[_layer])
		{
			if (typeid(*obj) == typeid(T))
			{
				ret.push_back(static_cast<T*>(obj));
			}
		}
		return ret;
	}
};