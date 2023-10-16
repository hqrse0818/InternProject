#pragma once
#include "../Component/Com_3DSprite.h"
#include "../DirectX//Shader.h"

class Com_Shadow :
    public Com_3DSprite
{
private:
    DirectX::SimpleMath::Vector2 mSize = DirectX::SimpleMath::Vector2(1.0f, 1.0f);
    DirectX::SimpleMath::Vector2 mOriginalSize = DirectX::SimpleMath::Vector2(1.0f, 1.0f);
    VERTEX_3D vertex[4];
    float fHeight = 0.05f;

    DirectX::SimpleMath::Vector3 mPosition = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
public:
    Com_Shadow();
    

    void Init();
    void Update();
    void Draw();

    void SetSize(float _x, float _y)
    {
        mOriginalSize.x = _x;
        mOriginalSize.y = _y;
    }

    void SetShadowHeight(float _height)
    {
        fHeight = _height;
    }

};

