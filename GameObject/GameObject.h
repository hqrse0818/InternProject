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

// オブジェクトIDのsecondの最大数
#define ObjectIDSecondMax 1000

struct Wint
{
	unsigned int first;
	unsigned int second;
};

class GameObject
{
protected:
	// ゲームオブジェクトが実際に持つprotected変数
	// 生成数
	static Wint s_mAllNum;

	// オブジェクトID
	Wint mID;

	// アクティベーション
	bool bActive = true;

	static Scene* s_p_mScene;

	// コンポーネントリスト
	Componentlist p_mComponentList;

public:
	// 子オブジェクトリスト
	Objectlist p_mChildren;

	// 破壊予約
	bool bDestroy = false;
	Collider::ColliderForm mColType = Collider::ColliderForm::None;

	// オブジェクトのヒットリスト
	Objectvector mCollisionvector;
	Objectvector mLastCollisionvector;

	// オブジェクト名(デバッグ用)
	std::string sObjectName;
	// オブジェクトのタグ
	std::string sTag;

	std::string sCollisionTag;

	// 親オブジェクト
	GameObject* p_mParent;

	// Com_Transformの簡易アクセス
	Com_Transform* p_mTransform;

public:
	// コンストラクタ
	GameObject(const char* _name);
	GameObject(std::string _name);
	GameObject();
	// デストラクタ
	virtual ~GameObject() {};

	// ゲームオブジェクトが実際に持つpublic関数
	// 初期化処理
	virtual void Init();

	// 開始処理
	virtual void Start();

	// 更新処理
	virtual void Update();

	// 描画前処理
	virtual void PreDraw();

	// 描画処理
	virtual void Draw();

	// 衝突時処理
	virtual void OnCollisionEnter(GameObject* _obj);

	// 衝突中処理
	virtual void OnCollisionStay(GameObject* _obj);

	// 衝突後処理
	virtual void OnCollisionExit(GameObject* _obj);

	// 解放処理
	virtual void Uninit();

	// アクティブのセッター
	void SetActive(bool _val) { bActive = _val; }
	// アクティブのゲッター
	bool GetActive() { return bActive; }

	// コンポーネント用のクラステンプレート
	template<typename T>
	T* GetComponent()
	{
		for (auto a : p_mComponentList)
		{
			// 型が同じならreturn
			if (typeid(*a) == typeid(T))
			{
				return static_cast<T*>(a);
			}
		}
		return nullptr;
	};

	// コンポーネントの取得
	Component* GetComponent(const type_info& type);

	// コンポーネントの追加
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
};
