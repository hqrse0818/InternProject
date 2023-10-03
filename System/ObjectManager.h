#pragma once
#include "../GameObject/GameObject.h"
#include <string>


class ObjectManager
{
private:
	Objectmap mObjectmap;

public:
	void AddGameObject(GameObject* _Object)
	{
		// �����̃��C���[�ɃI�u�W�F�N�g�̖��O�Ƃ��ēo�^
		
		// ���O������Ă���ꍇ�̏���
		if (mObjectmap.count(_Object->sObjectName) > 0)
		{
			// ���݂̃I�u�W�F�N�g���̖����ɃI�u�W�F�N�g��ID��t�^����
			std::string str = std::to_string(_Object->GetID().first);
			_Object->sObjectName = _Object->sObjectName + "_";
			_Object->sObjectName = _Object->sObjectName + str;
			str = std::to_string(_Object->GetID().second);
			_Object->sObjectName = _Object->sObjectName + "_";
			_Object->sObjectName = _Object->sObjectName + str;
			return;
		}
		mObjectmap[_Object->sObjectName] = _Object;
	}

	GameObject* GetGameObject(std::string _name)
	{
		if (mObjectmap.count(_name) > 0)
		{
			return mObjectmap[_name];
		}
		return nullptr;
	}

	GameObject* GetGameObject(const char* _name)
	{
		if (mObjectmap.count(_name) > 0)
		{
			return mObjectmap[_name];
		}
		return nullptr;
	}
};

