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

// レイヤー登録概要 //

// 0 カメラなど優先順位最高

// 1 プレイヤーや敵などのMovableで当たり判定を持つもの

// 2 固定オブジェクトで当たり判定を持つもの

// 3 その他オブジェクト

// 4 UIスプライト当たり判定のないもの

// 5  UIスプライトMovable当たり判定のあるもの

// 6 UIスプライト固定当たり判定のあるもの

// 7 UIスプライトその他

class Scene
{
protected:
	std::array<Objectlist, LayerNum> mList;
	int ListSize = 0;

	bool bLoadNextScene = false;

protected:
	ObjectManager mKeyObjectList;
	// シーンで当たり判定を行うか
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
	// ループ開始前処理(BGMオンなど)
	virtual void Start() {};
	virtual void Update() {};
	virtual void PreDraw() {};
	virtual void Draw() {};
	virtual void Uninit() {};

	// 初期化のベース処理
	void InitBase()
	{
		// 自身の初期化処理を呼ぶ
		Init();

		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Init();
			}
		}
	}

	// 開始のベース処理
	void StartBase()
	{
		// ゲームオブジェクトのターゲットシーンの設定
		GameObject::SetScene(this);

		// オブジェクトリストの数だけ回す
		for (auto& List : mList)
		{
			// リストの中身の数分解放処理
			for (auto& obj : List)
			{
				obj->Start();
			}
		}

		Start();
	}

	// 開放のベース処理
	void UninitBase()
	{
		// オブジェクトリストの数だけ回す
		for (auto& List : mList)
		{
			// リストの中身の数分解放処理
			for (auto& obj : List)
			{
				obj->Uninit();
				delete obj;
			}
			List.clear();
		}
		// 自身の解放処理を呼ぶ
		Uninit();
	}

	// 更新のベース処理
	void UpdateBase()
	{
		// 更新処理(List仕様)
		for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Update();
			}
			// ラムダ式による破壊チェック
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

		// 更新処理(vector仕様)
		/*for (auto& List : mList)
		{
			for (auto& obj : List)
			{
				obj->Update();
			}
		}*/

		// デストロイチェック(vector仕様)
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

		// 自身の更新処理を呼ぶ
		Update();

		if (bCheckCol == true)
		{
			CollisionUpdate();
		}
	}

	// 描画前処理のベース処理
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

	// 描画のベース処理
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

		// 自身のDraw処理を呼ぶ
		Draw();
	}

	// 通常のオブジェクト登録
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
	// 格納配列の決定
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
	// キーオブジェクトとして登録

	// unordered_mapに登録(取得までの処理は速いがfor文には適していない)
	void AddKeyObject(GameObject* _obj)
	{
		AddGameObject(_obj);
		mKeyObjectList.AddGameObject(_obj);
	}
	void AddKeyObject(GameObject* _obj, int Layer)
	{
		// 引数のレイヤーにオブジェクトの名前として登録
		mList[Layer].emplace_back(_obj);
		mKeyObjectList.AddGameObject(_obj);
	}
	// 登録オブジェクトの取得(GetGameObjectよりも高速)
	GameObject* GetKeyObject(const char* _name)
	{
		return mKeyObjectList.GetGameObject(_name);
	}
	GameObject* GetKeyObject(std::string _name)
	{
		return mKeyObjectList.GetGameObject(_name);
	}

	// 通常のオブジェクト取得(for文で回している分処理は遅くなる)
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