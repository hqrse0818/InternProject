#include "CustomMath.h"

float Math::GetRoot(float num)
{
    return sqrt(num);
}

float Math::GetDot(DirectX::SimpleMath::Vector3 _valueA, DirectX::SimpleMath::Vector3 _valueB)
{
    float result = (_valueA.x * _valueB.x) + (_valueA.y * _valueB.y) + (_valueA.z * _valueB.z);
    return result;
}

DirectX::SimpleMath::Vector3 Math::GetCross(DirectX::SimpleMath::Vector3 _valueA, DirectX::SimpleMath::Vector3 _valueB)
{
    Vector3 result;
    result.x = (_valueA.y * _valueB.z) - (_valueA.z * _valueB.y);
    result.y = (_valueA.z * _valueB.x) - (_valueA.x * _valueB.z);
    result.z = (_valueA.x * _valueB.y) - (_valueA.y * _valueB.x);

    return result;
}

float Math::GetDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End)
{
    Vector3 Sub = _End - _Start;

    float retx = GetPower(Sub.x, 2);
    float rety = GetPower(Sub.y, 2);
    float retz = GetPower(Sub.z, 2);

    float distance = GetRoot(retx + rety + retz);
    distance = Abs(distance);
    return distance;
}

float Math::GetDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End)
{
    Vector2 Sub = _End - _Start;
    float retx = GetPower(Sub.x, 2);
    float rety = GetPower(Sub.y, 2);

    // sqrt‚É‚·‚é
    float distance = GetRoot(retx + rety);
    distance = Abs(distance);

    return distance;
}

float Math::GetDoubleDistance(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End)
{
    Vector3 Sub = _End - _Start;

    float retx = GetPower(Sub.x, 2);
    float rety = GetPower(Sub.y, 2);
    float retz = GetPower(Sub.z, 2);

    return retx + rety + retz;
}

float Math::GetDoubleDistance(DirectX::SimpleMath::Vector2 _Start, DirectX::SimpleMath::Vector2 _End)
{
    Vector2 Sub = _End - _Start;
    float retx = GetPower(Sub.x, 2);
    float rety = GetPower(Sub.y, 2);

    return retx + rety;
}

float Math::GetLength(DirectX::SimpleMath::Vector3 _val)
{
    float result = GetDistance(Vector3(0, 0, 0), _val);

    return result;
}

float Math::GetDoubleLength(DirectX::SimpleMath::Vector3 _val)
{
    float result = GetDoubleDistance(Vector3(0, 0, 0), _val);

    return result;
}

DirectX::SimpleMath::Vector3 Math::Normalize(DirectX::SimpleMath::Vector3 _val)
{
    float len = GetLength(_val);

    Vector3 result;
    result.x = _val.x / len;
    result.y = _val.y / len;
    result.z = _val.z / len;

    return result;
}

DirectX::SimpleMath::Matrix Math::CalcMatrixFromVector(DirectX::SimpleMath::Vector3 _CurrentForward, DirectX::SimpleMath::Vector3 _TargetForward)
{
    // –Ú“I‚Ì³–ÊƒxƒNƒgƒ‹‚ð³‹K‰»
    _TargetForward = Normalize(_TargetForward);

    // ‰ñ“]—Ê‚ðŒvŽZ
    float dot = GetDot(_CurrentForward, _TargetForward);
    float angle = acos(dot);

    // ‰ñ“]Ž²‚ðŒvŽZ
    Vector3 rotAxis = GetCross(_CurrentForward, _TargetForward);

    // ‰ñ“]s—ñ‚ðŒvŽZ
    Matrix ret;
    ret.CreateFromAxisAngle(rotAxis, angle);

    return ret;
}

DirectX::SimpleMath::Vector3 Math::GetVector(DirectX::SimpleMath::Vector3 _Start, DirectX::SimpleMath::Vector3 _End)
{
    Vector3 result = _End - _Start;
   
    return result;
}

float Math::GetPower(float _val, int _num)
{
    float result = 1.0f;
    if (_num >= 0)
    {
        for (int i = 0; i < _num; i++)
        {
            result = result * _val;
        }
    }
    else
    {
        for (int i = 0; i < _num; i++)
        {
            result = result / _val;
        }
    }
    return result;
}

float Math::Abs(float _val)
{
    if (_val < 0.0f)
    {
        _val *= -1;
    }
    return _val;
}

float Math::Clamp(float _val, float _min, float _max)
{
    if (_val > _max)
    {
        return _max;
    }
    else if (_val < _min)
    {
        return _min;
    }
    return _val;
}
