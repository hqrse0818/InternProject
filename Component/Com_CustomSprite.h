#pragma once
#include "Com_Sprite.h"

// ���S�ƂȂ�ʒu���J�X�^���\
class Com_CustomSprite :
    public Com_Sprite
{
public:
    enum class CustomType
    {
        Center, CenterTop, CenetrBottom, Left, LeftTop, LeftBottom,Right, RightTop, RightBottom,
    };

    CustomType mType = CustomType::Center;

public:

    void Init()override;
    void Draw()override;
    void Create()override;
};

