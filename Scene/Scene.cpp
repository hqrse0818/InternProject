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
	// Movable�I�u�W�F�N�g���m�̏Փˌ��m
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
						// ��������
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł��������Ă���
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// �O�̃t���[���œ������Ă��Ȃ�
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// �������ĂȂ�
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł͓������Ă���
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
									// �O�̃t���[���ł��������Ă���
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
										break;
									}
								}
								// �O�̃t���[���œ������Ă��Ȃ�
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// �������ĂȂ�
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// �O�̃t���[���ł͓������Ă���
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
	

	// Movable�I�u�W�F�N�g��Static�I�u�W�F�N�g�̏Փˌ��m
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
						// ��������
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł��������Ă���
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// �O�̃t���[���œ������Ă��Ȃ�
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// �������ĂȂ�
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł͓������Ă���
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
									// �O�̃t���[���ł��������Ă���
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// �O�̃t���[���œ������Ă��Ȃ�
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// �������ĂȂ�
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// �O�̃t���[���ł͓������Ă���
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

						// ��������
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł��������Ă���
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// �O�̃t���[���œ������Ă��Ȃ�
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// �������ĂȂ�
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł͓������Ă���
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
									// �O�̃t���[���ł��������Ă���
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// �O�̃t���[���œ������Ă��Ȃ�
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// �������ĂȂ�
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// �O�̃t���[���ł͓������Ă���
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

						// ��������
						if (ret == true)
						{
							bool check = false;
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł��������Ă���
								if (n == Objectj)
								{
									Objecti->OnCollisionStay(Objectj);
									Objectj->OnCollisionStay(Objecti);
									check = true;
								}
							}
							// �O�̃t���[���œ������Ă��Ȃ�
							if (!check)
							{
								Objecti->OnCollisionEnter(Objectj);
								Objectj->OnCollisionEnter(Objecti);
							}

							Objecti->mCollisionvector.emplace_back(Objectj);
							Objectj->mCollisionvector.emplace_back(Objecti);
						}
						// �������ĂȂ�
						else
						{
							for (auto& n : Objecti->mLastCollisionvector)
							{
								// �O�̃t���[���ł͓������Ă���
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
									// �O�̃t���[���ł��������Ă���
									if (n == Objectj)
									{
										obj->OnCollisionStay(Objectj);
										Objectj->OnCollisionStay(obj);
										check = true;
									}
								}
								// �O�̃t���[���œ������Ă��Ȃ�
								if (!check)
								{
									obj->OnCollisionEnter(Objectj);
									Objectj->OnCollisionEnter(obj);
								}

								obj->mCollisionvector.emplace_back(Objectj);
								Objectj->mCollisionvector.emplace_back(obj);
							}
							// �������ĂȂ�
							else
							{
								for (auto& n : Objecti->mLastCollisionvector)
								{
									// �O�̃t���[���ł͓������Ă���
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

// �����蔻��𑝂₷�ꍇ�����𑝂₷
bool Scene::CollisionCheck(GameObject* objA, GameObject* objB)
{
	// objA��Box
	if (objA->mColType == Collider::ColliderForm::Box)
	{
		AABB Box1 = objA->GetComponent<Com_BoxCollider>()->GetAABB();
		// objB��BoxCollider
		if (objB->mColType == Collider::ColliderForm::Box)
		{
			AABB Box2 = objB->GetComponent<Com_BoxCollider>()->GetAABB();
			// �Փ˔���
			return Collision::AABB2AABB(Box1, Box2);
		}
		// objB��Sphere
		else if (objB->mColType == Collider::ColliderForm::Sphere)
		{
			Sphere Sphere1 = objB->GetComponent<Com_SphereCollider>()->GetSphere();
			// �Փ˔���
			return CollisionBox2Sphere(Box1, Sphere1);
		}
	}
	// objA��Cylinder
	else if (objA->mColType == Collider::ColliderForm::Cylinder)
	{
		Cylinder Cylinder1 = objA->GetComponent<Com_CylinderCollider>()->GetCylinder();
		// objB��Cylinder
		if (objB->mColType == Collider::ColliderForm::Cylinder)
		{
			Cylinder Cylinder2 = objB->GetComponent<Com_CylinderCollider>()->GetCylinder();
			// �Փ˔���
			return Collision::Cylinder2Cylinder(Cylinder1, Cylinder2);
		}
	}
	// objA��Sphere
	else if (objA->mColType == Collider::ColliderForm::Sphere)
	{
		Sphere sphere1 = objA->GetComponent<Com_SphereCollider>()->GetSphere();
		// objB��Sphere;
		if (objB->mColType == Collider::ColliderForm::Sphere)
		{
			Sphere sphere2 = objB->GetComponent<Com_SphereCollider>()->GetSphere();
			// �Փ˔���
			return Collision::Sphere2Sphere(sphere1, sphere2);
		}
		else if (objB->mColType == Collider::ColliderForm::Box)
		{
			AABB Box1 = objB->GetComponent<Com_BoxCollider>()->GetAABB();

			// �Փ˔���
			return CollisionBox2Sphere(Box1, sphere1);
		}
	}
	// objA��Box2D
	else if (objA->mColType == Collider::ColliderForm::Box2D)
	{
		// objB��Box2D
		Box2D Box1 = objA->GetComponent<Com_BoxCollider2D>()->GetBox();
		if (objB->mColType == Collider::ColliderForm::Box2D)
		{
			Box2D Box2 = objB->GetComponent<Com_BoxCollider2D>()->GetBox();
			return Collision::Box2D2Box2D(Box1, Box2);
		}
		// objB��Cirecle
		else if (objB->mColType == Collider::ColliderForm::Circle)
		{
			Circle Cir = objB->GetComponent<Com_CircleCollider>()->GetCircle();
			return Collision::Box2D2Circle(Box1, Cir);
		}
	}
	// objA��Circle
	else if (objA->mColType == Collider::ColliderForm::Circle)
	{
		// objB��Circle
		Circle Circle1 = objA->GetComponent<Com_CircleCollider>()->GetCircle();
		if (objB->mColType == Collider::ColliderForm::Box2D)
		{
			Box2D Box = objB->GetComponent<Com_BoxCollider2D>()->GetBox();
			return Collision::Box2D2Circle(Box, Circle1);
		}
		// objB��Box2D
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

	// ���g��Draw�������Ă�
	Draw();
}
