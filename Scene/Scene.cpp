#include "Scene.h"
#include "../System/Collision.h"
#include "../InternCodeAdachi/InternCollision.h"


void Scene::CollisionUpdate()
{
	mThreadA = std::thread([this]() { CollisionUpdate3D(); });
	mThreadB = std::thread([this]() { CollisionUpdate2D(); });

	mThreadA.join();
	mThreadB.join();
}

void Scene::CollisionUpdate3D()
{
	// Movableオブジェクト同士の衝突検知
	if (mList[1].size() > 0)
	{
		for (auto me = mList[1].begin(); me != mList[1].end(); me++)
		{
			GameObject* Objecti = *me;
			if (Objecti->GetActive())
			{
				for (auto other = std::next(me); other != mList[1].end(); other++)
				{
					GameObject* Objectj = *other;
					if (Objectj->GetActive())
					{
						bool ret = false;
						ret = CollisionCheck(Objecti, Objectj);
						// 当たった
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでも当たっている
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// 前のフレームで当たっていない
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// 当たってない
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでは当たっていた
								if (n == Objectj)
								{
									Objecti->OnCollisionExit(Objectj);
									Objectj->OnCollisionExit(Objecti);
								}
							}
						}

						for (auto obj : Objecti->p_mChildren)
						{
							ret = CollisionCheck(obj, Objectj);
							if (ret == true)
							{
								bool check = false;
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでも当たっている
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
										break;
									}
								}
								// 前のフレームで当たっていない
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// 当たってない
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでは当たっていた
									if (n == Objectj)
									{
										obj->OnCollisionExit(Objectj);
										Objectj->OnCollisionExit(obj);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	

	// MovableオブジェクトとStaticオブジェクトの衝突検知
	if (mList[1].size() > 0 && mList[2].size() > 0)
	{
		for (auto me = mList[1].begin(); me != mList[1].end(); me++)
		{
			GameObject* Objecti = *me;
			if (Objecti->GetActive())
			{
				for (auto other = mList[2].begin(); other != mList[2].end(); other++)
				{
					GameObject* Objectj = *other;
					if (Objectj->GetActive())
					{
						bool ret = false;
						ret = CollisionCheck(Objecti, Objectj);
						// 当たった
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでも当たっている
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// 前のフレームで当たっていない
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// 当たってない
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでは当たっていた
								if (n == Objectj)
								{
									Objecti->OnCollisionExit(Objectj);
									Objectj->OnCollisionExit(Objecti);
								}
							}
						}
						for (auto obj : Objecti->p_mChildren)
						{
							ret = CollisionCheck(obj, Objectj);
							if (ret == true)
							{
								bool check = false;
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでも当たっている
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// 前のフレームで当たっていない
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// 当たってない
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでは当たっていた
									if (n == Objectj)
									{
										obj->OnCollisionExit(Objectj);
										Objectj->OnCollisionExit(obj);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
}

void Scene::CollisionUpdate2D()
{
	if (mList[5].size() > 0)
	{
		for (auto me = mList[5].begin(); me != mList[5].end(); me++)
		{
			assert(*me);
			GameObject* Objecti = *me;
			if (Objecti->GetActive())
			{
				for (auto other = std::next(me); other != mList[5].end(); other++)
				{
					GameObject* Objectj = *other;
					if (Objectj->GetActive())
					{
						bool ret = false;
						ret = CollisionCheck(Objecti, Objectj);

						// 当たった
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでも当たっている
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// 前のフレームで当たっていない
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// 当たってない
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでは当たっていた
								if (n == Objectj)
								{
									Objecti->OnCollisionExit(Objectj);
									Objectj->OnCollisionExit(Objecti);
								}
							}
						}

						for (auto obj : Objecti->p_mChildren)
						{
							ret = CollisionCheck(obj, Objectj);
							if (ret == true)
							{
								bool check = false;
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでも当たっている
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// 前のフレームで当たっていない
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// 当たってない
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでは当たっていた
									if (n == Objectj)
									{
										obj->OnCollisionExit(Objectj);
										Objectj->OnCollisionExit(obj);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	if (mList[5].size() > 0 && mList[6].size() > 0)
	{
		for (auto me = mList[5].begin(); me != mList[5].end(); me++)
		{
			GameObject* Objecti = *me;
			if (Objecti->GetActive())
			{
				for (auto other = mList[6].begin(); other != mList[6].end(); other++)
				{
					GameObject* Objectj = *other;
					if (Objectj->GetActive())
					{
						bool ret = false;
						ret = CollisionCheck(Objecti, Objectj);

						// 当たった
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでも当たっている
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// 前のフレームで当たっていない
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// 当たってない
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// 前のフレームでは当たっていた
								if (n == Objectj)
								{
									Objecti->OnCollisionExit(Objectj);
									Objectj->OnCollisionExit(Objecti);
								}
							}
						}

						for (auto obj : Objecti->p_mChildren)
						{
							ret = CollisionCheck(obj, Objectj);
							if (ret == true)
							{
								bool check = false;
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでも当たっている
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// 前のフレームで当たっていない
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// 当たってない
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// 前のフレームでは当たっていた
									if (n == Objectj)
									{
										obj->OnCollisionExit(Objectj);
										Objectj->OnCollisionExit(obj);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
}

// 当たり判定を増やす場合ここを増やす
bool Scene::CollisionCheck(GameObject* objA, GameObject* objB)
{
	// objAがBox
	if (objA->mColType == Collider::ColliderForm::Box)
	{
		AABB Box1 = objA->GetComponent<Com_BoxCollider>()->GetAABB();
		// objBがBoxCollider
		if (objB->mColType == Collider::ColliderForm::Box)
		{
			AABB Box2 = objB->GetComponent<Com_BoxCollider>()->GetAABB();
			// 衝突判定
			return Collision::AABB2AABB(Box1, Box2);
		}
		// objBがSphere
		else if (objB->mColType == Collider::ColliderForm::Sphere)
		{
			Sphere Sphere1 = objB->GetComponent<Com_SphereCollider>()->GetSphere();
			// 衝突判定
			return CollisionBox2Sphere(Box1, Sphere1);
		}
	}
	// objAがCylinder
	else if (objA->mColType == Collider::ColliderForm::Cylinder)
	{
		Cylinder Cylinder1 = objA->GetComponent<Com_CylinderCollider>()->GetCylinder();
		// objBがCylinder
		if (objB->mColType == Collider::ColliderForm::Cylinder)
		{
			Cylinder Cylinder2 = objB->GetComponent<Com_CylinderCollider>()->GetCylinder();
			// 衝突判定
			return Collision::Cylinder2Cylinder(Cylinder1, Cylinder2);
		}
	}
	// objAがSphere
	else if (objA->mColType == Collider::ColliderForm::Sphere)
	{
		Sphere sphere1 = objA->GetComponent<Com_SphereCollider>()->GetSphere();
		// objBがSphere;
		if (objB->mColType == Collider::ColliderForm::Sphere)
		{
			Sphere sphere2 = objB->GetComponent<Com_SphereCollider>()->GetSphere();
			// 衝突判定
			return Collision::Sphere2Sphere(sphere1, sphere2);
		}
		else if (objB->mColType == Collider::ColliderForm::Box)
		{
			AABB Box1 = objB->GetComponent<Com_BoxCollider>()->GetAABB();

			// 衝突判定
			return CollisionBox2Sphere(Box1, sphere1);
		}
	}
	// objAがBox2D
	else if (objA->mColType == Collider::ColliderForm::Box2D)
	{
		// objBがBox2D
		Box2D Box1 = objA->GetComponent<Com_BoxCollider2D>()->GetBox();
		if (objB->mColType == Collider::ColliderForm::Box2D)
		{
			Box2D Box2 = objB->GetComponent<Com_BoxCollider2D>()->GetBox();
			return Collision::Box2D2Box2D(Box1, Box2);
		}
		// objBがCirecle
		else if (objB->mColType == Collider::ColliderForm::Circle)
		{
			Circle Cir = objB->GetComponent<Com_CircleCollider>()->GetCircle();
			return Collision::Box2D2Circle(Box1, Cir);
		}
	}
	// objAがCircle
	else if (objA->mColType == Collider::ColliderForm::Circle)
	{
		// objBがCircle
		Circle Circle1 = objA->GetComponent<Com_CircleCollider>()->GetCircle();
		if (objB->mColType == Collider::ColliderForm::Box2D)
		{
			Box2D Box = objB->GetComponent<Com_BoxCollider2D>()->GetBox();
			return Collision::Box2D2Circle(Box, Circle1);
		}
		// objBがBox2D
		else if (objB->mColType == Collider::ColliderForm::Circle)
		{
			Circle Circle2 = objB->GetComponent<Com_CircleCollider>()->GetCircle();
			return Collision::Circle2Circle(Circle1, Circle2);
		}
	}
	return false;
}

void Scene::ObjectPreDraw()
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

void Scene::ObjectDraw()
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
