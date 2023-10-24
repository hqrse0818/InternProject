#pragma once
#include "../InternCode.Kizuki/OBJ_Number.h"
class OBJ_DisplayScore :
    public GameObject
{
private:
    OBJ_Number* Nums[6];
    ShaderResourceView* p_mSRV{};
    GameObject* pScoreFont{};
public:
    OBJ_DisplayScore();
    OBJ_DisplayScore(const char* _name);
    OBJ_DisplayScore(const char* _name, const char* _FileName);

    void Init();
    void Start();
    void Update();
    void Uninit();

    void SetDisplay(bool _val)
    {
        pScoreFont->SetActive(_val);

        for (int i = 0; i < 6; i++)
        {
            Nums[i]->SetActive(_val);
        }
    }
};

