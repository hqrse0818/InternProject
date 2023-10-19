#pragma once
#include "../GameObject/GameObject.h"
#include "OBJ_Ice.h"

#include <list>

class OBJ_IceManager :
    public GameObject
{
private:
    static std::list<OBJ_Ice*> IceList;

    // 氷の揺れ時間
    static float fShakeTime;
    // 氷の揺れの強さ
    static float fShakePower;
    // 氷のコライダーの中心
    static DirectX::SimpleMath::Vector3 mColCenter;
    // 氷のコライダーのサイズ
    static DirectX::SimpleMath::Vector3 mColSize;
    // 氷のオブジェクトスケール
    static DirectX::SimpleMath::Vector3 mIceScale;

public:
    OBJ_IceManager();
    OBJ_IceManager(const char* _name);
    OBJ_IceManager(const char* _name, const char* _FileName);

    static void Uninit();

    static std::list<OBJ_Ice*>GetIceList()
    {
        return IceList;
    }

    static std::vector<OBJ_Ice*>GetIceVector()
    {
        std::vector<OBJ_Ice*> ices;
        for (auto obj : IceList)
        {
            if (obj != nullptr)
            {
                ices.emplace_back(obj);
            }
        }
        return ices;
    }

    static float GetShakeTime()
    {
        return fShakeTime;
    }

    static float GetShakePower()
    {
        return fShakePower;
    }

    static DirectX::SimpleMath::Vector3 GetColCenter()
    {
        return mColCenter;
    }

    static DirectX::SimpleMath::Vector3 GetColSize()
    {
        return mColSize;
    }

    static DirectX::SimpleMath::Vector3 GetScale()
    {
        return mIceScale;
    }

    static void RegisterIce(OBJ_Ice* _ice)
    {
        IceList.emplace_back(_ice);
    }
};
